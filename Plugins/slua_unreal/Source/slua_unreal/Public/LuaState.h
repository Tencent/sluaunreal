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

        /*
         * fn, lua file to load, fn may be a short filename
         * if find fn to load, return file size to len and file full path fo filepath arguments
         * if find fn and load successful, return buf of file content, otherwise return nullptr
         * you must delete[] buf returned by function for free memory.
         */
        typedef uint8* (*LoadFileDelegate) (const char* fn, uint32& len, FString& filepath);

        static LuaState* get(lua_State* L=nullptr);
        static bool isValid(lua_State* L);
        static lua_State* mainThread(lua_State* L);
        
        virtual bool init(USceneComponent* wld);
        virtual void tick(float dtime);
        virtual void close();

        LuaVar doString(const char* str);
        LuaVar doBuffer(const uint8* buf,uint32 len, const char* chunk);
        LuaVar doFile(const char* fn);

       

        template<typename ...ARGS>
        LuaVar call(const char* key,ARGS ...args) {
            LuaVar f = get(key);
            return f.call(std::forward<ARGS>(args)...);
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
        uint8* loadFile(const char* fn,uint32& len,FString& filepath);
		static int loader(lua_State* L);
		static int getStringFromMD5(lua_State* L);
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
        static LuaState* mainState;
		TMap<FString, FString> debugStringMap;

    };
}