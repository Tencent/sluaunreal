// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#ifdef _WIN32
#pragma warning (push)
#pragma warning (disable : 4018)
#endif

#include "LuaObject.h"
#include "LuaDelegate.h"
#include "LatentDelegate.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/Stack.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaSet.h"
#include "LuaState.h"
#include "LuaWrapper.h"

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
// For PUBG Mobile
#include "LuaEnums.h"
#endif

#include "SluaUtil.h"
#include "LuaReference.h"
#include "lstate.h"
#include "LuaBlueprintLibrary.h" // Comment For PUBG Mobile
#include "LuaFunctionAccelerator.h"
#include "LuaNet.h"
#include "LuaOverrider.h"
#include "Engine/UserDefinedEnum.h"

static int32 DeferGCStruct = 1;
FAutoConsoleVariableRef CVarSluaDeferGCStruct(
    TEXT("slua.DeferGCStruct"),
    DeferGCStruct,
    TEXT("Set defer gc struct is enabled.\n"),
    ECVF_Default);

static int32 GSluaEnableReference = 1;
FAutoConsoleVariableRef CVarSluaEnableReference(
    TEXT("slua.EnableReference"),
    GSluaEnableReference,
    TEXT("Whether enable struct reference."));

namespace NS_SLUA {
    static const uint64 ReferenceCastFlags = FArrayProperty::StaticClassCastFlags()
        | FMapProperty::StaticClassCastFlags()
        | FSetProperty::StaticClassCastFlags();

    TMap<FFieldClass*,LuaObject::PushPropertyFunction> pusherMap;
    TMap<FFieldClass*,LuaObject::CheckPropertyFunction> checkerMap;
    TMap<FFieldClass*,LuaObject::ReferencePusherPropertyFunction> referencePusherMap;
    TMap<FFieldClass*,LuaObject::ReferencePropertyFunction> referencerMap;
    
    struct ExtensionField {
        bool isFunction = true;
        union {
            struct {
                lua_CFunction getter;
                lua_CFunction setter;
            };
            lua_CFunction func;
        };

        ExtensionField(lua_CFunction funcf) : isFunction(true), func(funcf) {
            ensure(funcf);
        }
        ExtensionField(lua_CFunction getterf, lua_CFunction setterf) 
            : isFunction(false)
            , getter(getterf)
            , setter(setterf) {}
    };
    
    TMap< UClass*, TMap<FString, ExtensionField> > extensionMMap;
    TMap< UClass*, TMap<FString, ExtensionField> > extensionMMap_static;

    namespace ExtensionMethod{
        void init();
    }

    LuaStruct::LuaStruct()
        : buf(nullptr)
        , size(0)
        , uss(nullptr)
        , proxy(nullptr)
        , luaReplicatedIndex(InvalidReplicatedIndex)
        , isRef(false)
    {
    }

    void LuaStruct::Init(uint8* b, uint32 s, UScriptStruct* u, bool ref) {
        buf = b;
        size = s;
        uss = u;
        isRef = ref;
    }

    LuaStruct::~LuaStruct() {
        if (!isRef) {
            if (buf && size > 0) {
                uss->DestroyStruct(buf);
                FMemory::Free(buf);
                buf = nullptr;
            }
        }
    }

    void LuaStruct::AddReferencedObjects(FReferenceCollector& Collector) {
        Collector.AddReferencedObject(uss);
        
        if (isRef)
            return;
        
        if (uss->StructFlags & CPF_IsPlainOldData)
            return;
        
        LuaReference::addRefByStruct(Collector, uss, buf);
    }

    void LuaObject::addExtensionMethod(UClass* cls,const char* n,lua_CFunction func,bool isStatic) {
        if(isStatic) {
            auto& extmap = extensionMMap_static.FindOrAdd(cls);
            extmap.Add(n, ExtensionField(func));
        }
        else {
            auto& extmap = extensionMMap.FindOrAdd(cls);
            extmap.Add(n, ExtensionField(func));
        }
    }

    void LuaObject::addExtensionProperty(UClass * cls, const char * n, lua_CFunction getter, lua_CFunction setter, bool isStatic)
    {
        if (isStatic) {
            auto& extmap = extensionMMap_static.FindOrAdd(cls);
            extmap.Add(n, ExtensionField(getter,setter));
        }
        else {
            auto& extmap = extensionMMap.FindOrAdd(cls);
            extmap.Add(n, ExtensionField(getter, setter));
        }
    }

    static int findMember(lua_State* L,const char* name) {
       int popn = 0;
        if ((++popn, lua_getfield(L, -1, name) != 0)) {
            lua_remove(L, -2); // remove mt
            return 1;
        } else if ((++popn, lua_getfield(L, -2, ".get")) && (++popn, lua_getfield(L, -1, name))) {
            lua_pushvalue(L, 1);
            lua_call(L, 1, 1);
            lua_remove(L, -2); // remove .get
            return 1;
        } else {
            // find base
            lua_pop(L, popn);
            lua_getfield(L,-1, "__base");
            luaL_checktype(L, -1, LUA_TTABLE);
            // for each base
            {
                size_t cnt = lua_rawlen(L,-1);
                int r = 0;
                for(size_t n=0;n<cnt;n++) {
                    lua_geti(L,-1,n+1);
                    const char* tn = lua_tostring(L,-1);
                    lua_pop(L,1); // pop tn
                    luaL_getmetatable(L,tn);
                    luaL_checktype(L, -1, LUA_TTABLE);
                    if (findMember(L, name)) return 1;
                }
                lua_remove(L,-2); // remove __base
                return r;
            }
        }
    }

    static bool setMember(lua_State* L, const char* name) {
        int popn = 0;
        if ((++popn, lua_getfield(L, -1, ".set")) && (++popn, lua_getfield(L, -1, name))) {
            // push ud
            lua_pushvalue(L, 1);
            // push value
            lua_pushvalue(L, 3);
            // call setter
            lua_call(L, 2, 0);
            lua_pop(L, 1); // pop .set
            return true;
        }
        else {
            // find base
            lua_pop(L, popn);
            lua_getfield(L, -1, "__base");
            luaL_checktype(L, -1, LUA_TTABLE);
            // for each base
            {
                size_t cnt = lua_rawlen(L, -1);
                for (size_t n = 0; n < cnt; n++) {
                    lua_geti(L, -1, n + 1);
                    const char* tn = lua_tostring(L, -1);
                    lua_pop(L, 1); // pop tn
                    luaL_getmetatable(L, tn);
                    luaL_checktype(L, -1, LUA_TTABLE);
                    if (setMember(L, name)) return true;
                }
            }
            // pop __base
            lua_pop(L, 1);
            return false;
        }
    }

    int LuaObject::classIndex(lua_State* L) {
        lua_getmetatable(L, 1);
        const char* name = checkValue<const char*>(L, 2);
        if (!findMember(L, name))
            luaL_error(L, "can't get %s", name);
        lua_remove(L, -2);
        return 1;
    }

    int LuaObject::classNewindex(lua_State* L) {
        lua_getmetatable(L, 1);
        const char* name = checkValue<const char*>(L, 2);
        if(!setMember(L, name))
            luaL_error(L, "can't set %s", name);
        lua_pop(L, 1);
        return 0;
    }

    static void setMetaMethods(lua_State* L) {
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setfield(L, -3, ".get"); // upvalue
        lua_pushcclosure(L, LuaObject::classIndex, 1);
        lua_setfield(L, -2, "__index");
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setfield(L, -3, ".set"); // upvalue
        lua_pushcclosure(L, LuaObject::classNewindex, 1);
        lua_setfield(L, -2, "__newindex");
    }

    void LuaObject::newType(lua_State* L, const char* tn) {
        lua_pushglobaltable(L);                 // _G
        lua_newtable(L);                            // local t = {}
        lua_pushvalue(L, -1);
        lua_setfield(L, -3, tn);                    // _G[tn] = t
        lua_remove(L, -2);                      // remove global table;

        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setmetatable(L, -3);                    // setmetatable(t, mt)
        setMetaMethods(L);

        luaL_newmetatable(L, tn);
        setMetaMethods(L);
    }

    void LuaObject::newTypeWithBase(lua_State* L, const char* tn, std::initializer_list<const char*> bases) {
        newType(L,tn);

        // create base table
        lua_newtable(L);
        lua_pushvalue(L,-1);
        lua_setfield(L,-3,"__base");
        
        for(auto base:bases) {
            if(strlen(base)>0) {
                lua_pushstring(L,base);
                size_t p = lua_rawlen(L,-2);
                lua_seti(L,-2,p+1);
            }
        }
        // pop __base table
        lua_pop(L,1);
    }

    int LuaObject::push(lua_State * L, const LuaLString& lstr)
    {
        lua_pushlstring(L, lstr.buf, lstr.len);
        return 1;
    }

    bool LuaObject::isBaseTypeOf(lua_State* L,const char* tn,const char* base) {
        AutoStack as(L);
        int t = luaL_getmetatable(L,tn);
        if(t!=LUA_TTABLE)
            return false;

        if(lua_getfield(L,-1,"__base")==LUA_TTABLE) {
            size_t len = lua_rawlen(L,-1);
            for(int n=0;n<len;n++) {
                if(lua_geti(L,-1,n+1)==LUA_TSTRING) {
                    const char* maybeBase = lua_tostring(L,-1);
                    if(strcmp(maybeBase,base)==0) return true;
                    else return isBaseTypeOf(L,maybeBase,base);
                }
            }
            return false;
        }
        return false;
    }

    void LuaObject::addMethod(lua_State* L, const char* name, lua_CFunction func, bool isInstance) {
        lua_pushcfunction(L, func);
        lua_setfield(L, isInstance ? -2 : -3, name);
    }

    void LuaObject::addGlobalMethod(lua_State* L, const char* name, lua_CFunction func) {
        lua_pushcfunction(L, func);
        lua_setglobal(L,name);
    }

    void LuaObject::addField(lua_State* L, const char* name, lua_CFunction getter, lua_CFunction setter, bool isInstance) {
        lua_getfield(L, isInstance ? -1 : -2, ".get");
        lua_pushcfunction(L, getter);
        lua_setfield(L, -2, name);
        lua_pop(L, 1);
        lua_getfield(L, isInstance ? -1 : -2, ".set");
        lua_pushcfunction(L, setter);
        lua_setfield(L, -2, name);
        lua_pop(L, 1);
    }

    void LuaObject::addOperator(lua_State* L, const char* name, lua_CFunction func) {
        lua_pushcfunction(L, func);
        lua_setfield(L, -2, name);
    }

    // C++原生类和结构体的next和pairs
    int instanceCppNext(lua_State* L) {
        // key may be nil! top may be 1;
        lua_settop(L, 2); // Stack: [obj, key]
        if (lua_getmetatable(L, 1) == 0) // Stack: [obj, key, mt]
        {
            return 0;
        }

        lua_getfield(L, -1, ".get"); // local .get = mt[".get"]
        lua_pushvalue(L, 2); // Stack: [obj, key, mt, .get, key]
        if (lua_next(L, -2) == 0)// local key_getter, func_getter = next(.get, key)
        {
            return 0;
        }

        // remove the getter function
        lua_pop(L, 1); // Stack: [obj, key, mt, .get, key_getter]

        // get the name of the struct property
        const char* key_getter = lua_tostring(L, -1);

        lua_getfield(L, 1, key_getter); // prop = obj[key_getter]
        return 2; // return (key_getter, prop)
    }

    int instanceCppPairs(lua_State* L) {
        // obj
        lua_pushcfunction(L, instanceCppNext); // obj, next
        lua_pushvalue(L, 1); // obj, next, obj
        lua_pushnil(L); // obj, next, obj, nil

        return 3;
    }

    void LuaObject::finishType(lua_State* L, const char* tn, lua_CFunction ctor, lua_CFunction gc, lua_CFunction strHint) {
        if(ctor) {
            lua_pushcclosure(L, ctor, 0);
            lua_setfield(L, -3, "__call");
        }
        if(gc) {
            lua_pushcclosure(L, gc, 0); // t, mt, _instance, __gc
            lua_setfield(L, -2, "__gc"); // t, mt, _instance
        }
        if(strHint) {
            lua_pushcfunction(L, strHint);
            lua_setfield(L, -2, "__tostring");
        }
        lua_pushcfunction(L, instanceCppNext);
        lua_setfield(L, -2, "__next");
        lua_pushcfunction(L, instanceCppPairs);
        lua_setfield(L, -2, "__pairs");
        lua_pop(L,3);
    }

    bool LuaObject::matchType(lua_State* L, int p, const char* tn, bool noprefix) {
        if (!lua_isuserdata(L, p)) {
            return false;
        }
        if (lua_getmetatable(L, p)) {
            if (lua_getfield(L, -1, "__name") == LUA_TSTRING) {
                auto name = lua_tostring(L, -1);
                // skip first prefix "F" or "U" or "A"
                if (noprefix) return strcmp(name + 1, tn) == 0;
                else return strcmp(name, tn) == 0;
            }

            lua_pop(L, 2);
        }
    
        return false;
    }

    LuaObject::PushPropertyFunction LuaObject::getPusher(FFieldClass* cls) {
        auto it = pusherMap.Find(cls);
        if(it!=nullptr)
            return *it;
        return nullptr;
    }

    LuaObject::CheckPropertyFunction LuaObject::getChecker(FFieldClass* cls) {
        auto it = checkerMap.Find(cls);
        if(it!=nullptr)
            return *it;
        return nullptr;
    }

    LuaObject::ReferencePropertyFunction LuaObject::getReferencer(FFieldClass* cls) {
        auto it = referencerMap.Find(cls);
        if(it!=nullptr)
            return *it;
        return nullptr;
    }

    LuaObject::ReferencePusherPropertyFunction LuaObject::getReferencePusher(FFieldClass* cls) {
        auto it = referencePusherMap.Find(cls);
        if(it!=nullptr)
            return *it;
        return nullptr;
    }

    int LuaObject::setUservalueMeta(lua_State* L, UStruct* cls)
    {
        auto ls = LuaState::get(L);
        lua_geti(L, LUA_REGISTRYINDEX, ls->cacheClassPropRef);
        // push obj as key
        lua_pushlightuserdata(L, cls);
        
        // get key from table
        if (lua_rawget(L, -2) == LUA_TNIL)
        {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_pushstring(L, "v");
            lua_setfield(L, -2, "__mode");

            lua_pushlightuserdata(L, cls);
            lua_pushvalue(L, -2);
            lua_rawset(L, -4);
        }
        lua_remove(L, -2); // remove cache table
        
        lua_setmetatable(L, -2);
        return 1;
    }

    int LuaObject::pushReferenceAndCache(const ReferencePusherPropertyFunction& pusher, lua_State* L, UStruct* cls,
                                        FProperty* prop, uint8* parms, void* parentAdrres, uint16 replicateIndex)
    {
        int ret = pusher(L, prop, parms, parentAdrres, replicateIndex);
        if (ret) {
            int selfType = lua_type(L, 1);
            if (selfType == LUA_TUSERDATA) {
                if (lua_getuservalue(L, 1) == LUA_TNIL) {
                    lua_pop(L, 1);
                    lua_newtable(L);
                    lua_setuservalue(L, 1);
                    L->top++;
                    setUservalueMeta(L, cls);
                }

                lua_pushvalue(L, 2); // push key
                lua_pushvalue(L, -3); // push reference value
                lua_rawset(L, -3);
                L->top--;
            }
            else if (selfType == LUA_TTABLE) {
                lua_pushstring(L, LuaOverrider::CACHE_NAME);
                if (lua_rawget(L, 1) == LUA_TNIL) {
                    L->top--;
                    lua_newtable(L);
                    setUservalueMeta(L, cls);
                    lua_pushstring(L, LuaOverrider::CACHE_NAME);
                    lua_pushvalue(L, -2);
                    lua_rawset(L, 1);
                }
                lua_pushvalue(L, 2); // push key
                lua_pushvalue(L, -3); // push reference value
                lua_rawset(L, -3);
                L->top--;
            }
        }
        return ret;
    }

    LuaObject::PushPropertyFunction LuaObject::getPusher(FProperty* prop) {
        return getPusher(prop->GetClass());
    }

    LuaObject::CheckPropertyFunction LuaObject::getChecker(FProperty* prop) {
        return getChecker(prop->GetClass());        
    }

    LuaObject::ReferencePropertyFunction LuaObject::getReferencer(FProperty* prop) {
        auto sp = CastField<FStructProperty>(prop);
        if (sp && sp->Struct == FLuaBPVar::StaticStruct())
            return nullptr;
        return getReferencer(prop->GetClass());        
    }

    LuaObject::ReferencePusherPropertyFunction LuaObject::getReferencePusher(FProperty* prop) {
        auto cls = prop->GetClass();
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        constexpr auto StructCastFlag = CASTCLASS_UStructProperty;
        constexpr auto ArrayCastFlag = CASTCLASS_UArrayProperty;

        if (cls->HasAnyCastFlag(StructCastFlag | ArrayCastFlag)) {
            if (cls->HasAnyCastFlag(StructCastFlag)) {
                auto sp = static_cast<FStructProperty*>(prop);
                if (sp && sp->Struct == FSluaBPVar::StaticStruct())
                    return nullptr;
            }
            else {
                auto arrayProp = static_cast<FArrayProperty*>(prop);
                if (isBinStringProperty(arrayProp->Inner)) {
                    return nullptr;
                }
            }
        }
#else
        constexpr auto StructCastFlag = CASTCLASS_FStructProperty;
        constexpr auto ArrayCastFlag = CASTCLASS_FArrayProperty;

        if (cls->HasAnyCastFlags(StructCastFlag | ArrayCastFlag)) {
            if (cls->HasAnyCastFlags(StructCastFlag)) {
                auto sp = static_cast<FStructProperty*>(prop);
                if (sp && sp->Struct == FLuaBPVar::StaticStruct())
                    return nullptr;
            }
            else if (cls->HasAnyCastFlags(ArrayCastFlag)) {
                auto arrayProp = static_cast<FArrayProperty*>(prop);
                if (isBinStringProperty(arrayProp->Inner)) {
                    return nullptr;
                }
            }
        }
#endif
        return getReferencePusher(cls);
    }

    void regPusher(FFieldClass* cls,LuaObject::PushPropertyFunction func) {
        pusherMap.Add(cls, func);
    }

    void regChecker(FFieldClass* cls,LuaObject::CheckPropertyFunction func) {
        checkerMap.Add(cls, func);
    }

    void regReferencer(FFieldClass* cls,LuaObject::ReferencePropertyFunction func) {
        referencerMap.Add(cls, func);
    }

    void regReferencePusher(FFieldClass* cls,LuaObject::ReferencePusherPropertyFunction func) {
        referencePusherMap.Add(cls, func);
    }

    int classConstruct(lua_State* L) {
        UClass* cls = LuaObject::checkValue<UClass*>(L, 1);
        UObject* outter = LuaObject::checkValueOpt<UObject*>(L, 2, (UObject*)GetTransientPackage());
        if (cls && !outter->IsA(cls->ClassWithin)) {
            luaL_error(L, "Can't create object in %s", TCHAR_TO_UTF8(*outter->GetClass()->GetName()));
        }
        FName name = LuaObject::checkValueOpt<FName>(L, 3, FName(NAME_None));
        if(cls) {
            UObject* obj = NewObject<UObject>(outter,cls,name);
            if(obj) {
                LuaObject::push(L,obj,true);
                return 1;
            }
        }
        return 0;
    }

    void cacheFunction(lua_State* L, UClass* cls)
    {
        int t = lua_type(L, 1);
        if (t == LUA_TUSERDATA)
        {
            if (cls)
            {
                if (lua_getuservalue(L, 1) == LUA_TNIL) {
                    lua_pop(L, 1);
                    lua_newtable(L);
                    lua_setuservalue(L, 1);
                    L->top++;
                }
                lua_pushvalue(L, 2);
                lua_pushvalue(L, -3);
                lua_rawset(L, -3);

                lua_pop(L, 1);
            }
            else if (lua_getmetatable(L, 1))
            {
                lua_pushvalue(L, 2);
                lua_pushvalue(L, -3);
                lua_rawset(L, -3);

                lua_pop(L, 1);
            }
        }
        else if (t == LUA_TTABLE)
        {
            lua_pushvalue(L, 2);
            lua_pushvalue(L, -2);
            lua_rawset(L, 1);
        }
    }

    int searchExtensionMethod(lua_State* L,UClass* cls,const char* name,bool isStatic=false) {
        int ret = 0;
        // search class and its super
        while(cls!=nullptr) {
            TMap<FString,ExtensionField>* mapptr = isStatic?extensionMMap_static.Find(cls):extensionMMap.Find(cls);
            if(mapptr!=nullptr) {
                // find field
                auto fieldptr = mapptr->Find(name);
                if (fieldptr != nullptr) {
                    // is function
                    if (fieldptr->isFunction) {
                        lua_pushcfunction(L, fieldptr->func);
                        ret = 1;
                        break;
                    } 
                    // is property
                    else {
                        if (!fieldptr->getter) luaL_error(L, "Property %s is set only", name);
                        lua_pushcfunction(L, fieldptr->getter);
                        if (!isStatic) {
                            lua_pushvalue(L, 1); // push self
                            lua_call(L, 1, 1);
                        } else 
                            lua_call(L, 0, 1);
                        return 1;
                    }
                }
            }
            cls=cls->GetSuperClass();
        }

        if (ret)
        {
            cacheFunction(L, isStatic ? cls : nullptr);
        }
        return ret;
    }

    int searchExtensionMethod(lua_State* L,UObject* o,const char* name,bool isStatic=false) {
        auto cls = o->GetClass();
        return searchExtensionMethod(L,cls,name,isStatic);
    }

    int classIndex(lua_State* L) {
        if (lua_getuservalue(L, 1) != LUA_TNIL) {
            lua_pushvalue(L, 2);
            if (lua_rawget(L, -2)) {
                return 1;
            }
        }
        lua_pop(L, 1);

        UClass* cls = LuaObject::checkValue<UClass*>(L, 1);
        const char* name = lua_tostring(L, 2);

        // get blueprint member
        UFunction* func = cls->FindFunctionByName(ANSI_TO_TCHAR(name));
        if (func) {
            return LuaObject::push(L, func, cls);
        }
        return searchExtensionMethod(L,cls,name,true);
    }

    int structConstruct(lua_State* L) {
        UScriptStruct* uss = LuaObject::checkValue<UScriptStruct*>(L, 1);
        if(uss) {
            uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;
            uint8* buf = (uint8*)FMemory::Malloc(size);
            uss->InitializeStruct(buf);
            LuaStruct* ls = new LuaStruct();
            ls->Init(buf, size, uss, false);
            LuaObject::push(L,ls);
            LuaObject::addLink(L,buf);
            return 1;
        }
        return 0;
    }

    int luaFunctionCall(lua_State* L, UObject* obj, UFunction* func, int paramOffset, int paramCount) {
        if (func->FunctionFlags & FUNC_Net) {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            int functionCallspace = obj->GetFunctionCallspace(func, nullptr, nullptr);
#else
            int functionCallspace = obj->GetFunctionCallspace(func, nullptr);
#endif
            if (functionCallspace != FunctionCallspace::Local) {
                return -1;
            }
        }

        auto* table = ULuaOverrider::getObjectLuaTable(obj, L);
        if (table && table->getState() == L->l_G->mainthread) {
            LuaVar luaFunc = ULuaOverrider::getLuaFunction(L, obj, table, func->GetName());
            if (luaFunc.isFunction()) {
                int resultTop = lua_gettop(L);
                luaFunc.push(L);

                table->push(L);
                for (int i = paramOffset; i <= paramCount; i++) {
                    lua_pushvalue(L, i);
                }
                lua_call(L, paramCount - paramOffset + 2, LUA_MULTRET);

                return lua_gettop(L) - resultTop;
            }
        }

        return -1;
    }
   
    int ufuncClosure(lua_State* L) {
        int paramCount = lua_gettop(L);
        lua_pushvalue(L,lua_upvalueindex(1));
        void* ud = lua_touserdata(L, -1);
        lua_pop(L, 1); // pop ud of func
        
        if(!ud) luaL_error(L, "Call ufunction error");

        auto* funcAcc = reinterpret_cast<LuaFunctionAccelerator*>(ud);
        auto func = funcAcc->func;
#if !UE_BUILD_SHIPPING
        //PROFILER_WATCHER_X(ufuncClosure, TCHAR_TO_UTF8(*FString::Printf(TEXT("%s::%s"), *func->GetOuterUClass()->GetName(), *func->GetName())));
#endif

        lua_pushvalue(L,lua_upvalueindex(2));
        UClass* cls = reinterpret_cast<UClass*>(lua_touserdata(L, -1));
        lua_pop(L,1); // pop staticfunc flag
        
        UObject* obj;
        int offset=1;
        // use ClassDefaultObject if is static function call 
        if(cls) obj = cls->ClassDefaultObject;
        // use obj instance if is member function call
        // and offset set 2 to skip self
        else {
            obj = LuaObject::checkValue<UObject*>(L, 1);
            if (!obj) {
                luaL_error(L, "arg 1 expect UObject, but got nil!");
            }
            offset++;
        }

        if (funcAcc->bLuaOverride)
        {
            int ret = luaFunctionCall(L, obj, func, offset, paramCount);
            if (ret > -1) {
                return ret;
            }
        }

        bool isLatentFunction;
        int outParamCount;
        {
            NewObjectRecorder objectRecorder(L);
            outParamCount = funcAcc->call(L, offset, obj, isLatentFunction, &objectRecorder);
        }

        if (isLatentFunction)
            return lua_yield(L, outParamCount);
        return outParamCount;
    }

    FProperty* LuaObject::findCacheProperty(lua_State* L, UStruct* cls, const char* pname)
    {
        if (pname == nullptr)
        {
            return nullptr;
        }

        auto state = LuaState::get(L);
        return state->classMap.findProp(cls, pname);
    }

    int getTableMember(lua_State* L, const LuaVar& table, int keyIndex)
    {
        ensure(keyIndex > 0);
        
        table.push(L);
        lua_pushvalue(L, keyIndex);
        int t = lua_rawget(L, -2);
        if (t == LUA_TNIL)
        {
            lua_pop(L, 1);

            int type = luaL_getmetafield(L, -1, "__index");
            if (type == LUA_TFUNCTION)
            {
                // get metatable __index function's upvalue[0]
#if LUA_VERSION_NUM > 503
                TValue* v = s2v(L->top - 1);
                CClosure* f = clCvalue(v);
#else
                CClosure* f = clCvalue(L->top - 1);
#endif
                setobj2s(L, L->top - 1, &f->upvalue[0]);

                lua_pushvalue(L, -2); // push self table
                lua_pushvalue(L, keyIndex); // push key
                lua_call(L, 2, 1);
                
                t = lua_type(L, -1); // get return value type
            }
        }

        lua_remove(L, -2);
        return t;
    }

    int luaFuncClosure(lua_State* L) {
        int argsCount = lua_gettop(L);
        lua_pushvalue(L, lua_upvalueindex(1));

        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        if (!obj) {
            luaL_error(L, "arg 1 expect UObject, but got nil!");
        }
        auto* table = ULuaOverrider::getObjectLuaTable(obj, L);
        if (!table) {
            luaL_error(L, "arg 1 expect table, but got nil!");
        }

        int retCountFix = 0;
        if (lua_type(L, -1) == LUA_TSTRING) {
            if (getTableMember(L, *table, argsCount + 1) != LUA_TFUNCTION) {
                luaL_error(L, "can't find lua function %s", lua_tostring(L, -2));
            }
            retCountFix = 1;
        }
        
        table->push(L);

        for (int i = 2; i <= argsCount; ++i) {
            lua_pushvalue(L, i);
        }

        lua_call(L, argsCount, LUA_MULTRET);
        int retCount = lua_gettop(L) - argsCount - retCountFix;
        return retCount;
    }

    int LuaObject::fastIndex(lua_State* L, uint8* parent, UStruct* cls)
    {
        switch (lua_type(L, 1)) 
        {
        case LUA_TUSERDATA:
            if (lua_getuservalue(L, 1) != LUA_TNIL) 
            {
                lua_pushvalue(L, 2);
                if (lua_rawget(L, -2) != LUA_TNIL)
                {
                    return 1;
                }
                L->top--;
            
                if (lua_getmetatable(L, -1)) 
                {
                    lua_pushvalue(L, 2);
                    int cacheType = lua_rawget(L, -2);
                    if (cacheType == LUA_TFUNCTION) {
#if LUA_VERSION_NUM > 503
                        TValue* v = s2v(L->top - 1);
                        CClosure* f = clCvalue(v);
#else
                        CClosure* f = clCvalue(L->top - 1);
#endif

                        auto prop = (FProperty*)pvalue(&f->upvalue[0]);
                        void* pusher = pvalue(&f->upvalue[1]);
                        bool bReferencePusher = !!bvalue(&f->upvalue[3]);
                        if (bReferencePusher)
                        {
                            auto ud = reinterpret_cast<GenericUserData*>(lua_touserdata(L, 1));
                            void* parentAddress = ud->parent ? ud->parent : parent;
                            return pushReferenceAndCache((ReferencePusherPropertyFunction)pusher, L,
                                                         prop->GetOwnerClass(), prop,
                                                         parent + prop->GetOffset_ForInternal(), parentAddress, InvalidReplicatedIndex);
                        }
                        else
                        {
                            return ((PushPropertyFunction)pusher)(L, prop, parent + prop->GetOffset_ForInternal(), nullptr);
                        }
                    }
                    lua_pop(L, 2);
                }

            }

            lua_pop(L, 1);
            break;
        case LUA_TTABLE:
            lua_pushstring(L, LuaOverrider::CACHE_NAME);
            if (lua_rawget(L, 1)) {
                lua_pushvalue(L, 2);
                if (lua_rawget(L, -2) != LUA_TNIL)
                {
                    return 1;
                }
                L->top--;

                if (lua_getmetatable(L, -1))
                {
                    lua_pushvalue(L, 2);
                    int cacheType = lua_rawget(L, -2);
                    if (cacheType == LUA_TFUNCTION) {
#if LUA_VERSION_NUM > 503
                        TValue* v = s2v(L->top - 1);
                        CClosure* f = clCvalue(v);
#else
                        CClosure* f = clCvalue(L->top - 1);
#endif

                        auto prop = (FProperty*)pvalue(&f->upvalue[0]);
                        void* pusher = pvalue(&f->upvalue[1]);
                        bool bReferencePusher = !!bvalue(&f->upvalue[3]);
                        if (bReferencePusher)
                        {
                            return pushReferenceAndCache((ReferencePusherPropertyFunction)pusher, L,
                                                         cls, prop,
                                                         parent + prop->GetOffset_ForInternal(), parent, InvalidReplicatedIndex);
                        }
                        else
                        {
                            return ((PushPropertyFunction)pusher)(L, prop, parent + prop->GetOffset_ForInternal(), nullptr);
                        }
                    }
                    lua_pop(L, 2);
                }
            }
            lua_pop(L, 1);
            break;
        default:
            break;
        }
        
        return 0;
    }

    int LuaObject::fastNewIndex(lua_State* L, uint8* parent)
    {
        switch (lua_type(L, 1))
        {
        case LUA_TUSERDATA:
            if (lua_getuservalue(L, 1) != LUA_TNIL) 
            {
                if (lua_getmetatable(L, -1)) 
                {
                    lua_pushvalue(L, 2);
                    int cacheType = lua_rawget(L, -2);
                    if (cacheType == LUA_TFUNCTION) {
#if LUA_VERSION_NUM > 503
                        TValue* v = s2v(L->top - 1);
                        CClosure* f = clCvalue(v);
#else
                        CClosure* f = clCvalue(L->top - 1);
#endif

                        auto prop = (FProperty*)pvalue(&f->upvalue[0]);
                        auto checker = (CheckPropertyFunction)pvalue(&f->upvalue[2]);
                        checker(L, prop, parent + prop->GetOffset_ForInternal(), 3, true);
                        lua_pop(L, 2);
                        return 1;
                    }
                    lua_pop(L, 2);
                    return 0;
                }
            }

            lua_pop(L, 1);
            break;
        case LUA_TTABLE:
            lua_pushstring(L, LuaOverrider::CACHE_NAME);
            if (lua_rawget(L, 1)) {
                if (lua_getmetatable(L, -1))
                {
                    lua_pushvalue(L, 2);
                    int cacheType = lua_rawget(L, -2);
                    if (cacheType == LUA_TFUNCTION) {
#if LUA_VERSION_NUM > 503
                        TValue* v = s2v(L->top - 1);
                        CClosure* f = clCvalue(v);
#else
                        CClosure* f = clCvalue(L->top - 1);
#endif

                        auto prop = (FProperty*)pvalue(&f->upvalue[0]);
                        auto checker = (CheckPropertyFunction)pvalue(&f->upvalue[2]);
                        checker(L, prop, parent + prop->GetOffset_ForInternal(), 3, true);
                        lua_pop(L, 3);
                        return 1;
                    }
                    lua_pop(L, 3);
                    return 0;
                }
            }
            
            lua_pop(L, 1);
            break;
        default:
            break;
        }
        
        return 0;
    }

    int tryGetTableLuaFunc(lua_State* L, UObject* obj)
    {
        auto* objTable = ULuaOverrider::getObjectTable(obj, L);
        if (objTable)
        {
            auto table = &objTable->table;
            if (table->getState() != L->l_G->mainthread)
            {
                return 0;
            }

            int t = getTableMember(L, *table, 2);
            if (t == LUA_TFUNCTION && !lua_iscfunction(L, -1))
            {
                lua_pushvalue(L, 2); // push function name instead of lua function
                lua_pushcclosure(L, luaFuncClosure, 1); // push luaFuncClosure with function name upvalue
                if (!objTable->isInstance)
                {
                    cacheFunction(L, nullptr);
                }
            }

            if (t != LUA_TNIL)
            {
                return 1;
            }

            lua_pop(L, 1); // pop nil value
        }

        return 0;
    }

    int instanceIndex(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        if (int res = LuaObject::fastIndex(L, (uint8*)obj, obj->GetClass()))
        {
            return res;
        }

        const char* name = lua_tostring(L, 2);
        if (name == nullptr) {
            return 0;
        }

        const int ret = LuaObject::objectIndex(L, obj, name);
        if (ret) {
            return ret;
        }

        auto* objTable = ULuaOverrider::getObjectTable(obj, L);
        if (objTable && objTable->table.getState() == L->l_G->mainthread) {
            objTable->table.push(L); // push self table
            if (objTable->isInstance)
            {
                lua_pushstring(L, LuaOverrider::INSTANCE_CACHE_NAME);
                if (lua_rawget(L, -2))
                {
                    lua_pushvalue(L, 2);
                    if (lua_rawget(L, -2) != LUA_TNIL)
                    {
                        return 1;
                    }
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
            }

            lua_pushvalue(L, 2);
            int type = lua_gettable(L, -2);
            if (type != LUA_TNIL) {
                if (type == LUA_TFUNCTION) {
                    if (objTable->isInstance)
                    {
                        lua_pushcclosure(L, luaFuncClosure, 1);
                        // cache instance function in self.__instance_cache
                        lua_pushstring(L, LuaOverrider::INSTANCE_CACHE_NAME);
                        if (lua_rawget(L, -3) == LUA_TNIL)
                        {
                            lua_pop(L, 1);

                            lua_newtable(L);
                            lua_pushstring(L, LuaOverrider::INSTANCE_CACHE_NAME);
                            lua_pushvalue(L, -2);
                            lua_rawset(L, -5);
                        }
                        lua_pushvalue(L, 2);
                        lua_pushvalue(L, -3);
                        lua_rawset(L, -3);
                        
                        lua_pop(L, 1); // pop __instance_cache
                    }
                    else
                    {
                        lua_pop(L, 1); // pop lua function
                        lua_pushvalue(L, 2); // push function name instead of lua function
                        lua_pushcclosure(L, luaFuncClosure, 1); // push luaFuncClosure with function name upvalue

                        cacheFunction(L, nullptr);
                    }
                }
                return 1;
            }
        }
        return 0;
    }

    bool cachePropertyOperator(lua_State* L, FProperty* prop, UStruct* cls, void* pusher, void* checker, bool bReferencePusher)
    {
        int selfType = lua_type(L, 1);
        if (selfType == LUA_TUSERDATA) {
            if (lua_getuservalue(L, 1) == LUA_TNIL) {
                lua_pop(L, 1);
                lua_newtable(L);
                lua_setuservalue(L, 1);
                L->top++;
                LuaObject::setUservalueMeta(L, cls);
            }

            lua_getmetatable(L, -1);
            lua_pushvalue(L, 2);
            lua_pushlightuserdata(L, prop);
            lua_pushlightuserdata(L, pusher);
            lua_pushlightuserdata(L, checker);
            lua_pushboolean(L, !!bReferencePusher);
            lua_pushcclosure(L, instanceIndex, 4);
            lua_rawset(L, -3);
            lua_pop(L, 2);
            return true;
        }
        else if (selfType == LUA_TTABLE) {
            lua_pushstring(L, LuaOverrider::CACHE_NAME);
            if (lua_rawget(L, 1) == LUA_TNIL) {
                L->top--;
                lua_newtable(L);
                LuaObject::setUservalueMeta(L, cls);
                lua_pushstring(L, LuaOverrider::CACHE_NAME);
                lua_pushvalue(L, -2);
                lua_rawset(L, 1);
            }
            lua_getmetatable(L, -1);
            lua_pushvalue(L, 2);
            lua_pushlightuserdata(L, prop);
            lua_pushlightuserdata(L, pusher);
            lua_pushlightuserdata(L, checker);
            lua_pushboolean(L, !!bReferencePusher);
            lua_pushcclosure(L, instanceIndex, 4);
            lua_rawset(L, -3);
            lua_pop(L, 1);
            return true;
        }

        return false;
    }

    int LuaObject::objectIndex(lua_State* L, UObject* obj, const char* name, bool cacheToLua) {
        UClass* cls = obj->GetClass();
        FProperty* up = LuaObject::findCacheProperty(L, cls, name);
        if (up)
        {
            #pragma warning(push)
            #pragma warning(disable : 4996)

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            if (GSluaEnableReference || up->GetClass()->HasAnyCastFlag(ReferenceCastFlags))
#elif ENGINE_MAJOR_VERSION >= 5
            if (GSluaEnableReference || (up->GetCastFlags() & ReferenceCastFlags))
#else
            if (GSluaEnableReference || up->HasAnyCastFlags(ReferenceCastFlags))
#endif
            {
                auto referencePusher = getReferencePusher(up);
                if (referencePusher) {
                    return pushReferenceAndCache(referencePusher, L, cls, up, up->ContainerPtrToValuePtr<uint8>(obj), obj, InvalidReplicatedIndex);
                }
            }

            auto pusher = getPusher(up);
            if (pusher) {
                cachePropertyOperator(L, up, cls, (void*)pusher, (void*)getChecker(up), false);
                return pusher(L, up, up->ContainerPtrToValuePtr<uint8>(obj), nullptr);
            }
            else {
                FString clsName = up->GetClass()->GetName();
                FString propName = up->GetName();
                luaL_error(L, "unsupport type %s to push, prop:%s", TCHAR_TO_UTF8(*clsName), TCHAR_TO_UTF8(*propName));
                return 0;
            }

            #pragma warning(pop)
        }

        // get blueprint member
        FName wname(ANSI_TO_TCHAR(name));
        UFunction* func = cls->FindFunctionByName(wname);
        if (!func) {
            // search extension method
            return searchExtensionMethod(L, obj, name);
        }
        else {
            if (!(func->FunctionFlags & FUNC_Net))
            {
                if (lua_type(L, 1) == LUA_TTABLE)
                {
                    int top = lua_gettop(L);
        
                    lua_pushvalue(L, lua_upvalueindex(1));
                    lua_pushvalue(L, 1);
                    lua_pushvalue(L, 2);
                    lua_call(L, 2, 1);

                    int retCount = lua_gettop(L) - top;
                    if (retCount > 0)
                    {
                        if (lua_type(L, -retCount) == LUA_TFUNCTION)
                        {
                            return retCount;
                        }
                        lua_pop(L, retCount);
                    }
                }
                else if (int res = tryGetTableLuaFunc(L, obj))
                {
                    return res;
                }
            }
            return LuaObject::push(L, func);
        }
    }

    bool LuaObject::objectNewIndex(lua_State* L, UObject* obj, const char* name, int valueIdx, bool checkValid)
    {
        UClass* cls = obj->GetClass();
        FProperty* up = findCacheProperty(L, cls, name);
        if (!up) {
            if (checkValid)
                luaL_error(L, "Property %s not found", name);
            else
                return false;
        }

        auto checker = LuaObject::getChecker(up);
        if (!checker) luaL_error(L, "Property %s type is not support", name);

        bool bReferencePusher = false;
        void* pusher = nullptr;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        if (GSluaEnableReference || up->GetClass()->HasAnyCastFlag(ReferenceCastFlags))
#elif ENGINE_MAJOR_VERSION >= 5
        if (GSluaEnableReference || (up->GetCastFlags() & ReferenceCastFlags))
#else
        if (GSluaEnableReference || up->HasAnyCastFlags(ReferenceCastFlags))
#endif
        {
            pusher = (void*)getReferencePusher(up);
            bReferencePusher = pusher != nullptr;
        }

        if (!pusher)
        {
            pusher = (void*)getPusher(up);
        }

        cachePropertyOperator(L, up, cls, pusher, (void*)checker, bReferencePusher);

        // set property value
        checker(L, up, up->ContainerPtrToValuePtr<uint8>(obj), valueIdx, true);
        return true;
    }

    int newinstanceIndex(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        if (LuaObject::fastNewIndex(L, (uint8*)obj))
        {
            return 0;
        }

        const char* name = lua_tostring(L, 2);
        if (!LuaObject::objectNewIndex(L, obj, name, 3, false)) {
            auto* table = ULuaOverrider::getObjectLuaTable(obj, L);
            if (table) {
                table->push(L);
                // push key
                lua_pushvalue(L, 2);
                // push value
                lua_pushvalue(L, 3);
                // set table[key]=value
                lua_settable(L, -3);
                lua_pop(L, 1);
            }
        }
        return 0;
    }

    int instanceObjectNext(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);

        FProperty* up = nullptr;
        UClass* cls = obj->GetClass();

        lua_settop(L, 2);
        if (lua_isnil(L, 2)) {
            up = cls->PropertyLink;
        }
        else {
            const char* name = lua_tostring(L, 2);
            FProperty* current = LuaObject::findCacheProperty(L, cls, name);

            if (current) {
                up = current->PropertyLinkNext;
            }
        }

        if (up == nullptr) {
            lua_pushnil(L);
            return 1;
        }

        lua_pop(L, 1); // pop previous key to compatible with LuaObject::pushReferenceAndCache method

        FString key = up->GetName();
        lua_pushstring(L, TCHAR_TO_UTF8(*key));

        if (int res = LuaObject::fastIndex(L, (uint8*)obj, obj->GetClass()))
        {
            lua_pushvalue(L, 2);
            lua_pushvalue(L, -2);
            return res + 1;
        }

        return LuaObject::push(L, up, obj, nullptr) + 1;
    }

    int instanceObjectPairs(lua_State* L) {
        lua_pushcfunction(L, instanceObjectNext);
        lua_pushvalue(L, 1);
        lua_pushnil(L);

        return 3;
    }

    int instanceStructIndex(lua_State* L) {
        LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, 1);
        if (int res = LuaObject::fastIndex(L, ls->buf, ls->uss))
        {
            return res;
        }

        const char* name = lua_tostring(L, 2);
        
        auto* cls = ls->uss;
        FProperty* up = LuaObject::findCacheProperty(L, cls, name);
        if(!up) {
            // index self metatable.
            lua_getmetatable(L, 1);
            lua_pushvalue(L, 2);
            if (lua_gettable(L, -2)) {
                return 1;
            }
            return 0;
        }

        if (GSluaEnableReference)
        {
            auto referencePusher = LuaObject::getReferencePusher(up);
            if (referencePusher) {
                auto ud = reinterpret_cast<GenericUserData*>(lua_touserdata(L, 1));
                void* parent = ud->parent ? ud->parent : ls->buf;

                return LuaObject::pushReferenceAndCache(referencePusher, L, ls->uss, up, ls->buf + up->GetOffset_ForInternal(), parent, ls->luaReplicatedIndex);
            }
        }

        auto pusher = LuaObject::getPusher(up);
        if (pusher) {
            cachePropertyOperator(L, up, cls, (void*)pusher, (void*)LuaObject::getChecker(up), false);
            return pusher(L, up, ls->buf + up->GetOffset_ForInternal(), nullptr);
        }
        else {
            FString clsName = up->GetClass()->GetName();
            FString propName = up->GetName();
            luaL_error(L, "unsupport type %s to push, prop:%s", TCHAR_TO_UTF8(*clsName), TCHAR_TO_UTF8(*propName));
            return 0;
        }
    }

    int newinstanceStructIndex(lua_State* L) {
        LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, 1);
        if (LuaObject::fastNewIndex(L, ls->buf))
        {
            auto proxy = ls->proxy;
            if (proxy)
            {
                proxy->dirtyMark.Add(ls->luaReplicatedIndex);
                proxy->assignTimes++;
            }
            return 0;
        }
        const char* name = lua_tostring(L, 2);

        auto* cls = ls->uss;
        FProperty* up = LuaObject::findCacheProperty(L, cls, name);
        if (!up) luaL_error(L, "Can't find property named %s", name);

        auto checker = LuaObject::getChecker(up);
        if(!checker) luaL_error(L,"Property %s type is not support",name);

        bool bReferencePusher = false;
        void* pusher = nullptr;

        if (GSluaEnableReference)
        {
            pusher = (void*)LuaObject::getReferencePusher(up);
            bReferencePusher = pusher != nullptr;
        }

        if (!pusher)
        {
            pusher = (void*)LuaObject::getPusher(up);
        }

        cachePropertyOperator(L, up, cls, pusher, (void*)checker, bReferencePusher);
        checker(L, up, ls->buf + up->GetOffset_ForInternal(), 3, true);

        auto proxy = ls->proxy;
        if (proxy)
        {
            proxy->dirtyMark.Add(ls->luaReplicatedIndex);
            proxy->assignTimes++;
        }
        return 0;
    }

    FString getPropertyFriendlyName(FProperty* prop) {
        if (prop->IsNative()) {
            return prop->GetName();
        }

        FString fieldName = prop->GetName();

        int index = fieldName.Len();
        for (int i = 0; i < 2; ++i) {
            int findIndex = fieldName.Find(TEXT("_"), ESearchCase::CaseSensitive, ESearchDir::FromEnd, index);
            if (findIndex != INDEX_NONE) {
                index = findIndex;
            }
        }

        return fieldName.Left(index);
    }

    int instanceStructNext(lua_State* L) {
        LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, 1);
        
        auto* cls = ls->uss;
        FProperty* up = nullptr;

        lua_settop(L, 2);
        if (lua_isnil(L, 2)) {
            up = cls->PropertyLink;
        }
        else {
            const char* name = lua_tostring(L, 2);
            FProperty* current = LuaObject::findCacheProperty(L, cls, name);
            if (current) {
                up = current->PropertyLinkNext;
            }
        }

        if (up == nullptr) {
            lua_pushnil(L);
            return 1;
        }

        lua_pop(L, 1); // pop previous key to compatible with LuaObject::pushReferenceAndCache method

        FString key = getPropertyFriendlyName(up);
        lua_pushstring(L, TCHAR_TO_UTF8(*key));

        if (int res = LuaObject::fastIndex(L, ls->buf, ls->uss))
        {
            lua_pushvalue(L, 2);
            lua_pushvalue(L, -2);
            return res + 1;
        }

        return LuaObject::push(L, up, ls->buf + up->GetOffset_ForInternal(), nullptr) + 1;
    }

    int instanceStructPairs(lua_State* L) {
        lua_pushcfunction(L, instanceStructNext);
        lua_pushvalue(L, 1);
        lua_pushnil(L);

        return 3;
    }

    int instanceStructClone(lua_State* L) {
        LuaStruct* luaStruct = LuaObject::checkValue<LuaStruct*>(L, 1);
        auto uss = luaStruct->uss;

        uint32 size = luaStruct->size;
        uint8* buf = (uint8*)FMemory::Malloc(size);
        uss->InitializeStruct(buf);
        uss->CopyScriptStruct(buf, luaStruct->buf);
        
        LuaStruct* luaStructCopy = new LuaStruct();
        luaStructCopy->Init(buf, size, uss, false);
        int ret = LuaObject::push(L, luaStructCopy);
        LuaObject::addLink(L,buf);
        return ret;
    }

    int instanceIndexSelf(lua_State* L) {
        lua_getmetatable(L,1);

        lua_pushvalue(L, 2); // push key name
        lua_gettable(L, -2);

        lua_remove(L,-2); // remove mt of ud
        return 1;
    }

    int LuaObject::objectToString(lua_State* L)
    {
        const int BufMax = 128;
        static char buffer[BufMax] = { 0 };
        bool isnil;
        UObject* obj = LuaObject::testudata<UObject>(L, 1, isnil);
        if (obj) {
            auto clsname = obj->GetClass()->GetFName().ToString();
            auto objname = obj->GetFName().ToString();
            snprintf(buffer, BufMax, "%s: %p %s %p",TCHAR_TO_UTF8(*clsname), obj->GetClass(), TCHAR_TO_UTF8(*objname), obj);
        }
        else {
            // if ud isn't a uobject, get __name of metatable to cast it to string
            const void* ptr = lua_topointer(L,1);
            int tt = luaL_getmetafield(L, 1, "__name");
            // should have __name field
            if (tt == LUA_TSTRING) {
                const char* metaname = lua_tostring(L,-1);
                snprintf(buffer, BufMax, "%s: %p", metaname,ptr);
            }
            if (tt != LUA_TNIL)
                lua_pop(L, 1);
        }

        lua_pushstring(L, buffer);
        return 1;
    }

    void LuaObject::setupMetaTable(lua_State* L, const char* tn, lua_CFunction setupmt, lua_CFunction gc)
    {
        if (luaL_newmetatable(L, tn)) {
            if (setupmt)
                setupmt(L);
            if (gc) {
                lua_pushcfunction(L, gc);
                lua_setfield(L, -2, "__gc");
            }
        }
        lua_setmetatable(L, -2);
    }

    void LuaObject::setupMetaTable(lua_State* L, const char* tn, lua_CFunction setupmt, int gc)
    {
        if (luaL_newmetatable(L, tn)) {
            if (setupmt)
                setupmt(L);
            if (gc) {
                lua_pushvalue(L, gc);
                lua_setfield(L, -2, "__gc");
            }
        }
        lua_setmetatable(L, -2);
    }

    void LuaObject::setupMetaTable(lua_State* L, const char* tn, lua_CFunction gc)
    {
        luaL_getmetatable(L, tn);
        if (lua_isnil(L, -1))
            luaL_error(L, "Can't find type %s exported", tn);

        lua_pushcfunction(L, gc);
        lua_setfield(L, -2, "__gc");
        lua_setmetatable(L, -2);
    }

    template<typename T>
    int pushUProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p= (T*)prop;
        return LuaObject::push(L,p->GetPropertyValue(parms));
    }

    int pushEnumProperty(lua_State* L, FProperty* prop, uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FEnumProperty>(prop);
        ensure(p);
        auto p2 = p->GetUnderlyingProperty();
        ensure(p2);
        int i = p2->GetSignedIntPropertyValue(parms);
        return LuaObject::push(L, i);
    }

    int pushUArrayProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FArrayProperty>(prop);
        ensure(p);
        return LuaArray::push(L, p, p->GetPropertyValuePtr(parms));
    }

    int pushUMapProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FMapProperty>(prop);
        ensure(p);
        FScriptMap* v = p->GetPropertyValuePtr(parms);
        return LuaMap::push(L, p->KeyProp, p->ValueProp, v, false);
    }
    
    int pushUSetProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FSetProperty>(prop);
        ensure(p);
        return LuaSet::push(L, p->ElementProp, p->GetPropertyValuePtr(parms), false);
    }

    int pushUWeakProperty(lua_State* L, FProperty* prop, uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FWeakObjectProperty>(prop);
        ensure(p);
        FWeakObjectPtr v = p->GetPropertyValue(parms);
        return LuaObject::push(L, v);
    }

    int pushUSoftObjectProperty(lua_State *L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FSoftObjectProperty>(prop);
        ensure(p);
        FSoftObjectPtr v = p->GetPropertyValue(parms);
        FSoftObjectPtr* softObjectPtr = new FSoftObjectPtr(v);
        return LuaObject::push<FSoftObjectPtr>(L, "FSoftObjectPtr", softObjectPtr, UD_AUTOGC | UD_VALUETYPE);
    }
    
    int pushUSoftClassProperty(lua_State *L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FSoftClassProperty>(prop);
        ensure(p);
        FSoftObjectPtr v = p->GetPropertyValue(parms);
        FSoftObjectPtr* softObjectPtr = new FSoftObjectPtr(v);
        return LuaObject::push<FSoftObjectPtr>(L, "FSoftObjectPtr", softObjectPtr, UD_AUTOGC | UD_VALUETYPE);
    }

    int pushUInterfaceProperty(lua_State *L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FInterfaceProperty>(prop);
        ensure(p);
        auto &scriptInterface = p->GetPropertyValue(parms);
        UObject *obj = scriptInterface.GetObject();
        bool ref = objRecorder ? objRecorder->hasObject(obj) : false;
        return LuaObject::push(L, obj, ref);
    }

    void* checkUArrayProperty(lua_State* L,FProperty* prop,uint8* parms,int i,bool bForceCopy) {
        auto p = CastField<FArrayProperty>(prop);
        ensure(p);
        int type = lua_type(L, i);
        if (type == LUA_TTABLE) {
            int arraySize = lua_rawlen(L, i);
            if (arraySize <= 0)
                return 0;
            int tableIndex = i;
            if (i < 0 && i > LUA_REGISTRYINDEX) {
                tableIndex = i - 1;
            }

            FScriptArrayHelper arrayHelper(p, parms);
            arrayHelper.Resize(arraySize);

            auto checker = LuaObject::getChecker(p->Inner);

            int index = 0;

            lua_pushnil(L);
            while (index < arraySize && lua_next(L, tableIndex) != 0) {
                checker(L, p->Inner, arrayHelper.GetRawPtr(index++), -1, bForceCopy);
                lua_pop(L, 1);
            }
            return nullptr;
        }

        auto scriptArray = (FScriptArray*)parms;
        if (type == LUA_TSTRING && LuaObject::isBinStringProperty(p->Inner)) {
            size_t len;
            uint8* content = (uint8*)lua_tolstring(L, i, &len);
#if ENGINE_MAJOR_VERSION==5
            scriptArray->Add((int32)len, 1, GetPropertyAlignment(p->Inner));
#else
            scriptArray->Add((int32)len, 1);
#endif
            uint8* dest = (uint8*)scriptArray->GetData();
            FMemory::Memcpy(dest, content, len);
            return nullptr;
        }
        CheckUD(LuaArray,L,i);
        if (!UD)
            luaL_error(L, "expect LuaArray at %d, but got nil", i);

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        auto outerFunc = Cast<UFunction>(p->GetOuter());
#else
        auto outerFunc = Cast<UFunction>(p->GetOwnerUObject());
#endif
        if (!bForceCopy && IsReferenceParam(p->PropertyFlags, outerFunc))
        {
            FMemory::Memcpy(scriptArray, UD->get(), sizeof(FScriptArray));
            return UD->get();
        }
        else
        {
            LuaArray::clone(scriptArray,p,UD->get());
            return nullptr;
        }
    }

    void* checkUMapProperty(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FMapProperty>(prop);
        ensure(p);

        if (lua_istable(L, i)) {
            int tableIndex = i;
            if (i < 0 && i > LUA_REGISTRYINDEX) {
                tableIndex = i - 1;
            }
            
            FScriptMapHelper mapHelper(p, parms);

            lua_pushnil(L);
            while (lua_next(L, tableIndex) != 0) {
                FDefaultConstructedPropertyElement tempKey(p->KeyProp);
                FDefaultConstructedPropertyElement tempValue(p->ValueProp);
                auto keyPtr = tempKey.GetObjAddress();
                auto valuePtr = tempValue.GetObjAddress();
                auto keyChecker = LuaObject::getChecker(p->KeyProp);
                auto valueChecker = LuaObject::getChecker(p->ValueProp);
                keyChecker(L, p->KeyProp, (uint8*)keyPtr, -2, bForceCopy);
                valueChecker(L, p->ValueProp, (uint8*)valuePtr, -1, bForceCopy);
                mapHelper.AddPair(keyPtr, valuePtr);
                lua_pop(L, 1);
            }
            return nullptr;
        }

        CheckUD(LuaMap, L, i);
        if (!UD)
            luaL_error(L, "expect LuaMap at %d, but got nil", i);

        auto scriptMap = (FScriptMap*)parms;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        auto outerFunc = Cast<UFunction>(p->GetOuter());
#else
        auto outerFunc = Cast<UFunction>(p->GetOwnerUObject());
#endif
        if (!bForceCopy && IsReferenceParam(p->PropertyFlags, outerFunc))
        {
            FMemory::Memcpy(scriptMap, UD->get(), sizeof(FScriptMap));
            return UD->get();
        }
        else
        {
            LuaMap::clone(scriptMap,p->KeyProp,p->ValueProp,UD->get());
            return nullptr;
        }
    }

    void* checkUSetProperty(lua_State* L, FProperty* prop, uint8* params, int i, bool bForceCopy) {
        auto p = CastField<FSetProperty>(prop);
        ensure(p);

        if (lua_istable(L, i)) {
            int tableIndex = i;
            if (i <0 && i > LUA_REGISTRYINDEX) {
                tableIndex = i - 1;
            }

            FScriptSetHelper SetHelper(p, params);

            lua_pushnil(L);

            const auto ElementChecker = LuaObject::getChecker(p->ElementProp);

            while (lua_next(L, tableIndex) != 0) {
                FDefaultConstructedPropertyElement TempInElement(p->ElementProp);
                const auto ElementPtr = TempInElement.GetObjAddress();
                ElementChecker(L, p->ElementProp, static_cast<uint8*>(ElementPtr), -1, bForceCopy);
                SetHelper.AddElement(ElementPtr);
                lua_pop(L, 1);
            }
            return nullptr;
        }
        CheckUD(LuaSet, L, i);
        if (!UD)
            luaL_error(L, "expect LuaSet at %d, but got nil", i);

        auto scriptSet = (FScriptSet*)params;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        auto outerFunc = Cast<UFunction>(p->GetOuter());
#else
        auto outerFunc = Cast<UFunction>(p->GetOwnerUObject());
#endif
        if (!bForceCopy && IsReferenceParam(p->PropertyFlags, outerFunc))
        {
            FMemory::Memcpy(scriptSet, UD->get(), sizeof(FScriptSet));
            return UD->get();
        }
        else
        {
            LuaSet::clone(scriptSet, p->ElementProp, UD->get());
            return nullptr;
        }
    }

    void referenceUArrayProperty(lua_State* L,FProperty* prop,uint8* src,void* dst) {
        auto p = CastField<FArrayProperty>(prop);
        ensure(p && (p->PropertyFlags & (CPF_ReferenceParm|CPF_OutParm)) && IsRealOutParam(p->PropertyFlags));
        FMemory::Memcpy(dst, src, sizeof(FScriptArray));
    }

    void referenceUMapProperty(lua_State* L,FProperty* prop,uint8* src,void* dst) {
        auto p = CastField<FMapProperty>(prop);
        ensure(p && (p->PropertyFlags & (CPF_ReferenceParm|CPF_OutParm)) && IsRealOutParam(p->PropertyFlags));
        FMemory::Memcpy(dst, src, sizeof(FScriptMap));
    }

    void referenceUSetProperty(lua_State* L,FProperty* prop,uint8* src,void* dst) {
        auto p = CastField<FSetProperty>(prop);
        ensure(p && (p->PropertyFlags & (CPF_ReferenceParm|CPF_OutParm)) && IsRealOutParam(p->PropertyFlags));
        FMemory::Memcpy(dst, src, sizeof(FScriptSet));
    }

    void referenceUStructProperty(lua_State* L,FProperty* prop,uint8* src,void* dst) {
        auto p = CastField<FStructProperty>(prop);
        ensure(p && (p->PropertyFlags & (CPF_ReferenceParm|CPF_OutParm)) && IsRealOutParam(p->PropertyFlags));
        FMemory::Memcpy(dst, src, p->GetSize());
    }

    int referencePusherUArrayProperty(lua_State* L,FProperty* prop,uint8* parms,void* parentAddress,uint16 replicateIndex) {
        auto p = CastField<FArrayProperty>(prop);
        ensure(p);
        
        bool isNetReplicateType = replicateIndex != InvalidReplicatedIndex;
        FLuaNetSerializationProxy* proxy = nullptr;
        if (isNetReplicateType)
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps((UObject*)parentAddress);
            if (classLuaReplciated)
            {
                auto replicateProp = classLuaReplciated->ownerProperty.Get();
                if (replicateProp)
                {
                    FLuaNetSerialization* luaNetSerialization = replicateProp->ContainerPtrToValuePtr<FLuaNetSerialization>(parentAddress);
                    proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                }
            }
        }

        FScriptArray* scriptArray = reinterpret_cast<FScriptArray*>(parms);

        LuaArray* luaArrray = new LuaArray(p, scriptArray, true, proxy, replicateIndex);
        return LuaObject::pushReference<LuaArray*>(L, luaArrray, parentAddress);
    }

    int referencePusherUMapProperty(lua_State* L,FProperty* prop,uint8* parms,void* parentAddress,uint16 replicatedIndex) {
        auto p = CastField<FMapProperty>(prop);
        ensure(p);

        bool isNetReplicateType = replicatedIndex != InvalidReplicatedIndex;
        FLuaNetSerializationProxy* proxy = nullptr;
        if (isNetReplicateType)
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps((UObject*)parentAddress);
            if (classLuaReplciated)
            {
                auto replicateProp = classLuaReplciated->ownerProperty.Get();
                if (replicateProp)
                {
                    FLuaNetSerialization* luaNetSerialization = replicateProp->ContainerPtrToValuePtr<FLuaNetSerialization>(parentAddress);
                    proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                }
            }
        }

        FScriptMap* scriptMap = reinterpret_cast<FScriptMap*>(parms);

        LuaMap* luaMap = new LuaMap(p, scriptMap, true, proxy, replicatedIndex);
        return LuaObject::pushReference<LuaMap*>(L, luaMap, parentAddress);
    }

    int referencePusherUSetProperty(lua_State* L,FProperty* prop,uint8* parms,void* parentAddress,uint16 replicatedIndex) {
        auto p = CastField<FSetProperty>(prop);
        ensure(p);

        bool isNetReplicateType = replicatedIndex != InvalidReplicatedIndex;
        FLuaNetSerializationProxy* proxy = nullptr;
        if (isNetReplicateType)
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps((UObject*)parentAddress);
            if (classLuaReplciated)
            {
                auto replicateProp = classLuaReplciated->ownerProperty.Get();
                if (replicateProp)
                {
                    FLuaNetSerialization* luaNetSerialization = replicateProp->ContainerPtrToValuePtr<FLuaNetSerialization>(parentAddress);
                    proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                }
            }
        }

        FScriptSet* scriptSet = reinterpret_cast<FScriptSet*>(parms);

        LuaSet* luaSet = new LuaSet(p, scriptSet, true, proxy, replicatedIndex);
        return LuaObject::pushReference<LuaSet*>(L, luaSet, parentAddress);
    }

    int referencePusherUStructProperty(lua_State* L,FProperty* prop,uint8* parms,void* parentAddress,uint16 replicatedIndex) {
        auto p = CastField<FStructProperty>(prop);
        ensure(p);

        bool isNetReplicateType = replicatedIndex != InvalidReplicatedIndex;
        FLuaNetSerializationProxy* proxy = nullptr;
        if (isNetReplicateType)
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps((UObject*)parentAddress);
            if (classLuaReplciated)
            {
                auto replicateProp = classLuaReplciated->ownerProperty.Get();
                if (replicateProp)
                {
                    FLuaNetSerialization* luaNetSerialization = replicateProp->ContainerPtrToValuePtr<FLuaNetSerialization>(parentAddress);
                    proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                }
            }
        }

        auto uss = p->Struct;
        SimpleString str(TCHAR_TO_ANSI(*uss->GetStructCPPName()));
        const char* tname = str.c_str();

        luaL_getmetatable(L,tname);
        if (!lua_isnil(L, -1)) {
            size_t userSize = sizeof(GenericUserData);
            if (isNetReplicateType)
            {
                userSize = sizeof(GenericNetStructUserData);
            }
            auto ud = lua_newuserdata(L, userSize);
            if (!ud) luaL_error(L, "out of memory to new ud");
            auto udptr = reinterpret_cast<GenericNetStructUserData* >(ud);
            udptr->parent = parentAddress;
            udptr->ud = parms;
            udptr->flag = UD_NOFLAG;
            if (isNetReplicateType)
            {
                udptr->proxy = proxy;
                udptr->luaReplicatedIndex = replicatedIndex;
                udptr->flag |= UD_NETTYPE;
            }

            lua_pushvalue(L, -2);
            lua_setmetatable(L, -2);
            lua_remove(L, -2); // remove metatable

            LuaObject::linkProp(L, parentAddress, ud);
            return 1;
        }
        else {
            lua_pop(L, 1);
        }

        LuaStruct* ls = new LuaStruct();
        ls->Init(parms, p->GetSize(), uss, true);
        if (isNetReplicateType)
        {
            ls->proxy = proxy;
            ls->luaReplicatedIndex = replicatedIndex;
        }
        return LuaObject::pushReference<LuaStruct*>(L, ls, parentAddress);
    }

    int referencePusherUSoftObjectProperty(lua_State* L,FProperty* prop,uint8* parms,void* parentAddress,uint16 replicateIndex) {
        auto p = CastField<FSoftObjectProperty>(prop);
        ensure(p);
        
        NewUD(FSoftObjectPtr, &p->GetPropertyValue(parms), UD_NOFLAG);
        udptr->parent = parentAddress;
        luaL_getmetatable(L,"FSoftObjectPtr");
        lua_setmetatable(L, -2);
        LuaObject::linkProp(L, parentAddress, ud);
        return 1;
    }

    int referencePusherUSoftClassProperty(lua_State* L,FProperty* prop,uint8* parms,void* parentAddress,uint16 replicateIndex) {
        auto p = CastField<FSoftClassProperty>(prop);
        ensure(p);

        NewUD(FSoftObjectPtr, &p->GetPropertyValue(parms), UD_NOFLAG);
        udptr->parent = parentAddress;
        luaL_getmetatable(L,"FSoftObjectPtr");
        lua_setmetatable(L, -2);
        LuaObject::linkProp(L, parentAddress, ud);
        return 1;
    }

    int pushUStructProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FStructProperty>(prop);
        ensure(p);
        auto uss = p->Struct;

        if (LuaWrapper::pushValue(L, p, uss, parms))
            return 1;

        // Comment For PUBG Mobile
        if (uss == FLuaBPVar::StaticStruct()) {
            ((FLuaBPVar*)parms)->value.push(L);
            return 1;
        }

        uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;
        uint8* buf = (uint8*)FMemory::Malloc(size);
        uss->InitializeStruct(buf);
        uss->CopyScriptStruct(buf, parms);
        
        LuaStruct* ls = new LuaStruct();
        ls->Init(buf, size, uss, false);
        int ret = LuaObject::push(L, ls);
        LuaObject::addLink(L,buf);
        return ret;
    }  

    int pushUDelegateProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FDelegateProperty>(prop);
        ensure(p);
        FScriptDelegate* delegate = p->GetPropertyValuePtr(parms);
        return LuaDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
    }

    int pushUMulticastDelegateProperty(lua_State* L,FProperty* prop,uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FMulticastDelegateProperty>(prop);
        ensure(p);
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        FMulticastScriptDelegate* delegate = p->GetPropertyValuePtr(parms);
#else
        FMulticastScriptDelegate* delegate = const_cast<FMulticastScriptDelegate*>(p->GetMulticastDelegate(parms));
#endif
        return LuaMultiDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
    }

#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
    int pushUMulticastInlineDelegateProperty(lua_State* L,FProperty* prop,uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FMulticastInlineDelegateProperty>(prop);
        ensure(p);
        FMulticastScriptDelegate* delegate = const_cast<FMulticastScriptDelegate*>(p->GetMulticastDelegate(parms));
        return LuaMultiDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
    }

    int pushUMulticastSparseDelegateProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FMulticastSparseDelegateProperty>(prop);
        ensure(p);
        FSparseDelegate* SparseDelegate = (FSparseDelegate*)parms;
        return LuaMultiDelegate::push(L, p, SparseDelegate, p->SignatureFunction, prop->GetNameCPP());
    }
#endif

    void* checkUDelegateProperty(lua_State* L,FProperty* prop,uint8* parms,int i,bool bForceCopy) {
        auto p = CastField<FDelegateProperty>(prop);
        ensure(p);
        CheckUD(UObject,L,i);
        // bind SignatureFunction
        if(auto dobj=Cast<ULuaDelegate>(UD)) dobj->bindFunction(p->SignatureFunction);
        else luaL_error(L,"arg 1 expect an UDelegateObject");

        FScriptDelegate d;
        d.BindUFunction(UD, TEXT("EventTrigger"));

        p->SetPropertyValue(parms,d);
        return nullptr;
    }

#if ENGINE_MAJOR_VERSION==5
    int pushUObjectPtrProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FObjectPtrProperty>(prop);
        ensure(p);
        auto objPtr = p->GetPropertyValue(parms);
        UObject* o = objPtr.Get();
        bool ref = objRecorder ? objRecorder->hasObject(o) : false;
        return LuaObject::push(L, o, ref);
    }
#endif
     
    int pushUObjectProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastField<FObjectProperty>(prop);
        ensure(p);
        UObject* o = p->GetPropertyValue(parms);
        bool ref = objRecorder ? objRecorder->hasObject(o) : false;
        return LuaObject::push(L, o, ref);
    }

    template<typename T>
    void* checkUProperty(lua_State* L,FProperty* prop,uint8* parms,int i,bool bForceCopy) {
        auto p = CastField<T>(prop);
        ensure(p);
        auto value = LuaObject::checkValue<typename T::TCppType>(L,i);
        p->SetPropertyValue(parms, value);
        return nullptr;
    }

    template<>
    void* checkUProperty<FEnumProperty>(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FEnumProperty>(prop);
        ensure(p);
        auto v = (int64)LuaObject::checkValue<int>(L, i);
        p->CopyCompleteValue(parms, &v);
        return nullptr;
    }

    template<>
    void* checkUProperty<FObjectProperty>(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FObjectProperty>(prop);
        ensure(p);
        UObject* arg = LuaObject::checkValue<UObject*>(L, i);
        if (arg && !LuaObject::isUObjectValid(arg))
            luaL_error(L, "arg %d is invalid UObject!", i);
        
        if (arg && arg->GetClass() != p->PropertyClass && !arg->GetClass()->IsChildOf(p->PropertyClass))
            luaL_error(L, "arg %d expect %s, but got %s", i,
                p->PropertyClass ? TCHAR_TO_UTF8(*p->PropertyClass->GetName()) : "", 
                arg->GetClass() ? TCHAR_TO_UTF8(*arg->GetClass()->GetName()) : "");

        p->SetPropertyValue(parms, arg);
        return arg;
    }
    
    bool fillUStructWithTable(lua_State* L, FStructProperty* prop, uint8* params, int i) {
        check(lua_istable(L, i));

        auto uss = prop->Struct;

        for (TFieldIterator<FProperty> it(uss); it; ++it) {
            AutoStack as(L);
            FString fieldName = getPropertyFriendlyName(*it);
            if (lua_getfield(L, i, TCHAR_TO_UTF8(*fieldName)) == LUA_TNIL) {
                continue;
            }
            
            auto checker = LuaObject::getChecker(*it);
            if (checker) {
                checker(L, *it, it->ContainerPtrToValuePtr<uint8>(params), -1, true);
            }
        }

        return true;
    }

    void* checkUStructProperty(lua_State* L,FProperty* prop,uint8* parms,int i,bool bForceCopy) {
        auto p = CastField<FStructProperty>(prop);
        ensure(p);

        auto uss = p->Struct;

        // Comment For PUBG Mobile
        // if it's LuaBPVar
        if (uss == FLuaBPVar::StaticStruct())
            return FLuaBPVar::checkValue(L, p, parms, i);
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        auto outerFunc = Cast<UFunction>(p->GetOuter());
#else
        auto outerFunc = Cast<UFunction>(p->GetOwnerUObject());
#endif
        if (lua_istable(L, i)) {
            // Don't delete this below code: if you wan't strict limit for output parameter, then open it.
            /*if (IsReferenceParam(p->PropertyFlags, outerFunc) && !(p->PropertyFlags & CPF_ConstParm)) {
                luaL_error(L, "reference arg %d expect %s, but got lua table!", i, TCHAR_TO_UTF8(*uss->GetName()));
                return nullptr;
            }*/
            fillUStructWithTable(L, p, parms, i);
            return nullptr;
        }

        bool isLuaStruct = false;
        
        if (lua_getmetatable(L, i)) {
            if (lua_getfield(L, -1, "__name") == LUA_TSTRING) {
                const char* typeName = lua_tostring(L, -1);
                if (strcmp(typeName, "LuaStruct") == 0)
                    isLuaStruct = true;
            }
            lua_pop(L, 2);
        }
        
        LuaStruct* ls = nullptr;
        if (isLuaStruct) {
            auto UD = (UserData<LuaStruct*>*)lua_touserdata(L, i);
            if (UD->flag & UD_HADFREE)
                luaL_error(L, "arg %d had been freed, can't be used", lua_absindex(L, i));

            ls = UD->ud;
        }
        else {
            auto buf = LuaWrapper::checkValue(L, p, uss, parms, i);
            if (buf)
                return buf;
        }

        if(!ls) {
            luaL_error(L, "expect struct but got nil");
        }

        if (p->GetSize() != ls->size)
            luaL_error(L, "expect struct size == %d, but got %d", p->GetSize(), ls->size);
        if (!bForceCopy && IsReferenceParam(p->PropertyFlags, outerFunc)) {
            // shallow copy
            FMemory::Memcpy(parms, ls->buf, p->GetSize());
        }
        else {
            p->CopyCompleteValue(parms, ls->buf);
        }
        return ls->buf;
    }

    const char* LuaObject::getType(lua_State* L, int p) {
        if (!lua_isuserdata(L, p)) {
            lua_pop(L, 1);
            return "";
        }
        int tt = luaL_getmetafield(L, p, "__name");
        if (tt==LUA_TSTRING)
        {
            const char* typeName = lua_tostring(L, -1);
            lua_pop(L, 1);
            return typeName;
        }
        if(tt!=LUA_TNIL)
            lua_pop(L, 1);
        return "";
    }
    
    int pushUClassProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastField<FClassProperty>(prop);
        ensure(p);
        UClass* cls = Cast<UClass>(p->GetPropertyValue(parms));
        return LuaObject::pushClass(L, cls);
    }

    void* checkUClassProperty(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FClassProperty>(prop);
        ensure(p);
        p->SetPropertyValue(parms, LuaObject::checkValue<UClass*>(L, i));
        return nullptr;
    }

    void* checkUSoftObjectProperty(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FSoftObjectProperty>(prop);
        ensure(p);
        auto t = lua_type(L, i);
        if (t == LUA_TSTRING) {
            const char* path = lua_tostring(L, i);
            auto softObjectPtr = FSoftObjectPtr(FSoftObjectPath(UTF8_TO_TCHAR(path)));
            p->SetPropertyValue(parms, softObjectPtr);
            return nullptr;
        }
        auto typeName = LuaObject::getType(L, i);
        if (strcmp(typeName, "UObject") == 0) {
            const UObject* obj = LuaObject::checkUD<UObject>(L, i);;
            if (obj && obj->GetClass() != p->PropertyClass && !obj->GetClass()->IsChildOf(p->PropertyClass))
                luaL_error(L, "arg %d expect %s, but got %s", i,
                    p->PropertyClass ? TCHAR_TO_UTF8(*p->PropertyClass->GetName()) : "", 
                    obj->GetClass() ? TCHAR_TO_UTF8(*obj->GetClass()->GetName()) : "");
            p->SetPropertyValue(parms, FSoftObjectPtr(obj));
        }
        else if (strcmp(typeName, "FSoftObjectPtr") == 0) {
            auto softObjectPtr = LuaObject::checkUD<FSoftObjectPtr>(L, i);
#if WITH_EDITOR
            auto obj = softObjectPtr->LoadSynchronous();
            if (obj && obj->GetClass() != p->PropertyClass && !obj->GetClass()->IsChildOf(p->PropertyClass))
                luaL_error(L, "arg %d expect %s, but got %s", i,
                    p->PropertyClass ? TCHAR_TO_UTF8(*p->PropertyClass->GetName()) : "", 
                    obj->GetClass() ? TCHAR_TO_UTF8(*obj->GetClass()->GetName()) : "");
#endif
            p->SetPropertyValue(parms, *softObjectPtr);
        }
        return nullptr;
    }

    void* checkUSoftClassProperty(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FSoftClassProperty>(prop);
        ensure(p);
        auto t = lua_type(L, i);
        if (t == LUA_TSTRING) {
            const char* path = lua_tostring(L, i);
            auto softObjectPtr = FSoftObjectPtr(FSoftObjectPath(UTF8_TO_TCHAR(path)));
            p->SetPropertyValue(parms, softObjectPtr);
            return nullptr;
        }
        auto typeName = LuaObject::getType(L, i);
        if (strcmp(typeName, "UClass") == 0) {
            const UClass* cls = LuaObject::checkUD<UClass>(L, i);;
            if (cls && cls != p->MetaClass && !cls->IsChildOf(p->MetaClass))
                luaL_error(L, "arg %d expect class of %s, but got %s", i,
                    p->MetaClass ? TCHAR_TO_UTF8(*p->MetaClass->GetName()) : "", 
                    cls ? TCHAR_TO_UTF8(*cls->GetName()) : "");
            p->SetPropertyValue(parms, FSoftObjectPtr(cls));
        }
        else if (strcmp(typeName, "FSoftObjectPtr") == 0) {
            auto softObjectPtr = LuaObject::checkUD<FSoftObjectPtr>(L, i);
#if WITH_EDITOR
            auto cls = Cast<UClass>(softObjectPtr->LoadSynchronous());
            if (cls && cls != p->MetaClass && !cls->IsChildOf(p->MetaClass))
                luaL_error(L, "arg %d expect class of %s, but got %s", i,
                    p->MetaClass ? TCHAR_TO_UTF8(*p->MetaClass->GetName()) : "", 
                    cls ? TCHAR_TO_UTF8(*cls->GetName()) : "");
#endif
            p->SetPropertyValue(parms, *softObjectPtr);
        }
        return nullptr;
    }

    void* checkUInterfaceProperty(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FInterfaceProperty>(prop);
        ensure(p);
        UObject* obj = LuaObject::checkUD<UObject>(L, i);
        void* interfacePtr = obj->GetInterfaceAddress(p->InterfaceClass);
        if (!interfacePtr)
            luaL_error(L, "arg %d expect interface class of %s, but got %s", TCHAR_TO_UTF8(*p->InterfaceClass->GetName()), 
                        obj->GetClass() ? TCHAR_TO_UTF8(*obj->GetClass()->GetName()) : "");
        p->SetPropertyValue(parms, FScriptInterface(obj, interfacePtr));
        return nullptr;
    }

    void* checkUWeakObjectProperty(lua_State* L, FProperty* prop, uint8* parms, int i, bool bForceCopy) {
        auto p = CastField<FWeakObjectProperty>(prop);
        ensure(p);
        const UObject* obj = LuaObject::checkUD<UObject>(L, i);;
        p->SetPropertyValue(parms, FWeakObjectPtr(obj));
        return nullptr;
    }

    // search obj from registry, push cached obj and return true if find it
    bool LuaObject::getObjCache(lua_State* L,void* obj,const char* tn) {
        LuaState* ls = LuaState::get(L);
        ensure(ls->cacheObjRef!=LUA_NOREF);
        if (!getCache(L, obj, ls->cacheObjRef))
            return false;

        // check type of ud matched
        // ensure(checkType(L, -1, tn));
        return true;
    }

    void LuaObject::addRef(lua_State* L,UObject* obj,void* ud,bool ref) {
        auto sl = LuaState::get(L);
        sl->addRef(obj,ud,ref);
    }


    void LuaObject::removeRef(lua_State* L,UObject* obj,void* ud/*=nullptr*/) {
        QUICK_SCOPE_CYCLE_COUNTER(STAT_Lua_RemoveRef);
        auto sl = LuaState::get(L);
        sl->unlinkUObject(obj,ud);
    }

    void LuaObject::addLink(lua_State* L, void* address)
    {
        LuaState* ls = LuaState::get(L);
        ls->addLink(address);
    }

    void LuaObject::releaseLink(lua_State* L, void* address) {
        LuaState* ls = LuaState::get(L);
        ls->releaseLink(address);
    }

    void LuaObject::linkProp(lua_State* L, void* parentAddress, void* prop)
    {
        LuaState* ls = LuaState::get(L);
        ls->linkProp(parentAddress, prop);
    }

    void LuaObject::unlinkProp(lua_State* L, void* prop)
    {
        LuaState* ls = LuaState::get(L);
        ls->unlinkProp(prop);
    }

    void LuaObject::cacheObj(lua_State* L, void* obj) {
        LuaState* ls = LuaState::get(L);
        addCache(L, obj, ls->cacheObjRef);
    }

    void LuaObject::removeObjCache(lua_State * L, void* obj)
    {
        // get cache table
        LuaState* ls = LuaState::get(L);
        removeCache(L, obj, ls->cacheObjRef);
    }

    bool LuaObject::getCache(lua_State* L, const void* obj, int ref)
    {
        lua_geti(L, LUA_REGISTRYINDEX, ref);
        // should be a table
        ensure(lua_type(L, -1) == LUA_TTABLE);
        // push obj as key
        lua_pushlightuserdata(L, const_cast<void*>(obj));
        // get key from table
        lua_rawget(L, -2);
        lua_remove(L, -2); // remove cache table

        if (lua_isnil(L, -1)) 
        {
            lua_pop(L, 1);
            return false;
        }
        return true;
    }

    void LuaObject::addCache(lua_State* L, const void* obj, int ref)
    {
        lua_geti(L, LUA_REGISTRYINDEX, ref);
        lua_pushlightuserdata(L, const_cast<void*>(obj));
        lua_pushvalue(L, -3); // obj userdata
        lua_rawset(L, -3);
        lua_pop(L, 1); // pop cache table
    }

    void LuaObject::removeCache(lua_State* L, const void* obj, int ref)
    {
        // get cache table
        lua_geti(L, LUA_REGISTRYINDEX, ref);
        lua_pushlightuserdata(L, const_cast<void*>(obj));
        // avoid lua table resize
        if (lua_rawget(L, -2) != LUA_TNIL)
        {
            L->top -= 1;
            lua_pushlightuserdata(L, const_cast<void*>(obj));
            lua_pushnil(L);
            // cache[obj] = nil
            lua_rawset(L, -3);
        }
        else
        {
            // pop nil
            L->top -= 1;
        }
        // pop cache table;
        L->top -= 1;
    }
    
    ULatentDelegate* LuaObject::getLatentDelegate(lua_State* L)
    {
        LuaState* ls = LuaState::get(L);
        return ls->getLatentDelegate();
    }

    void LuaObject::createTable(lua_State* L, const char * tn)
    {
        auto ls = LuaState::get(L);
        ensure(ls);
        LuaVar t = ls->createTable(tn);
        t.push(L);
    }


    int LuaObject::pushClass(lua_State* L,UClass* cls) {
        if(!cls) {
            lua_pushnil(L);
            return 1;
        }
        return pushGCObject<UClass*>(L, cls, "UClass", setupClassMT, gcClass, true, nullptr);
    }

    int LuaObject::pushStruct(lua_State* L,UScriptStruct* cls) {
        if(!cls) {
            lua_pushnil(L);
            return 1;
        }    
        return pushGCObject<UScriptStruct*>(L,cls,"UScriptStruct",setupStructMT,gcStructClass,true, nullptr);
    }

    int enumIndex(lua_State* L)
    {
        const char* key = lua_tostring(L, 2);
        lua_pushvalue(L, 1);
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) 
        {
            const char* name = lua_tostring(L, -2);
            if (FPlatformString::Stricmp(key, name) == 0)
            {
                lua_pushvalue(L, 2);
                lua_pushvalue(L, -2);
                lua_rawset(L, 1);
                return 1;
            }

            lua_pop(L, 1);
        }

        return 0;
    }

    int LuaObject::pushEnum(lua_State* L, UEnum* e)
    {
        LuaState* ls = LuaState::get(L);
        ensure(ls->cacheEnumRef!=LUA_NOREF);
        if (getCache(L, e, ls->cacheEnumRef))
            return 1;

        bool isbpEnum = Cast<UUserDefinedEnum>(e) != nullptr;
        // return a enum as table
        lua_newtable(L);
        int num = e->NumEnums();
        for (int i = 0; i < num; i++) {
            FString name;
            // if is bp enum, can't get name as key
            if(isbpEnum)
                name = *FTextInspector::GetSourceString(e->GetDisplayNameTextByIndex(i));
            else
                name = e->GetNameStringByIndex(i);
            int64 value = e->GetValueByIndex(i);
            lua_pushinteger(L, value);
            lua_setfield(L, -2, TCHAR_TO_UTF8(*name));
        }

        if (luaL_newmetatable(L, "UEnum"))
        {
            lua_pushcfunction(L, enumIndex);
            lua_setfield(L, -2, "__index");
        }
        lua_setmetatable(L, -2);

        addCache(L, e, ls->cacheEnumRef);
        return 1;
    }

    int LuaObject::gcObject(lua_State* L) {
        QUICK_SCOPE_CYCLE_COUNTER(Stat_GCUObject);
        void* userdata = lua_touserdata(L, 1);
        CheckUDGC(UObject,L,1);
        removeRef(L,UD,userdata);
        return 0;
    }

    int LuaObject::gcClass(lua_State* L) {
        QUICK_SCOPE_CYCLE_COUNTER(Stat_GCUClass);
        void* userdata = lua_touserdata(L, 1);
        CheckUDGC(UClass,L,1);
        removeRef(L,UD,userdata);
        return 0;
    }

    int LuaObject::gcStructClass(lua_State* L) {
        QUICK_SCOPE_CYCLE_COUNTER(Stat_GCUClass);
        void* userdata = lua_touserdata(L, 1);
        CheckUDGC(UScriptStruct,L,1);
        removeRef(L,UD,userdata);
        return 0;
    }

    int LuaObject::gcStruct(lua_State* L) {
        QUICK_SCOPE_CYCLE_COUNTER(Stat_GCUStruct);
        auto userdata = (UserData<LuaStruct*>*)luaL_testudata(L, 1, "LuaStruct");
        auto ls = userdata->ud;
        if (!userdata->parent && !(userdata->flag & UD_HADFREE))
            releaseLink(L, ls->buf);
        if (ls->isRef) {
            unlinkProp(L, userdata);
        }

        if (DeferGCStruct && !ls->isRef)
        {
            LuaState* luaState = LuaState::get(L);
            luaState->deferGCStruct.Add(ls);
        }
        else
        {
            delete ls;
        }

        return 0;
    }

    int LuaObject::push(lua_State* L, UObject* obj, bool ref, NewObjectRecorder* objRecorder) {
        if (!obj) return pushNil(L);
        static const EClassCastFlags EnumCastFlag = UEnum::StaticClassCastFlags();
        static const EClassCastFlags ClassCastFlag = UClass::StaticClassCastFlags();
        static const EClassCastFlags ScriptStructCastFlag = UScriptStruct::StaticClassCastFlags();
        static const EClassCastFlags NotUObjectCastFlag = EnumCastFlag | ClassCastFlag | ScriptStructCastFlag;
        auto cls = obj->GetClass();
        if (cls->HasAnyCastFlag(NotUObjectCastFlag))
        {
            if (cls->HasAnyCastFlag(EnumCastFlag))
            {
                auto e = Cast<UEnum>(obj);
                return pushEnum(L, e);
            }
            else if (cls->HasAnyCastFlag(ClassCastFlag))
            {
                auto c = Cast<UClass>(obj);
                return pushClass(L, c);
            }
            else if (cls->HasAnyCastFlag(ScriptStructCastFlag))
            {
                auto s = Cast<UScriptStruct>(obj);
                return pushStruct(L, s);
            }

            ensureMsgf(false, TEXT("Imposible code path!"));
            return 0;
        }
        else {
            ref = objRecorder ? objRecorder->hasObject(obj) : ref;
            return pushGCObject<UObject*>(L, obj, "UObject", setupInstanceMT, gcObject, ref, [L, obj]()
            {
                auto ls = LuaState::get(L);
                lua_geti(L, LUA_REGISTRYINDEX, ls->cacheClassFuncRef);

                auto cls = obj->GetClass();
                // push obj as key
                lua_pushlightuserdata(L, cls);

                // get key from table
                if (lua_rawget(L, -2) == LUA_TNIL)
                {
                    lua_pop(L, 1);
                    lua_newtable(L); // function cache metatable

                    lua_getmetatable(L, -3); // get metatable of obj
                    lua_pushnil(L);
                    while (lua_next(L, -2) != 0) 
                    {
                        lua_settable(L, -4);
                        L->top++;
                    }
                    lua_pushstring(L, "__index");
                    lua_pushvalue(L, -3);
                    lua_rawset(L, -4);

                    lua_setmetatable(L, -2); // set metatetable of obj to "function cache metatable"

                    lua_pushlightuserdata(L, cls);
                    lua_pushvalue(L, -2);
                    lua_rawset(L, -4);
                }
                lua_setmetatable(L, -3); // set metatetable of obj to newtable
                lua_pop(L, 1);
            });
        }
    }

    int LuaObject::push(lua_State* L, FWeakObjectPtr ptr) {
        UObject* obj = ptr.Get();
        if (!obj) {
            lua_pushnil(L);
            return 1;
        }
        if (getObjCache(L, obj, "UObject")) return 1;
        int r = pushWeakType(L, new WeakUObjectUD(ptr));
        if (r) {
            addLink(L, obj);
            cacheObj(L, obj);
        }
        return r;
    }

    template<typename T>
    inline void regPusher() {
        pusherMap.Add(T::StaticClass(), pushUProperty<T>);
    }

    template<typename T>
    inline void regChecker() {
        checkerMap.Add(T::StaticClass(), checkUProperty<T>);
    }

    void LuaObject::init(lua_State* L) {
        regPusher<FIntProperty>();
        regPusher<FUInt32Property>();
        regPusher<FInt64Property>();
        regPusher<FUInt64Property>();
        regPusher<FInt16Property>();
        regPusher<FUInt16Property>();
        regPusher<FInt8Property>();
        regPusher<FByteProperty>(); // uint8
        regPusher<FFloatProperty>();
        regPusher<FDoubleProperty>();
        regPusher<FBoolProperty>();
        regPusher<FTextProperty>();
        regPusher<FStrProperty>();
        regPusher<FNameProperty>();
        
        regPusher(FDelegateProperty::StaticClass(), pushUDelegateProperty);
        regPusher(FMulticastDelegateProperty::StaticClass(),pushUMulticastDelegateProperty);
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        regPusher(FMulticastInlineDelegateProperty::StaticClass(),pushUMulticastInlineDelegateProperty);
        regPusher(FMulticastSparseDelegateProperty::StaticClass(), pushUMulticastSparseDelegateProperty);
#endif
#if ENGINE_MAJOR_VERSION==5
        regPusher(FObjectPtrProperty::StaticClass(),pushUObjectPtrProperty);
#endif
        regPusher(FObjectProperty::StaticClass(),pushUObjectProperty);
        regPusher(FArrayProperty::StaticClass(),pushUArrayProperty);
        regPusher(FMapProperty::StaticClass(),pushUMapProperty);
        regPusher(FSetProperty::StaticClass(), pushUSetProperty);
        regPusher(FStructProperty::StaticClass(),pushUStructProperty);
        regPusher(FEnumProperty::StaticClass(), pushEnumProperty);
        regPusher(FClassProperty::StaticClass(), pushUClassProperty);
        regPusher(FWeakObjectProperty::StaticClass(), pushUWeakProperty);
        regPusher(FSoftObjectProperty::StaticClass(), pushUSoftObjectProperty);
        regPusher(FSoftClassProperty::StaticClass(), pushUSoftClassProperty);
        regPusher(FInterfaceProperty::StaticClass(), pushUInterfaceProperty);
        
        regChecker<FIntProperty>();
        regChecker<FUInt32Property>();
        regChecker<FInt64Property>();
        regChecker<FUInt64Property>();
        regChecker<FInt16Property>();
        regChecker<FUInt16Property>();
        regChecker<FInt8Property>();
        regChecker<FByteProperty>(); // uint8
        regChecker<FFloatProperty>();
        regChecker<FDoubleProperty>();
        regChecker<FBoolProperty>();
        regChecker<FNameProperty>();
        regChecker<FTextProperty>();
        regChecker<FObjectProperty>();
        regChecker<FStrProperty>();
        regChecker<FEnumProperty>();

        regChecker(FArrayProperty::StaticClass(),checkUArrayProperty);
        regChecker(FMapProperty::StaticClass(),checkUMapProperty);
        regChecker(FSetProperty::StaticClass(), checkUSetProperty);
        regChecker(FDelegateProperty::StaticClass(),checkUDelegateProperty);
        regChecker(FStructProperty::StaticClass(),checkUStructProperty);
        regChecker(FClassProperty::StaticClass(), checkUClassProperty);
        regChecker(FWeakObjectProperty::StaticClass(), checkUWeakObjectProperty);
        regChecker(FSoftObjectProperty::StaticClass(), checkUSoftObjectProperty);
        regChecker(FSoftClassProperty::StaticClass(), checkUSoftClassProperty);
        regChecker(FInterfaceProperty::StaticClass(), checkUInterfaceProperty);

        regReferencer(FArrayProperty::StaticClass(), referenceUArrayProperty);
        regReferencer(FMapProperty::StaticClass(), referenceUMapProperty);
        regReferencer(FSetProperty::StaticClass(), referenceUSetProperty);
        regReferencer(FStructProperty::StaticClass(), referenceUStructProperty);

        regReferencePusher(FArrayProperty::StaticClass(), referencePusherUArrayProperty);
        regReferencePusher(FMapProperty::StaticClass(), referencePusherUMapProperty);
        regReferencePusher(FSetProperty::StaticClass(), referencePusherUSetProperty);
        regReferencePusher(FStructProperty::StaticClass(), referencePusherUStructProperty);
        regReferencePusher(FSoftObjectProperty::StaticClass(), referencePusherUSoftObjectProperty);
        regReferencePusher(FSoftClassProperty::StaticClass(), referencePusherUSoftClassProperty);
        
        LuaWrapper::initExt(L);
        // For PUBG Mobile
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        LuaEnums::init(L);
#endif
        ExtensionMethod::init();
    }

    int LuaObject::push(lua_State* L,UFunction* func,UClass* cls)  {
        lua_pushlightuserdata(L, LuaFunctionAccelerator::findOrAdd(func));
        if(cls) {
            lua_pushlightuserdata(L, cls);
            lua_pushcclosure(L, ufuncClosure, 2);
        }
        else
            lua_pushcclosure(L, ufuncClosure, 1);

        cacheFunction(L, cls);
        return 1;
    }

    int LuaObject::push(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto pusher = getPusher(prop);
        if (pusher)
            return pusher(L,prop,parms,objRecorder);
        else {
            FString clsName = prop->GetClass()->GetName();
            FString propName = prop->GetName();
            luaL_error(L, "unsupport type %s to push, prop:%s", TCHAR_TO_UTF8(*clsName), TCHAR_TO_UTF8(*propName));
            return 0;
        }
    }

    int LuaObject::push(lua_State* L, FProperty* up, UObject* obj, NewObjectRecorder* objRecorder) {
        #pragma warning(push)
        #pragma warning(disable : 4996)
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        if (GSluaEnableReference || up->GetClass()->HasAnyCastFlag(ReferenceCastFlags))
#elif ENGINE_MAJOR_VERSION >= 5
        if (GSluaEnableReference || (up->GetCastFlags() & ReferenceCastFlags))
#else
        if (GSluaEnableReference || up->HasAnyCastFlags(ReferenceCastFlags))
#endif
        
        {
            auto referencePusher = getReferencePusher(up);
            if (referencePusher) {
                return pushReferenceAndCache(referencePusher, L, obj->GetClass(), up, up->ContainerPtrToValuePtr<uint8>(obj), obj, InvalidReplicatedIndex);
            }
        }

        return push(L, up, up->ContainerPtrToValuePtr<uint8>(obj), objRecorder);
        #pragma warning(pop)
    }

    int LuaObject::push(lua_State* L, LuaStruct* ls) {
        return pushType<LuaStruct*>(L, ls, "LuaStruct", setupInstanceStructMT, gcStruct);
    }

    int LuaObject::push(lua_State* L, LuaArray* array)
    {
        return LuaArray::push(L, array);
    }

    int LuaObject::push(lua_State* L, LuaMap* map)
    {
        return LuaMap::push(L, map);
    }

    int LuaObject::push(lua_State* L, LuaSet* set)
    {
        return LuaSet::push(L, set);
    }

    int LuaObject::push(lua_State* L, double v) {
        lua_pushnumber(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, float v) {
        lua_pushnumber(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, int64 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, uint64 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, int v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, bool v) {
        lua_pushboolean(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, uint32 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, int16 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, uint16 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, int8 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, uint8 v) {
        lua_pushinteger(L, v);
        return 1;
    }

    int LuaObject::push(lua_State* L, const LuaVar& v) {
        return v.push(L);
    }

    int LuaObject::push(lua_State* L, void* ptr) {
        lua_pushlightuserdata(L,ptr);
        return 1;
    }

    int LuaObject::push(lua_State* L, const FText& v) {
        FString str = v.ToString();
        lua_pushstring(L, TCHAR_TO_UTF8(*str));
        return 1;
    }

    int LuaObject::push(lua_State* L, const FString& str) {
        lua_pushstring(L, TCHAR_TO_UTF8(*str));
        return 1;
    }

    int LuaObject::push(lua_State* L, const FName& name) {
        lua_pushstring(L, TCHAR_TO_UTF8(*name.ToString()));
        return 1;
    }

    int LuaObject::push(lua_State* L, const char* str) {
        lua_pushstring(L, str);
        return 1;
    }

    int LuaObject::setupMTSelfSearch(lua_State* L) {
        lua_pushcfunction(L, instanceIndexSelf);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, objectToString);
        lua_setfield(L, -2, "__tostring");
        return 0;
    }


    int LuaObject::setupClassMT(lua_State* L) {
        lua_pushcfunction(L, classConstruct);
        lua_setfield(L, -2, "__call");
        lua_pushcfunction(L, NS_SLUA::classIndex);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, objectToString);
        lua_setfield(L, -2, "__tostring");
        return 0;
    }

    int LuaObject::setupStructMT(lua_State* L) {
        lua_pushcfunction(L, structConstruct);
        lua_setfield(L, -2, "__call");
        lua_pushcfunction(L, objectToString);
        lua_setfield(L, -2, "__tostring");
        return 0;
    }

    int LuaObject::setupInstanceMT(lua_State* L) {
        lua_pushcfunction(L, instanceIndex);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, newinstanceIndex);
        lua_setfield(L, -2, "__newindex");
        lua_pushcfunction(L, objectToString);
        lua_setfield(L, -2, "__tostring");
        lua_pushcfunction(L, instanceObjectNext);
        lua_setfield(L, -2, "__next");
        lua_pushcfunction(L, instanceObjectPairs);
        lua_setfield(L, -2, "__pairs");
        return 0;
    }

    int LuaObject::setupInstanceStructMT(lua_State* L) {
        lua_pushcfunction(L, instanceStructIndex);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, newinstanceStructIndex);
        lua_setfield(L, -2, "__newindex");
        lua_pushcfunction(L, objectToString);
        lua_setfield(L, -2, "__tostring");
        lua_pushcfunction(L, instanceStructNext);
        lua_setfield(L, -2, "__next");
        lua_pushcfunction(L, instanceStructPairs);
        lua_setfield(L, -2, "__pairs");
        lua_pushcfunction(L, instanceStructClone);
        lua_setfield(L, -2, "clone");
        return 0;
    }
}

#ifdef _WIN32
#pragma warning (pop)
#endif
