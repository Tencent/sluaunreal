
// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

#include "MemorySnapShot.h"
#include "Log.h"


namespace NS_SLUA {
    #define converStr(data) FString::Printf(TEXT(data))
    
    void SnapshotMap::initSnapShotMap(int typeSize){
        for(int i = 0; i < typeSize; i++) {
            MemoryNodeMap map;
            typeArray.Add(map);
        }
    }
    
    bool SnapshotMap::isMarked(const void *pointer){
        return false;
    }
    
    SnapshotMap MemorySnapshot::getMemorySnapshot(lua_State *L, int typeSize){
        this->L = L;
        shotMap.initSnapShotMap(typeSize);
        lua_pushvalue(this->L, LUA_REGISTRYINDEX);
        markTable(NULL, converStr("registry"));
        lua_close(this->L);
        
        return shotMap;
    }
    
    FString MemorySnapshot::getKey(int index){
        return converStr("");
    }

    const void* MemorySnapshot::readObject(const void *parent, FString description){
        void *ref = (void *)"";
        return ref;
    }
    
    void MemorySnapshot::markObject(const void *parent, FString description){
        
    }
    
    void MemorySnapshot::markTable(const void *parent, FString description){
        
    }
    
    void MemorySnapshot::markThread(const void *parent, FString description){
        
    }
    
    void MemorySnapshot::markUserdata(const void *parent, FString description){
        
    }
    
    void MemorySnapshot::markFunction(const void *parent, FString description){
        
    }
    
}
