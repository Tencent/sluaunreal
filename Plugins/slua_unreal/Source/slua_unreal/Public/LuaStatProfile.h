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

#include "CoreMinimal.h"
#include "lua.h"

namespace NS_SLUA {
    enum HookCoroutineState {
        ENTER = 7,
        EXIT = 8,
    };

    class LuaStatProfile
    {
    public:
        LuaStatProfile();
        ~LuaStatProfile();

        static void onError(const char* err);
        static void setHook(lua_State* L, bool enable);
        static void setHookLevel(int level);
        static void clearSetHookData(lua_State* L = nullptr);
        static bool switcher;
    private:
        struct LuaStackInfo
        {
            lua_State* luaState;
            int stackNum;
            LuaStackInfo()
            {
                stackNum = 0;
                luaState = nullptr;
            }
            LuaStackInfo(lua_State* info, int num)
            {
                luaState = info;
                stackNum = num;
            }
        };

        static TArray<FString> blackScripts;
        static TArray<LuaStackInfo> luaStateStack;
        static int coroutineStack;
        static int mainStack;
        static int coroutine;
        static int level;
        static FDelegateHandle errorHandle;

        static void profile_coroutine_hook(lua_State* L, lua_Debug* ar);
        static void profile_hook(lua_State* L, lua_Debug* ar);
        static bool checkHookSuc(lua_Debug* ar);
        static FString generateCounterName(lua_Debug* ar);
        static void checkCoroutine();
    };
}
