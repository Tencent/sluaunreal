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
#include "LuaState.h"
#include "LuaBitArray.h"
#include "LuaNetType.h"
#include "Net/RepLayout.h"
#include "Containers/StaticBitArray.h"

#include "LuaNetSerialization.generated.h"

namespace NS_SLUA
{
    struct ClassLuaReplicated
    {
        static constexpr int32 MaxArrayLimit = 64;
        
        typedef TMap<FString, ReplicateIndexType> ReplicatedNameToIndexMap;
        typedef TArray<FString> ReplicatedIndexToNameMap;
        typedef TArray<NS_SLUA::FProperty*> ReplicatedProperties;

    #if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        TWeakObjectPtr<NS_SLUA::FProperty> ownerProperty;
    #else
        TWeakFieldPtr<NS_SLUA::FProperty> ownerProperty;
    #endif
        ReplicatedNameToIndexMap replicatedNameToIndexMap;
        ReplicatedIndexToNameMap replicatedIndexToNameMap;
            
        TArray<ELifetimeCondition> lifetimeConditions;
        TSet<ReplicateIndexType> repNotifies;

        TWeakObjectPtr<UStruct> ustruct;
        ReplicatedProperties properties;
        
        FlatReplicatedProperties flatProperties;
        ReplicateOffsetToMarkType propertyOffsetToMarkIndex;
        
        TMap<int32, FlatArrayPropInfo> flatArrayPropInfos;
    };

    class FLuaNetBaseState : public INetDeltaBaseState
    {
    public:
        bool IsStateEqual(INetDeltaBaseState* otherState) override;

        int32 assignTimes = 0;
        int32 historyEnd = 0;
    };

    struct FLuaNetSerializerGuidReferences
    {
        TSet<FNetworkGUID> unmappedGUIDs;
        TSet<FNetworkGUID> mappedDynamicGUIDs;

        /** Buffer of data to re-serialize when the guids are mapped */
        TArray<uint8> buffer;

        /** Number of bits in the buffer */
        int32 numBufferBits;
    };

    /** Holds the unique identifier and offsets/lengths of a net serialized property used for Shared Serialization */
    struct FLuaRepSerializedPropertyInfo
    {
        FLuaRepSerializedPropertyInfo():
            BitOffset(0),
            BitLength(0),
            bShared(false),
            bArray(false)
        {}
        
        /** Bit offset into shared buffer of the shared data */
        int32 BitOffset;

        /** Length in bits of all serialized data for this property, may include handle and checksum. */
        int32 BitLength;

        bool bShared;
        bool bArray;
    };

    /** Holds a set of shared net serialized properties */
    struct FLuaRepSerializationSharedInfo
    {
        FLuaRepSerializationSharedInfo():
            SerializedProperties(MakeUnique<FNetBitWriter>(0)),
            bIsValid(false)
        {}

        void SetValid()
        {
            bIsValid = true;
        }

        void Init()
        {
            if (!SerializedProperties.IsValid())
            {
                SerializedProperties.Reset(new FNetBitWriter(0));
            }
        }

        bool IsValid() const
        {
            return bIsValid;
        }

        void Reset()
        {
            if (bIsValid)
            {
                SharedPropertyInfo.Reset();
                SerializedProperties->Reset();

                bIsValid = false;
            }
        }

        /** Metadata for properties in the shared data blob. */
        TArray<FLuaRepSerializedPropertyInfo> SharedPropertyInfo;

        /** Binary blob of net serialized data to be shared */
        TUniquePtr<FNetBitWriter> SerializedProperties;

    private:

        /** Whether or not shared serialization data has been successfully built. */
        bool bIsValid;
    };

    struct FLuaNetSerializationProxy : public FGCObject
    {
        /** The maximum number of individual changelists allowed.*/
        static constexpr int32 MAX_CHANGE_HISTORY = 64;
        
        TWeakObjectPtr<class UObject> owner;
        
        TArray<uint8, TAlignedHeapAllocator<16>> values;
        TArray<uint8, TAlignedHeapAllocator<16>> oldValues;

        TMap<ReplicateIndexType, FLuaNetSerializerGuidReferences> guidReferencesMap;
        
        int32 assignTimes;

        LuaBitArray dirtyMark;
        
        LuaBitArray flatDirtyMark;
        TMap<int32, LuaBitArray> arrayDirtyMark;
        TMap<ReplicateIndexType, TArray<NS_SLUA::LuaVar*>> propListeners;
        
        TWeakObjectPtr<UStruct> contentStruct;

        int32 historyStart = 0;
        int32 historyEnd = 0;
        LuaBitArray changeHistorys[MAX_CHANGE_HISTORY];
        TMap<int32, LuaBitArray> arrayChangeHistorys[MAX_CHANGE_HISTORY];

        uint32 lastReplicationFrame = 0;
        bool bDirtyThisFrame = false;

        FLuaRepSerializationSharedInfo sharedSerialization;
        TMap<int32, FLuaRepSerializationSharedInfo> sharedArraySerialization;

    #if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        FReplicationFlags repFlags;
        TStaticBitArray<COND_Max> conditionMap;
    #endif

        virtual void AddReferencedObjects( FReferenceCollector& Collector );
    #if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
        virtual FString GetReferencerName() const override
        {
            return FString::Printf(TEXT("FLuaNetSerializationProxy, Owner: %s."), owner.IsValid() ? *owner->GetName() : TEXT("NULL"));
        }
    #endif

        ~FLuaNetSerializationProxy();
    };
}

USTRUCT()
struct SLUA_UNREAL_API FLuaNetSerialization
{
    GENERATED_BODY()

public:
    static int32 bEnableLuaNetReplicate;
    static int32 SerializeVersion;

    FLuaNetSerialization();

    bool NetDeltaSerialize(FNetDeltaSerializeInfo& deltaParms);
    static bool IsSupportSharedSerialize(NS_SLUA::FProperty* prop);

protected:
    typedef TFunction<void (int32 arrayNum, int32 innerPropNum)> PrepareSerializeArrayCallback;
    typedef TFunctionRef<void (NS_SLUA::FlatPropInfo& propInfo, FScriptArrayHelper& arrayHelper, int32 arrayIndex, int32 dirtyIndex)> SerializeArrayCallback;
    
    bool Read(FNetDeltaSerializeInfo& deltaParms, NS_SLUA::FLuaNetSerializationProxy* proxy);
    void ReadItem(FNetDeltaSerializeInfo& deltaParms, NS_SLUA::FLuaNetSerializationProxy& proxy, FBitReader& reader, NS_SLUA::ClassLuaReplicated* classReplicated,
                  int32 index, uint8* data, uint8* oldData);
    
    bool Write(FNetDeltaSerializeInfo& deltaParms, NS_SLUA::FLuaNetSerializationProxy* proxy);
    
    bool CompareProperties(UObject* obj, NS_SLUA::FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame);
    bool UpdateChangeListMgr_V1(NS_SLUA::FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame);
    void BuildSharedSerialization_V1(class UPackageMap* map, NS_SLUA::ClassLuaReplicated* classLuaReplicated,
        NS_SLUA::FLuaNetSerializationProxy* proxy, const LuaBitArray& changes,
                                     const TMap<int32, LuaBitArray>& arrayChanges);

    void SerializeArrayProperty(FBitWriter& writer, NS_SLUA::ClassLuaReplicated* classLuaReplicated,
                                const TMap<int32, LuaBitArray>& arrayChanges, uint8* data, int32 index,
                                PrepareSerializeArrayCallback preapareCallback,
                                const SerializeArrayCallback& serializeCallback);
    
    bool UpdateChangeListMgr(NS_SLUA::FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame);
    void BuildSharedSerialization(class UPackageMap* map, NS_SLUA::ClassLuaReplicated* classLuaReplicated, NS_SLUA::FLuaNetSerializationProxy* proxy, const LuaBitArray& changes);
    
    void CallOnRep(NS_SLUA::lua_State* L, const NS_SLUA::LuaVar& luaTable, const FString& propName, NS_SLUA::FProperty* prop, uint8* oldData);
    
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
    TStaticBitArray<COND_Max> BuildConditionMapFromRepFlags(const FReplicationFlags RepFlags);
#endif

private:
    TMap<FString, NS_SLUA::LuaVar> RepFuncMap;
};

template<>
struct TStructOpsTypeTraits<FLuaNetSerialization> : public TStructOpsTypeTraitsBase2<FLuaNetSerialization>
{
    enum
    {
        WithNetDeltaSerializer = true,
    };
};
