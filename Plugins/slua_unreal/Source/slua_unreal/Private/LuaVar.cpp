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
#include "LuaState.h"
#include "lobject.h"

namespace slua {

    LuaVar::LuaVar()
        :L(nullptr)
    {
        vars = nullptr;
        numOfVar = 0;
    }

    LuaVar::LuaVar(int n)
        :LuaVar()
    {
        alloc(n);
    }

    LuaVar::LuaVar(lua_State* L,lua_Integer v)
        :LuaVar(1) 
    {
        vars[0].luatype = LV_INT;
        vars[0].i = v;
    }

    LuaVar::LuaVar(lua_State* L,lua_Number v)
        :LuaVar(1) 
    {
        vars[0].luatype = LV_NUMBER;
        vars[0].d = v;
    }

    LuaVar::LuaVar(lua_State* L,int p):LuaVar() {
        int t = lua_type(L,p);
        LuaVar::Type type = LV_NIL;
        switch(t) {
            case LUA_TNUMBER:
                {
                if(lua_isinteger(L,p))
                    type = LV_INT;
                else
                    type = LV_NUMBER;
                }
                break;
            case LUA_TSTRING:
                type = LV_STRING;
                break;
            case LUA_TFUNCTION:
                type = LV_FUNCTION;
                break;
            case LUA_TTABLE:
                type = LV_TABLE;
                break;
            case LUA_TNIL:
            default:
                type = LV_NIL;
                break;
        }
        init(L,p,type);
    }

    LuaVar::LuaVar(lua_State* L,int p,LuaVar::Type type):LuaVar() {
        init(L,p,type);
    }

    // used to create number n of tuple
    // it used for return value from lua
    // don't call it to create n element of tuple
    LuaVar::LuaVar(lua_State* L,size_t n) {
        
    }

    void LuaVar::init(lua_State* l,int p,LuaVar::Type type) {
        switch(type) {
        case LV_NIL:
            break;
        case LV_INT:
            set(lua_tointeger(l,p));
            break;
        case LV_NUMBER:
            set(lua_tonumber(l,p));
            break;
        case LV_STRING:
            set(lua_tostring(l,p));
            break;
        case LV_FUNCTION: this->L = l;
            ensure(lua_type(L,p)==LUA_TFUNCTION);
            alloc(1);
            lua_pushvalue(l,p);
            vars[0].ref=luaL_ref(l,LUA_REGISTRYINDEX);
            vars[0].luatype=LV_FUNCTION;
            break;
        default:
            break;
        }
    }

    LuaVar::~LuaVar() {
        free();
    }

    void LuaVar::free() {
        for(int n=0;n<numOfVar;n++) {
            if(( vars[n].luatype==LV_FUNCTION || vars[n].luatype==LV_TABLE) && vars[n].ref!=LUA_NOREF)
                luaL_unref(L,LUA_REGISTRYINDEX,vars[0].ref);
            else if(vars[n].luatype==LV_STRING)
                ::free(vars[n].s);
        }
        delete[] vars;
    }

    void LuaVar::alloc(int n) {
        if(n>0) {
            vars = new lua_var[n];
            numOfVar = n;
        }
    }

    void LuaVar::set(lua_Integer v) {
        free();
        alloc(1);
        vars[0].i = v;
        vars[0].luatype = LV_INT;
    }

    void LuaVar::set(lua_Number v) {
        free();
        alloc(1);
        vars[0].d = v;
        vars[0].luatype = LV_NUMBER;
    }

    void LuaVar::set(const char* v) {
        free();
        alloc(1);
        vars[0].s = strdup(v);
        vars[0].luatype = LV_STRING;
    }

    int LuaVar::push(lua_State* l) const {
        if(l==nullptr) l=L;
        lua_geti(l,LUA_REGISTRYINDEX,vars[0].ref);
        return 1;
    }

    bool LuaVar::isNil() const {
        return vars==nullptr && numOfVar==0;
    }

    bool LuaVar::isFunction() const {
        return numOfVar==1 && vars[0].luatype==LV_FUNCTION;
    }



    LuaVar::Type LuaVar::type() const {
        if(numOfVar==0)
            return LV_NIL;
        else if(numOfVar==1)
            return vars[0].luatype;
        else
            return LV_TUPLE;
    }

    int LuaVar::docall(int argn) {
        int top = lua_gettop(L);
        top=top-argn+1;
        LuaState::pushErrorHandler(L);
        lua_insert(L,top);
        lua_geti(L,LUA_REGISTRYINDEX,vars[0].ref);
        lua_insert(L,top+1);
        // top is err handler
        if(lua_pcallk(L,argn,LUA_MULTRET,top,NULL,NULL))
            lua_pop(L,1);
        lua_pop(L,1); // pop err handler
        return lua_gettop(L)-top;
    }

    int LuaVar::pushArgByParms(UProperty* prop,uint8* parms) {
        if (LuaObject::push(L,prop,parms))
            return prop->ElementSize;
        return 0;
    }

    void LuaVar::callByUFunction(UFunction* func,uint8* parms) {
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
    inline void LuaVar::call() {
        int err = LuaState::pushErrorHandler(L);
        lua_geti(L,LUA_REGISTRYINDEX,vars[0].ref);
        if(lua_pcallk(L,0,0,err,NULL,NULL))
            lua_pop(L,1);
        lua_pop(L,1); // pop err handler
    }
}