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
#include "SluaMicro.h"

namespace NS_SLUA
{
    typedef uint16 ReplicateIndexType;
    typedef TMap<int32, int32> ReplicateOffsetToMarkType;
    static constexpr ReplicateIndexType InvalidReplicatedIndex = 0xFFFF;

    struct FlatPropInfo
    {
        int32 propIndex;
        int32 offset;
        bool bSupportSharedSerialize;
        NS_SLUA::FProperty* prop;
    };

    typedef TArray<FlatPropInfo> FlatReplicatedProperties;

    struct FlatArrayPropInfo
    {
        int32 propIndex;
        int32 offset;
        ReplicateOffsetToMarkType markIndex;
        int32 innerPropertyNum;
        FlatReplicatedProperties properties;
    };
}
