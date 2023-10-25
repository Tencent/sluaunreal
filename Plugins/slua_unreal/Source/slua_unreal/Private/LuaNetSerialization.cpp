#include "LuaNetSerialization.h"
#include "Engine/ActorChannel.h"
#include "Net/RepLayout.h"
#include "Engine/NetConnection.h"
#include "Engine/PackageMapClient.h"
#include "LuaNet.h"
#include "LuaOverrider.h"
#include "LuaReference.h"

extern FAutoConsoleVariableRef CVarEnableLuaNetSerialization;

int32 FLuaNetSerialization::bEnableLuaNetReplicate = 1;
int32 FLuaNetSerialization::SerializeVersion = 1;

FAutoConsoleVariableRef CVarEnableLuaNetSerialization(
    TEXT("lua.EnableLuaNetSerialization"),
    FLuaNetSerialization::bEnableLuaNetReplicate,
    TEXT("enable lua net serialization. 1: on, 0: off\n"),
    ECVF_Default);

FAutoConsoleVariableRef CVarLuaNetSerializationVersion(
    TEXT("lua.LuaNetSerializationVersion"),
    FLuaNetSerialization::SerializeVersion,
    TEXT("Lua net serialization version. 0: old type, 1: new type\n"),
    ECVF_Default);

namespace NS_SLUA
{
    bool FLuaNetBaseState::IsStateEqual(INetDeltaBaseState* otherState)
    {
        FLuaNetBaseState* other = static_cast<FLuaNetBaseState*>(otherState);
        return assignTimes == other->assignTimes;
    }

    void FLuaNetSerializationProxy::AddReferencedObjects(FReferenceCollector& Collector)
    {
        if (!contentStruct.IsValid())
        {
            return;
        }

        NS_SLUA::LuaReference::addRefByStruct(Collector, contentStruct.Get(), values.GetData());
    }

    FLuaNetSerializationProxy::~FLuaNetSerializationProxy()
    {
        for (auto Iter : propListeners)
        {
            for (auto funcIter : Iter.Value)
            {
                delete funcIter;
            }
        }

        propListeners.Empty();
    }
}

bool NetSerializeItem(NS_SLUA::FProperty* Prop, FArchive& Ar, UPackageMap* Map, void* Data)
{
    if (auto StructProp = CastField<NS_SLUA::FStructProperty>(Prop))
    {
        if (StructProp->Struct->StructFlags & STRUCT_NetSerializeNative)
        {
            return StructProp->NetSerializeItem(Ar, Map, Data);
        }
        else
        {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            StructProp->SerializeItem(Ar, Data, nullptr);
#else
            StructProp->SerializeItem(FStructuredArchiveFromArchive(Ar).GetSlot(), Data, nullptr);
#endif
            return true;
        }
    }
    else if (auto MapProp = CastField<NS_SLUA::FMapProperty>(Prop))
    {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        MapProp->SerializeItem(Ar, Data, nullptr);
#else
        MapProp->SerializeItem(FStructuredArchiveFromArchive(Ar).GetSlot(), Data, nullptr);
#endif
        return true;
    }
    else if (FLuaNetSerialization::SerializeVersion == 0)
    {
        if (CastField<NS_SLUA::FArrayProperty>(Prop))
        {
            return false;
        }
    }

    return Prop->NetSerializeItem(Ar, Map, Data);
}

FLuaNetSerialization::FLuaNetSerialization()
{
}

bool FLuaNetSerialization::NetDeltaSerialize(FNetDeltaSerializeInfo& deltaParms)
{
    if (!FLuaNetSerialization::bEnableLuaNetReplicate)
    {
        return false;
    }
    
    QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization);
    auto proxy = NS_SLUA::LuaNet::getLuaNetSerializationProxy(this);
    if (!proxy)
    {
        return false;
    }
    
    auto obj = proxy->owner.Get();
    if (!obj)
    {
        return false;
    }
    if (deltaParms.GatherGuidReferences)
    {
        for (const auto& guidReferencesPair : proxy->guidReferencesMap)
        {
            const auto& guidReferences = guidReferencesPair.Value;

            deltaParms.GatherGuidReferences->Append(guidReferences.unmappedGUIDs);
            deltaParms.GatherGuidReferences->Append(guidReferences.mappedDynamicGUIDs);
        }
        return true;
    }

    if (deltaParms.MoveGuidToUnmapped)
    {
        bool bFound = false;

        const FNetworkGUID GUID = *deltaParms.MoveGuidToUnmapped;

        // Try to find the guid in the field, and make sure it's on the unmapped lists now
        for (auto& guidReferencesPair : proxy->guidReferencesMap)
        {
            auto& guidReferences = guidReferencesPair.Value;

            if (guidReferences.mappedDynamicGUIDs.Contains(GUID))
            {
                guidReferences.mappedDynamicGUIDs.Remove(GUID);
                guidReferences.unmappedGUIDs.Add(GUID);
                bFound = true;
            }
        }

        return bFound;
    }

    if (deltaParms.bUpdateUnmappedObjects)
    {
        // new version
        auto classLuaReplciated = NS_SLUA::LuaNet::getClassReplicatedProps(obj);
        auto &properties = classLuaReplciated->properties;
        auto &flatProperties = classLuaReplciated->flatProperties;
        uint8 *data = proxy->values.GetData();
        uint8 *oldData = proxy->oldValues.GetData();
        TArray<NS_SLUA::ReplicateIndexType> changes;
        
        // Loop over each item that has unmapped objects
        for (auto It = proxy->guidReferencesMap.CreateIterator(); It; ++It)
        {
            // Get the element id
            const auto index = It.Key();

            // Get a reference to the unmapped item itself
            auto& guidReferences = It.Value();

            if ((guidReferences.unmappedGUIDs.Num() == 0 && guidReferences.mappedDynamicGUIDs.Num() == 0))
            {
                // If for some reason the item is gone (or all guids were removed), we don't need to track guids for this item anymore
                It.RemoveCurrent();
                continue;        // We're done with this unmapped item
            }

            // Loop over all the guids, and check to see if any of them are loaded yet
            bool bMappedSomeGUIDs = false;

            for (auto unmappedIt = guidReferences.unmappedGUIDs.CreateIterator(); unmappedIt; ++unmappedIt)
            {
                const FNetworkGUID& GUID = *unmappedIt;

                if (deltaParms.Map->IsGUIDBroken(GUID, false))
                {
                    // Stop trying to load broken guids
                    UE_LOG(Slua, Warning, TEXT("LuaNetSerialization: Broken GUID. NetGuid: %s"), *GUID.ToString());
                    unmappedIt.RemoveCurrent();
                    continue;
                }

                {
                    UObject* mapObject = deltaParms.Map->GetObjectFromNetGUID(GUID, false);

                    if (mapObject != nullptr)
                    {
                        // This guid loaded!
                        if (GUID.IsDynamic())
                        {
                            // Move back to mapped list
                            guidReferences.mappedDynamicGUIDs.Add(GUID);
                        }
                        unmappedIt.RemoveCurrent();
                        bMappedSomeGUIDs = true;
                    }
                }
            }

            // Check to see if we loaded any guids. If we did, we can serialize the element again which will load it this time
            if (bMappedSomeGUIDs)
            {
                deltaParms.bOutSomeObjectsWereMapped = true;

                if (!deltaParms.bCalledPreNetReceive)
                {
                    // Call PreNetReceive if we are going to change a value (some game code will need to think this is an actual replicated value)
                    deltaParms.Object->PreNetReceive();
                    deltaParms.bCalledPreNetReceive = true;
                }

                if (SerializeVersion == 0)
                {
                    if (properties.IsValidIndex(index))
                    {
                        // Initialize the reader with the stored buffer that we need to read from
                        FNetBitReader reader(deltaParms.Map, guidReferences.buffer.GetData(), guidReferences.numBufferBits);
                        auto& prop = properties[index];
                        int32 propOffset = prop->GetOffset_ForInternal();
                        prop->CopyCompleteValue(oldData + propOffset, data + propOffset);
                        NetSerializeItem(prop, reader, deltaParms.Map, data + propOffset);

                        changes.Add(index);
                    }
                }
                else
                {
                    if (flatProperties.IsValidIndex(index))
                    {
                        // Initialize the reader with the stored buffer that we need to read from
                        FNetBitReader reader(deltaParms.Map, guidReferences.buffer.GetData(), guidReferences.numBufferBits);
                        ReadItem(deltaParms, *proxy, reader, classLuaReplciated, index, data, oldData);

                        auto &flatPropInfo = flatProperties[index];
                        changes.AddUnique(flatPropInfo.propIndex);
                    }
                }
            }

            // If we have no more guids, we can remove this item for good
            if (guidReferences.unmappedGUIDs.Num() == 0 && guidReferences.mappedDynamicGUIDs.Num() == 0)
            {
                It.RemoveCurrent();
            }
        }

        // If we still have unmapped items, then communicate this to the outside
        if (proxy->guidReferencesMap.Num() > 0)
        {
            deltaParms.bOutHasMoreUnmapped = true;
        }

        {
            QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization_OnRep);
            auto& repNotifies = classLuaReplciated->repNotifies;
            auto& replicatedIndexToNameMap = classLuaReplciated->replicatedIndexToNameMap;
        
            auto luaTablePtr = ULuaOverrider::getObjectLuaTable(obj);
            if (!luaTablePtr)
            {
                return false;
            }
            auto luaTable = *luaTablePtr;
            NS_SLUA::lua_State* L = luaTable.getState();
        
            for (auto index : changes)
            {
                if (repNotifies.Contains(index))
                {
                    if (auto guidReferences = proxy->guidReferencesMap.Find(index))
                    {
                        if (guidReferences->unmappedGUIDs.Num())
                        {
                            continue;
                        }
                    }

                    auto& propName = replicatedIndexToNameMap[index];
                    auto& prop = properties[index];
                    CallOnRep(L, luaTable, propName, prop, oldData + prop->GetOffset_ForInternal());
                }

                NS_SLUA::AutoStack as(L);
                NS_SLUA::LuaNet::onPropModify(L, proxy, index, [&]()
                {
                    auto& prop = properties[index];
                    NS_SLUA::LuaObject::push(L, prop, data + prop->GetOffset_ForInternal(), nullptr);
                });
            }
        }

        return true;
    }
    
    if (deltaParms.Reader)
    {
        return Read(deltaParms, proxy);
    }
    else if (deltaParms.Writer)
    {
        return Write(deltaParms, proxy);
    }
    return false;
}

bool FLuaNetSerialization::Read(FNetDeltaSerializeInfo& deltaParms, NS_SLUA::FLuaNetSerializationProxy* proxy)
{
    QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization_Read);
    auto& reader = *deltaParms.Reader;
    
    auto object = proxy->owner.Get();
    auto classLuaReplciated = NS_SLUA::LuaNet::getClassReplicatedProps(object);

    {
        auto &properties = classLuaReplciated->properties;
        auto &flatProperties = classLuaReplciated->flatProperties;
        uint8 *data = proxy->values.GetData();
        uint8 *oldData = proxy->oldValues.GetData();
    
        auto luaTablePtr = ULuaOverrider::getObjectLuaTable(object);
        NS_SLUA::lua_State* L = luaTablePtr ? luaTablePtr->getState() : nullptr;

        int32 propNum;
        if (SerializeVersion == 0)
        {
            propNum = classLuaReplciated->properties.Num();
        }
        else
        {
            propNum = classLuaReplciated->flatProperties.Num();
        }
        LuaBitArray changes(propNum);
        reader << changes;
    
        for (LuaBitArray::FIterator It(changes); It; ++It)
        {
            NS_SLUA::ReplicateIndexType index = *It;
            if (SerializeVersion == 0)
            {
                if (index >= properties.Num())
                {
                    break;
                }
            }
            else
            {
                if (index >= flatProperties.Num())
                {
                    break;
                }
            }
        
            deltaParms.Map->ResetTrackedGuids(true);

            // Remember where we started reading from, so that if we have unmapped properties, we can re-deserialize from this data later
            FBitReaderMark mark( reader );

            if (SerializeVersion)
            {
                ReadItem(deltaParms, *proxy, reader, classLuaReplciated, index, data, oldData);
            }
            else
            {
                auto &prop = properties[index];
                int32 propOffset = prop->GetOffset_ForInternal();
                prop->CopyCompleteValue(oldData + propOffset, data + propOffset);
                NetSerializeItem(prop, reader, deltaParms.Map, data + propOffset);
            }

            if (!reader.IsError())
            {
                // Track unmapped guids
                const TSet< FNetworkGUID >& trackedUnmappedGuids = deltaParms.Map->GetTrackedUnmappedGuids();
                const TSet< FNetworkGUID >& trackedMappedDynamicGuids = deltaParms.Map->GetTrackedDynamicMappedGuids();

                if (trackedUnmappedGuids.Num() || trackedMappedDynamicGuids.Num())
                {
                    auto& guidReferences = proxy->guidReferencesMap.FindOrAdd(index);

                    // If guid lists are different, make note of that, and copy respective list
                    if (!NetworkGuidSetsAreSame(guidReferences.unmappedGUIDs, trackedUnmappedGuids))
                    {
                        // Copy the unmapped guid list to this unmapped item
                        guidReferences.unmappedGUIDs = trackedUnmappedGuids;
                        deltaParms.bGuidListsChanged = true;
                    }

                    if (!NetworkGuidSetsAreSame(guidReferences.mappedDynamicGUIDs, trackedMappedDynamicGuids))
                    {
                        // Copy the mapped guid list
                        guidReferences.mappedDynamicGUIDs = trackedMappedDynamicGuids;
                        deltaParms.bGuidListsChanged = true;
                    }

                    guidReferences.buffer.Empty();
                    // Remember the number of bits in the buffer
                    guidReferences.numBufferBits = reader.GetPosBits() - mark.GetPos();
                    
                    // Copy the buffer itself
                    mark.Copy(reader, guidReferences.buffer);

                    // Hijack this property to communicate that we need to be tracked since we have some unmapped guids
                    if (trackedUnmappedGuids.Num())
                    {
                        deltaParms.bOutHasMoreUnmapped = true;
                    }
                }
                else
                {
                    // If we don't have any unmapped objects, make sure we're no longer tracking this item in the unmapped lists
                    proxy->guidReferencesMap.Remove(index);
                }
            }

            // Stop tracking unmapped objects
            deltaParms.Map->ResetTrackedGuids(false);

            if (reader.IsError())
            {
                return false;
            }

            proxy->assignTimes++;
        }

        if (SerializeVersion == 0)
        {
            proxy->dirtyMark |= changes;
        }
        else
        {
            proxy->flatDirtyMark |= changes;
        }

        if (luaTablePtr)
        {
            QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization_OnRep);

            // Copy from luaTablePtr to avaid ULuaOverrider::ObjectTableMap rehash
            auto luaTable = *luaTablePtr;
            
            auto& repNotifies = classLuaReplciated->repNotifies;
            auto& replicatedIndexToNameMap = classLuaReplciated->replicatedIndexToNameMap;
            int32 preIndex = -1;
            for (LuaBitArray::FIterator It(changes); It; ++It)
            {
                NS_SLUA::ReplicateIndexType index = *It;
                if (SerializeVersion)
                {
                    if (!flatProperties.IsValidIndex(index))
                    {
                        UE_LOG(Slua, Error, TEXT("FLuaNetSerialization::Read Error: Object[%s]'s flatProperties index[%d] is out of range[%d]!"), *object->GetFullName(), index, flatProperties.Num());
                        break;
                    }

                    index = flatProperties[index].propIndex;
                    if (preIndex == index)
                    {
                        continue;
                    }
                    preIndex = index;

                    proxy->dirtyMark.Add(index);
                }
                if (repNotifies.Contains(index))
                {
                    if (auto guidReferences = proxy->guidReferencesMap.Find(index))
                    {
                        if (guidReferences->unmappedGUIDs.Num())
                        {
                            continue;
                        }
                    }
                
                    auto& propName = replicatedIndexToNameMap[index];
                    auto& prop = properties[index];
                    CallOnRep(L, luaTable, propName, prop, oldData + prop->GetOffset_ForInternal());
                }

                NS_SLUA::AutoStack as(L);
                NS_SLUA::LuaNet::onPropModify(L, proxy, index, [&]()
                {
                    auto& prop = properties[index];
                    NS_SLUA::LuaObject::push(L, prop, data + prop->GetOffset_ForInternal(), nullptr);
                });
            }
        }
    }

    return true;
}


void FLuaNetSerialization::ReadItem(FNetDeltaSerializeInfo& deltaParms, NS_SLUA::FLuaNetSerializationProxy& proxy, FBitReader& reader,
                                    NS_SLUA::ClassLuaReplicated* classReplicated, int32 index, uint8* data, uint8* oldData)
{
    auto &flatProperties = classReplicated->flatProperties;
    auto &flatPropInfo = flatProperties[index];
    auto &prop = flatPropInfo.prop;
    int32 flatOffset = flatPropInfo.offset;
    auto arrayProp = CastField<NS_SLUA::FArrayProperty>(prop);
    if (arrayProp)
    {
        auto &arrayPropInfo = classReplicated->flatArrayPropInfos[flatOffset];
        auto &flatReplicateProperties = arrayPropInfo.properties;
        auto innerPropNum = arrayPropInfo.innerPropertyNum;
        auto innerProp = CastField<slua::FArrayProperty>(flatPropInfo.prop)->Inner;
        auto arrayHelper = FScriptArrayHelper::CreateHelperFormInnerProperty(innerProp, data + flatOffset);

        int32 arrayNum = 0;
        reader << arrayNum;
        arrayHelper.Resize(arrayNum);

        LuaBitArray changes(arrayPropInfo.innerPropertyNum * NS_SLUA::ClassLuaReplicated::MaxArrayLimit);
        reader << changes;
        for (LuaBitArray::FIterator arrIt(changes); arrIt; ++arrIt)
        {
            int32 dirtyIndex = *arrIt;
            int32 arrayIndex = dirtyIndex / innerPropNum;
            if (arrayIndex >= arrayNum)
            {
                break;
            }
            
            int32 innerIndex = dirtyIndex % innerPropNum;
            auto &innerSubPropInfo = flatReplicateProperties[innerIndex];
            auto p = innerSubPropInfo.prop;
            NetSerializeItem(p, reader, deltaParms.Map, arrayHelper.GetRawPtr(arrayIndex) + innerSubPropInfo.offset);
        }
        proxy.arrayDirtyMark[flatOffset] = changes;
    }
    else
    {
        prop->CopyCompleteValue(oldData + flatOffset, data + flatOffset);
        NetSerializeItem(prop, reader, deltaParms.Map, data + flatOffset);
    }
}

bool FLuaNetSerialization::Write(FNetDeltaSerializeInfo& deltaParms, NS_SLUA::FLuaNetSerializationProxy* proxy)
{
    QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization_Write);
    auto obj = proxy->owner.Get();
    auto actor = Cast<AActor>(obj);
    if (!actor)
    {
        auto actorComp = Cast<UActorComponent>(obj);
        if (actorComp)
        {
            actor = actorComp->GetOwner();
        }

        if (!actor && NS_SLUA::LuaNet::isLuaReplicateObject(obj))
        {
            actor = obj->GetTypedOuter<AActor>();
        }

        if (!actor)
        {
            return false;
        }
    }
    
    
    FRepState* repState = nullptr;
    auto connection = deltaParms.Map ? Cast<UPackageMapClient>(deltaParms.Map)->GetConnection() : actor->GetNetConnection();
    if (!connection)
    {
        return false;
    }

#if ENGINE_MAJOR_VERSION==5
    #pragma warning(push)
    #pragma warning(disable : 4996)
#endif
    {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        UActorChannel* actorChannel = connection->ActorChannels.FindRef(actor);
#else
        UActorChannel* actorChannel = connection->ActorChannelMap().FindRef(actor);
#endif
        if (actorChannel)
        {
            auto& objectReplicator = actorChannel->GetActorReplicationData();
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            repState = objectReplicator.RepState;
#else
            repState = objectReplicator.RepState.Get();
#endif
        }

        if (!repState)
        {
            return false;
        }

        auto replicationFrame = connection->Driver->ReplicationFrame;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        auto &conditionMap = repState->ConditionMap;
#else
        auto sendingRepState = repState->GetSendingRepState();
        if (sendingRepState->RepFlags.Value != proxy->repFlags.Value)
        {
            proxy->repFlags = sendingRepState->RepFlags;
            proxy->conditionMap = BuildConditionMapFromRepFlags(sendingRepState->RepFlags);
        }
        auto &conditionMap = proxy->conditionMap;
#endif
        if (SerializeVersion == 1)
        {
#if !UE_SERVER
            bool bIsServer = false;
#if WITH_EDITOR
            bIsServer = NM_DedicatedServer == actor->GetNetMode();
#endif
            if (bIsServer || !conditionMap[COND_ReplayOnly])
#endif
            {
                CompareProperties(obj, *proxy, replicationFrame);
            }
            UpdateChangeListMgr_V1(*proxy, replicationFrame);
        }
        else
        {
            UpdateChangeListMgr(*proxy, replicationFrame);
        }

        auto& writer = *deltaParms.Writer;
    
        NS_SLUA::FLuaNetBaseState* oldState = deltaParms.OldState ? static_cast<NS_SLUA::FLuaNetBaseState*>(deltaParms.OldState) : nullptr;

        if (!oldState || proxy->bDirtyThisFrame
            || (proxy->assignTimes != oldState->assignTimes))
        {
            auto classLuaReplicated = NS_SLUA::LuaNet::getClassReplicatedProps(obj);
            auto &properties = classLuaReplicated->properties;
            auto &flatProperties = classLuaReplicated->flatProperties;

            // update change list
            auto &changeHistorys = proxy->changeHistorys;
            auto &arrayChangeHistorys = proxy->arrayChangeHistorys; 
            if (SerializeVersion == 0)
            {
                LuaBitArray changes(properties.Num());
                if (!oldState)
                {
                    changes.MarkAll();
                }

                int historyStart = oldState ? oldState->historyEnd : proxy->historyStart;

                if (proxy->historyStart > historyStart)
                {
                    historyStart = proxy->historyStart;
                }

                for (int32 Index = historyStart; Index < proxy->historyEnd; ++Index)
                {
                    changes |= changeHistorys[Index % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY];
                }
        
                if (!changes.IsEmpty() && !proxy->sharedSerialization.IsValid())
                {
                    BuildSharedSerialization(deltaParms.Map, classLuaReplicated, proxy, changes);
                }

                auto& lifetimeConditions = classLuaReplicated->lifetimeConditions;
                if (!changes.IsEmpty())
                {
                    // filter changes
                    for (LuaBitArray::FIterator It(changes); It; ++It)
                    {
                        int32 propIndex = *It;
                        if (propIndex >= properties.Num() || !conditionMap[lifetimeConditions[propIndex]])
                        {
                            changes.Remove(propIndex);
                        }
                    }

                    if (changes.IsEmpty())
                    {
                        return false;
                    }
                }

                if (!changes.IsEmpty())
                {
                    writer << changes;

                    auto &sharedSerialization = proxy->sharedSerialization;
                    auto &sharedPropertyInfo = sharedSerialization.SharedPropertyInfo;

                    uint8 *data = proxy->values.GetData();
            
                    for (LuaBitArray::FIterator It(changes); It; ++It)
                    {
                        int32 propIndex = *It;
                        auto &sharedInfo = sharedPropertyInfo[propIndex];
                        if (sharedInfo.bShared)
                        {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                            writer.SerializeBits(sharedSerialization.SerializedProperties->GetData() + (sharedInfo.BitOffset >> 3), sharedInfo.BitLength);
#else
                            writer.SerializeBitsWithOffset(sharedSerialization.SerializedProperties->GetData(), sharedInfo.BitOffset, sharedInfo.BitLength);
#endif
                        }
                        else
                        {
                            auto &prop = properties[propIndex]; 
                            NetSerializeItem(prop, writer, deltaParms.Map, data + prop->GetOffset_ForInternal());
                        }
                    }
            
                    NS_SLUA::FLuaNetBaseState* newState = new NS_SLUA::FLuaNetBaseState();
                    check(deltaParms.NewState);
                    *deltaParms.NewState = MakeShareable(newState);

                    newState->historyEnd = proxy->historyEnd;
                    newState->assignTimes = proxy->assignTimes;

                    return true;
                }
            }
            else
            {
                LuaBitArray changes(flatProperties.Num());
                TMap<int32, LuaBitArray> arrayChanges;
                
                int historyStart = oldState ? oldState->historyEnd : proxy->historyStart;

                if (proxy->historyStart > historyStart)
                {
                    historyStart = proxy->historyStart;
                }

                for (int32 index = historyStart; index < proxy->historyEnd; ++index)
                {
                    changes |= changeHistorys[index % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY];
                    for (auto iter = arrayChangeHistorys[index % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY].CreateIterator(); iter; ++iter)
                    {
                        auto &arrayChange = arrayChanges.FindOrAdd(iter.Key());
                        arrayChange |= iter.Value();
                    }
                }
        
                if (!changes.IsEmpty() && !proxy->sharedSerialization.IsValid())
                {
                    BuildSharedSerialization_V1(deltaParms.Map, classLuaReplicated, proxy, changes, arrayChanges);
                }

                auto& lifetimeConditions = classLuaReplicated->lifetimeConditions;
                if (!changes.IsEmpty())
                {
                    // filter changes
                    for (LuaBitArray::FIterator It(changes); It; ++It)
                    {
                        int32 index = *It;
                        int32 propIndex = flatProperties[index].propIndex;

                        if (propIndex >= properties.Num() || !conditionMap[lifetimeConditions[propIndex]])
                        {
                            changes.Remove(index);
                        }
                    }

                    if (changes.IsEmpty())
                    {
                        return false;
                    }
                }

                if (!oldState || !changes.IsEmpty())
                {
                    writer << changes;

                    auto &sharedSerialization = proxy->sharedSerialization;
                    auto sharedData = sharedSerialization.SerializedProperties->GetData();
                    auto &sharedPropertyInfo = sharedSerialization.SharedPropertyInfo;
                    auto &sharedArraySerialization = proxy->sharedArraySerialization;

                    uint8 *data = proxy->values.GetData();
            
                    for (LuaBitArray::FIterator It(changes); It; ++It)
                    {
                        int32 index = *It;
                        auto &sharedInfo = sharedPropertyInfo[index];
                        if (sharedInfo.bShared)
                        {
                            auto writeShareSerializeBit = [](FBitWriter& writer, uint8* data, const NS_SLUA::FLuaRepSerializedPropertyInfo& sharedInfo)
                            {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                                writer.SerializeBits(data + (sharedInfo.BitOffset >> 3), sharedInfo.BitLength);
#else
                                writer.SerializeBitsWithOffset(data, sharedInfo.BitOffset, sharedInfo.BitLength);
#endif
                            };

                            // is array
                            if (sharedInfo.bArray)
                            {
                                auto &flatPropInfo = flatProperties[index];
                                int32 flatOffset = flatPropInfo.offset;
                                auto &arraySharedSerializetion = sharedArraySerialization[flatOffset];
                                auto sharedArrayData = arraySharedSerializetion.SerializedProperties->GetData();
                                
                                SerializeArrayProperty(writer, classLuaReplicated, arrayChanges, data, index, TFunction<void (int32, int32)>(),
                                    [&](NS_SLUA::FlatPropInfo& propInfo, FScriptArrayHelper& arrayHelper, int32 arrayIndex, int32 dirtyIndex)
                                            {
                                                auto prop = propInfo.prop;
                                                if (propInfo.bSupportSharedSerialize)
                                                {
                                                    writeShareSerializeBit(writer, sharedArrayData, arraySharedSerializetion.SharedPropertyInfo[dirtyIndex]);
                                                }
                                                else
                                                {
                                                    NetSerializeItem(prop, writer, deltaParms.Map, arrayHelper.GetRawPtr(arrayIndex) + propInfo.offset);
                                                }
                                            });
                            }
                            else
                            {
                                writeShareSerializeBit(writer, sharedData, sharedInfo);
                            }
                        }
                        else
                        {
                            auto prop = flatProperties[index].prop;
                            auto arrayProp = CastField<NS_SLUA::FArrayProperty>(prop);
                            if (arrayProp)
                            {
                                SerializeArrayProperty(writer, classLuaReplicated, arrayChanges, data, index, TFunction<void (int32, int32)>(),
                                    [&](NS_SLUA::FlatPropInfo& propInfo, FScriptArrayHelper& arrayHelper, int32 arrayIndex, int32 dirtyIndex)
                                            {
                                                auto p = propInfo.prop;
                                                NetSerializeItem(p, writer, deltaParms.Map, arrayHelper.GetRawPtr(arrayIndex) + propInfo.offset);
                                            });
                            }
                            else
                            {
                                NetSerializeItem(prop, writer, deltaParms.Map, data + flatProperties[index].offset);
                            }
                        }
                    }
            
                    NS_SLUA::FLuaNetBaseState* newState = new NS_SLUA::FLuaNetBaseState();
                    check(deltaParms.NewState);
                    *deltaParms.NewState = MakeShareable(newState);

                    newState->historyEnd = proxy->historyEnd;
                    newState->assignTimes = proxy->assignTimes;

                    return true;
                }
            }
        }
    
        return false;
    }

#if ENGINE_MAJOR_VERSION==5
    #pragma warning(pop)
#endif
}

bool FLuaNetSerialization::CompareProperties(UObject* obj, NS_SLUA::FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame)
{
    if (proxy.lastReplicationFrame == ReplicationFrame)
    {
        return false;
    }

    if (proxy.dirtyMark.IsEmpty())
    {
        return false;
    }

    auto data = proxy.values.GetData();
    auto oldData = proxy.oldValues.GetData();
    auto classLuaReplicated = NS_SLUA::LuaNet::getClassReplicatedProps(obj);
    for (LuaBitArray::FIterator It(proxy.dirtyMark); It; ++It)
    {
        int32 propIndex = *It;
        auto prop = classLuaReplicated->properties[propIndex];
        int32 propOffset = prop->GetOffset_ForInternal();
        int32 propSize = prop->GetSize();
        int32 startIndex = classLuaReplicated->propertyOffsetToMarkIndex[propOffset];
        int32 endIndex = classLuaReplicated->propertyOffsetToMarkIndex[propOffset + propSize];
        auto &flatProperties = classLuaReplicated->flatProperties;
        for (int32 flatIndex = startIndex; flatIndex < endIndex; flatIndex++)
        {
            auto flatPropInfo = flatProperties[flatIndex];
            auto flatOffset = flatPropInfo.offset;
            auto flatProp = flatPropInfo.prop;
            auto arrayProp = CastField<NS_SLUA::FArrayProperty>(flatProp);
            if (arrayProp)
            {
                auto innerProp = arrayProp->Inner;
                auto newArrayHelper = FScriptArrayHelper::CreateHelperFormInnerProperty(innerProp, data + flatOffset);
                auto oldArrayHelper = FScriptArrayHelper::CreateHelperFormInnerProperty(innerProp, oldData + flatOffset);
                int32 newArrayNum = newArrayHelper.Num();
                if (newArrayNum > NS_SLUA::ClassLuaReplicated::MaxArrayLimit)
                {
                    UE_LOG(Slua, Error, TEXT("FLuaNetSerialization::CompareProperties Error: Object[%s]'s replicated property[%s] array num[%d] is greater than MaxArrayLimit!"),
                        *obj->GetFullName(), *flatProp->GetName(), newArrayNum);
                }
                int32 newLen = FMath::Min(newArrayNum, NS_SLUA::ClassLuaReplicated::MaxArrayLimit);
                int32 oldLen = oldArrayHelper.Num();
                int32 min = FMath::Min(newLen, oldLen);
                int32 max = FMath::Max(newLen, oldLen);

                oldArrayHelper.Resize(newLen);

                auto &arrayMark = proxy.arrayDirtyMark[flatOffset];
                auto &arrayPropInfo = classLuaReplicated->flatArrayPropInfos[flatOffset];
                int32 innerPropNum = arrayPropInfo.innerPropertyNum;
                int32 elementSize = innerProp->ElementSize;
                if (min != max)
                {
                    arrayMark.AddRange(innerPropNum * min, innerPropNum * max - 1);
                }
                auto &properties = arrayPropInfo.properties;
                bool bHasDiff = false;
                // maybe much cost!
                uint8* arrayData = newArrayHelper.GetRawPtr(0);
                uint8* oldArrayData = oldArrayHelper.GetRawPtr(0);
                for (int32 arrayIndex = 0; arrayIndex < min; arrayIndex++)
                {
                    int32 elementOffset = elementSize * arrayIndex;
                    int32 markOffset = innerPropNum * arrayIndex;
                    for (int32 innerIndex = 0; innerIndex < innerPropNum; innerIndex++)
                    {
                        auto &flatArrayPropInfo = properties[innerIndex];
                        int32 offset = flatArrayPropInfo.offset + elementOffset;
                        auto innerFlatProp = flatArrayPropInfo.prop;
                        if (!innerFlatProp->Identical(oldArrayData + offset, arrayData + offset))
                        {
                            arrayMark.Add(markOffset + innerIndex);
                            innerFlatProp->CopyCompleteValue(oldArrayData + offset, arrayData + offset);
                            bHasDiff = true;
                        }
                    }
                }

                if (oldLen != newLen || bHasDiff)
                {
                    proxy.flatDirtyMark.Add(flatIndex);
                }
            }
            else if (!flatProp->Identical(oldData + flatOffset,  data+ flatOffset))
            {
                proxy.flatDirtyMark.Add(flatIndex);
                flatProp->CopyCompleteValue(oldData + flatOffset,  data + flatOffset);
            }
        }
    }
    
    return true;
}

bool FLuaNetSerialization::UpdateChangeListMgr_V1(NS_SLUA::FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame)
{
    if (proxy.lastReplicationFrame == ReplicationFrame)
    {
        return false;
    }

    if (proxy.dirtyMark.IsEmpty())
    {
        proxy.bDirtyThisFrame = false;
        proxy.lastReplicationFrame = ReplicationFrame;
        return false;
    }

    const int32 HistoryIndex = proxy.historyEnd % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY;
    LuaBitArray& newHistoryItem = proxy.changeHistorys[HistoryIndex];
    auto &arrayHistoryItem = proxy.arrayChangeHistorys[HistoryIndex];

    newHistoryItem = proxy.flatDirtyMark;
    arrayHistoryItem = proxy.arrayDirtyMark;
    
    proxy.dirtyMark.Clear();
    proxy.flatDirtyMark.Clear();
    for (auto iter = proxy.arrayDirtyMark.CreateIterator(); iter; ++iter)
    {
        iter.Value().Clear();
    }
    
    proxy.bDirtyThisFrame = true;
    
    proxy.historyEnd++;

    proxy.sharedSerialization.Reset();
    for (auto iter = proxy.sharedArraySerialization.CreateIterator(); iter; ++iter)
    {
        iter.Value().Reset();
    }

    // If we're full, merge the oldest up, so we always have room for a new entry
    if ((proxy.historyEnd - proxy.historyStart) == NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY)
    {
        const int32 firstHistoryIndex = proxy.historyStart % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY;

        proxy.historyStart++;

        const int32 secondHistoryIndex = proxy.historyStart % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY;

        // merge change list
        proxy.changeHistorys[secondHistoryIndex] |= proxy.changeHistorys[firstHistoryIndex];

        // proxy.arrayChangeHistorys[secondHistoryIndex] |= proxy.arrayChangeHistorys[firstHistoryIndex];
        auto &secondHistorys = proxy.arrayChangeHistorys[secondHistoryIndex];
        auto &firstHistorys = proxy.arrayChangeHistorys[firstHistoryIndex];
        
        for (auto iter = secondHistorys.CreateIterator(); iter; ++iter)
        {
            auto &history = iter.Value();
            history |= firstHistorys[iter.Key()];
        }
    }

    proxy.lastReplicationFrame = ReplicationFrame;
    return true;
}

void FLuaNetSerialization::BuildSharedSerialization_V1(UPackageMap* map, NS_SLUA::ClassLuaReplicated* classLuaReplicated,
    NS_SLUA::FLuaNetSerializationProxy* proxy, const LuaBitArray& changes, const TMap<int32, LuaBitArray>& arrayChanges)
{
    auto &sharedSerialization = proxy->sharedSerialization;
    auto &sharedArraySerialization = proxy->sharedArraySerialization;
    auto &sharedPropertyInfo = sharedSerialization.SharedPropertyInfo;
    sharedSerialization.Init();

    auto &serializedProperties = sharedSerialization.SerializedProperties;

    auto &properties = classLuaReplicated->flatProperties;
    sharedPropertyInfo.SetNum(properties.Num());
    
    uint8 *data = proxy->values.GetData();

    for (LuaBitArray::FIterator It(changes); It; ++It)
    {
#if ENGINE_MAJOR_VERSION==5
        #pragma warning(push)
        #pragma warning(disable : 4996)
#endif
        int32 propIndex = *It;
        if (!properties.IsValidIndex(propIndex))
        {
            UE_LOG(Slua, Error, TEXT("FLuaNetSerialization::BuildSharedSerialization index[%d] out of range[%d] with Object[%s]"), propIndex, properties.Num(), *proxy->owner->GetName());
            break;
        }

        auto &flatPropInfo = properties[propIndex];
        auto prop = flatPropInfo.prop;
        auto propOffset = flatPropInfo.offset;
        auto arrayProp = CastField<NS_SLUA::FArrayProperty>(prop);
        if (!arrayProp && !flatPropInfo.bSupportSharedSerialize)
        {
            continue;;
        }
        
        NS_SLUA::FLuaRepSerializedPropertyInfo &sharedPropInfo = sharedPropertyInfo[propIndex];
        sharedPropInfo.bShared = true;
        sharedPropInfo.BitOffset = serializedProperties->GetNumBits();

        if (arrayProp)
        {
            const uint32 bArray = 1;
            sharedPropInfo.bArray = bArray;
            
            auto &sharedArray = sharedArraySerialization.FindOrAdd(propOffset);
            sharedArray.Init();

            auto &ar = *sharedArray.SerializedProperties;
            auto prepearCallback = [&](int32 arrayNum, int32 innerPropNum)
            {
                sharedArray.SharedPropertyInfo.SetNum(arrayNum * innerPropNum);
            };
            
            SerializeArrayProperty(ar, classLuaReplicated, arrayChanges, data, propIndex, prepearCallback,
                [&](NS_SLUA::FlatPropInfo& propInfo, FScriptArrayHelper& arrayHelper, int32 arrayIndex, int32 dirtyIndex)
                                {
                                    auto p = propInfo.prop;
                                    if (propInfo.bSupportSharedSerialize)
                                    {
                                        NS_SLUA::FLuaRepSerializedPropertyInfo &sharedArrayPropInfo = sharedArray.SharedPropertyInfo[dirtyIndex];
                                        sharedArrayPropInfo.bShared = true;
                                        sharedArrayPropInfo.BitOffset = ar.GetNumBits();
                                        
                                        NetSerializeItem(p, ar, map, arrayHelper.GetRawPtr(arrayIndex) + propInfo.offset);

                                        sharedArrayPropInfo.BitLength = ar.GetNumBits() - sharedArrayPropInfo.BitOffset;

                    #if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                                        if (ar.GetNumBits() & 7)
                                        {
                                            ar.WriteAlign();
                                        }
                    #endif
                                    }
                                });
            
            sharedArray.SetValid();
        }
        else
        {
            NetSerializeItem(prop, *serializedProperties, map, data + propOffset);
        }

        sharedPropInfo.BitLength = serializedProperties->GetNumBits() - sharedPropInfo.BitOffset;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        if (serializedProperties->GetNumBits() & 7)
        {
            serializedProperties->WriteAlign();
        }
#endif
#if ENGINE_MAJOR_VERSION==5
        #pragma warning(pop)
#endif
    }

    sharedSerialization.SetValid();
}

void FLuaNetSerialization::SerializeArrayProperty(FBitWriter& writer, NS_SLUA::ClassLuaReplicated* classLuaReplicated,
                                                  const TMap<int32, LuaBitArray>& arrayChanges, uint8* data, int32 index,
                                                  PrepareSerializeArrayCallback preapareCallback,
                                                  const SerializeArrayCallback& serializeCallback)
{
    auto &flatProperties = classLuaReplicated->flatProperties;
    
    
    auto &flatPropInfo = flatProperties[index];
    int32 flatOffset = flatPropInfo.offset;
    auto &arrayPropInfo = classLuaReplicated->flatArrayPropInfos[flatOffset];
    auto &flatReplicateProperties = arrayPropInfo.properties;
    auto innerPropNum = arrayPropInfo.innerPropertyNum;
    auto arrayProp = CastField<NS_SLUA::FArrayProperty>(flatPropInfo.prop);
    auto innerProp = arrayProp->Inner;
    auto arrayHelper = FScriptArrayHelper::CreateHelperFormInnerProperty(innerProp, data + flatOffset);
    int32 arrayNum = FMath::Min(arrayHelper.Num(), NS_SLUA::ClassLuaReplicated::MaxArrayLimit);

    if (preapareCallback)
    {
        (preapareCallback)(arrayNum, innerPropNum);
    }
    
    writer << arrayNum;

    auto &arrayMark = arrayChanges[flatOffset];
    writer << arrayMark;

    for (LuaBitArray::FIterator arrIt(arrayMark); arrIt; ++arrIt)
    {
        int32 dirtyIndex = *arrIt;
        int32 arrayIndex = dirtyIndex / innerPropNum;

        if (arrayIndex >= arrayNum)
        {
            break;
        }
                                    
        int32 innerIndex = dirtyIndex % innerPropNum;
        auto &innerSubPropInfo = flatReplicateProperties[innerIndex];
        serializeCallback(innerSubPropInfo, arrayHelper, arrayIndex, dirtyIndex);
    }
}

bool FLuaNetSerialization::UpdateChangeListMgr(NS_SLUA::FLuaNetSerializationProxy& proxy, uint32 ReplicationFrame)
{
    if (proxy.lastReplicationFrame == ReplicationFrame)
    {
        return false;
    }

    if (proxy.dirtyMark.IsEmpty())
    {
        proxy.bDirtyThisFrame = false;
        proxy.lastReplicationFrame = ReplicationFrame;
        return false;
    }

    const int32 HistoryIndex = proxy.historyEnd % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY;
    LuaBitArray& newHistoryItem = proxy.changeHistorys[HistoryIndex];

    newHistoryItem = proxy.dirtyMark;
    proxy.dirtyMark.Clear();
    proxy.bDirtyThisFrame = true;
    
    proxy.historyEnd++;

    proxy.sharedSerialization.Reset();

    // If we're full, merge the oldest up, so we always have room for a new entry
    if ((proxy.historyEnd - proxy.historyStart) == NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY)
    {
        const int32 firstHistoryIndex = proxy.historyStart % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY;

        proxy.historyStart++;

        const int32 secondHistoryIndex = proxy.historyStart % NS_SLUA::FLuaNetSerializationProxy::MAX_CHANGE_HISTORY;

        // merge change list
        proxy.changeHistorys[secondHistoryIndex] |= proxy.changeHistorys[firstHistoryIndex];
    }

    proxy.lastReplicationFrame = ReplicationFrame;
    return true;
}

void FLuaNetSerialization::BuildSharedSerialization(UPackageMap* map, NS_SLUA::ClassLuaReplicated* classLuaReplicated,
    NS_SLUA::FLuaNetSerializationProxy* proxy, const LuaBitArray& changes)
{
    auto &sharedSerialization = proxy->sharedSerialization;
    auto &sharedPropertyInfo = sharedSerialization.SharedPropertyInfo;
    auto &serializedProperties = sharedSerialization.SerializedProperties;

    auto &properties = classLuaReplicated->properties;
    sharedPropertyInfo.SetNum(properties.Num());
    
    uint8 *data = proxy->values.GetData();

    for (LuaBitArray::FIterator It(changes); It; ++It)
    {
#if ENGINE_MAJOR_VERSION==5
        #pragma warning(push)
        #pragma warning(disable : 4996)
#endif
        int32 propIndex = *It;
        if (!properties.IsValidIndex(propIndex))
        {
            UE_LOG(Slua, Error, TEXT("FLuaNetSerialization::BuildSharedSerialization index[%d] out of range[%d] with Object[%s]"), propIndex, properties.Num(), *proxy->owner->GetName());
            break;
        }
        auto prop = properties[propIndex];
        if (!IsSupportSharedSerialize(prop))
        {
            continue;;
        }
        
        NS_SLUA::FLuaRepSerializedPropertyInfo &sharedPropInfo = sharedPropertyInfo[propIndex];
        sharedPropInfo.bShared = true;
        sharedPropInfo.BitOffset = serializedProperties->GetNumBits();

        NetSerializeItem(prop, *serializedProperties, map, data + prop->GetOffset_ForInternal());

        sharedPropInfo.BitLength = serializedProperties->GetNumBits() - sharedPropInfo.BitOffset;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        if (serializedProperties->GetNumBits() & 7)
        {
            serializedProperties->WriteAlign();
        }
#endif
#if ENGINE_MAJOR_VERSION==5
        #pragma warning(pop)
#endif
    }

    sharedSerialization.SetValid();
}

bool FLuaNetSerialization::IsSupportSharedSerialize(NS_SLUA::FProperty* prop)
{
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    if (Cast<UObjectProperty>(prop))
    {
        return false;
    }

    if (auto structProp = Cast<UStructProperty>(prop))
    {
        auto cppStructOps = structProp->Struct->GetCppStructOps();
        if (cppStructOps && cppStructOps->IsPlainOldData())
        {
            return true;
        }

        return false;
    }

    return true;
#else
    return prop->SupportsNetSharedSerialization();
#endif
}


void FLuaNetSerialization::CallOnRep(NS_SLUA::lua_State* L, const slua::LuaVar& luaTable, const FString& propName, NS_SLUA::FProperty* prop, uint8* oldData)
{
    QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization_CallOnRep);
    const FString funcName = "OnRep_" + propName;
    if (!RepFuncMap.Contains(funcName))
    {
        RepFuncMap.Add(funcName, luaTable.getFromTable<NS_SLUA::LuaVar>(funcName));
    }
    const auto &repFunc = RepFuncMap[funcName];
    if (repFunc.isFunction())
    {
        QUICK_SCOPE_CYCLE_COUNTER(LuaNetDeltaSerialization_CallOnRep_LuaCall);
        int errorHandle = NS_SLUA::LuaState::pushErrorHandler(L);
        // Push rep function.
        repFunc.push(L);
        // Push self and old value.
        luaTable.push(L);
        NS_SLUA::LuaObject::push(L, prop, oldData, nullptr);

        // Call OnRep_PropName function.
        if (lua_pcall(L, 2, 0, errorHandle))
            lua_pop(L, 1);
        // Remove err handler.
        lua_pop(L, 1);
    }
}

#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
TStaticBitArray<COND_Max> FLuaNetSerialization::BuildConditionMapFromRepFlags(const FReplicationFlags RepFlags)
{
    TStaticBitArray<COND_Max> ConditionMap;

    // Setup condition map
    const bool bIsInitial = RepFlags.bNetInitial ? true : false;
    const bool bIsOwner = RepFlags.bNetOwner ? true : false;
    const bool bIsSimulated = RepFlags.bNetSimulated ? true : false;
    const bool bIsPhysics = RepFlags.bRepPhysics ? true : false;
    const bool bIsReplay = RepFlags.bReplay ? true : false;

    ConditionMap[COND_None] = true;
    ConditionMap[COND_InitialOnly] = bIsInitial;

    ConditionMap[COND_OwnerOnly] = bIsOwner;
    ConditionMap[COND_SkipOwner] = !bIsOwner;

    ConditionMap[COND_SimulatedOnly] = bIsSimulated;
    ConditionMap[COND_SimulatedOnlyNoReplay] = bIsSimulated && !bIsReplay;
    ConditionMap[COND_AutonomousOnly] = !bIsSimulated;

    ConditionMap[COND_SimulatedOrPhysics] = bIsSimulated || bIsPhysics;
    ConditionMap[COND_SimulatedOrPhysicsNoReplay] = (bIsSimulated || bIsPhysics) && !bIsReplay;

    ConditionMap[COND_InitialOrOwner] = bIsInitial || bIsOwner;
    ConditionMap[COND_ReplayOrOwner] = bIsReplay || bIsOwner;
    ConditionMap[COND_ReplayOnly] = bIsReplay;
    ConditionMap[COND_SkipReplay] = !bIsReplay;

    ConditionMap[COND_Custom] = true;
    ConditionMap[COND_Never] = false;

    return ConditionMap;
}
#endif