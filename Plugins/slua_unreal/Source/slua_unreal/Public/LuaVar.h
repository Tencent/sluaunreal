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
#include "LuaObject.h"
#include "lua/lua.hpp"
#include "Log.h"

struct lua_State;

namespace slua {

    class LuaVar {
    public:
        enum Type {LV_NIL,LV_INT,LV_NUMBER,LV_STRING,LV_FUNCTION,LV_TABLE,LV_TUPLE};
        LuaVar();
        
        LuaVar(lua_State* L,int p);
        LuaVar(lua_State* L,int p,Type t);
        LuaVar(lua_State* L,lua_Integer v);
        LuaVar(lua_State* L,lua_Number v);
        LuaVar(lua_State* L,const char* v);

        LuaVar(const LuaVar& other):LuaVar() {
            clone(other);
        }
        LuaVar(LuaVar&& other):LuaVar() {
            move(std::move(other));
        }

        void operator=(const LuaVar& other) {
            free();
            clone(other);
        }
        void operator=(LuaVar&& other) {
            free();
            move(std::move(other));
        }

        virtual ~LuaVar();

        void set(lua_Integer v);
        void set(lua_Number v);
        void set(const char* v);

        int push(lua_State *l=nullptr) const;

        bool isNil() const;
        bool isFunction() const;
        Type type() const;

        template<class RET,class ...ARGS>
        RET call(ARGS ...args) {
            if(!isFunction()) {
                Log::Error("LuaVar is not a function, can't be called");
                return RET();
            }

            int n = pushArg(args...);
            int ret = docall(n);
            return getReturn<RET>(ret);
        }

        template<class ...ARGS>
        void call(ARGS ...args) {
            if(!isFunction()) {
                Log::Error("LuaVar is not a function, can't be called");
                return;
            }        
            int n = pushArg(args...);
            int ret = docall(n);
        }

        void callByUFunction(UFunction* ufunc,uint8* parms);
    private:
        friend class LuaState;
        // init number n of element
        LuaVar(int n);
        // used to create number n of tuple
        LuaVar(lua_State* L,size_t n);

        void init(lua_State* L,int p,Type t);


        void free();
        void alloc(int n);

        lua_State* L;
        typedef struct {
            union {
                int ref;
                lua_Integer i;
                lua_Number d;
                char* s;
            };
            Type luatype;
        } lua_var;

        lua_var* vars;
        size_t numOfVar;
    
        template<class F,class ...ARGS>
        int pushArg(F f,ARGS ...args) {
            LuaObject::push(L,f);
            return 1+pushArg(args...);
        }

        int pushArg() {
            return 0;
        }

        template<class RET>
        RET getReturn(int n) {

        }
        int docall(int argn);
        int pushArgByParms(UProperty* prop,uint8* parms);

        void clone(const LuaVar& other) {
            L = other.L;
            numOfVar = other.numOfVar;
            if(numOfVar>0 && other.vars) {
                vars = new lua_var[numOfVar];
                for(int n=0;n<numOfVar;n++) {
                    switch(other.vars[n].luatype) {
                    case LV_INT:
                        vars[n].i = other.vars[n].i;
                        break;
                    case LV_NUMBER:
                        vars[n].d = other.vars[n].d;
                        break;
                    case LV_STRING:
                        vars[n].s = strdup(other.vars[n].s);
                        break;
                    case LV_FUNCTION:
                    case LV_TABLE:
                        lua_geti(L,LUA_REGISTRYINDEX,other.vars[n].ref);
                        vars[n].ref=luaL_ref(L,LUA_REGISTRYINDEX);
                        break;
                    }
                    vars[n].luatype = other.vars[n].luatype;
                }
            }
        }

        void move(LuaVar&& other) {
            L = other.L;
            numOfVar = other.numOfVar;
            vars = other.vars;

            other.numOfVar = 0;
            other.vars = nullptr;
        }
    };
}