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
#include "lauxlib.h"
#include "SluaMicro.h"
#include "UObject/UnrealType.h"
#include "UObject/GCObject.h"
#include "PropertyUtil.h"

namespace NS_SLUA {

    template<typename T>
    struct TPairTraits;

    template <typename TKey, typename TValue>
    struct TPairTraits<TPair<TKey, TValue>> {
        typedef TKey    KeyType;
        typedef TValue    ValueType;
    };

    template <typename T> 
    struct TIsTMap { enum { Value = false }; };

    template<typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> 
    struct TIsTMap<TMap<KeyType, ValueType, SetAllocator, KeyFuncs>> { enum { Value = true }; };
    template<typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> 
    struct TIsTMap<const TMap<KeyType, ValueType, SetAllocator, KeyFuncs>> { enum { Value = true }; };
    template<typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> 
    struct TIsTMap<volatile TMap<KeyType, ValueType, SetAllocator, KeyFuncs>> { enum { Value = true }; };
    template<typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> 
    struct TIsTMap<const volatile TMap<KeyType, ValueType, SetAllocator, KeyFuncs>> { enum { Value = true }; };

    class SLUA_UNREAL_API LuaMap : public FGCObject{

    public:
        static void reg(lua_State* L);
        static int push(lua_State* L, FProperty* keyProp, FProperty* valueProp, FScriptMap* buf, bool bIsNewInner);
        static int push(lua_State* L, LuaMap* luaMap);
        
        template<typename K,typename V>
        static typename std::enable_if<DeduceType<K>::value != EPropertyClass::Struct && DeduceType<V>::value != EPropertyClass::Struct, int>::type
    	push(lua_State* L, const TMap<K, V>& v) {
            FProperty* keyProp = PropertyProto::createDeduceProperty<K>();
            FProperty* valueProp = PropertyProto::createDeduceProperty<V>();
            return push(L, keyProp, valueProp, reinterpret_cast<FScriptMap*>(const_cast<TMap<K, V>*>(&v)), false);
        }

        template<typename K, typename V>
        static typename std::enable_if<DeduceType<K>::value != EPropertyClass::Struct && DeduceType<V>::value == EPropertyClass::Struct, int>::type
            push(lua_State* L, const TMap<K, V>& v) {
            FProperty* keyProp = PropertyProto::createDeduceProperty<K>();
            FProperty* valueProp = PropertyProto::createDeduceProperty<V>(V::StaticStruct());
            return push(L, keyProp, valueProp, reinterpret_cast<FScriptMap*>(const_cast<TMap<K, V>*>(&v)), false);
        }

        template<typename K, typename V>
        static typename std::enable_if<DeduceType<K>::value == EPropertyClass::Struct && DeduceType<V>::value == EPropertyClass::Struct, int>::type
            push(lua_State* L, const TMap<K, V>& v) {
            FProperty* keyProp = PropertyProto::createDeduceProperty<K>(K::StaticStruct);
            FProperty* valueProp = PropertyProto::createDeduceProperty<V>(V::StaticStruct());
            return push(L, keyProp, valueProp, reinterpret_cast<FScriptMap*>(const_cast<TMap<K, V>*>(&v)), false);
        }

        static void clone(FScriptMap* dest,FProperty* keyProp, FProperty* valueProp,const FScriptMap* src);

        LuaMap(FMapProperty* prop, FScriptMap* buf, bool bIsRef, struct FLuaNetSerializationProxy* netProxy, uint16 replicatedIndex);
        LuaMap(FProperty* keyProp, FProperty* valueProp, FScriptMap* buf, bool bIsRef, bool bIsNewInner);
        ~LuaMap();
        
        FScriptMap* get() {
            return map;
        }

        FProperty* getKeyProp() const
        {
            return keyProp;
        }

        FProperty* getValueProp() const
        {
            return valueProp;
        }

        static bool markDirty(LuaMap* luaMap);

        virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
        virtual FString GetReferencerName() const override
        {
            return "LuaMap";
        }
#endif

        // Cast FScriptMap to TMap<TKey, TValue> if ElementSize matched
        template<typename TKey, typename TValue>
        const TMap<TKey, TValue>& asTMap(lua_State* L) const {
            if (sizeof(TKey) != keyProp->ElementSize)
                luaL_error(L, "Cast to TMap error, key element size isn't mathed(%d,%d)", sizeof(TKey), keyProp->ElementSize);
            if (sizeof(TValue) != valueProp->ElementSize)
                luaL_error(L, "Cast to TMap error, value element size isn't mathed(%d,%d)", sizeof(TValue), valueProp->ElementSize);

            // modified FScriptMap::CheckConstraints function to check type constraints
            typedef FScriptMap ScriptType;
            typedef TMap<TKey, TValue> RealType;

            // Check that the class footprint is the same
            static_assert(sizeof(ScriptType) == sizeof(RealType), "FScriptMap's size doesn't match TMap");
            static_assert(alignof(ScriptType) == alignof(RealType), "FScriptMap's alignment doesn't match TMap");

            // Check member sizes
            typedef FScriptSet ScriptPairsType;
            typedef TSet<typename RealType::ElementType> RealPairsType;
            static_assert(sizeof(FScriptSet) == sizeof(RealPairsType), "FScriptMap's Pairs member size does not match TMap's");

            return *(reinterpret_cast<const TMap<TKey, TValue>*>(
                map));
        }

    protected:
        static int __ctor(lua_State* L);
        static int Num(lua_State* L);
        static int Get(lua_State* L);
        static int Add(lua_State* L);
        static int Remove(lua_State* L);
        static int Clear(lua_State* L);
        static int Pairs(lua_State* L);
        static int Enumerable(lua_State* L);
        static int CreateValueTypeObject(lua_State* L);

    private:
        FScriptMap* map;
        FProperty* keyProp;
        FProperty* valueProp;
        FScriptMapHelper helper;
        bool isRef;
        bool isNewInner;

        struct FLuaNetSerializationProxy* proxy;
        uint16 luaReplicatedIndex;

        static int setupMT(lua_State* L);
        static int gc(lua_State* L);

        uint8* getKeyPtr(uint8* pairPtr);
        uint8* getValuePtr(uint8* pairPtr);
        void clear();
        int32 num() const;
        void emptyValues(int32 Slack = 0);
        void destructItems(int32 Index, int32 Count);
        void destructItems(uint8* PairPtr, uint32 Stride, int32 Index, int32 Count, bool bDestroyKeys, bool bDestroyValues);
        bool removePair(const void* KeyPtr);
        void removeAt(int32 Index, int32 Count = 1);

        struct Enumerator {
            LuaMap* map = nullptr;
            int32 index = 0;
            int32 num = 0;

            static int gc(lua_State* L);
        };
    };
    
}
