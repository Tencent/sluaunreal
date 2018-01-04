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
    };

    template<class T>
    struct UserData {
        T ud;
    };

    class LuaObject
    {
    public:

        static void init(lua_State* L);
        
        template<class T>
        static T checkValue(lua_State* L,int p);


        template<class T>
        static int pushType(lua_State* L,T cls,const char* tn,lua_CFunction setupmt=NULL,lua_CFunction gc=NULL) {
            if(!cls)
                lua_pushnil(L);
                
            UserData<T>* ud = reinterpret_cast< UserData<T>* >(lua_newuserdata(L, sizeof(UserData<T>)));
            ud->ud = cls;
            
            if(luaL_newmetatable(L, tn)) {
                if(setupmt)
                    setupmt(L);
                if(gc) {
                    lua_pushcfunction(L,gc);
                    lua_setfield(L,-2,"__gc");
                }
            }
            lua_setmetatable(L, -2);
            return 1;
        }
        
        static int pushClass(lua_State* L,UClass* cls) {
            cls->AddToRoot();
            return pushType<UClass*>(L,cls,"UClass",setupClassMT,gcClass);
        }

        static int pushStruct(lua_State* L,UScriptStruct* cls) {
            cls->AddToRoot();            
            return pushType<UScriptStruct*>(L,cls,"UScriptStruct",setupStructMT,gcStructClass);
        }

        static int push(lua_State* L, UObject* obj) {
            obj->AddToRoot();
            return pushType<UObject*>(L,obj,"UObject",setupInstanceMT,gcObject);
        }

        static int push(lua_State* L, FScriptDelegate* obj) {
            return pushType<FScriptDelegate*>(L,obj,"FScriptDelegate");
        }

        static int push(lua_State* L, LuaStruct* ls) {
            return pushType<LuaStruct*>(L,ls,"LuaStruct",setupInstanceMT,gcStruct);
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

        static int push(lua_State* L, const FText& v) {
            FString str = v.ToString();
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
        static int setupStructMT(lua_State* L);

        static int gcObject(lua_State* L) {
            CheckUD(UObject,L,1);
            UD->RemoveFromRoot();
            return 0;
        }

        static int gcClass(lua_State* L) {
            CheckUD(UClass,L,1);
            UD->RemoveFromRoot();
            return 0;
        }

        static int gcStructClass(lua_State* L) {
            CheckUD(UScriptStruct,L,1);
            UD->RemoveFromRoot();
            return 0;
        }

        static int gcStruct(lua_State* L) {
            CheckUD(LuaStruct,L,1);
            FMemory::Free(UD->buf);
            delete UD;
            return 0;
        }
    };

    template<>
    UClass* LuaObject::checkValue(lua_State* L,int p);

    template<>
    UObject* LuaObject::checkValue(lua_State* L,int p);

    template<>
    UScriptStruct* LuaObject::checkValue(lua_State* L,int p);

    template<>
    LuaStruct* LuaObject::checkValue(lua_State* L,int p);

    template<>
    const char* LuaObject::checkValue(lua_State* L,int p);

    template<>
    float LuaObject::checkValue(lua_State* L,int p);

    template<>
    int LuaObject::checkValue(lua_State* L,int p);

    template<>
    bool LuaObject::checkValue(lua_State* L,int p);

    template<>
    FText LuaObject::checkValue(lua_State* L,int p);

    

}