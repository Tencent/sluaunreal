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
#include "LuaVar.h"
#include "LuaNetSerialization.h"

namespace NS_SLUA
{
    struct FLuaNetSerializationProxy;

    class SLUA_UNREAL_API LuaNet
    {
    public:
        typedef TFunction<void ()> PrepareParamCallback;

        // Only support c++ native UClass
        static void addLuaRepilcateClass(const UClass* someBase);
        static bool isLuaReplicateObject(UObject* obj);

        static void addLuaRPCType(const FString& rpcType, EFunctionFlags netFlag);
        
        static ClassLuaReplicated* addClassReplicatedProps(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar& luaModule);
        static void initLuaReplicatedProps(NS_SLUA::lua_State* L, UObject* obj, const ClassLuaReplicated& classReplicated, const NS_SLUA::LuaVar& luaTable);

        static FLuaNetSerializationProxy* getLuaNetSerializationProxy(struct FLuaNetSerialization* luaNetSerialization);

        static ClassLuaReplicated* getClassReplicatedProps(const UObject* obj);

        static void removeObjectTable(UObject* obj);
        static void onObjectDeleted(UClass* cls);

        static void onPropModify(lua_State* L, FLuaNetSerializationProxy* proxy, ReplicateIndexType index, PrepareParamCallback callback);

    protected:
        friend class LuaOverrider;
        static const char* ADD_LISTENER_FUNC;
        static const char* REMOVE_LISTENER_FUNC;
        
        void addClassRPC(lua_State* L, UClass* cls, const FString& luaFilePath);
        bool addClassRPCRecursive(lua_State* L, UClass* cls, const FString& luaFilePath, LuaVar& cppSuperModule);
        LuaVar findFirstCommomModule(lua_State* L, const LuaVar& A, const LuaVar& B);
        bool addModuleRPCRecursive(lua_State* L, UClass* cls, const LuaVar& luaModule, const LuaVar& cppSuperModule);
        bool addClassRPCByType(lua_State* L, UClass* cls, const LuaVar& luaModule, const FString& repType, EFunctionFlags netFlag);

        static void initFlatReplicatedProps(ClassLuaReplicated& classReplicated,
                                            ReplicateOffsetToMarkType& markIndex, UStruct* ustruct, int32& index, 
                                            const int32 offset, int32 ownerPropIndex, NS_SLUA::FlatArrayPropInfo* arrayInfo);

        static int __index(lua_State* L, UObject* obj, const char* keyName);
        static int __newindex(lua_State* L, UObject* obj, const char* keyName);

        static int setupFunctions(lua_State* L);
        static int addListener(lua_State* L);
        static int removeListener(lua_State* L);
        
        typedef TMap<TWeakObjectPtr<UClass>, ClassLuaReplicated*, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UClass>, ClassLuaReplicated*>> ClassLuaReplicatedMap;
        static ClassLuaReplicatedMap classLuaReplicatedMap;

        typedef TMap<void*, FLuaNetSerializationProxy*> LuaNetSerializationMap;
        typedef TMap<TWeakObjectPtr<UObject>, void*, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UObject>, void*>> ObjectToLuaNetAddressMap;
        static LuaNetSerializationMap luaNetSerializationMap;
        static ObjectToLuaNetAddressMap objectToLuaNetAddressMap;

        static TArray<const UClass*> luaReplicateClasses;

        static TMap<FString, EFunctionFlags> luaRPCTypeMap;
        static TSet<TWeakObjectPtr<UClass>> addedRPCClasses;
#if WITH_EDITOR
        static TSet<TWeakObjectPtr<UFunction>> luaRPCFuncs;
#endif
    };
}
