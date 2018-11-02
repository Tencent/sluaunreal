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
#include "CoreMinimal.h"
#include "lua/lua.hpp"
#include "UObject/UnrealType.h"
#include "UObject/WeakObjectPtr.h"
#include "Blueprint/UserWidget.h"
#include "SluaUtil.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaObject.generated.h"


UCLASS()
class SLUA_UNREAL_API ULuaObject : public UObject {
    GENERATED_UCLASS_BODY()
public:
    void AddRef(UObject* obj);
    void Remove(UObject* obj);
private:
    UPROPERTY()
    TMap<UObject*,UObject*> Cache;
};


#define CheckUD(Type,L,P) auto UD = LuaObject::checkUD<Type>(L,P);
#define RegMetaMethodByName(L,NAME,METHOD) \
    lua_pushcfunction(L,METHOD); \
    lua_setfield(L,-2,NAME);

#define RegMetaMethod(L,METHOD) RegMetaMethodByName(L,#METHOD,METHOD)

#define NewUD(T, v, o) auto ud = lua_newuserdata(L, sizeof(UserData<T*>)); \
	if (!ud) luaL_error(L, "out of memory to new ud"); \
	auto udptr = reinterpret_cast< UserData<T*>* >(ud); \
	udptr->ud = const_cast<T*>(v); \
    udptr->owned = o;


namespace slua {

    class LuaVar;

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

    struct LuaStruct {
        uint8* buf;
        uint32 size;
        UScriptStruct* uss;

        LuaStruct(uint8* buf,uint32 size,UScriptStruct* uss);
        ~LuaStruct();
    };

    template<class T>
    struct UserData {
        T ud;
        bool owned;
    };

    template<typename T, bool isUObject = std::is_base_of<UObject,T>::value>
    struct TypeName {
        static const char* value();
    };

    template<typename T>
    struct TypeName<T, true> {
        static const char* value() {
            return "UObject";
        }
    };

    template<typename T, bool isUObject>
    struct TypeName<const T*, isUObject> {
        static const char* value() {
            return TypeName<T>::value();
        }
    };

    #define DefTypeName(T) \
    template<> \
    struct TypeName<T, false> { \
        static const char* value() { \
            return #T;\
        }\
    };\

    DefTypeName(LuaArray);
    DefTypeName(LuaMap);

    template<typename T>
    struct LuaOwnedPtr {
        T* ptr;
        LuaOwnedPtr(T* p):ptr(p) {}
    };

    class SLUA_UNREAL_API LuaObject
    {
    private:

        // testudata, if T is base of uobject but isn't uobject, try to  cast it to T
        template<typename T>
        static typename std::enable_if<std::is_base_of<UObject,T>::value && !std::is_same<UObject,T>::value, T*>::type testudata(lua_State* L,int p) {
            UserData<UObject*>* ptr = (UserData<UObject*>*)luaL_testudata(L,p,"UObject");
            T* t = ptr?Cast<T>(ptr->ud):nullptr;
            if(!t) {
                FString clsname = TEXT("U") + T::StaticClass()->GetName();
                UserData<T*>* tptr = (UserData<T*>*) luaL_testudata(L,p,TCHAR_TO_UTF8(*clsname));
                t = tptr?tptr->ud:nullptr;
            }
            return t;
        }

        // testudata, if T is uobject
        template<typename T>
        static typename std::enable_if<std::is_same<UObject,T>::value, T*>::type testudata(lua_State* L,int p) {
            auto ptr = (UserData<T*>*)luaL_testudata(L,p,"UObject");
            return ptr?ptr->ud:nullptr;
        }

        // testudata, if T isn't uobject
        template<typename T>
        static typename std::enable_if<!std::is_base_of<UObject,T>::value && !std::is_same<UObject,T>::value, T*>::type testudata(lua_State* L,int p) {
            auto ptr = (UserData<T*>*)luaL_testudata(L,p,TypeName<T>::value());
            return ptr?ptr->ud:nullptr;
        }

    public:

        typedef int (*PushPropertyFunction)(lua_State* L,UProperty* prop,uint8* parms);
        typedef int (*CheckPropertyFunction)(lua_State* L,UProperty* prop,uint8* parms,int i);

        static CheckPropertyFunction getChecker(UClass* prop);
        static PushPropertyFunction getPusher(UProperty* prop);
        static CheckPropertyFunction getChecker(UProperty* cls);
        static PushPropertyFunction getPusher(UClass* cls);

		static bool matchType(lua_State* L, int p, const char* tn);

		static int classIndex(lua_State* L);
		static int classNewindex(lua_State* L);

		static void newType(lua_State* L, const char* tn);
        static void newTypeWithBase(lua_State* L, const char* tn, std::initializer_list<const char*> bases);
		static void addMethod(lua_State* L, const char* name, lua_CFunction func, bool isInstance = true);
		static void addGlobalMethod(lua_State* L, const char* name, lua_CFunction func);
		static void addField(lua_State* L, const char* name, lua_CFunction getter, lua_CFunction setter, bool isInstance = true);
		static void addOperator(lua_State* L, const char* name, lua_CFunction func);
		static void finishType(lua_State* L, const char* tn, lua_CFunction ctor, lua_CFunction gc, lua_CFunction strHint=nullptr);

        static void init(lua_State* L);


        


        // check arg at p is exported lua class named __name in field 
        // of metable of the class, if T is base of class or class is T, 
        // return the pointer of class, otherwise return nullptr
        template<typename T>
        static T* checkUD(lua_State* L,int p) {
        
            T* ret = testudata<T>(L,p);
            if(ret) return ret;

            const char *typearg = nullptr;
            if (luaL_getmetafield(L, p, "__name") == LUA_TSTRING)
                typearg = lua_tostring(L, -1);
                
            lua_pop(L,1);

            if(!typearg)
                luaL_error(L,"expect userdata at %d",p);

            if(LuaObject::isBaseTypeOf(L,typearg,TypeName<T>::value()))
                return (T*) lua_touserdata(L,p);
            luaL_error(L,"expect userdata %s, but got %s",TypeName<T>::value(),typearg);
            return nullptr;
        }

		template<class T>
		static T checkValueOpt(lua_State* L, int p, const T& defaultValue) {
			if (lua_isnone(L, p)) {
				return defaultValue;
			} else {
				return checkValue<T>(L, p);
			}
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
				luaL_error(L, "excpect userdata at arg %d", p);

			void* ud = lua_touserdata(L, p);
			UserData<T> *udptr = reinterpret_cast<UserData<T>*>(ud);
			return udptr->ud;
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

        template<class T>
        static UObject* checkUObject(lua_State* L,int p) {
            UserData<UObject*>* ud = reinterpret_cast<UserData<UObject*>*>(luaL_checkudata(L, p,"UObject"));
            if(!ud) luaL_error(L, "checkValue error at %d",p);
            return Cast<T>(ud->ud);
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
		static int push(lua_State* L, const char* fn, const T* v, bool owned=false) {
            if(getFromCache(L,void_cast(v))) return 1;
			NewUD(T, v, owned);
            luaL_getmetatable(L,fn);
			lua_setmetatable(L, -2);
            cacheObj(L,void_cast(v));
            return 1;
		}

        typedef void SetupMetaTableFunc(lua_State* L,const char* tn,lua_CFunction setupmt,lua_CFunction gc);

        template<class T>
        static int pushType(lua_State* L,T cls,const char* tn,lua_CFunction setupmt=nullptr,lua_CFunction gc=nullptr) {
            if(!cls) lua_pushnil(L);
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdata(L, sizeof(UserData<T>)));
            ud->ud = cls;
            ud->owned = gc!=nullptr;
            setupMetaTable(L,tn,setupmt,gc);
            return 1;
        }

        static void addRef(lua_State* L,UObject* obj);
        static void removeRef(lua_State* L,UObject* obj);

        template<typename T>
        static int pushGCObject(lua_State* L,T obj,const char* tn,lua_CFunction setupmt,lua_CFunction gc) {
            if(getFromCache(L,obj)) return 1;
            addRef(L,obj);
            lua_pushcclosure(L,gc,0);
            lua_pushcclosure(L,removeFromCacheGC,1);
            int f = lua_gettop(L);
            int r = pushType<T>(L,obj,tn,setupmt,f);
            lua_remove(L,f); // remove wraped gc function
            if(r) cacheObj(L,obj);
            return r;
        }

        template<typename T>
        static int pushObject(lua_State* L,T obj,const char* tn,lua_CFunction setupmt=nullptr) {
            if(getFromCache(L,obj)) return 1;
            int r = pushType<T>(L,obj,tn,setupmt,nullptr);
            if(r) cacheObj(L,obj);
            return r;
        }

		static int setupMTSelfSearch(lua_State* L);
        
        static int pushClass(lua_State* L,UClass* cls);
        static int pushStruct(lua_State* L,UScriptStruct* cls);
        static int push(lua_State* L, UObject* obj);
		static int push(lua_State* L, FScriptDelegate* obj);
		static int push(lua_State* L, LuaStruct* ls);
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
        static int push(lua_State* L, UProperty* up, uint8* parms);

        // check tn is base of base
        static bool isBaseTypeOf(lua_State* L,const char* tn,const char* base);

        template<typename T>
        static int push(lua_State* L,T* ptr,typename std::enable_if<!std::is_base_of<UObject,T>::value>::type* = nullptr) {
            return push(L,TypeName<T>::value(),ptr);
        }

        template<typename T>
        static int push(lua_State* L,LuaOwnedPtr<T> ptr) {
            return push(L,TypeName<T>::value(),ptr.ptr,true);
        }

        template<typename T>
        static int push(lua_State* L,T v,typename std::enable_if<std::is_enum<T>::value>::type* = nullptr) {
            return push(L,static_cast<int>(v));
        }

		// static int push(lua_State* L, FScriptArray* array);
        
        static int pushNil(lua_State* L) {
            lua_pushnil(L);
            return 1;
        }

        static void addExtensionMethod(UClass* cls,const char* n,lua_CFunction func,bool isStatic=false);

		static UProperty* getDefaultProperty(lua_State* L, UE4CodeGen_Private::EPropertyClass type);

        static UFunction* findCacheFunction(lua_State* L,const FString& cname,const char* fname);
        static void cacheFunction(lua_State* L,const FString& cname,const char* fame,UFunction* func);
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

		static int removeFromCacheGC(lua_State* L);
		static bool getFromCache(lua_State* L, void* obj);
		static void cacheObj(lua_State* L, void* obj);

        static void setupMetaTable(lua_State* L,const char* tn,lua_CFunction setupmt,lua_CFunction gc) {
            if(luaL_newmetatable(L, tn)) {
                if(setupmt)
                    setupmt(L);
                if(gc) {
                    lua_pushcfunction(L,gc);
                    lua_setfield(L,-2,"__gc");
                }
            }
            lua_setmetatable(L, -2);
        }

        static void setupMetaTable(lua_State* L,const char* tn,lua_CFunction setupmt,int gc) {
            if(luaL_newmetatable(L, tn)) {
                if(setupmt)
                    setupmt(L);
                if(gc) {
                    lua_pushvalue(L,gc);
                    lua_setfield(L,-2,"__gc");
                }
            }
            lua_setmetatable(L, -2);
        }

        template<class T>
        static int pushType(lua_State* L,T cls,const char* tn,lua_CFunction setupmt,int gc) {
            if(!cls)
                lua_pushnil(L);
                
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdata(L, sizeof(UserData<T>)));
            ud->ud = cls;
            ud->owned = true;
            
            setupMetaTable(L,tn,setupmt,gc);
            return 1;
        }
    };

    template<>
    inline UClass* LuaObject::checkValue(lua_State* L, int p) {
        CheckUD(UClass, L, p);
        return UD;
    }

    template<>
    inline UObject* LuaObject::checkValue(lua_State* L, int p) {
        int lt = lua_type(L,p);
        if(lt == LUA_TUSERDATA) {
            UObject* ud = checkUD<UObject>(L,p);
            if(!ud) goto errorpath;
            return ud;
        }
        else if(lt == LUA_TTABLE) {
            AutoStack g(L);
            lua_getfield(L,p,"__cppinst");
            if(lua_type(L,-1)==LUA_TUSERDATA) {
                UObject* ud = checkUD<UObject>(L,-1);
                if(!ud) goto errorpath;
                return ud;
            }
        }
        else if(lt == LUA_TNIL)
            return nullptr;
    errorpath:
        luaL_error(L, "checkValue error at %d",p);
        return nullptr;
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