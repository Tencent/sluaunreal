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
#include "Components/SceneComponent.h"
#include "LuaVar.h"
#include <string>
#include <memory>

namespace slua {

    class SLUA_UNREAL_API LuaState
    {
    public:
        LuaState();
        virtual ~LuaState();

        typedef uint8* (*LoadFileDelegate) (const char* fn, uint32& len);

        static LuaState* get(lua_State* L);
        
        virtual bool init(USceneComponent* wld);
        virtual void tick(float dtime);
        virtual void close();

        LuaVar doString(const char* str);
        LuaVar doBuffer(const uint8* buf,uint32 len, const char* chunk);
        LuaVar doFile(const char* fn);

       

        template<typename ...ARGS>
        LuaVar call(const char* key,ARGS ...args) {
            LuaVar f = get(key);
            return f.call(args...);
        }

        LuaVar get(const char* key);

		void setLoadFileDelegate(LoadFileDelegate func);

		lua_State* getLuaState()
		{
			return L;
		}
		operator lua_State*()
		{
			return L;
		}


        void addRef(UObject* obj) {
            ensure(root);
            root->AddRef(obj);
        }

        void removeRef(UObject* obj) {
            ensure(root);
            root->Remove(obj);
        }
        
        static int pushErrorHandler(lua_State* L);
    protected:
        LoadFileDelegate loadFileDelegate;
        uint8* loadFile(const char* fn,uint32& len);
		static int loader(lua_State* L);
    private:
        friend class LuaObject;
        friend class SluaUtil;
        lua_State* L;
        USceneComponent* sluaComponent;
        int cacheObjRef;
        int _pushErrorHandler(lua_State* L);
        static int _atPanic(lua_State* L);
        ULuaObject* root;
        int stackCount;
    };
}