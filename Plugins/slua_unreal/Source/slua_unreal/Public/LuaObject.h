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
#include "LuaObject.generated.h"


UCLASS()
class SLUA_UNREAL_API ULuaObject : public UObject {
    GENERATED_UCLASS_BODY()
public:
    void AddRef(UObject* obj);
    void Remove(UObject* obj);
private:
    UPROPERTY()
    TArray<UObject*> Cache;
};


#define CheckUD(Type,L,P) UserData<Type*>* ud = reinterpret_cast<UserData<Type*>*>(luaL_checkudata(L, P,#Type)); \
    if(!ud) { luaL_error(L, "checkValue error at %d",P); } \
    Type* UD = ud->ud; \
    ((void)(UD))

#define CheckUDEX(Type,UD,L,P) UserData<Type*>* UD = reinterpret_cast<UserData<Type*>*>(luaL_checkudata(L, P,#Type)); \
    if(!UD) { luaL_error(L, "checkValue error at %d",P); } \

#define RegMetaMethod(L,METHOD) \
    lua_pushcfunction(L,METHOD); \
    lua_setfield(L,-2,#METHOD);

#define NewUD(T, v, o) auto ud = lua_newuserdata(L, sizeof(UserData<T*>)); \
	if (!ud) luaL_error(L, "out of memory to new ud"); \
	auto udptr = reinterpret_cast< UserData<T*>* >(ud); \
	udptr->ud = const_cast<T*>(v); \
    udptr->owned = o;


namespace slua {

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

    template<typename T>
    struct LuaOwnedPtr {
        T* ptr;
        LuaOwnedPtr(T* p):ptr(p) {}
    };

    class SLUA_UNREAL_API LuaObject
    {
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
		static void addMethod(lua_State* L, const char* name, lua_CFunction func, bool isInstance = true);
		static void addField(lua_State* L, const char* name, lua_CFunction getter, lua_CFunction setter, bool isInstance = true);
		static void addOperator(lua_State* L, const char* name, lua_CFunction func);
		static void finishType(lua_State* L, const char* tn, lua_CFunction ctor, lua_CFunction gc);

        static void init(lua_State* L);
        
        template<class T>
		static T checkValue(lua_State* L, int p) {
			if (!lua_isuserdata(L, p))
				luaL_error(L, "excpect userdata at arg %d", p);

			void* ud = lua_touserdata(L, p);
			UserData<T> *udptr = reinterpret_cast<UserData<T>*>(ud);
			return udptr->ud;
		}

        // check value if it's TArray
        template<class T>
		static T checkTArray(lua_State* L, int p) {
            CheckUD(LuaArray,L,p);
			return UD->asTArray<typename T::ElementType>(L);
		}

        template<class T>
        static UObject* checkUObject(lua_State* L,int p) {
            UserData<UObject*>* ud = reinterpret_cast<UserData<UObject*>*>(luaL_checkudata(L, p,"UObject"));
            if(!ud) luaL_error(L, "checkValue error at %d",p);
            return Cast<T>(ud->ud);
        }

		template<class T>
		static int push(lua_State* L, const char* fn, const T* v, bool owned=false) {
			NewUD(T, v, owned);
            luaL_getmetatable(L,fn);
			lua_setmetatable(L, -2);
            return 1;
		}

        typedef void SetupMetaTableFunc(lua_State* L,const char* tn,lua_CFunction setupmt,lua_CFunction gc);

        template<class T>
        static int pushType(lua_State* L,T cls,const char* tn,lua_CFunction setupmt=nullptr,lua_CFunction gc=nullptr) {
            if(!cls) lua_pushnil(L);
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdata(L, sizeof(UserData<T>)));
            ud->ud = cls;
            ud->owned = true;
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
		static int push(lua_State* L, float v);
		static int push(lua_State* L, int v);
		static int push(lua_State* L, bool v);
		static int push(lua_State* L, uint32 v);
		static int push(lua_State* L, void* v);
		static int push(lua_State* L, const FText& v);
		static int push(lua_State* L, const FString& str);
		static int push(lua_State* L, const FName& str);
		static int push(lua_State* L, const char* str);
        static int push(lua_State* L, UFunction* func, UClass* cls=nullptr);
        static int push(lua_State* L, UProperty* up, uint8* parms);


        template<typename T>
        static int push(lua_State* L,T* ptr,typename std::enable_if<!std::is_base_of<UObject,T>::value>::type* = nullptr) {
            return push(L,TypeName<T>::value(),ptr);
        }

        template<typename T>
        static int push(lua_State* L,LuaOwnedPtr<T> ptr) {
            return push(L,TypeName<T>::value(),ptr.ptr,true);
        }

		// static int push(lua_State* L, FScriptArray* array);
        
        static int pushNil(lua_State* L) {
            lua_pushnil(L);
            return 1;
        }

        static void addExtensionMethod(UClass* cls,const char* n,lua_CFunction func);
    private:
        static int setupClassMT(lua_State* L);
        static int setupInstanceMT(lua_State* L);
        static int setupInstanceStructMT(lua_State* L);
        static int setupStructMT(lua_State* L);

        static int gcObject(lua_State* L);
        static int gcClass(lua_State* L);
        static int gcStructClass(lua_State* L);
		static int gcStruct(lua_State* L);

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
            UserData<UObject*>* ud = reinterpret_cast<UserData<UObject*>*>(luaL_checkudata(L, p, "UObject")); 
            if(!ud) goto errorpath;
            return ud->ud;
        }
        else if(lt == LUA_TTABLE) {
            AutoStack g(L);
            lua_getfield(L,p,"__cppinst");
            if(lua_type(L,-1)==LUA_TUSERDATA) {
                UserData<UObject*>* ud = reinterpret_cast<UserData<UObject*>*>(luaL_checkudata(L, -1, "UObject"));
                if(!ud) goto errorpath;
                return ud->ud;
            }
        }
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
    inline int LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checkinteger(L, p);
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