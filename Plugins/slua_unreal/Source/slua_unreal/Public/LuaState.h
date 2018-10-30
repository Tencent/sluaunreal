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

        inline static LuaState* get(lua_State* l=nullptr) {
            // if L is nullptr, return main state
            if(!l) return mainState;
            return (LuaState*)*((void**)lua_getextraspace(l));
        }
        // get LuaState from state index
        static LuaState* get(int index);

        // return specified index is valid state index
        inline static bool isValid(int index)  {
            return get(index)!=nullptr;
        }
        
        // return state index
        int stateIndex() const { return si; }
        
        // init lua state
        virtual bool init();
        // tick function
        virtual void tick(float dtime);
        // close lua state
        virtual void close();

        // execute lua string
        LuaVar doString(const char* str, LuaVar* pEnv = nullptr);
        // execute bytes buffer and named buffer to chunk
        LuaVar doBuffer(const uint8* buf,uint32 len, const char* chunk, LuaVar* pEnv = nullptr);
        // load file and execute it
        // file how to loading depend on load delegation
        // see setLoadFileDelegate function
        LuaVar doFile(const char* fn, LuaVar* pEnv = nullptr);

       
        // call function that specified by key
        // any supported c++ value can be passed as argument to lua 
        template<typename ...ARGS>
        LuaVar call(const char* key,ARGS&& ...args) {
            LuaVar f = get(key);
            return f.call(std::forward<ARGS>(args)...);
        }

        // get field from _G, support "x.x.x.x" to search children field
        LuaVar get(const char* key);

        // set load delegation function to load lua code
		void setLoadFileDelegate(LoadFileDelegate func);

		lua_State* getLuaState() const
		{
			return L;
		}
		operator lua_State*() const
		{
			return L;
		}

        // create a empty table
        LuaVar createTable();


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
        int cacheObjRef;
        int _pushErrorHandler(lua_State* L);
        static int _atPanic(lua_State* L);
        ULuaObject* root;
        int stackCount;
        int si;

        TMap<FString,TMap<FString,UFunction*>*> classMap;
        TMap<FString,UFunction*> instanceFuncMap;

        static LuaState* mainState;

        #if WITH_EDITOR
        // used for debug
		TMap<FString, FString> debugStringMap;
        #endif
    };
}