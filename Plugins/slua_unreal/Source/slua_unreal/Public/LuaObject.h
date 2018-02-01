// The MIT License (MIT)

// Copyright 2015 Siney/Pangweiwei siney@yeah.net
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "lua/lua.hpp"
#include "UObject/WeakObjectPtr.h"
#include <string>

#define CheckUD(Type,L,P) UserData<Type*>* ud = reinterpret_cast<UserData<Type*>*>(luaL_checkudata(L, P,#Type)); \
    if(!ud) { luaL_error(L, "checkValue error at %d",P); } \
    Type* UD = ud->ud; \
    ((void)(UD))

#define CheckUDEX(Type,UD,L,P) UserData<Type*>* UD = reinterpret_cast<UserData<Type*>*>(luaL_checkudata(L, P,#Type)); \
    if(!UD) { luaL_error(L, "checkValue error at %d",P); } \

#define RegMetaMethod(L,METHOD) \
    lua_pushcfunction(L,METHOD); \
    lua_setfield(L,-2,#METHOD);

namespace slua {

    struct AutoStack {
        AutoStack(lua_State* L) {
            this->L = L;
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
    };

    class SLUA_UNREAL_API LuaObject
    {
    public:

        static void init(lua_State* L);
        
        template<class T>
        static T checkValue(lua_State* L,int p);

        typedef void SetupMetaTableFunc(lua_State* L,const char* tn,lua_CFunction setupmt,lua_CFunction gc);

        template<class T>
        static int pushType(lua_State* L,T cls,const char* tn,lua_CFunction setupmt=NULL,lua_CFunction gc=NULL) {
            if(!cls)
                lua_pushnil(L);
                
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdata(L, sizeof(UserData<T>)));
            ud->ud = cls;
            
            setupMetaTable(L,tn,setupmt,gc);
            return 1;
        }

        template<class T>
        static int pushGCObject(lua_State* L,T obj,const char* tn,lua_CFunction setupmt=NULL,lua_CFunction gc=NULL) {
            if(getFromCache(L,obj))
                return 1;
            obj->AddToRoot();
            lua_pushcclosure(L,gc,0);
            lua_pushcclosure(L,removeFromCacheGC,1);
            int f = lua_gettop(L);
            int r = pushType<T>(L,obj,tn,setupmt,f);
            lua_remove(L,f); // remove wraped gc function
            if(r) {
                cacheObj(L,obj);
            }
            return r;
        }
        
        static int pushClass(lua_State* L,UClass* cls);
        static int pushStruct(lua_State* L,UScriptStruct* cls);
        static int push(lua_State* L, UObject* obj);

        static int push(lua_State* L, FScriptDelegate* obj) {
            return pushType<FScriptDelegate*>(L,obj,"FScriptDelegate");
        }

        static int push(lua_State* L, LuaStruct* ls) {
            return pushType<LuaStruct*>(L,ls,"LuaStruct",setupInstanceStructMT,gcStruct);
        }

        static int push(lua_State* L, double v) {
            lua_pushnumber(L,v);
            return 1;
        }

        static int push(lua_State* L, float v) {
            lua_pushnumber(L,v);
            return 1;
        }

        static int push(lua_State* L, int v) {
            lua_pushinteger(L,v);
            return 1;
        }

        static int push(lua_State* L, uint32 v) {
            lua_pushnumber(L,v);
            return 1;
        }

        static int push(lua_State* L, const std::string& v) {
            lua_pushlstring(L,v.c_str(),v.size());
            return 1;
        }

        static int push(lua_State* L, const FText& v) {
            FString str = v.ToString();
            lua_pushstring(L,TCHAR_TO_UTF8(*str));
            return 1;
        }

        static int push(lua_State* L, const FString& str) {
            lua_pushstring(L,TCHAR_TO_UTF8(*str));
            return 1;
        }
        
        static int push(lua_State* L, FScriptArray* array);

        static int push(lua_State* L, UFunction* func);
        static int push(lua_State* L, UProperty* up, uint8* parms);

        static int setupMTSelfSearch(lua_State* L);
        
    private:
        static int setupClassMT(lua_State* L);
        static int setupInstanceMT(lua_State* L);
        static int setupInstanceStructMT(lua_State* L);
        static int setupStructMT(lua_State* L);

        static int gcObject(lua_State* L);
        static int gcClass(lua_State* L);
        static int gcStructClass(lua_State* L);

        static int gcStruct(lua_State* L) {
            CheckUD(LuaStruct,L,1);
            delete UD;
            return 0;
        }

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
            
            setupMetaTable(L,tn,setupmt,gc);
            return 1;
        }

        static int removeFromCacheGC(lua_State* L);

        static bool getFromCache(lua_State* L,void* obj);
        static void cacheObj(lua_State* L,void* obj);
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
    inline const char* LuaObject::checkValue(lua_State* L, int p) {
        return luaL_checkstring(L, p);
    }

    template<>
    inline float LuaObject::checkValue(lua_State* L, int p) {
        return (float)luaL_checknumber(L, p);
    }

    template<>
    inline int LuaObject::checkValue(lua_State* L, int p) {
        return (float)luaL_checkinteger(L, p);
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
}