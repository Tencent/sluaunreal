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

namespace NS_SLUA {
    
    // used for lua interface
    class SluaUtil {
    public:
        static void openLib(lua_State* L);
        static void reg(lua_State* L, const char* fn, lua_CFunction f);
    private:
        static int getGameInstance(lua_State* L);
        static int getWorld(lua_State* L);
        static int loadUI(lua_State* L);
        static int loadClass(lua_State* L);
        static int loadObject(lua_State* L);
        static int createDelegate(lua_State* L);

        // remote profile
        static int setTickFunction(lua_State* L);
        static int getMicroseconds(lua_State* L);
        static int getMiliseconds(lua_State* L);
        static int getGStartTime(lua_State* L);

        static int setGCParam(lua_State* L);

        // dump all uobject that referenced by lua
        static int dumpUObjects(lua_State* L);
        // get all UUserWidget that referenced by lua
        static int getAllWidgetObjects(lua_State* L);
        // return whether an userdata is valid?
        static int isValid(lua_State* L);
        // return whether an userdata is LuaStruct?
        static int isStruct(lua_State* L);

        static int addRef(lua_State* L);
        static int removeRef(lua_State * L);
        
        static int removeDelegate(lua_State* L);
#if UE_BUILD_DEVELOPMENT
        static int getObjectTableMap(lua_State* L);
        static int getRefTraceback(lua_State* L);
        static int toggleRefTraceback(lua_State* L);
#endif
    };

}