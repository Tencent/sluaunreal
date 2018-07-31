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
#include "lua/lua.hpp"
#include "UObject/UnrealType.h"

namespace slua {

    class SLUA_UNREAL_API LuaArray {
    public:
        static void reg(lua_State* L);
        static int push(lua_State* L,UArrayProperty* prop,FScriptArray* array);

        LuaArray(UArrayProperty* prop,FScriptArray* buf);
        ~LuaArray();
    protected:
        static int Num(lua_State* L);
        static int Get(lua_State* L);
        static int Add(lua_State* L);
        static int Remove(lua_State* L);
        static int Insert(lua_State* L);
        static int Clear(lua_State* L);
    private:
        UArrayProperty* prop;
        FScriptArray array;

        static int setupMT(lua_State* L);
        static int gc(lua_State* L);
    };

}