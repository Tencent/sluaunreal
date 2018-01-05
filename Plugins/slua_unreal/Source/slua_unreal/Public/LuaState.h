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
#include "LuaVar.h"
#include <string>
#include <memory>

struct lua_State;

namespace slua {

    class SLUA_UNREAL_API LuaState
    {
    public:
        LuaState();
        ~LuaState();

        typedef uint8* (*LoadFileDelegate) (const char* fn, uint32& len);

        static LuaState* get(lua_State* L);
        
        bool init(UWorld* wld);
        void close();

        LuaVar doString(const char* str);
        LuaVar doBuffer(const uint8* buf,uint32 len, const char* chunk);
        LuaVar doFile(const char* fn);

        template<typename RET,typename ...ARGS>
        RET call(const char* key,ARGS ...args) {
            LuaVar f = get(key);
            RET r = f.call<RET>(args...);
            return LuaObject::push(L,r);
        }

        template<typename ...ARGS>
        void call(const char* key,ARGS ...args) {
            LuaVar f=get(key);
            f.call<void>(args...);
        }

        LuaVar get(const char* key) {
            AutoStack g(L);
            // TODO, search full path of key
            lua_getglobal(L,key);
            return LuaVar(L,-1);

        }

        void setLoadFileDelegate(LoadFileDelegate func) {
            loadFileDelegate = func;
        }

        static int pushErrorHandler(lua_State* L);
    protected:
        LoadFileDelegate loadFileDelegate;
        uint8* loadFile(const char* fn,uint32& len);
        static int loader(lua_State* L);
    private:
        lua_State* L;
        int _pushErrorHandler(lua_State* L);
    };
}