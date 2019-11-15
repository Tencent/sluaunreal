
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
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "LuaState.h"
#include "lua/lua.hpp"

namespace NS_SLUA {
    typedef TMap<void*, FString> MemoryNodeMap;
    
    class SnapshotMap{
    public:
        void initSnapShotMap(int typeSize);
        bool isMarked(const void *pointer);
    private:
        TArray<MemoryNodeMap> typeArray;
    };
    
    class MemorySnapshot{
    public:
        SnapshotMap getMemorySnapshot(lua_State *L, int typeSize);
    private:
        lua_State *L;
        SnapshotMap shotMap;
        
        FString getKey(int index);
        const void* readObject(const void *parent, FString description);
        
        void markObject(const void *parent, FString description);
        void markTable(const void *parent, FString description);
        void markThread(const void *parent, FString description);
        void markUserdata(const void *parent, FString description);
        void markFunction(const void *parent, FString description);
    };
}
