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
#include "Net/RepLayout.h"
#include "Containers/StaticBitArray.h"

#include "LuaNetSerialization.generated.h"

struct ClassLuaReplicated
{
    static constexpr int32 MaxArrayLimit = 64;
    typedef uint16 ReplicateIndexType;
    
    typedef TMap<FString, ReplicateIndexType> ReplicatedNameToIndexMap;
    typedef TArray<FString> ReplicatedIndexToNameMap;
    typedef TArray<NS_SLUA::FProperty*> ReplicatedProperties;
    typedef TMap<int32, int32> OffsetToMarkType;

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION>=4)
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

    struct FlatPropInfo
    {
        int32 propIndex;
        int32 offset;
        bool bSupportSharedSerialize;
        NS_SLUA::FProperty* prop;
    };
    typedef TArray<FlatPropInfo> FlatReplicatedProperties;
    FlatReplicatedProperties flatProperties;
    OffsetToMarkType propertyOffsetToMarkIndex;

    struct FlatArrayPropInfo
    {
        int32 propIndex;
        int32 offset;
        OffsetToMarkType markIndex;
        int32 innerPropertyNum;
        FlatReplicatedProperties properties;
    };
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

#if (ENGINE_MINOR_VERSION<=25) && (ENGINE_MAJOR_VERSION>=4)
/** Holds the unique identifier and offsets/lengths of a net serialized property used for Shared Serialization */
struct FRepSerializedPropertyInfo
{
    FRepSerializedPropertyInfo():
        Guid(),
        BitOffset(0),
        BitLength(0)
    {}

    /** Unique identifier for this property, may include array index and depth. */
    FGuid Guid;

    /** Bit offset into shared buffer of the shared data */
    int32 BitOffset;

    /** Length in bits of all serialized data for this property, may include handle and checksum. */
    int32 BitLength;
};

/** Holds a set of shared net serialized properties */
struct FRepSerializationSharedInfo
{
    FRepSerializationSharedInfo():
        SerializedProperties(MakeUnique<FNetBitWriter>(0)),
        bIsValid(false)
    {}

    void SetValid()
    {
        bIsValid = true;
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
    TArray<FRepSerializedPropertyInfo> SharedPropertyInfo;

    /** Binary blob of net serialized data to be shared */
    TUniquePtr<FNetBitWriter> SerializedProperties;

private:

    /** Whether or not shared serialization data has been successfully built. */
    bool bIsValid;
};
#endif

struct FLuaNetSerializationProxy : public FGCObject
{
    /** The maximum number of individual changelists allowed.*/
    static constexpr int32 MAX_CHANGE_HISTORY = 64;
    
    TWeakObjectPtr<class UObject> owner;
    
    TArray<uint8, TAlignedHeapAllocator<16>> values;
    TArray<uint8, TAlignedHeapAllocator<16>> oldValues;

    TMap<ClassLuaReplicated::ReplicateIndexType, FLuaNetSerializerGuidReferences> guidReferencesMap;
    
    int32 assignTimes;

    LuaBitArray dirtyMark;
    
    LuaBitArray flatDirtyMark;
    TMap<int32, LuaBitArray> arrayDirtyMark;
    
    TWeakObjectPtr<UStruct> contentStruct;

    int32 historyStart = 0;
    int32 historyEnd = 0;
    LuaBitArray changeHistorys[MAX_CHANGE_HISTORY];
    TMap<int32, LuaBitArray> arrayChangeHistorys[MAX_CHANGE_HISTORY];

    uint32 lastReplicationFrame = 0;
    bool bDirtyThisFrame = false;

    FRepSerializationSharedInfo sharedSerialization;
    TMap<int32, FRepSerializationSharedInfo> sharedArraySerialization;

#if (ENGINE_MINOR_VERSION>=25) && (ENGINE_MAJOR_VERSION>=4)
    FReplicationFlags repFlags;
    TStaticBitArray<COND_Max> conditionMap;
#endif

    virtual void AddReferencedObjects( FReferenceCollector& Collector );
    
};

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
    typedef TFunctionRef<void (ClassLuaReplicated::FlatPropInfo& propInfo, FScriptArrayHelper& arrayHelper, int32 arrayIndex, int32 dirtyIndex)> SerializeArrayCallback;
    
    bool Read(FNetDeltaSerializeInfo& deltaParms, FLuaNetSerializationProxy* proxy);
    void ReadItem(FNetDeltaSerializeInfo& deltaParms, FBitReader& reader, ClassLuaReplicated* classReplicated,
                  int32 index, uint8* data, uint8* oldData);
    
    bool Write(FNetDeltaSerializeInfo& deltaParms, FLuaNetSerializationProxy* proxy);
    
    bool CompareProperties(UObject* obj, FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame);
    bool UpdateChangeListMgr_V1(FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame);
    void BuildSharedSerialization_V1(class UPackageMap* map, ClassLuaReplicated* classLuaReplicated,
                                     FLuaNetSerializationProxy* proxy, const LuaBitArray& changes,
                                     const TMap<int32, LuaBitArray>& arrayChanges);

    void SerializeArrayProperty(FBitWriter& writer, ClassLuaReplicated* classLuaReplicated,
                                const TMap<int32, LuaBitArray>& arrayChanges, uint8* data, int32 index,
                                PrepareSerializeArrayCallback preapareCallback,
                                const SerializeArrayCallback& serializeCallback);
    
    bool UpdateChangeListMgr(FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame);
    void BuildSharedSerialization(class UPackageMap* map, ClassLuaReplicated* classLuaReplicated, FLuaNetSerializationProxy* proxy, const LuaBitArray& changes);
    
    void CallOnRep(NS_SLUA::lua_State* L, const NS_SLUA::LuaVar& luaTable, const FString& propName, NS_SLUA::FProperty* prop, uint8* oldData);
    
#if (ENGINE_MINOR_VERSION>=25) && (ENGINE_MAJOR_VERSION>=4)
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
