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

struct lua_State;

namespace slua {

    class LuaVar {
    public:
        LuaVar();
        virtual ~LuaVar(){};

        virtual int push(lua_State *l=nullptr) const;
        bool isNil() const;
        bool isFunction() const;
        int type() const { return luatype; }

    protected:
        lua_State* L;
        int ref;
        uint8 luatype;
    };

    class LuaFunction : public LuaVar {

    private:
        template<class F,class ...ARGS>
        int pushArg(F f,ARGS ...args) {
            LuaObject::push(L,f);
            return 1+pushArg(args...);
        }

        int pushArg() {
            return 0;
        }

    public:
        LuaFunction():LuaVar() {}
        LuaFunction(lua_State* L,int p,bool autopop=false);
        ~LuaFunction();

        template<class RET,class ...ARGS>
        RET call(ARGS ...args) {
            int n = pushArg(args...);
            int ret = docall(n);
            return getReturn<RET>(ret);
        }

        template<class ...ARGS>
        void call(ARGS ...args) {
            int n = pushArg(args...);
            int ret = docall(n);
        }

        void callByUFunction(UFunction* ufunc,uint8* parms);

    private:

        template<class RET>
        RET getReturn(int n) {

        }

        

        int docall(int argn);
        int pushArgByParms(UProperty* prop,uint8* parms);
    };
}