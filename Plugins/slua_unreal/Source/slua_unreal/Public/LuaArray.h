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
        static int push(lua_State* L,UProperty* prop,FScriptArray* array);

        LuaArray(UProperty* prop,FScriptArray* buf);
        ~LuaArray();

        const FScriptArray* get() {
            return &array;
        }

        // Cast FScriptArray to TArray<T> if ElementSize matched
        template<typename T>
        const TArray<T>& asTArray(lua_State* L) const {
            if(sizeof(T)!=inner->ElementSize)
                luaL_error(L,"Cast to TArray error, element size isn't mathed(%d,%d)",sizeof(T),inner->ElementSize);
            return *(reinterpret_cast<const TArray<T>*>( &array ));
        }
        
    protected:
        static int __ctor(lua_State* L);
        static int Num(lua_State* L);
        static int Get(lua_State* L);
        static int Add(lua_State* L);
        static int Remove(lua_State* L);
        static int Insert(lua_State* L);
        static int Clear(lua_State* L);
    private:
        UProperty* inner;
        FScriptArray array;

        void clear();
        uint8* getRawPtr(int index) const;
        bool isValidIndex(int index) const;
        uint8* insert(int index);
        uint8* add();
        void remove(int index);
        int num() const;
        void constructItems(int index,int count);
        void destructItems(int index,int count);      

        static int setupMT(lua_State* L);
        static int gc(lua_State* L);
    };

}