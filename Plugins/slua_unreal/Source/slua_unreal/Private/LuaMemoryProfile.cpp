// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "LuaMemoryProfile.h"
#include "LuaState.h"
#include "Log.h"
#include "lua/lstate.h"
namespace slua {

     TMap<void*,FString> memoryRecord;

    void* LuaMemoryProfile::alloc (void *ud, void *ptr, size_t osize, size_t nsize) {
        (void)osize;  /* not used */

        LuaState* ls = (LuaState*)ud;
        (void)ls;

        if (nsize == 0) {
            // Not completed
            //removeRecord(ls,ptr,nsize);
            FMemory::Free(ptr);
            return NULL;
        }
        else {
            ptr = FMemory::Realloc(ptr,nsize);
            // Not completed
            //addRecord(ls,ptr,nsize);
            return ptr;
        }
    }

    bool getTrackInfo(lua_State* L,FString& info) {
        lua_Debug ar;
        bool isvalid = false;
        for(int i=0;;i++) {
            if(lua_getstack(L,i,&ar) && lua_getinfo(L,"nS",&ar)) {
                CallInfo* ci = (CallInfo*) ar.i_ci;
                if(!isLua(ci))
                    break;
                info += ">";
                if(strcmp(ar.what,"Lua")==0) {
                    isvalid = true;
                    info += (ar.name?ar.name:"[Unknown Function]]");
                }
                else if(strcmp(ar.what,"main")==0) {
                    isvalid = true;
                    info += "[main]";
                }
            }
            else
                break;
        }
        return isvalid;
    }

    void LuaMemoryProfile::addRecord(LuaState* LS,void* ptr,size_t size) {
        // skip if lua_State is null, lua_State hadn't binded to LS
        lua_State* L = *LS;
        if(!L) return;

        FString trackInfo;
        if(getTrackInfo(L,trackInfo)) {
            Log::Log("alloc memory %d from %s",size,TCHAR_TO_UTF8(*trackInfo));
        }
    }

    void LuaMemoryProfile::removeRecord(LuaState* LS,void* ptr,size_t size) {

    }

}