
// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

#include "MemorySnapshot.h"
#include "Log.h"

#define TABLE 1
#define FUNCTION 2
#define SOURCE 3
#define THREAD 4
#define USERDATA 5
#define MARKED 6

#define convert2str(data) FString::Printf(TEXT(data))

namespace NS_SLUA {
    void SnapshotMap::initSnapShotMap(int typeSize){
        for(int i = 0; i < typeSize; i++) {
            MemoryTypeMap map;
            typeArray.Add(map);
        }
    }
    
    bool SnapshotMap::isMarked(const void *pointer){
        if(typeArray[MARKED].Contains(pointer))
           return true;
           
       typeArray[MARKED].Add(pointer);
       return false;
    }
    
    MemoryTypeMap SnapshotMap::getMemoryMap(int index){
        return typeArray[index];
    }
    
    SnapshotMap MemorySnapshot::getMemorySnapshot(lua_State *cL, int typeSize){
        L = cL;
        shotMap.initSnapShotMap(typeSize);
        //get lua registry table
        lua_pushvalue(this->L, LUA_REGISTRYINDEX);
        // mark lua registry table
        markTable(NULL, convert2str("registry table"));
        // free pointer L;
        L = nullptr;
        delete L;
        return shotMap;
    }
    
    
    /* get the value's key in one pair */
    FString MemorySnapshot::getKey(int keyIndex){
        int type = lua_type(L, keyIndex);
        FString keyStr = convert2str("");
        switch (type) {
            case LUA_TSTRING:
                keyStr = FString::Printf(TEXT("%s"), lua_tostring(L, keyIndex));
                break;
            case LUA_TNIL:
                keyStr = convert2str("nil");
                break;
            case LUA_TBOOLEAN:
                keyStr = lua_toboolean(L, keyIndex) ? FString::Printf(TEXT("true")) : FString::Printf(TEXT("false"));
                break;
            case LUA_TNUMBER:
                keyStr = FString::Printf(TEXT("%f"),lua_tonumber(L, keyIndex));
                break;
            default:
                keyStr = FString::Printf(TEXT("%s : %p"), lua_typename(L, type), lua_topointer(L, keyIndex));
                break;
        }
        
        return keyStr;
    }

    const void* MemorySnapshot::readObject(const void *parent, FString description){
        int type = lua_type(L, -1);
        int mapType = 0;
        
        switch (type) {
            case LUA_TTABLE:
                mapType = TABLE;
                break;
            case LUA_TFUNCTION:
                mapType = FUNCTION;
            case LUA_TTHREAD:
                mapType = THREAD;
                break;
            case LUA_TUSERDATA:
                mapType = USERDATA;
                break;
            default:
                lua_pop(L, 1);
                break;
        }
        
        const void *pointer = lua_topointer(L, -1);
        if(shotMap.isMarked(pointer)){
            MemoryNodeMap *childMap = shotMap.getMemoryMap(mapType).Find(pointer);
            if(childMap == nullptr){
                childMap->Add(parent, description);
            }
            lua_pop(L, 1);
            return NULL;
        }
        
        MemoryNodeMap childMap;
        shotMap.getMemoryMap(mapType).Add(pointer, childMap);
        return pointer;
    }
    
    void MemorySnapshot::markObject(const void *parent, FString description){
        int type = lua_type(L, -1);
        switch (type) {
            case LUA_TTABLE:
                markTable(parent, description);
                break;
            case LUA_TTHREAD:
                markThread(parent, description);
                break;
            case LUA_TFUNCTION:
                markFunction(parent, description);
                break;
            case LUA_TUSERDATA:
                markUserdata(parent, description);
                break;
            default:
                lua_pop(L, 1);
                break;
        }
    }
    
    void MemorySnapshot::markTable(const void *parent, FString description){
        const void *pointer = readObject(parent, description);
        
        if(pointer == nullptr) return;
        
        // check the mode of table's key and value
        bool weakKey = false;
        bool weakValue = false;
        
        if(lua_getmetatable(L, -1)) {
            // push the key in top and get the key's value
            lua_pushliteral(L, "__mode");
            lua_rawget(L, -2);
            if(lua_isstring(L, -1)) {
                const char *mode = lua_tostring(L, -1);
                
                if(strchr(mode, 'k'))
                        weakKey == true;
                if(strchr(mode, 'v'))
                        weakValue == true;
            }
            lua_pop(L, 1);
            markTable(pointer, convert2str("metatable"));
        }
        //traverce table - regirstry table or the table's value(if value is a table -1:nil, -2:value, -3:key)
        lua_pushnil(L);
        while(lua_next(L, -2)) {
            // traverce statck top item : value(L : -1)
            if(weakValue) {
                lua_pop(L, -1);
            } else {
                FString childDescription = getKey(-2);
                markObject(pointer, childDescription);
            }
            
            if(!weakKey) {
                // copy key and put it onto top to mark top value of stack and keep the stack balance
                lua_pushvalue(L, -1);
                markObject(pointer, "table's key");
            }
        }
        
        lua_pop(L, 1);
    }
    
    void MemorySnapshot::markThread(const void *parent, FString description){
        
    }
    
    void MemorySnapshot::markUserdata(const void *parent, FString description){
        
    }
    
    void MemorySnapshot::markFunction(const void *parent, FString description){
        const void *pointer = readObject(parent, description);
        
        if(pointer == nullptr) return;
        
        markEnviroment(parent, "function enviroment");
        
        // record function upvalue;
        int upvalueIndex = 1;
        while(true) {
            const char *upvalueName = lua_getupvalue(L, -1, upvalueIndex);
            
            if(upvalueName == nullptr) break;
            
            upvalueIndex++;
            markObject(pointer, FString::Printf(TEXT("%s"), upvalueName));
        }
        
        // record c function or lua closure
        if(lua_iscfunction(L, -1)){
            // the c function have no upvalue means that it is a light c function
            if(upvalueIndex == 1) {
                MemoryNodeMap map;
                // NULL value use to judge whether the function map item is light c function
                shotMap.getMemoryMap(FUNCTION).Add(pointer);
            }
            
            lua_pop(L, 1);
        } else {
            // get lua closure debug info
            lua_Debug ar;
            FString info;
            
            lua_getinfo(L, "nSl", &ar);
//            lua_getinfo(L, ">S", &ar);
            info = FString::Printf(TEXT("%s:%d"), UTF8_TO_TCHAR(ar.source), ar.currentline);
            
            MemoryNodeMap map;
            map.Add(pointer, info);
            shotMap.getMemoryMap(SOURCE).Add(pointer, map);
        }
    }
    
    void MemorySnapshot::markEnviroment(const void *parent, FString description){
    }
    
    /* print the map recording lua memory*/
    void MemorySnapshot::printMap() {
        for(int i = 0; i < MARKED; i++){
            FString mapType = convert2str("");
            switch (i) {
                case TABLE:
                    mapType = convert2str("Table");
                    break;
                case FUNCTION:
                    mapType = convert2str("Function");
                    break;
                case THREAD:
                    mapType = convert2str("Thread");
                    break;
                case USERDATA:
                    mapType = convert2str("Userdata");
                    break;
                default:
                    break;
            }
            MemoryTypeMap map = shotMap.getMemoryMap(i);
            for(auto &parent : map) {
                FString memInfo = convert2str("");
                memInfo = mapType + FString::Printf(TEXT("Stack Item Address : %p \n"), parent.Key);
                
                if(i == SOURCE) {
                    MemoryNodeMap *sourceMap = shotMap.getMemoryMap(SOURCE).Find(parent.Key);
                    FString source = FString::Printf(TEXT("%s"), sourceMap ? "light c function"
                                                                            :(convert2str("lua closure")+ sourceMap->FindRef(parent.Key)));
                    memInfo += source;
                }
                for(auto &child : parent.Value)
                    memInfo = FString::Printf(TEXT("Item Child : \n \t child address :%p    value : %s"), child.Key, *child.Value);
                Log::Log(*memInfo);
            }
        }
    }
}
