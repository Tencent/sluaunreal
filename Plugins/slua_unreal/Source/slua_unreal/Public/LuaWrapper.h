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
#include "lua.h"
#include "SluaMicro.h"
#include "SluaUtil.h"

namespace NS_SLUA {

#if ((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
    #include "LuaWrapper4.18Head.inc"
#elif ((ENGINE_MINOR_VERSION>=25) && (ENGINE_MAJOR_VERSION==4))
    #include "LuaWrapper4.25Head.inc"
#elif ((ENGINE_MINOR_VERSION==1) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.1Head.inc"
    DefTypeName(VectorRegister4d);
#elif ((ENGINE_MINOR_VERSION==2) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.2Head.inc"
    DefTypeName(VectorRegister4d);
#elif ((ENGINE_MINOR_VERSION>=3) && (ENGINE_MAJOR_VERSION==5))
    using FVector2 = UE::Math::TVector2<FVector::FReal>;
    #include "LuaWrapper5.3Head.inc"
#endif
    DefTypeName(FSoftObjectPtr);

    struct LuaWrapper {

        static void init(lua_State* L);
        static void initExt(lua_State* L);
        static int pushValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms);
        static void* checkValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms, int i);

    };

}
