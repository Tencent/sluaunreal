// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaNet.h"
#include "LuaOverrider.h"
#include "LuaOverriderInterface.h"
#include "LuaNetSerialization.h"
#include "Engine/NetDriver.h"

namespace NS_SLUA
{
    const char* LuaNet::ADD_LISTENER_FUNC = "AddLuaNetListener";
    const char* LuaNet::REMOVE_LISTENER_FUNC = "RemoveLuaNetListener";
    LuaNet::ClassLuaReplicatedMap LuaNet::classLuaReplicatedMap;
    LuaNet::LuaNetSerializationMap LuaNet::luaNetSerializationMap;
    LuaNet::ObjectToLuaNetAddressMap LuaNet::objectToLuaNetAddressMap;
    TArray<const UClass*> LuaNet::luaReplicateClasses;
    TSet<TWeakObjectPtr<UClass>> LuaNet::addedRPCClasses;
#if WITH_EDITOR
    TSet<TWeakObjectPtr<UFunction>> LuaNet::luaRPCFuncs;
#endif
    TMap<FString, EFunctionFlags> LuaNet::luaRPCTypeMap = {
        {TEXT("MulticastRPC"), FUNC_NetMulticast},
        {TEXT("ServerRPC"), FUNC_NetServer},
        {TEXT("ClientRPC"), FUNC_NetClient}
    };
    
    void LuaNet::addLuaRepilcateClass(const UClass* someBase)
    {
        luaReplicateClasses.AddUnique(someBase);
    }

    bool LuaNet::isLuaReplicateObject(UObject* obj)
    {
        static const EClassCastFlags ActorCastFlag = AActor::StaticClassCastFlags();
        // Try to assign net replicated prop first.
        auto cls = obj->GetClass();
        if (cls->HasAnyCastFlag(ActorCastFlag) || Cast<UActorComponent>(obj))
        {
            return true;
        }

        for (auto repClass : luaReplicateClasses)
        {
            if (obj->IsA(repClass))
            {
                return true;
            }
        }
        return false;
    }

    ClassLuaReplicated* LuaNet::getClassReplicatedProps(const UObject* obj)
    {
        auto cls = obj->GetClass();
        auto classLuaReplicatedPtr = classLuaReplicatedMap.Find(cls);
        if (classLuaReplicatedPtr)
        {
            return *classLuaReplicatedPtr;
        }

        return nullptr;
    }

    void LuaNet::removeObjectTable(UObject* obj)
    {
        void** ptr = objectToLuaNetAddressMap.Find(obj);
        if (ptr)
        {
            auto proxy = luaNetSerializationMap.FindChecked(*ptr);
            {
                uint8 *data = proxy->values.GetData();
                uint8 *oldData = proxy->oldValues.GetData();
                for (TFieldIterator<FProperty> it(proxy->contentStruct.Get()); it; ++it)
                {
                    auto p = *it;
                    p->DestroyValue_InContainer(data);
                    p->DestroyValue_InContainer(oldData);
                }
            }
            delete proxy;

            luaNetSerializationMap.Remove(*ptr);
            objectToLuaNetAddressMap.Remove(obj);
        }
    }

    void LuaNet::onObjectDeleted(UClass* cls)
    {
        auto classLuaReplicatedPtr = classLuaReplicatedMap.Find(cls);
        if (classLuaReplicatedPtr)
        {
            delete * classLuaReplicatedPtr;
            classLuaReplicatedMap.Remove(cls);
        }
    }

    void LuaNet::addLuaRPCType(const FString& rpcType, EFunctionFlags netFlag)
    {
        luaRPCTypeMap.Add(rpcType, netFlag);
    }

    ClassLuaReplicated* LuaNet::addClassReplicatedProps(slua::lua_State* L, UObject* obj, const slua::LuaVar& luaModule)
    {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        typedef NS_SLUA::EPropertyClass EPropertyClass;
#endif

        if (isLuaReplicateObject(obj))
        {
            auto cls = obj->GetClass();
            auto classReplicatedPtr = classLuaReplicatedMap.Find(cls);
            
            if (classReplicatedPtr)
            {
                return *classReplicatedPtr;
            }
            else
            {
                FProperty* prop = cls->FindPropertyByName(TEXT("LuaNetSerialization"));
                if (prop)
                {
                    NS_SLUA::LuaVar getLifetimeFunc = luaModule.getFromTable<NS_SLUA::LuaVar>("GetLifetimeReplicatedProps");
                    if (getLifetimeFunc.isFunction())
                    {
                        auto luaReplicatedTable = getLifetimeFunc.call();
                        if (luaReplicatedTable.isTable())
                        {
                            auto classReplicatedPtr = classLuaReplicatedMap.Add(cls, new ClassLuaReplicated());
                            auto& classReplicated = *classReplicatedPtr;
                            classReplicated.ownerProperty = prop;
                    
                            auto &replicatedNameToIndexMap = classReplicated.replicatedNameToIndexMap;
                            auto &replicatedIndexToNameMap = classReplicated.replicatedIndexToNameMap;
                            auto &properties = classReplicated.properties;
                            auto &lifetimeConditions = classReplicated.lifetimeConditions;
                            
                            NS_SLUA::AutoStack as(L);
                            
                            {
                                auto ustruct = NewObject<UStruct>();
                                ustruct->AddToRoot();
                            
                                classReplicated.ustruct = ustruct;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                                NS_SLUA::FField** currentField = &(ustruct->Children);
#else
                                FField** currentField = &(ustruct->ChildProperties);
#endif
                            
                                luaReplicatedTable.push(L);
                                ReplicateIndexType index = 0;
                                lua_pushnil(L);
                                while (lua_next(L, -2))
                                {
                                    lua_geti(L, -1, 1);
                                    const char* name = luaL_checkstring(L, -1);
                                    lua_pop(L, 1);

                                    lua_geti(L, -1, 2);
                                    ELifetimeCondition lifeCond = (ELifetimeCondition)luaL_checkinteger(L, -1);
                                    lua_pop(L, 1);

                                    lua_geti(L, -1, 3);
                                
                                    FProperty *childProperty = nullptr;
                                    if (lua_isinteger(L, -1))
                                    {
                                        EPropertyClass propertyClass = (EPropertyClass)lua_tointeger(L, -1);
                                        if (propertyClass == EPropertyClass::Array)
                                        {
                                            lua_pop(L, 1);
                                            
                                            lua_geti(L, -1, 4);
                                            NS_SLUA::LuaVar propClassVar(L, -1);
                                            if (propClassVar.isInt())
                                            {
                                                childProperty = NS_SLUA::PropertyProto::createProperty(NS_SLUA::PropertyProto(EPropertyClass::Array, (EPropertyClass)lua_tointeger(L, -1)), ustruct);
                                            }
                                            else if (auto scriptStruct = propClassVar.asUserdata<UScriptStruct>("UScriptStruct"))
                                            {
                                                childProperty = NS_SLUA::PropertyProto::createProperty(NS_SLUA::PropertyProto(EPropertyClass::Array, scriptStruct), ustruct);
                                            }
                                            else if (auto uclass = propClassVar.asUserdata<UClass>("UClass"))
                                            {
                                                childProperty = NS_SLUA::PropertyProto::createProperty(NS_SLUA::PropertyProto(EPropertyClass::Array, uclass), ustruct);
                                            }
                                        }
                                        else
                                        {
                                            childProperty = NS_SLUA::PropertyProto::createProperty(NS_SLUA::PropertyProto(propertyClass), ustruct);
                                        }
                                        
                                        childProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);
                                    }
                                    else if (lua_isuserdata(L, -1))
                                    {
                                        NS_SLUA::LuaVar propClassVar(L, -1);
                                        if (auto scriptStruct = propClassVar.asUserdata<UScriptStruct>("UScriptStruct"))
                                        {
                                            childProperty = NS_SLUA::PropertyProto::createProperty(NS_SLUA::PropertyProto(EPropertyClass::Struct, scriptStruct), ustruct);
                                        }
                                        else if (auto uclass = propClassVar.asUserdata<UClass>("UClass"))
                                        {
                                            childProperty = NS_SLUA::PropertyProto::createProperty(NS_SLUA::PropertyProto(EPropertyClass::Class, uclass), ustruct);
                                        }
                                    }
                                    lua_pop(L, 1);

                                    if (childProperty)
                                    {
                                        *currentField = childProperty;
                                        currentField = &childProperty->Next;

                                        FString keyName = UTF8_TO_TCHAR(name);
                                        replicatedIndexToNameMap.Add(keyName);
                                        replicatedNameToIndexMap.Add(keyName, index++);
                                        properties.Add(childProperty);

                                        lifetimeConditions.Add(lifeCond);
                                    }

                                    lua_pop(L, 1);
                                }

                                ustruct->StaticLink(true);

                                int32 flatIndex = 0;
                                initFlatReplicatedProps(classReplicated, classReplicated.propertyOffsetToMarkIndex, ustruct, flatIndex, 0, 0, nullptr);
                            }

                            auto &repNotifies = classReplicated.repNotifies;
                            luaModule.push(L);
                            for (ReplicateIndexType i =0, n = replicatedIndexToNameMap.Num(); i < n; ++i)
                            {
                                auto &propName = replicatedIndexToNameMap[i];
                                if (lua_getfield(L, -1, TCHAR_TO_UTF8(*(TEXT("OnRep_") + propName))) != LUA_TNIL)
                                {
                                    repNotifies.Add(i);
                                }
                                lua_pop(L, 1);
                            }

                            lua_pop(L, 1);

                            return &classReplicated;
                        }
                    }
                }
            }
        }

        return nullptr;
    }

    void LuaNet::initFlatReplicatedProps(ClassLuaReplicated& classReplicated,
                                         ReplicateOffsetToMarkType& markIndex, UStruct* ustruct,
                                         int32& index, const int32 offset, int32 ownerPropIndex, NS_SLUA::FlatArrayPropInfo* arrayInfo)
    {
        bool outMost = ustruct == classReplicated.ustruct;

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        for (FProperty* iter = (FProperty*)ustruct->Children; iter != nullptr; iter = (FProperty*)iter->Next)
#else
        for (auto iter = (FProperty*)ustruct->ChildProperties; iter != nullptr; iter = (FProperty*)iter->Next)
#endif
        {
            int32 propOffset = offset + iter->GetOffset_ForInternal();
            if (auto structProp = CastField<FStructProperty>(iter))
            {
                initFlatReplicatedProps(classReplicated, markIndex, structProp->Struct, index, propOffset, ownerPropIndex, arrayInfo);
            }
            else
            {
                markIndex.Add(propOffset, index);
                markIndex.Add(propOffset + iter->GetSize(), index + 1);
                if (arrayInfo)
                {
                    arrayInfo->properties.Add({ownerPropIndex, propOffset, FLuaNetSerialization::IsSupportSharedSerialize(iter), iter});
                }
                else
                {
                    classReplicated.flatProperties.Add({ownerPropIndex, propOffset, FLuaNetSerialization::IsSupportSharedSerialize(iter),iter});
                }
                index++;
            }

            if (auto arrayProp = CastField<FArrayProperty>(iter))
            {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                ensureMsgf(!arrayInfo, TEXT("Array in array is forbidden with Class[%s]!"), *classReplicated.ownerProperty->GetOuter()->GetName());
#else
                ensureMsgf(!arrayInfo, TEXT("Array in array is forbidden with Class[%s]!"), *classReplicated.ownerProperty->GetOwnerUObject()->GetName());
#endif

                auto &arrayPropInfo = classReplicated.flatArrayPropInfos.Add(propOffset);
                arrayPropInfo.propIndex = ownerPropIndex;
                arrayPropInfo.offset = propOffset;
                auto inner = arrayProp->Inner;
                auto innerStructProp = CastField<FStructProperty>(inner);
                if (innerStructProp)
                {
                    int32 arrayIndex = 0;
                    initFlatReplicatedProps(classReplicated, arrayPropInfo.markIndex, innerStructProp->Struct, arrayIndex, 0, ownerPropIndex, &arrayPropInfo);
                    arrayPropInfo.innerPropertyNum = arrayIndex;
                }
                else
                {
                    arrayPropInfo.properties.Add({ownerPropIndex, 0, FLuaNetSerialization::IsSupportSharedSerialize(inner), inner});
                    arrayPropInfo.innerPropertyNum = 1;
                }
            }

            if (outMost)
            {
                ownerPropIndex++;
            }
        }

        int32 structEndOffset = offset + ustruct->GetPropertiesSize();
        if (!markIndex.Contains(structEndOffset))
        {
            markIndex.Add(structEndOffset, index);
        }
    }

    void LuaNet::initLuaReplicatedProps(slua::lua_State* L, UObject* obj, const ClassLuaReplicated& classReplicated,
        const slua::LuaVar& luaTable)
    {
        auto prop = classReplicated.ownerProperty.Get();
        if (!prop)
        {
            return;
        }

        auto& luaReplicatedMap = classReplicated.replicatedNameToIndexMap;
        if (!luaReplicatedMap.Num())
        {
            return;
        }

        {
            uint8* data = nullptr;
            uint8* oldData = nullptr;
#if WITH_EDITOR
            bool bIsInited = false;
            if (objectToLuaNetAddressMap.Contains(obj))
            {
                bIsInited = true;
            }

            if (!bIsInited)
            {
#endif
                FLuaNetSerialization* luaNetSerialization = prop->ContainerPtrToValuePtr<FLuaNetSerialization>(obj);
                objectToLuaNetAddressMap.Add(obj, luaNetSerialization);
                FLuaNetSerializationProxy *newProxy = new FLuaNetSerializationProxy();
                FLuaNetSerializationProxy &proxy = *luaNetSerializationMap.Add(luaNetSerialization, newProxy);
                proxy.owner = obj;
                proxy.contentStruct = classReplicated.ustruct;
                proxy.dirtyMark = LuaBitArray(classReplicated.properties.Num());

                proxy.flatDirtyMark = LuaBitArray(classReplicated.flatProperties.Num());
                for (auto iter : classReplicated.flatArrayPropInfos)
                {
                    proxy.arrayDirtyMark.Add(iter.Key, LuaBitArray(iter.Value.innerPropertyNum * ClassLuaReplicated::MaxArrayLimit));
                }
                
                auto &content = proxy.values;
                auto &oldContent = proxy.oldValues;
                int32 propertiesSize = classReplicated.ustruct->GetPropertiesSize();
            
                content.SetNumZeroed(propertiesSize);
                oldContent.SetNumZeroed(propertiesSize);
            
                data = content.GetData();
                oldData = oldContent.GetData();
                for(TFieldIterator<FProperty> it(proxy.contentStruct.Get());it;++it)
                {
                    auto p = *it;
                    if (!p->HasAnyPropertyFlags(CPF_ZeroConstructor))
                    {
                        p->InitializeValue_InContainer(data);
                        p->InitializeValue_InContainer(oldData);
                    }
                }
#if WITH_EDITOR
            }
#endif

            NS_SLUA::AutoStack as(L);
        
            luaTable.push(L);
            for (auto &iter: luaReplicatedMap)
            {
                // iter.Key
                lua_getfield(L, -1, TCHAR_TO_UTF8(*iter.Key));

                bool bHasValue = !lua_isnil(L, -1);
#if WITH_EDITOR
                if (!bIsInited)
                {
#endif
                    if (bHasValue)
                    {
                        auto p = classReplicated.properties[iter.Value];
                        auto checker = NS_SLUA::LuaObject::getChecker(p);
                        auto propOffset = p->GetOffset_ForInternal();
                        if (checker)
                        {
                            checker(L, p, data + propOffset, -1, true);
                        }
                        p->CopyCompleteValue(oldData + propOffset, data + propOffset);
                    }
#if WITH_EDITOR
                }
#endif

                if (bHasValue)
                {
                    lua_pop(L, 1);

                    lua_pushnil(L);
                    lua_setfield(L, -2, TCHAR_TO_UTF8(*iter.Key));
                }
                else
                {
                    lua_pop(L, 1);
                }
            }
        }
    }

    FLuaNetSerializationProxy* LuaNet::getLuaNetSerializationProxy(FLuaNetSerialization* luaNetSerialization)
    {
        auto netSerializationPtr = luaNetSerializationMap.Find(luaNetSerialization);
        if (!netSerializationPtr)
        {
            return nullptr;
        }

        return *netSerializationPtr;
    }

    void LuaNet::addClassRPC(lua_State* L, UClass* cls, const FString& luaFilePath)
    {
        if (!L || !cls) { return; }
        if (addedRPCClasses.Contains(cls)) { return; }

        LuaVar cppSuperModule;
        addClassRPCRecursive(L, cls, luaFilePath, cppSuperModule);

#if UE_BUILD_DEVELOPMENT
        LuaState* state = LuaState::get(L);
        if (!state) { return; }
        UGameInstance* gameInstance = state->getGameInstance();
        if (!gameInstance) { return; }
        UWorld* world = gameInstance->GetWorld();
        if (!world) { return; }
        UNetDriver* netDriver = world->GetNetDriver();
        if (!netDriver) { return; }
        TSharedPtr<FClassNetCacheMgr> netCache = netDriver->NetCache;
        if (!netCache.IsValid()) { return; }

        const FClassNetCache* newClassCache = netCache->GetClassNetCache(cls);
        if (!newClassCache) { return; }

        for (int32 index = 0; index < newClassCache->GetMaxIndex(); index++)
        {
            const FFieldNetCache* fieldCache = newClassCache->GetFromIndex(index);

            FString fieldName = TEXT("None");
            FString outerName = TEXT("None");
            uint32 checkSum = 0;
            if (fieldCache)
            {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                fieldName = fieldCache->Field ? fieldCache->Field->GetFName().ToString() : fieldName;
                if (fieldCache->Field && fieldCache->Field->GetOuter())
                {
                    outerName = fieldCache->Field->GetOuter()->GetFName().ToString();
                }
                
#else
                fieldName = fieldCache->Field ? fieldCache->Field.GetFName().ToString() : fieldName;
                if (fieldCache->Field && fieldCache->Field.GetOutermost())
                {
                    outerName = fieldCache->Field.GetOutermost()->GetFName().ToString();
                }
#endif
                checkSum = fieldCache->FieldChecksum;
            }
            UE_LOG(Slua, Log, TEXT("LuaOverrider::addClassRPC NewClassCache ClassName:%s FieldName:%s, Index:%d, CheckSum:%u OuterName:%s"), *cls->GetName(), *fieldName, index, checkSum, *outerName);
        }
#endif
    }

    bool LuaNet::addClassRPCRecursive(lua_State* L, UClass* cls, const FString& luaFilePath, LuaVar& cppSuperModule)
    {
        if (luaFilePath.IsEmpty()) { return false; }

        auto sluaState = LuaState::get(L);
        const LuaVar luaModule = sluaState->requireModule(TCHAR_TO_UTF8(*luaFilePath));
        if (!luaModule.isValid()) { return false; }
        if (!luaModule.isTable()) { return false; }

        if (addedRPCClasses.Contains(cls))
        { 
            cppSuperModule = luaModule;
            return false; 
        }
        
        bool bAdded = false;
        UClass* superCls = cls->GetSuperClass();
        if (superCls && superCls->ImplementsInterface(ULuaOverriderInterface::StaticClass()))
        {
            bool bHookInstancedObj;
            const FString superLuaFilePath = LuaOverrider::getLuaFilePath(nullptr, superCls, true, bHookInstancedObj);
            bAdded |= addClassRPCRecursive(L, superCls, superLuaFilePath, cppSuperModule);
        }

        // if LuaModule equals to CppSuperModule, then LuaRPCs are already hooked in Super Class. No need to hook again.
        if (luaModule != cppSuperModule) 
        {
            auto commonModule = findFirstCommomModule(L, luaModule, cppSuperModule);
            bAdded |= addModuleRPCRecursive(L, cls, luaModule, commonModule);
            cppSuperModule = luaModule;
        }

        if (bAdded)
        {
            cls->ClearFunctionMapsCaches();
            addedRPCClasses.Add(cls);
        }

        return bAdded;
    }

    LuaVar getLuaImpl(lua_State* L, const LuaVar& luaModule)
    {
        LuaVar ret;

        luaModule.push(L);
        if (lua_getmetatable(L, -1))
        {
            lua_pop(L, 1); // pop metatable

            // Find subclass function names.
            int subType = lua_getfield(L, -1, "__inner_impl");
            if (subType == LUA_TTABLE)
            {
                ret.set(L, -1);
            }
            lua_pop(L, 1); // pop __inner_impl
        }
        lua_pop(L, 1); // pop luaModule
        return ret;
    }

    LuaVar LuaNet::findFirstCommomModule(lua_State* L, const LuaVar& A, const LuaVar& B)
    {
        if (A.isTable() && !B.isTable())
        {
            return B;
        }

        if (!A.isTable() && B.isTable())
        {
            return A;
        }

        LuaVar temp1 = A;
        LuaVar temp2 = B;

        while (temp1 != temp2)
        {
            auto impl = getLuaImpl(L, temp1);
            temp1 = impl.isTable() ? impl.getFromTable<LuaVar>("__super") : LuaVar();

            if (temp1 == B) // Adapt to most situations and prune.
            {
                break;
            }

            if (!temp1.isTable())
            {
                temp1 = B;
            }
            
            impl = getLuaImpl(L, temp2);
            temp2 = impl.isTable() ? impl.getFromTable<LuaVar>("__super") : LuaVar();
            if (!temp2.isTable())
            {
                temp2 = A;
            }
        }

        return temp1;
    }

    bool LuaNet::addModuleRPCRecursive(lua_State* L, UClass* cls, const LuaVar& luaModule, const LuaVar& cppSuperModule)
    {
        bool bAdded = false;
        if (!luaModule.isTable()) { return bAdded; }

        // if LuaModule equals to CppSuperModule, then LuaRPCs are already hooked in Super Class. No need to hook again.
        if (luaModule == cppSuperModule) { return bAdded; }

        LuaVar luaImpl = getLuaImpl(L, luaModule);
        if (luaImpl.isTable())
        {
            LuaVar luaSuperModule = luaImpl.getFromTable<LuaVar>("__super");
            bAdded |= addModuleRPCRecursive(L, cls, luaSuperModule, cppSuperModule);
        }

        for (TMap<FString, EFunctionFlags>::TConstIterator iter(LuaNet::luaRPCTypeMap); iter; ++iter)
        {
            bAdded |= addClassRPCByType(L, cls, luaModule, iter.Key(), iter.Value());
        }
        return bAdded;
    }

    bool LuaNet::addClassRPCByType(lua_State* L, UClass* cls, const LuaVar& luaModule, const FString& repType, EFunctionFlags netFlag)
    {
#if WITH_EDITOR
        // Don't move this line of code to below!
        auto& funcs = LuaOverrider::classAddedFuncs.FindOrAdd(cls);
#endif
        bool bAdded = false;
        if (!luaModule.isTable())
        {
            return bAdded;
        }
        LuaVar luaImpl = getLuaImpl(L, luaModule);
        if (!luaImpl.isTable())
        {
            return bAdded;
        }
        LuaVar rpcList = luaImpl.getFromTable<LuaVar>(repType);
        if (!rpcList.isTable())
        {
            return bAdded;
        }

        LuaVar key;
        LuaVar value;
        TArray<FString> rpcNames;
        while (rpcList.next(key, value))
        {
            if (!key.isString()) { continue; }
            rpcNames.Add(key.asString());
        }
        rpcNames.Sort();

        for (FString& rpcName: rpcNames)
        {
            LuaVar rpcTable = rpcList.getFromTable<LuaVar>(rpcName);
            if (!rpcTable.isTable()) { continue; }

            bool bReliable = rpcTable.getFromTable<bool>("Reliable");

            UFunction* func = cls->FindFunctionByName(FName(*rpcName), EIncludeSuperFlag::ExcludeSuper);
            if (func){ continue;}

            func = NewObject<UFunction>(cls, *rpcName, RF_Public);

            func->FunctionFlags = FUNC_Public | FUNC_Net | netFlag;
            if (bReliable)
            {
                func->FunctionFlags |= FUNC_NetReliable;
            }
            func->ReturnValueOffset = MAX_uint16;
            func->FirstPropertyToInit = NULL;
            func->Next = cls->Children;
            cls->Children = func;

            LuaVar params = rpcTable.getFromTable<NS_SLUA::LuaVar>("Params");
            if (params.isTable())
            {
                LuaVar index;
                LuaVar paramType;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                FField** propertyStorageLocation = &(func->Children);
#else
                FField** propertyStorageLocation = &(func->ChildProperties);
#endif
                while (params.next(index, paramType))
                {
                    FProperty* newProperty = nullptr;
                    FName paramName(*FString::Printf(TEXT("%s_param%s"), *rpcName, UTF8_TO_TCHAR(index.toString())));
                    if (paramType.isInt())
                    {
                        EPropertyClass propertyClass = (EPropertyClass)paramType.asInt();
                        newProperty = PropertyProto::createProperty(PropertyProto(propertyClass), func, paramName);
                        newProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);
                    } 
                    else if (paramType.isUserdata("UScriptStruct"))
                    {
                        UScriptStruct* scriptStruct = paramType.castTo<UScriptStruct*>();
                        if (scriptStruct)
                        {
                            newProperty = PropertyProto::createProperty(PropertyProto(EPropertyClass::Struct, scriptStruct), func, paramName);
                        }
                    }
                    else if (paramType.isUserdata("UClass"))
                    {
                        UClass* propertyClass = paramType.castTo<UClass*>();
                        if (propertyClass)
                        {
                            newProperty = PropertyProto::createProperty(PropertyProto(EPropertyClass::Object, propertyClass), func, paramName);
                        }
                    }
                    else if (paramType.isTable())
                    {
                        LuaVar mainType = paramType.getAt(1);
                        LuaVar subType = paramType.getAt(2);
                        if (mainType.isInt())
                        {
                            EPropertyClass propertyClass = (EPropertyClass)mainType.asInt();
                            if (subType.isUserdata("UScriptStruct"))
                            {
                                UScriptStruct* scriptStruct = subType.castTo<UScriptStruct*>();
                                if (scriptStruct)
                                {
                                    newProperty = PropertyProto::createProperty(PropertyProto(propertyClass, scriptStruct), func, paramName);
                                }
                            }
                            else if (subType.isUserdata("UClass"))
                            {
                                UClass* subClass = subType.castTo<UClass*>();
                                if (subClass)
                                {
                                    newProperty = PropertyProto::createProperty(PropertyProto(propertyClass, subClass), func, paramName);
                                }
                            }
                            else if (subType.isInt())
                            {
                                EPropertyClass typeEnum = subType.castTo<EPropertyClass>();
                                newProperty = PropertyProto::createProperty(PropertyProto(propertyClass, typeEnum), func, paramName);
                            }
                        }
                    }

                    if (newProperty)
                    {
                        newProperty->SetPropertyFlags(CPF_Parm);

                        *propertyStorageLocation = newProperty;
                        propertyStorageLocation = &(newProperty->Next);
                    }
                }
            }

            func->StaticLink(true);

            cls->AddFunctionToFunctionMap(func, *rpcName);
            cls->NetFields.Add(func);
#if WITH_EDITOR
            luaRPCFuncs.Add(func);
            funcs.Add(func);
#endif
            func->SetNativeFunc((FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc);
            func->Script.Insert(LuaOverrider::Code, LuaOverrider::CodeSize, 0);

            if (GUObjectArray.IsDisregardForGC(cls) && !GUObjectArray.IsOpenForDisregardForGC())
            {
                func->AddToRoot();
            }
            else
            {
                func->AddToCluster(cls);
            }

            bAdded = true;
        }

        return bAdded;
    }

    int LuaNet::__index(lua_State* L, UObject* obj, const char* keyName)
    {
        if (NS_SLUA::LuaNet::isLuaReplicateObject(obj))
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps(obj);
            if (classLuaReplciated)
            {
                auto prop = classLuaReplciated->ownerProperty.Get();
                if (prop && classLuaReplciated->replicatedNameToIndexMap.Num())
                {
                    auto luaReplicatedIndex = classLuaReplciated->replicatedNameToIndexMap.Find(UTF8_TO_TCHAR(keyName));
                    
                    if (luaReplicatedIndex)
                    {
                        FLuaNetSerialization* luaNetSerialization = prop->ContainerPtrToValuePtr<FLuaNetSerialization>(obj);
                        auto proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                        if (proxy)
                        {
                            int index = *luaReplicatedIndex;
                            {
                                auto p = classLuaReplciated->properties[index];
                                auto referencePusher = LuaObject::getReferencePusher(p);
                                if (referencePusher) {
                                    return LuaObject::pushReferenceAndCache(referencePusher, L, obj->GetClass(), p, proxy->values.GetData() + p->GetOffset_ForInternal(), obj, index);
                                }

                                auto pusher = LuaObject::getPusher(p);
                                return pusher(L, p, proxy->values.GetData() + p->GetOffset_ForInternal(), nullptr);
                            }
                        }
                    }
                }
            }
        }

        return 0;
    }

    int LuaNet::__newindex(lua_State* L, UObject* obj, const char* keyName)
    {
        // Try to assign net replicated prop first.
        if (LuaNet::isLuaReplicateObject(obj))
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps(obj);
            if (classLuaReplciated)
            {
                auto prop = classLuaReplciated->ownerProperty.Get();
                if (prop && classLuaReplciated->replicatedNameToIndexMap.Num())
                {
                    auto luaReplicatedIndexPtr = classLuaReplciated->replicatedNameToIndexMap.Find(UTF8_TO_TCHAR(keyName));
                    if (luaReplicatedIndexPtr)
                    {
                        auto luaReplicatedIndex = *luaReplicatedIndexPtr;
                        FLuaNetSerialization* luaNetSerialization = prop->ContainerPtrToValuePtr<FLuaNetSerialization>(obj);
                        auto proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                        if (proxy)
                        {
                            {
                                auto p = classLuaReplciated->properties[luaReplicatedIndex];
                                auto checker = LuaObject::getChecker(p);

                                if (checker)
                                {
                                    auto data = proxy->values.GetData();
                                    int32 propOffset =  p->GetOffset_ForInternal();
                                    checker(L, p, data + propOffset, 3, true);
                                    proxy->dirtyMark.Add(luaReplicatedIndex);
                                    proxy->assignTimes++;
                                    onPropModify(L, proxy, luaReplicatedIndex, nullptr);
                                }
                            }
                        }
                        
                        return 1;
                    }
                }
            }
        }

        return 0;
    }

    int LuaNet::setupFunctions(lua_State* L)
    {
        lua_pushstring(L, LuaNet::ADD_LISTENER_FUNC);
        lua_pushcfunction(L, LuaNet::addListener);
        lua_rawset(L, -3);

        lua_pushstring(L, LuaNet::REMOVE_LISTENER_FUNC);
        lua_pushcfunction(L, LuaNet::removeListener);
        lua_rawset(L, -3);
        return 0;
    }

    int LuaNet::addListener(lua_State* L)
    {
        lua_pushstring(L, SLUA_CPPINST);
        lua_rawget(L, 1);
        void* ud = lua_touserdata(L, -1);
        lua_pop(L, 1);

        auto obj = (UObject*)ud;

        if (!NS_SLUA::LuaObject::isUObjectValid(obj))
        {
            return 0;
        }

        if (NS_SLUA::LuaNet::isLuaReplicateObject(obj))
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps(obj);
            if (classLuaReplciated)
            {
                auto prop = classLuaReplciated->ownerProperty.Get();
                if (prop && classLuaReplciated->replicatedNameToIndexMap.Num())
                {
                    const char* keyName = lua_tostring(L, 2);
                    auto luaReplicatedIndex = classLuaReplciated->replicatedNameToIndexMap.Find(UTF8_TO_TCHAR(keyName));
                    
                    if (luaReplicatedIndex)
                    {
                        FLuaNetSerialization* luaNetSerialization = prop->ContainerPtrToValuePtr<FLuaNetSerialization>(obj);
                        auto proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                        if (proxy)
                        {
                            int index = *luaReplicatedIndex;
                            {
                                auto &listeners = proxy->propListeners.FindOrAdd(index);
                                listeners.Add(new LuaVar(L, 3));
                                return 1;
                            }
                        }
                    }
                }
            }
        }

        return 0;
    }

    int LuaNet::removeListener(lua_State* L)
    {
        lua_pushstring(L, SLUA_CPPINST);
        lua_rawget(L, 1);
        void* ud = lua_touserdata(L, -1);
        lua_pop(L, 1);

        auto obj = (UObject*)ud;

        if (!NS_SLUA::LuaObject::isUObjectValid(obj))
        {
            return 0;
        }

        if (NS_SLUA::LuaNet::isLuaReplicateObject(obj))
        {
            auto classLuaReplciated = LuaNet::getClassReplicatedProps(obj);
            if (classLuaReplciated)
            {
                auto prop = classLuaReplciated->ownerProperty.Get();
                if (prop && classLuaReplciated->replicatedNameToIndexMap.Num())
                {
                    const char* keyName = lua_tostring(L, 2);
                    auto luaReplicatedIndex = classLuaReplciated->replicatedNameToIndexMap.Find(UTF8_TO_TCHAR(keyName));
                    
                    if (luaReplicatedIndex)
                    {
                        FLuaNetSerialization* luaNetSerialization = prop->ContainerPtrToValuePtr<FLuaNetSerialization>(obj);
                        auto proxy = LuaNet::getLuaNetSerializationProxy(luaNetSerialization);
                        if (proxy)
                        {
                            int index = *luaReplicatedIndex;
                            {
                                auto &listeners = proxy->propListeners.FindOrAdd(index);
                                auto funcToRemove = LuaVar(L, 3);
                                auto indexToRemove = listeners.IndexOfByPredicate([&](const LuaVar* Item)
                                {
                                    if (*Item == funcToRemove)
                                    {
                                        delete Item;
                                        return true;
                                    }

                                    return false;
                                });
                                if (indexToRemove >= 0)
                                {
                                    listeners.RemoveAt(indexToRemove);
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }

        return 0;
    }

    void LuaNet::onPropModify(lua_State* L, FLuaNetSerializationProxy* proxy, ReplicateIndexType index, PrepareParamCallback callback)
    {
        auto *listeners = proxy->propListeners.Find(index);
        if (listeners)
        {
            if (listeners->Num() <= 0)
            {
                return;
            }

            if (callback)
            {
                callback();
            }

            auto listenersCopy = *listeners;
            auto fillParam = [L]()
            {
                lua_pushvalue(L, -3);
                return 1;
            };
            for (auto listener : listenersCopy)
            {
                listener->callWithNArg(fillParam);
            }
        }
    }
}

