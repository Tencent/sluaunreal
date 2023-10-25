// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#pragma once
#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"
#include "lfunc.h"
#include "lobject.h"
#include "lstate.h"
#include "SluaMicro.h"
#include "UObject/UnrealType.h"
#include "UObject/WeakObjectPtr.h"
#include "LuaWrapper.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaSet.h"

#ifndef SLUA_CPPINST
#define SLUA_CPPINST "__cppinst"
#endif 

// checkUD will report error if ud had been freed
#define CheckUD(Type,L,P) auto UD = LuaObject::checkUD<Type>(L,P);
// UD may be freed by Engine, so skip it in gc phase
#define CheckUDGC(Type,L,P) auto UD = LuaObject::checkUD<Type>(L,P,false); \
    if(!UD) return 0;

#define RegMetaMethodByName(L,NAME,METHOD) \
    lua_pushcfunction(L,METHOD); \
    lua_setfield(L,-2,NAME);

#define RegMetaMethod(L,METHOD) RegMetaMethodByName(L,#METHOD,METHOD)

#define NewUD(T, v, f) auto ud = lua_newuserdata(L, sizeof(UserData<T*>)); \
    if (!ud) luaL_error(L, "out of memory to new ud"); \
    auto udptr = reinterpret_cast< UserData<T*>* >(ud); \
    udptr->parent = nullptr; \
    udptr->ud = const_cast<T*>(v); \
    udptr->flag = f;

#define NewNetStructUD(T, v, f) auto ud = lua_newuserdata(L, proxy ? sizeof(NetStructUserData<T*>) : sizeof(UserData<T*>)); \
    if (!ud) luaL_error(L, "out of memory to new ud"); \
    auto udptr = reinterpret_cast< NetStructUserData<T*>* >(ud); \
    udptr->parent = nullptr; \
    udptr->ud = const_cast<T*>(v); \
    udptr->flag = f; \

#define CheckSelf(T) \
    auto udptr = reinterpret_cast<NetStructUserData<T*>*>(lua_touserdata(L, 1)); \
    if(!udptr) luaL_error(L, "self ptr missing"); \
    if (udptr->flag & UD_HADFREE) \
        luaL_error(L, #T" checkValue error, obj parent has been freed"); \
    auto self = udptr->ud

#define CheckSelfSafe(T) \
    auto udptr = reinterpret_cast<NetStructUserData<T*>*>(lua_touserdata(L, 1)); \
    if(!udptr) return 0; \
    if (udptr->flag & UD_HADFREE) return 0; \
    auto self = udptr->ud

#define IsRealOutParam(propflag) ((propflag&CPF_OutParm) && !(propflag&CPF_ConstParm) && !(propflag&CPF_BlueprintReadOnly))
#define IsReferenceParam(propflag, outerFunc) (((propflag & CPF_ReferenceParm) && !IsRealOutParam(propflag)) || \
    ((propflag & CPF_OutParm) && (outerFunc && (outerFunc->FunctionFlags & FUNC_Native) && !(propflag & CPF_ReturnParm))))

class ULatentDelegate;

namespace NS_SLUA {
    class LuaVar;
    class NewObjectRecorder;

    extern SLUA_UNREAL_API FString getPropertyFriendlyName(FProperty* prop);

    struct AutoStack {
        AutoStack(lua_State* l) {
            this->L = l;
            this->top = lua_gettop(L);
        }
        ~AutoStack() {
            lua_settop(this->L,this->top);
        }
        lua_State* L;
        int top;
    };

    struct SLUA_UNREAL_API LuaStruct : public FGCObject {
        uint8* buf;
        uint32 size;
        UScriptStruct* uss;

        struct FLuaNetSerializationProxy* proxy;
        uint16 luaReplicatedIndex;
            
        bool isRef;

        LuaStruct();
        ~LuaStruct();
        void Init(uint8* buf,uint32 size,UScriptStruct* uss,bool isRef);

        virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
        virtual FString GetReferencerName() const override
        {
            return "LuaStruct";
        }
#endif
    };

    DefTypeName(LuaStruct)

    #define UD_NOFLAG 0
    #define UD_AUTOGC 1 // flag userdata should call __gc and maintain by lua
    #define UD_HADFREE 1<<2 // flag userdata had been freed
    #define UD_SHAREDPTR 1<<3 // it's a TSharedPtr in userdata instead of raw pointer
    #define UD_SHAREDREF 1<<4 // it's a TSharedRef in userdata instead of raw pointer
    #define UD_THREADSAFEPTR 1<<5 // it's a TSharedptr with thread-safe mode in userdata instead of raw pointer
    #define UD_UOBJECT 1<<6 // flag it's an UObject
    #define UD_USTRUCT 1<<7 // flag it's an UStruct
    #define UD_WEAKUPTR 1<<8 // flag it's a weak UObject ptr
    #define UD_REFERENCE 1<<9
    #define UD_VALUETYPE 1<<10 // flag it's a valuetype, don't cache value by ptr
    #define UD_NETTYPE 1<<11 // flag it's a net replicate property

    struct UDBase {
        uint32 flag;
        void* parent;
    };

    // Memory layout of GenericUserData and UserData should be same
    struct GenericUserData : public UDBase {
        void* ud;
    };

    template<class T>
    struct UserData : public UDBase {
        static_assert(sizeof(T) == sizeof(void*), "Userdata type should size equal to sizeof(void*)");
        T ud; 
    };

    struct GenericNetStructUserData : public GenericUserData {
        struct FLuaNetSerializationProxy* proxy;
        uint16 luaReplicatedIndex;
    };

    template<class T>
    struct NetStructUserData : public UserData<T> {
        struct FLuaNetSerializationProxy* proxy;
        uint16 luaReplicatedIndex;
    };

    DefTypeName(LuaArray);
    DefTypeName(LuaMap);
    DefTypeName(LuaSet);

    template<typename T>
    struct LuaOwnedPtr {
        T* ptr;
        LuaOwnedPtr(T* p):ptr(p) {}
        T* operator->() const {
            return ptr;
        }
    };

    template<typename T,ESPMode mode>
    struct SharedRefUD {
    private:
        TSharedRef<T, mode> ref;
    public:
        typedef T type;
        SharedRefUD(const TSharedRef<T, mode>& other) :ref(other) {}
        
        T* get(lua_State *L) {
            return &ref.Get();
        }

        const int32 getSharedReferenceCount() {
            return ref.GetSharedReferenceCount();
        }
    };

    template<typename T, ESPMode mode>
    struct SharedPtrUD {
    private:
        TSharedPtr<T, mode> ptr;
    public:
        typedef T type;
        SharedPtrUD(const TSharedPtr<T, mode>& other) :ptr(other) {}

        T* get(lua_State *L) {
            return ptr.Get();
        }

        const int32 getSharedReferenceCount() {
            return ptr.GetSharedReferenceCount();
        }
    };

    struct WeakUObjectUD {
        FWeakObjectPtr ud;
        WeakUObjectUD(FWeakObjectPtr ptr):ud(ptr) {

        }

        bool isValid() {
            return ud.IsValid();
        }

        UObject* get() {
            return ud.Get();
        }
    };

    class SLUA_UNREAL_API LuaObject
    {
    private:

        #define CHECK_UD_VALID(ptr) if (ptr && ptr->flag&UD_HADFREE) { \
        if (checkfree) \
            luaL_error(L, "arg %d had been freed, can't be used", lua_absindex(L, p)); \
        else \
            return nullptr; \
        }

        template<typename T>
        static T* maybeAnUDTable(lua_State* L, int p,bool checkfree) {
            if(lua_istable(L, p)) {
                AutoStack as(L);
                // use lua_rawget instead of lua_getfield to avoid __index loop!
                lua_pushstring(L, SLUA_CPPINST);
                lua_rawget(L, p);
                if (lua_islightuserdata(L, -1)) {
                    void* ud = lua_touserdata(L, -1);
                    return (T*)ud;
                }
                else if (lua_type(L, -1) == LUA_TUSERDATA)
                    return checkUD<T>(L, lua_absindex(L, -1), checkfree);
            }
            return nullptr;
        }

        // testudata, if T is base of uobject but isn't uobject, try to  cast it to T
        template<typename T>
        static typename std::enable_if<std::is_base_of<UObject,T>::value && !std::is_same<UObject,T>::value, T*>::type 
        testudata(lua_State* L,int p,bool &isnil,bool checkfree=true) {
            UserData<UObject*>* ptr = (UserData<UObject*>*)getUserdataFast(L, p, "UObject", isnil);
            if (isnil) { return nullptr; }
            CHECK_UD_VALID(ptr);
            T* t;
            // if it's a weak UObject, rawget it
            if (ptr && ptr->flag&UD_WEAKUPTR) {
                auto wptr = (UserData<WeakUObjectUD*>*)ptr;
                t = Cast<T>(wptr->ud->get());
            }
            else t = ptr?Cast<T>(ptr->ud):nullptr;

            if (!t && lua_isuserdata(L, p)) {
                luaL_getmetafield(L, p, "__name");
                if (lua_isnil(L, -1)) {
                    return t;
                }
                FString clsname(lua_tostring(L, -1));
                lua_pop(L, 1);
                // skip first char may be 'U' or 'A'
                if (clsname.Find(T::StaticClass()->GetName()) == 1) {
                    UserData<T*>* tptr = (UserData<T*>*) lua_touserdata(L, p);
                    CHECK_UD_VALID(tptr);
                    t = tptr ? tptr->ud : nullptr;
                }
            }
            else if (!t)
                return maybeAnUDTable<T>(L, p,checkfree);

            // check UObject is valid
            if (isUObjectValid(t)) return t;
            return nullptr;
        }

        // testudata, if T is uobject
        template<typename T>
        static typename std::enable_if<std::is_same<UObject,T>::value, T*>::type 
        testudata(lua_State* L,int p,bool &isnil,bool checkfree=true) {
            auto ptr = (UserData<UObject*>*)getUserdataFast(L, p, "UObject", isnil);
            if (isnil) { return nullptr; }
            CHECK_UD_VALID(ptr);
            if (!ptr) return maybeAnUDTable<T>(L, p, checkfree);
            // if it's a weak UObject ptr
            if (ptr->flag&UD_WEAKUPTR) {
                auto wptr = (UserData<WeakUObjectUD*>*)ptr;
                return wptr->ud->get();
            }
            else if (isUObjectValid(ptr->ud) || !checkfree)
                return ptr->ud;
            return nullptr;
        }

        template<class T>
        static typename std::enable_if<!std::is_base_of<TSharedFromThis<T>,T>::value, T*>::type
        unboxSharedUD(lua_State* L, UserData<T*>* ptr) {
            // ptr may be a ThreadSafe sharedref or NotThreadSafe sharedref
            // but we don't care about it, we just Get raw ptr from it
            static_assert(sizeof(SharedPtrUD<T, ESPMode::NotThreadSafe>) == sizeof(SharedPtrUD<T, ESPMode::ThreadSafe>), "unexpected static assert");
            auto sptr = (UserData<SharedPtrUD<T, ESPMode::NotThreadSafe>*>*)ptr;
            // unbox shared ptr to rawptr
            return sptr->ud->get(L);
        }

        template<class T>
        static typename std::enable_if<std::is_base_of<TSharedFromThis<T>, T>::value, T*>::type
        unboxSharedUD(lua_State* L, UserData<T*>* ptr) {
            // never run here
            ensureMsgf(false, TEXT("You cannot use a TSharedPtr of one mode with a type which inherits TSharedFromThis of another mode."));
            return nullptr;
        }

        template<class T>
        static T* unboxSharedUDRef(lua_State* L, UserData<T*>* ptr) {
            // ptr may be a ThreadSafe sharedref or NotThreadSafe sharedref
            // but we don't care about it, we just Get raw ptr from it
            static_assert(sizeof(SharedRefUD<T, ESPMode::NotThreadSafe>) == sizeof(SharedRefUD<T, ESPMode::ThreadSafe>), "unexpected static assert");
            auto sptr = (UserData<SharedRefUD<T, ESPMode::NotThreadSafe>*>*)ptr;
            // unbox shared ptr to rawptr
            return sptr->ud->get(L);
        }

        // testudata, if T isn't uobject
        template<typename T>
        static typename std::enable_if<!std::is_base_of<UObject,T>::value && !std::is_same<UObject,T>::value, T*>::type 
        testudata(lua_State* L,int p,bool &isnil,bool checkfree=true) {
            auto ptr = (UserData<T*>*)getUserdataFast(L, p, TypeName<T>::value().c_str(), isnil);
            if (isnil) { return nullptr; }
            CHECK_UD_VALID(ptr);
            // ptr is boxed shared ptr?
            if (ptr) {
                if (ptr->flag&UD_SHAREDPTR) {
                    return unboxSharedUD<T>(L,ptr);
                }
                else if (ptr->flag&UD_SHAREDREF) {
                    return unboxSharedUDRef<T>(L,ptr);
                }
            }
            if (!ptr) return maybeAnUDTable<T>(L, p, checkfree);
            return ptr?ptr->ud:nullptr;
        }

    public:
        typedef int (*PushPropertyFunction)(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder);
        typedef void* (*CheckPropertyFunction)(lua_State* L,FProperty* prop,uint8* parms,int i,bool bForceCopy);
        typedef void (*ReferencePropertyFunction)(lua_State* L, FProperty* prop, uint8* src, void* dst);
        typedef int (*ReferencePusherPropertyFunction)(lua_State* L,FProperty* prop,uint8* parms,void* parentAdrres,uint16 replicateIndex);

        static PushPropertyFunction getPusher(FProperty* prop);
        static CheckPropertyFunction getChecker(FProperty* prop);
        static ReferencePropertyFunction getReferencer(FProperty* prop);
        static ReferencePusherPropertyFunction getReferencePusher(FProperty* prop);
        static PushPropertyFunction getPusher(FFieldClass* cls);
        static CheckPropertyFunction getChecker(FFieldClass* cls);
        static ReferencePropertyFunction getReferencer(FFieldClass* cls);
        static ReferencePusherPropertyFunction getReferencePusher(FFieldClass* cls);

        static int setUservalueMeta(lua_State* L, UStruct* cls);
        static int pushReferenceAndCache(const ReferencePusherPropertyFunction& pusher, lua_State* L, UStruct* cls,
                                        FProperty* prop, uint8* parms, void* parentAdrres, uint16 replicateIndex);

        static bool matchType(lua_State* L, int p, const char* tn, bool noprefix=false);

        static int classIndex(lua_State* L);
        static int classNewindex(lua_State* L);
        static int objectIndex(lua_State* L, UObject* obj, const char* name, bool cacheToLua=false);
        static bool objectNewIndex(lua_State* L, UObject* obj, const char* name, int valueIdx, bool checkValid = true);

        static void newType(lua_State* L, const char* tn);
        static void newTypeWithBase(lua_State* L, const char* tn, std::initializer_list<const char*> bases);
        static void addMethod(lua_State* L, const char* name, lua_CFunction func, bool isInstance = true);
        static void addGlobalMethod(lua_State* L, const char* name, lua_CFunction func);
        static void addField(lua_State* L, const char* name, lua_CFunction getter, lua_CFunction setter, bool isInstance = true);
        static void addOperator(lua_State* L, const char* name, lua_CFunction func);
        static void finishType(lua_State* L, const char* tn, lua_CFunction ctor, lua_CFunction gc, lua_CFunction strHint=nullptr);

        // check UObject is valid
        static bool isUObjectValid(UObject* obj) {
#if ENGINE_MAJOR_VERSION >= 5
            return IsValid(obj);
#else
            return obj && !obj->IsUnreachable() && !obj->IsPendingKill();
#endif
        }

        // create new enum type to lua, see DefEnum macro
        template<class T>
        static void newEnum(lua_State* L, const char* tn, const char* keys, std::initializer_list<T> values) {
            FString fkey(keys);
            // remove namespace prefix
            fkey.ReplaceInline(*FString::Format(TEXT("{0}::"), { UTF8_TO_TCHAR(tn) }), TEXT(""));
            // remove space
            fkey.ReplaceInline(TEXT(" "),TEXT(""));
            // create enum table
            createTable(L, tn);

            FString key, right;
            for (size_t i = 0; i < values.size() && strSplit(fkey, ",", &key, &right); ++i) {
                lua_pushinteger(L, (int)(*(values.begin() + i)));
                lua_setfield(L, -2, TCHAR_TO_UTF8(*key));
                fkey = right;
            }
            // pop t
            lua_pop(L, 1);
        }
        static void init(lua_State* L);

        /**
         * Get 'TValue' from Lua stack
         */
        static TValue* getTValue(lua_State* L, int32 index)
        {
#if 504 == LUA_VERSION_NUM
            CallInfo* ci = L->ci;
            if (index > 0)
            {
                StkId o = ci->func + index;
                check(index <= L->ci->top - (ci->func + 1));
                if (o >= L->top)
                {
                    return &L->l_G->nilvalue;
                }
                else
                {
                    return s2v(o);
                }
            }
            else if (LUA_REGISTRYINDEX < index)
            {  /* negative index */
                check(index != 0 && -index <= L->top - (ci->func + 1));
                return s2v(L->top + index);
            }
            else if (index == LUA_REGISTRYINDEX)
            {
                return &L->l_G->l_registry;
            }
            else
            {  /* upvalues */
                index = LUA_REGISTRYINDEX - index;
                check(index <= MAXUPVAL + 1);
                if (ttislcf(s2v(ci->func)))
                {
                    /* light C function? */
                    return &L->l_G->nilvalue;  /* it has no upvalues */
                }
                else
                {
                    CClosure* func = clCvalue(s2v(ci->func));
                    return (index <= func->nupvalues) ? &func->upvalue[index - 1] : &L->l_G->nilvalue;
                }
            }
#else
            CallInfo* ci = L->ci;
            if (index > 0)
            {
                TValue* V = ci->func + index;
                check(index <= ci->top - (ci->func + 1));
                return V >= L->top ? (TValue*)NULL : V;
            }
            else if (index > LUA_REGISTRYINDEX)             // negative
            {
                check(index != 0 && -index <= L->top - (ci->func + 1));
                return L->top + index;
            }
            else if (index == LUA_REGISTRYINDEX)
            {
                return &L->l_G->l_registry;
            }
            else                                            // upvalues
            {
                index = LUA_REGISTRYINDEX - index;
                check(index <= MAXUPVAL + 1);
                if (ttislcf(ci->func))
                {
                    return (TValue*)NULL;                   // light C function has no upvalues
                }
                else
                {
                    CClosure* Closure = clCvalue(ci->func);
                    return (index <= Closure->nupvalues) ? &Closure->upvalue[index - 1] : (TValue*)NULL;
                }
            }
#endif
        }

        static int32 getTValueType(TValue* value)
        {
            if (!value)
            {
                return LUA_TNIL;
            }
#if 504 == LUA_VERSION_NUM
            return ttype(value);
#else
            return ttnov(value);
#endif
        }

        static void* getUserdataFast(lua_State* L, int32 i, const char* typeName, bool &isnil)
        {
            void* userdata = nullptr;

            TValue* value = getTValue(L, i);
            int32 currentType = getTValueType(value);
            isnil = currentType == LUA_TNIL;
            if (currentType == LUA_TUSERDATA)
            {
                Udata* U = uvalue(value);
                Table* mt = U->metatable;
                if (mt)
                {
#if LUA_VERSION_NUM > 503
                    val_(s2v(L->top)).gc = obj2gco(mt);
                    settt_(s2v(L->top), ctb(LUA_VTABLE));
#else
                    val_(L->top).gc = obj2gco(mt);
                    settt_((L->top), ctb(LUA_TTABLE));
#endif

                    L->top++;
                    lua_pushstring(L, "__name");
                    int tt = lua_rawget(L, -2);
                    if (tt != LUA_TNIL)
                    {
                        if (strcmp(typeName, lua_tostring(L, -1)) == 0)
                        {
                            lua_pop(L, 2);
                            userdata = getudatamem(U);
                            return userdata;
                        }
                    }

                    lua_pop(L, 2);
                }
            }
            return userdata;
        }

        // check arg at p is exported lua class named __name in field 
        // of metable of the class, if T is base of class or class is T, 
        // return the pointer of class, otherwise return nullptr
        template<typename T>
        static T* checkUD(lua_State* L,int p,bool checkfree=true) {
            bool isnil;
            T* ret = testudata<T>(L,p,isnil,checkfree);
            if(ret || isnil) return ret;

            const char *typearg = nullptr;
            int tt = luaL_getmetafield(L, p, "__name");
            if (tt == LUA_TSTRING)
                typearg = lua_tostring(L, -1);

            if(tt!=LUA_TNIL) lua_pop(L,1);

            if(checkfree && !typearg)
                luaL_error(L,"expect userdata at %d, if you passed an UObject, maybe it's unreachable",p);

            if (LuaObject::isBaseTypeOf(L, typearg, TypeName<T>::value().c_str())) {
                UserData<T*> *udptr = reinterpret_cast<UserData<T*>*>(lua_touserdata(L, p));
                CHECK_UD_VALID(udptr);
                return udptr->ud;
            }
            if(checkfree) 
                luaL_error(L,"expect userdata %s at %d, but got %s, if you passed an UObject, maybe it's unreachable",TypeName<T>::value().c_str(), p, typearg);
            return nullptr;
        }

        template<class T>
        static T checkValueOpt(lua_State* L, int p, const T& defaultValue=T()) {
            if (!typeMatched<T>(lua_type(L,p))) {
                return defaultValue;
            } else {
                return checkValue<T>(L, p);
            }
        }

        template<class T>
        static typename std::enable_if< std::is_pointer<T>::value,T >::type checkReturn(lua_State* L, int p) {
            UserData<T> *udptr = reinterpret_cast<UserData<T>*>(lua_touserdata(L, p));
            if (udptr->flag & UD_HADFREE)
                luaL_error(L, "checkValue error, obj parent has been freed");
            // if it's an UStruct, check struct type name is matched
            if (udptr->flag & UD_USTRUCT) {
                UserData<LuaStruct*> *structptr = reinterpret_cast<UserData<LuaStruct*>*>(udptr);
                LuaStruct* ls = structptr->ud;
                // skip first prefix like 'F','U','A'
                if (sizeof(typename std::remove_pointer<T>::type) == ls->size && strcmp(TypeName<T>::value().c_str()+1, TCHAR_TO_UTF8(*ls->uss->GetName())) == 0)
                    return (T)(ls->buf);
                else
                    luaL_error(L, "checkValue error, type dismatched, expect %s", TypeName<T>::value().c_str());
            }
            return udptr->ud;
        }

        // if T isn't pointer, we should assume UserData box a pointer and dereference it to return
        template<class T>
        static typename std::enable_if< !std::is_pointer<T>::value,T >::type checkReturn(lua_State* L, int p) {
            UserData<T*> *udptr = reinterpret_cast<UserData<T*>*>(lua_touserdata(L, p));
            if (udptr->flag & UD_HADFREE)
                luaL_error(L, "checkValue error, obj parent has been freed");
            // if it's an UStruct, check struct type name is matched
            if (udptr->flag & UD_USTRUCT) {
                UserData<LuaStruct*> *structptr = reinterpret_cast<UserData<LuaStruct*>*>(udptr);
                LuaStruct* ls = structptr->ud;
                // skip first prefix like 'F','U','A'
                if (sizeof(T) == ls->size && strcmp(TypeName<T>::value().c_str() + 1, TCHAR_TO_UTF8(*ls->uss->GetName())) == 0)
                    return *((T*)(ls->buf));
                else
                    luaL_error(L, "checkValue error, type dismatched, expect %s", TypeName<T>::value().c_str());
            }
            return *(udptr->ud);
        }
        
        template<class T>
        static T checkValue(lua_State* L, int p) {
            if(std::is_pointer<T>::value && lua_isnil(L,p))
                return T();

            using TT = typename remove_cr<T>::type;
            if(std::is_class<TT>::value && std::is_default_constructible<TT>::value && lua_isnil(L,p))
                return TT();

            static_assert(!std::is_same<wchar_t*, typename remove_ptr_const<T>::type>::value,
                "checkValue does not support parameter const TCHAR*, use FString instead");

            if (!lua_isuserdata(L, p))
                luaL_error(L, "expect userdata at arg %d", p);

            return checkReturn<T>(L, p);
        }

        template<class T>
        bool checkValue(lua_State* L, int p, T& out) {
            if (!typeMatched<T>(lua_type(L, p)))
                return false;
            out = checkValue<T>(L, p);
            return true;
        }

        // check value if it's enum
        template<typename T>
        static T checkEnumValue(lua_State* L, int p) {
            return static_cast<T>(luaL_checkinteger(L, p));
        }

        // check value if it's TArray
        template<class T>
        static T checkTArray(lua_State* L, int p) {
            CheckUD(LuaArray,L,p);
            return UD->asTArray<typename T::ElementType>(L);
        }

        // check value if it's TMap
        template<class T>
        static T checkTMap(lua_State* L, int p) {
            CheckUD(LuaMap, L, p);
            using KeyType = typename TPairTraits<typename T::ElementType>::KeyType;
            using ValueType = typename TPairTraits<typename T::ElementType>::ValueType;
            return UD->asTMap<KeyType, ValueType>(L);
        }

        // check value if it's a TSet
        template<class T>
        static T checkTSet(lua_State* L, int p) {
            CheckUD(LuaSet, L, p);
            return UD->asTSet<typename T::ElementType>(L);
        }

        template<typename T>
        static void* void_cast( const T* v ) {
            return reinterpret_cast<void *>(const_cast< T* >(v));
        }

        template<typename T>
        static void* void_cast( T* v ) {
            return reinterpret_cast<void *>(v);
        }

        template<class T>
        static int push(lua_State* L, const char* fn, const T* v, uint32 flag = UD_NOFLAG) {
            luaL_getmetatable(L,fn);

            // if v is the UnrealType
            UScriptStruct* uss = nullptr;
            if (lua_isnil(L, -1) && isUnrealStruct(fn, &uss)) {
                lua_pop(L, 1); // pop nil
                uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;
                ensure(size == sizeof(T));
                LuaStruct* ls = new LuaStruct();
                ls->Init((uint8*)v, size, uss, false);
                int ret = push(L, ls);
                if (ret) {
                    if (flag & UD_VALUETYPE) {
                        addLink(L, const_cast<T*>(v));
                    }
                }
                
                return ret;
            }
            NewUD(T, v, flag);
            lua_pushvalue(L, -2);
            lua_setmetatable(L, -2);
            lua_remove(L, -2); // remove metatable of fn
            if (flag & UD_VALUETYPE) {
                addLink(L, const_cast<T*>(v));
            }
            return 1;
        }

        static void addLink(lua_State* L, void* address);
        static void releaseLink(lua_State* L, void* address);
        static void linkProp(lua_State* L, void* parentAddress, void* prop);
        static void unlinkProp(lua_State* L, void* prop);

        template<class T>
        static int pushAndLink(lua_State* L, const void* parent, const char* tn, const T* v, void* proxy, uint16 replicatedIndex) {
            NewNetStructUD(T, v, UD_NOFLAG)
            luaL_getmetatable(L, tn);
            lua_setmetatable(L, -2);
            linkProp(L, void_cast(parent), void_cast(udptr));
            if (proxy) {
                udptr->proxy = (FLuaNetSerializationProxy*)proxy;
                udptr->luaReplicatedIndex = replicatedIndex;
                udptr->flag |= UD_NETTYPE;
            }
            return 1;
        }

        template<class T>
        static int pushReference(lua_State* L,T cls,void* parentAddress)
        {
            int ret = push(L, cls);
            void* ud = lua_touserdata(L, -ret);
            if (ud) {
                linkProp(L, parentAddress, ud);
            }
            return ret;
        }

        template<class T, bool F = IsUObject<T>::value >
        static int pushType(lua_State* L,T cls,const char* tn,lua_CFunction setupmt=nullptr,lua_CFunction gc=nullptr, short nuvalues=1) {
            if(!cls) {
                lua_pushnil(L);
                return 1;
            }
            ensure(nuvalues <= 1);
#if LUA_VERSION_NUM > 503 
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdatauv(L, sizeof(UserData<T>), nuvalues));
#else
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdata(L, sizeof(UserData<T>)));
#endif
            ud->parent = nullptr;
            ud->ud = cls;
            ud->flag = gc!=nullptr?UD_AUTOGC:UD_NOFLAG;
            if (F) ud->flag |= UD_UOBJECT;
            setupMetaTable(L,tn,setupmt,gc);
            return 1;
        }

        static const char* getType(lua_State* L, int p);

        // for weak UObject

        static int gcWeakUObject(lua_State* L) {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            UserData<WeakUObjectUD*>* ud = reinterpret_cast<UserData<WeakUObjectUD*>*>(lua_touserdata(L, 1));
            ensure(ud->flag&UD_WEAKUPTR);
            ud->flag |= UD_HADFREE;
            SafeDelete(ud->ud);
            return 0;
        }

        static int pushWeakType(lua_State* L, WeakUObjectUD* cls) {
#if LUA_VERSION_NUM > 503 
            UserData<WeakUObjectUD*>* ud = reinterpret_cast<UserData<WeakUObjectUD*>*>(lua_newuserdatauv(L, sizeof(UserData<WeakUObjectUD*>), 0));
#else
            UserData<WeakUObjectUD*>* ud = reinterpret_cast<UserData<WeakUObjectUD*>*>(lua_newuserdata(L, sizeof(UserData<WeakUObjectUD*>)));
#endif
            
            ud->parent = nullptr;
            ud->ud = cls;
            ud->flag = UD_WEAKUPTR | UD_AUTOGC;
            setupMetaTable(L, "UObject", setupInstanceMT, gcWeakUObject);
            return 1;
        }

        // for TSharePtr version

        template<class T, ESPMode mode>
        static int gcSharedUD(lua_State* L) {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            UserData<T*>* ud = reinterpret_cast<UserData<T*>*>(lua_touserdata(L, 1));
            ud->flag |= UD_HADFREE;
            auto shared = ud->ud;
            if (shared->getSharedReferenceCount() == 1) {
                LuaObject::releaseLink(L, shared->get(L));
            }
            SafeDelete(ud->ud);
            return 0;
        }

        template<class BOXPUD, ESPMode mode, bool F>
        static int pushSharedType(lua_State* L, BOXPUD* cls, const char* tn, int flag) {
#if LUA_VERSION_NUM > 503 
            UserData<BOXPUD*>* ud = reinterpret_cast<UserData<BOXPUD*>*>(lua_newuserdatauv(L, sizeof(UserData<BOXPUD*>), 0));
#else
            UserData<BOXPUD*>* ud = reinterpret_cast<UserData<BOXPUD*>*>(lua_newuserdata(L, sizeof(UserData<BOXPUD*>)));
#endif
            
            ud->parent = nullptr;
            ud->ud = cls;
            ud->flag = UD_AUTOGC | flag;
            if (F) ud->flag |= UD_UOBJECT;
            if (mode == ESPMode::ThreadSafe) ud->flag |= UD_THREADSAFEPTR;
            setupMetaTable(L, tn, gcSharedUD<BOXPUD, mode>);
            return 1;
        }

        template<class T,ESPMode mode, bool F = IsUObject<T>::value>
        static int pushType(lua_State* L, SharedPtrUD<T, mode>* cls, const char* tn) {
            if (!cls) {
                lua_pushnil(L);
                return 1;
            }
            using BOXPUD = SharedPtrUD<T, mode>;
            return pushSharedType<BOXPUD,mode,F>(L, cls, tn, UD_SHAREDPTR);
        }

        template<class T, ESPMode mode, bool F = IsUObject<T>::value>
        static int pushType(lua_State* L, SharedRefUD<T, mode>* cls, const char* tn) {
            if (!cls) {
                lua_pushnil(L);
                return 1;
            }
            using BOXPUD = SharedRefUD<T, mode>;
            return pushSharedType<BOXPUD, mode,F>(L, cls, tn, UD_SHAREDREF);
        }

        static void addRef(lua_State* L,UObject* obj, void* ud, bool ref);
        static void removeRef(lua_State* L,UObject* obj,void* ud=nullptr);

        template<typename T>
        static int pushGCObject(lua_State* L,T obj,const char* tn,lua_CFunction setupmt,lua_CFunction gc,bool ref, TFunction<void ()> callback) {
            if(getObjCache(L,obj,tn)) return 1;
            int r = pushType<T>(L,obj,tn,setupmt,gc);
            if (r) {
                if (callback)
                    callback();

                addLink(L, obj);
                addRef(L, obj, lua_touserdata(L, -1), ref);
                cacheObj(L, obj);
            }
            return r;
        }

        static int setupMTSelfSearch(lua_State* L);
        
        static int pushClass(lua_State* L,UClass* cls);
        static int pushStruct(lua_State* L,UScriptStruct* cls);
        static int pushEnum(lua_State* L, UEnum* e);
        static int push(lua_State* L, UObject* obj, bool ref=false, NewObjectRecorder* objRecorder = nullptr);
        inline static int push(lua_State* L, const UObject* obj, bool ref = false, NewObjectRecorder* objRecorder = nullptr) {
            return push(L, const_cast<UObject*>(obj), ref, objRecorder);
        }
        static int push(lua_State* L, FWeakObjectPtr ptr);
        static int push(lua_State* L, LuaStruct* ls);
        static int push(lua_State* L, LuaArray* array);
        static int push(lua_State* L, LuaMap* map);
        static int push(lua_State* L, LuaSet* set);
        static int push(lua_State* L, double v);
        static int push(lua_State* L, int64 v);
        static int push(lua_State* L, uint64 v);
        static int push(lua_State* L, int8 v);
        static int push(lua_State* L, uint8 v);
        static int push(lua_State* L, int16 v);
        static int push(lua_State* L, uint16 v);
        static int push(lua_State* L, float v);
        static int push(lua_State* L, int v);
        static int push(lua_State* L, bool v);
        static int push(lua_State* L, uint32 v);
        static int push(lua_State* L, void* v);
        static int push(lua_State* L, const FText& v);
        static int push(lua_State* L, const FString& str);
        static int push(lua_State* L, const FName& str);
        static int push(lua_State* L, const char* str);
        static int push(lua_State* L, const LuaVar& v);
        static int push(lua_State* L, UFunction* func, UClass* cls=nullptr);
        static int push(lua_State* L, const LuaLString& lstr);
        static int push(lua_State* L, FProperty* up, uint8* parms, NewObjectRecorder* objRecorder = nullptr);
        static int push(lua_State* L, FProperty* up, UObject* obj, NewObjectRecorder* objRecorder = nullptr);

        // check tn is base of base
        static bool isBaseTypeOf(lua_State* L,const char* tn,const char* base);

        template<typename T>
        static int push(lua_State* L,T* ptr,typename std::enable_if<!std::is_base_of<UObject,T>::value && !Has_LUA_typename<T>::value>::type* = nullptr) {
            return push(L, TypeName<T>::value().c_str(), ptr);
        }

        // it's an override for non-uobject, non-ptr, only accept struct or class value
        template<typename T>
        static int push(lua_State* L, const T& v, typename std::enable_if<!std::is_base_of<UObject, T>::value && std::is_class<T>::value>::type* = nullptr) {
            T* newPtr = new T(v);
            return push<T>(L, TypeName<T>::value().c_str(), newPtr, UD_AUTOGC | UD_VALUETYPE);
        }

        // used this branch
        template<typename T>
        static int push(lua_State* L, T* ptr, typename std::enable_if<!std::is_base_of<UObject, T>::value && Has_LUA_typename<T>::value>::type* = nullptr) {
            return push(L, ptr->LUA_typename().c_str(), ptr);
        }

        template<typename T>
        static int push(lua_State* L, LuaOwnedPtr<T> ptr, typename std::enable_if<!std::is_base_of<UObject, T>::value && Has_LUA_typename<T>::value>::type* = nullptr) {
            return push(L, ptr->LUA_typename().c_str(), ptr.ptr, UD_AUTOGC);
        }

        template<typename T>
        static int push(lua_State* L, LuaOwnedPtr<T> ptr, typename std::enable_if<!std::is_base_of<UObject, T>::value && !Has_LUA_typename<T>::value>::type* = nullptr) {
            return push(L, TypeName<T>::value().c_str(), ptr.ptr, UD_AUTOGC);
        }

        template<typename T, ESPMode mode>
        static int push(lua_State* L, const TSharedPtr<T, mode>& ptr) {
            // get raw ptr from sharedptr
            T* rawptr = ptr.Get();
            // get typename 
            auto tn = TypeName<T>::value();
            if (getObjCache(L, rawptr, tn.c_str())) return 1;
            int r = pushType<T>(L, new SharedPtrUD<T, mode>(ptr), tn.c_str());
            if (r && !lua_isnil(L, -1)) {
                LuaObject::addLink(L, rawptr);
                cacheObj(L, rawptr);
            }
            return r;
        }

        template<typename T, ESPMode mode>
        static int push(lua_State* L, const TSharedRef<T, mode>& ref) {
            // get raw ptr from sharedptr
            T& rawref = ref.Get();
            // get typename 
            auto tn = TypeName<T>::value();
            if (getObjCache(L, &rawref, tn.c_str())) return 1;
            int r = pushType<T>(L, new SharedRefUD<T, mode>(ref), tn.c_str());
            if (r && !lua_isnil(L, -1)) {
                LuaObject::addLink(L, &rawref);
                cacheObj(L, &rawref);
            }
            return r;
        }
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        // for TBaseDelegate
        template<class R, class ...ARGS>
        static int push(lua_State* L, TBaseDelegate<R, ARGS...>& delegate);
#else
        // for TDelegate
        template<class R, class ...ARGS>
        static int push(lua_State* L, TDelegate<R, ARGS...>& delegate);
#endif
        

        template<typename T>
        static int push(lua_State* L,T v,typename std::enable_if<std::is_enum<T>::value>::type* = nullptr) {
            return push(L,static_cast<int>(v));
        }

        template<typename T>
        static int push(lua_State* L, const TArray<T>& v) {
            return LuaArray::push(L, v);
        }

        template<typename K,typename V>
        static int push(lua_State* L, const TMap<K,V>& v) {
            return LuaMap::push(L, v);
        }
        
        template<typename T>
        static int push(lua_State* L, const TSet<T>& v) {
            return LuaSet::push(L, v);
        }

        // static int push(lua_State* L, FScriptArray* array);
        
        static int pushNil(lua_State* L) {
            lua_pushnil(L);
            return 1;
        }

        static void addExtensionMethod(UClass* cls, const char* n, lua_CFunction func, bool isStatic = false);
        static void addExtensionProperty(UClass* cls, const char* n, lua_CFunction getter, lua_CFunction setter, bool isStatic = false);

        static FProperty* findCacheProperty(lua_State* L, UStruct* cls, const char* pname);
        static int fastIndex(lua_State* L, uint8* parent, UStruct* cls);
        static int fastNewIndex(lua_State* L, uint8* parent);

        static bool getObjCache(lua_State* L, void* obj, const char* tn);
        static void cacheObj(lua_State* L, void* obj);
        static void removeObjCache(lua_State* L, void* obj);

        static bool getCache(lua_State* L, const void* obj, int ref);
        static void addCache(lua_State* L, const void* obj, int ref);
        static void removeCache(lua_State* L, const void* obj, int ref);
        
        static ULatentDelegate* getLatentDelegate(lua_State* L);
        
    private:
        static int setupClassMT(lua_State* L);
        static int setupInstanceMT(lua_State* L);
        static int setupInstanceStructMT(lua_State* L);
        static int setupStructMT(lua_State* L);

        static int gcObject(lua_State* L);
        static int gcClass(lua_State* L);
        static int gcStructClass(lua_State* L);
        static int gcStruct(lua_State* L);
        static int objectToString(lua_State* L);
        static void setupMetaTable(lua_State* L,const char* tn,lua_CFunction setupmt,lua_CFunction gc);
        static void setupMetaTable(lua_State* L, const char* tn, lua_CFunction setupmt, int gc);
        static void setupMetaTable(lua_State* L, const char* tn, lua_CFunction gc);
        static void callRpc(lua_State* L, UObject* obj, UFunction* func, uint8* params);
        static void createTable(lua_State* L, const char* tn);
    };

    template<>
    inline UClass* LuaObject::checkValue(lua_State* L, int p) {
        CheckUD(UClass, L, p);
        return UD;
    }

    template<>
    inline UObject* LuaObject::checkValue(lua_State* L, int p) {
        CheckUD(UObject, L, p);
        return UD;
    }

    template<>
    inline UScriptStruct* LuaObject::checkValue(lua_State* L, int p) {
        CheckUD(UScriptStruct, L, p);
        return UD;
    }

    template<>
    inline LuaStruct* LuaObject::checkValue(lua_State* L, int p) {
        CheckUD(LuaStruct, L, p);
        return UD;
    }

    template<>
    inline FSoftObjectPtr LuaObject::checkValue(lua_State* L, int p) {
        CheckUD(FSoftObjectPtr, L, p);
        return *UD;
    }

    template<>
    inline const char* LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checkstring(L, p);
    }

    template<>
    inline float LuaObject::checkValue(lua_State* L, int p) {
        return (float)luaL_checknumber(L, p);
    }

    template<>
    inline double LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checknumber(L, p);
    }

    template<>
    inline int LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checkinteger(L, p);
    }

    template<>
    inline uint32 LuaObject::checkValue(lua_State* L, int p) {
        return (uint32) luaL_checkinteger(L, p);
    }

    template<>
    inline int8 LuaObject::checkValue(lua_State* L, int p) {
        return (int8) luaL_checkinteger(L, p);
    }

    template<>
    inline uint8 LuaObject::checkValue(lua_State* L, int p) {
        return (uint8) luaL_checkinteger(L, p);
    }

    template<>
    inline int16 LuaObject::checkValue(lua_State* L, int p) {
        return (int16) luaL_checkinteger(L, p);
    }

    template<>
    inline uint16 LuaObject::checkValue(lua_State* L, int p) {
        return (uint16) luaL_checkinteger(L, p);
    }

    template<>
    inline int64 LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checkinteger(L, p);
    }

    template<>
    inline uint64 LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checkinteger(L, p);
    }

    template<>
    inline bool LuaObject::checkValue(lua_State* L, int p) {
        luaL_checktype(L, p, LUA_TBOOLEAN);
        return !!lua_toboolean(L, p);
    }

    template<>
    inline FText LuaObject::checkValue(lua_State* L, int p) {
        const char* s = luaL_checkstring(L, p);
        return FText::FromString(UTF8_TO_TCHAR(s));
    }

    template<>
    inline FString LuaObject::checkValue(lua_State* L, int p) {
        const char* s = luaL_checkstring(L, p);
        return FString(UTF8_TO_TCHAR(s));
    }

    template<>
    inline FName LuaObject::checkValue(lua_State* L, int p) {
        const char* s = luaL_checkstring(L, p);
        return FName(UTF8_TO_TCHAR(s));
    }

    template<>
    inline void* LuaObject::checkValue(lua_State* L, int p) {
        luaL_checktype(L,p,LUA_TLIGHTUSERDATA);
        return lua_touserdata(L,p);
    }

}