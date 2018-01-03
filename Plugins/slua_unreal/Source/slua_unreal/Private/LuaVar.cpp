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

#include "LuaVar.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/Stack.h"
#include "Blueprint/WidgetTree.h"
#include "lua/lua.hpp"
#include "LuaState.h"

namespace slua {

    LuaVar::LuaVar()
        :L(nullptr)
        ,ref(LUA_NOREF)
        ,luatype(LUA_TNIL)
    {

    }

    int LuaVar::push(lua_State* l) const {
        if(l==nullptr) l=L;
        lua_geti(l,LUA_REGISTRYINDEX,ref);
        return 1;
    }

    bool LuaVar::isNil() const {
        return luatype==LUA_TNIL;
    }

    bool LuaVar::isFunction() const {
        return luatype==LUA_TFUNCTION;
    }

    LuaFunction::LuaFunction(lua_State* L,int p,bool autopop) {
        this->L = L;
        if(!autopop)
            lua_pushvalue(L,p);
        ref=luaL_ref(L,LUA_REGISTRYINDEX);
        luatype=LUA_TFUNCTION;
    }

    LuaFunction::~LuaFunction() {
        if(ref!=LUA_NOREF)
            luaL_unref(L,LUA_REGISTRYINDEX,ref);
    }

    int LuaFunction::docall(int argn) {
        int top = lua_gettop(L);
        top=top-argn+1;
        LuaState::pushErrorHandler(L);
        lua_insert(L,top);
        lua_geti(L,LUA_REGISTRYINDEX,ref);
        lua_insert(L,top+1);
        // top is err handler
        if(lua_pcallk(L,argn,LUA_MULTRET,top,NULL,NULL))
            lua_pop(L,1);
        lua_pop(L,1); // pop err handler
        return lua_gettop(L)-top;
    }

    int LuaFunction::pushArgByParms(UProperty* prop,uint8* parms) {
        if (LuaObject::push(L,prop,parms))
            return prop->ElementSize;
        return 0;
    }

    void LuaFunction::callByUFunction(UFunction* func,uint8* parms) {
        int n=0;
        int offset = 0;
        for(TFieldIterator<UProperty> it(func);it && (it->PropertyFlags&CPF_Parm);++it) {
            UProperty* prop = *it;
            uint64 propflag = prop->GetPropertyFlags();
            if((propflag&CPF_ReturnParm))
                continue;

            offset += pushArgByParms(prop,parms+offset);
            n++;
        }
        docall(n);
    }

    template<>
    inline void LuaFunction::call() {
        int err = LuaState::pushErrorHandler(L);
        lua_geti(L,LUA_REGISTRYINDEX,ref);
        if(lua_pcallk(L,0,0,err,NULL,NULL))
            lua_pop(L,1);
        lua_pop(L,1); // pop err handler
    }
}