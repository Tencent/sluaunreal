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
#include "SluaUtil.h"

namespace NS_SLUA {

    DefTypeName(FRotator);
    DefTypeName(FQuat);
    DefTypeName(FTransform);
    DefTypeName(FLinearColor);
    DefTypeName(FColor);
    DefTypeName(FPlane);
    DefTypeName(FVector);
    DefTypeName(FVector2D);
    DefTypeName(FVector4);
    DefTypeName(FRandomStream);
    DefTypeName(FGuid);
    DefTypeName(FBox2D);
    DefTypeName(FFallbackStruct);
    DefTypeName(FFloatRangeBound);
    DefTypeName(FFloatRange);
    DefTypeName(FInt32RangeBound);
    DefTypeName(FInt32Range);
    DefTypeName(FFloatInterval);
    DefTypeName(FInt32Interval);
    DefTypeName(FFrameNumber);
    DefTypeName(FPrimaryAssetType);
    DefTypeName(FPrimaryAssetId);
    DefTypeName(FDateTime);
    DefTypeName(FSoftObjectPath);
    DefTypeName(FSoftClassPath);

    struct LuaWrapper {

        static void init(lua_State* L);
        static int pushValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms);
        static void* checkValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms, int i);

    };

}
