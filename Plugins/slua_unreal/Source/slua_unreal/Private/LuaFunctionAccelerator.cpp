// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaFunctionAccelerator.h"

#include "LatentDelegate.h"
#include "LuaOverrider.h"

namespace NS_SLUA
{
    TMap<UFunction*, LuaFunctionAccelerator*> LuaFunctionAccelerator::cache;

    inline bool isLatentProperty(FProperty* prop)
    {
        FStructProperty* structProp = CastField<FStructProperty>(prop);
        if (structProp && (structProp->Struct == FLatentActionInfo::StaticStruct()))
        {
	        return true;
        }
	    return false;
    }

    LuaFunctionAccelerator::LuaFunctionAccelerator(UFunction* inFunc)
        : func(inFunc)
        , bLuaOverride(ULuaOverrider::isUFunctionHooked(inFunc))
    {
        auto funcFlag = func->FunctionFlags;
        bNativeFunc = (funcFlag & EFunctionFlags::FUNC_Native) != 0;

        int propIndex = 0;
        for (TFieldIterator<FProperty> it(func); it && (it->PropertyFlags & CPF_Parm); ++it, ++propIndex)
        {
            FProperty* prop = *it;
            uint64 propflag = prop->GetPropertyFlags();

            if (prop->HasAnyPropertyFlags(CPF_OutParm))
            {
                outParmRecProps.Add(prop);
            }

            FCheckerInfo checkerInfo = {false, false, false, false, propIndex, prop->GetOffset_ForInternal(), prop};
            FCheckerInfo* checkerRef = &checkerInfo;
            if (!prop->HasAnyPropertyFlags(CPF_NoDestructor))
            {
                checkerInfo.bInit = true;
                checkerInfo.bReference = IsReferenceParam(prop->PropertyFlags, func) && LuaObject::getReferencer(prop);
                paramsChecker.Add(checkerInfo);
                
                checkerRef = &paramsChecker.Top();
            }

            if (bNativeFunc)
            {
                if ((propflag & CPF_ReturnParm))
                    continue;
            }
            else if (IsRealOutParam(propflag))
                continue;
            
            if (isLatentProperty(prop))
            {
                checkerRef->bLatent = true;
            }
            else
            {
                auto checker = LuaObject::getChecker(prop);
                checkerRef->bCheck = true;
                checkerRef->checker = checker;
            }

            if (checkerRef == &checkerInfo)
            {
                paramsChecker.Add(checkerInfo);
            }
        }

        bHasReturnParam = func->ReturnValueOffset != MAX_uint16;
        if (bHasReturnParam)
        {
            auto returnProperty = func->GetReturnProperty();
            auto pusher = LuaObject::getPusher(returnProperty);

            returnPusherInfo.bReference = false;
            returnPusherInfo.offset = returnProperty->GetOffset_ForInternal();
            returnPusherInfo.prop = returnProperty;
            returnPusherInfo.pusher = pusher;
        }

        int i = 0;
        for (TFieldIterator<FProperty> it(func); it && (it->PropertyFlags & CPF_Parm); ++it)
        {
            FProperty* prop = *it;
            auto propflag = prop->PropertyFlags;
            // skip return param
            if(propflag&CPF_ReturnParm)
                continue;
                
            if (!isLatentProperty(prop))
            {
                if (IsRealOutParam(propflag))
                {
                    if (IsReferenceParam(propflag, func))
                    {
                        const auto referencer = LuaObject::getReferencer(prop);
                        if (referencer)
                        {
                            FPusherInfo pusherInfo = {true, i, prop->GetOffset_ForInternal(), prop, referencer, LuaObject::getPusher(prop)};
                            outPropsPusher.Add(pusherInfo);
                        }
                        else
                        {
                            FPusherInfo pusherInfo = {false, i, prop->GetOffset_ForInternal(), prop, nullptr, LuaObject::getPusher(prop)};
                            outPropsPusher.Add(pusherInfo);
                        }
                    }
                    else
                    {
                        FPusherInfo pusherInfo = {false, i, prop->GetOffset_ForInternal(), prop, nullptr, LuaObject::getPusher(prop)};
                        outPropsPusher.Add(pusherInfo);
                    }

                    if (bNativeFunc)
                    {
                        i++;
                    }
                }
                else
                {
                    i++;
                }
            }
        }
    }

    LuaFunctionAccelerator* LuaFunctionAccelerator::findOrAdd(UFunction* inFunc)
    {
        auto ret = cache.Find(inFunc);
        if (ret)
        {
            return *ret;
        }
        
        auto value = new LuaFunctionAccelerator(inFunc);
        cache.Emplace(inFunc, value);
        return value;
    }

    bool LuaFunctionAccelerator::remove(UFunction* inFunc)
    {
        auto funcPtr = cache.Find(inFunc);
        if (funcPtr)
        {
            delete *funcPtr;
            cache.Remove(inFunc);
            return true;
        }

        return false;
    }

    void LuaFunctionAccelerator::clear()
    {
        for (auto iter : cache)
        {
            delete iter.Value;
        }

        cache.Empty();
    }

    int LuaFunctionAccelerator::call(lua_State* L, int offset, UObject* obj, bool& isLatentFunction, NewObjectRecorder* objRecorder)
    {
        isLatentFunction = false;
        auto funcFlag = func->FunctionFlags;
        if (!(funcFlag & FUNC_Net) && !bNativeFunc && func->Script.Num() == 0)
        {
            return 0;
        }

        int i = offset;
        uint16 propertiesSize = func->PropertiesSize;
        uint8* params = (uint8*)FMemory_Alloca(propertiesSize);
        uint16 paramsPointerSize = func->NumParms * sizeof(void*);
        FProperty** propertyList = (FProperty**)FMemory_Alloca(paramsPointerSize);
        PTRINT* outParams = (PTRINT*)FMemory_Alloca(paramsPointerSize);

        if (propertiesSize)
            FMemory::Memzero(params, propertiesSize);
        if (paramsPointerSize)
            FMemory::Memzero(propertyList, paramsPointerSize);

        FFrame newStack(obj, func, params, nullptr,
#if ENGINE_MINOR_VERSION >= 25 || ENGINE_MAJOR_VERSION > 4
            func->ChildProperties
#else
            func->Children
#endif
        );

        checkSlow(newStack.Locals || func->ParmsSize == 0);
        FOutParmRec** lastOut = &newStack.OutParms;
        AutoDestructor autoDestructor(propertyList, params, func->NumParms);

        for (auto prop : outParmRecProps)
        {
            CA_SUPPRESS(6263)
            auto out = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));
            out->Property = prop;
            out->PropAddr = prop->ContainerPtrToValuePtr<uint8>(params);

            if (*lastOut)
            {
                (*lastOut)->NextOutParm = out;
                lastOut = &(*lastOut)->NextOutParm;
            }
            else
            {
                *lastOut = out;
            }
        }

        if (*lastOut)
        {
            (*lastOut)->NextOutParm = NULL;
        }

        
        for (auto& checkerInfo : paramsChecker)
        {
            auto prop = checkerInfo.prop;
            if (checkerInfo.bInit && !(checkerInfo.bReference && (lua_type(L, i) == LUA_TUSERDATA)))
            {
                if (!prop->HasAnyPropertyFlags(CPF_ZeroConstructor))
                {
                    prop->InitializeValue_InContainer(params);
                }
                *propertyList = prop;
                ++propertyList;
            }

            if (checkerInfo.bLatent)
            {
                // bind a callback to the latent function
                lua_State* mainThread = L->l_G->mainthread;

                ULatentDelegate* latentObj = LuaObject::getLatentDelegate(mainThread);
                int threadRef = latentObj->getThreadRef(L);
                FLatentActionInfo LatentActionInfo(threadRef, GetTypeHash(FGuid::NewGuid()),
                                                   *ULatentDelegate::NAME_LatentCallback, latentObj);

                prop->CopySingleValue(prop->ContainerPtrToValuePtr<void>(params), &LatentActionInfo);
                isLatentFunction = true;
            }
            else if (checkerInfo.bCheck)
            {
                PTRINT* pointer = outParams + checkerInfo.index;
                *pointer = PTRINT(0);
                // if is out param, can accept nil
                uint64 propflag = prop->GetPropertyFlags();
                if ((propflag & CPF_OutParm) && lua_isnil(L, i))
                {
                    i++;
                    continue;
                }

                auto checker = checkerInfo.checker;
                *pointer = PTRINT(checker(L, prop, params + checkerInfo.offset, i, false));
                i++;
            }
        }

        uint8* returnValueAddress = bHasReturnParam ? ((uint8*)params + func->ReturnValueOffset) : nullptr;
        if (funcFlag & FUNC_Net)
        {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            int32 functionCallspace = obj->GetFunctionCallspace(func, params, &newStack);
#else
            int32 functionCallspace = obj->GetFunctionCallspace(func, &newStack);
#endif
            uint8* savedCode = NULL;

            if (functionCallspace & FunctionCallspace::Remote)
            {
                savedCode = newStack.Code;
                // Since this is native, we need to rollback the stack if we are calling both remotely and locally
                obj->CallRemoteFunction(func, params, newStack.OutParms, &newStack);
            }

            if (functionCallspace & FunctionCallspace::Local)
            {
                if (savedCode)
                {
                    newStack.Code = savedCode;
                }
#if ENGINE_MINOR_VERSION >= 23 && (PLATFORM_MAC || PLATFORM_IOS)
                FFrame *frame = (FFrame *)&newStack;
                func->Invoke(obj, *frame, returnValueAddress);
#else
                func->Invoke(obj, newStack, returnValueAddress);
#endif
            }
        }
        else
        {
            func->Invoke(obj, newStack, returnValueAddress);
        }

        int32 ret = 0;
        if (bHasReturnParam)
        {
            auto returnProperty = returnPusherInfo.prop;
            ret += returnPusherInfo.pusher(L, returnProperty, params + returnPusherInfo.offset, objRecorder);
        }

        i = offset;
        for (auto &pusherInfo : outPropsPusher)
        {
            auto prop = pusherInfo.prop;
            auto propflag = prop->PropertyFlags;

            uint8* src = params + pusherInfo.offset;
            int32 index = pusherInfo.index;
            if (pusherInfo.bReference && *(outParams + index))
            {
                pusherInfo.referencePusher(L, prop, src, reinterpret_cast<void*>(*(outParams + index)));
                lua_pushvalue(L, i + index);
                ret++;
            }
            else
            {
                ret += pusherInfo.pusher(L, prop, src, objRecorder);
            }
        }
        
        return ret;
    }

    void LuaFunctionAccelerator::fillParam(lua_State* L,int i, NewObjectRecorder* objRecorder,const PostFillParamCallback& callback ,bool &isLatentFunction) {
        uint16 paramsPointerSize = func->NumParms * sizeof(void*);
        uint16 parmsSize = func->ParmsSize;
        uint8* params = (uint8*)FMemory_Alloca(parmsSize);
        FProperty** propertyList = (FProperty**)FMemory_Alloca(paramsPointerSize);
        PTRINT* outParams = (PTRINT*)FMemory_Alloca(paramsPointerSize);
        if (parmsSize)
            FMemory::Memzero(params, func->ParmsSize);
        if (paramsPointerSize)
            FMemory::Memzero(propertyList, paramsPointerSize);

        AutoDestructor autoDestructor(propertyList, params, func->NumParms);
        isLatentFunction = false;
        for (auto& checkerInfo : paramsChecker)
        {
            auto prop = checkerInfo.prop;
            if (checkerInfo.bInit && !(checkerInfo.bReference && (lua_type(L, i) == LUA_TUSERDATA)))
            {
                if (!prop->HasAnyPropertyFlags(CPF_ZeroConstructor))
                {
                    prop->InitializeValue_InContainer(params);
                }
                *propertyList = prop;
                ++propertyList;
            }

            if (checkerInfo.bLatent)
            {
                // bind a callback to the latent function
                lua_State* mainThread = L->l_G->mainthread;

                ULatentDelegate* latentObj = LuaObject::getLatentDelegate(mainThread);
                int threadRef = latentObj->getThreadRef(L);
                FLatentActionInfo LatentActionInfo(threadRef, GetTypeHash(FGuid::NewGuid()),
                                                   *ULatentDelegate::NAME_LatentCallback, latentObj);

                prop->CopySingleValue(prop->ContainerPtrToValuePtr<void>(params), &LatentActionInfo);
                isLatentFunction = true;
            }
            else if (checkerInfo.bCheck)
            {
                PTRINT* pointer = outParams + checkerInfo.index;
                *pointer = PTRINT(0);
                // if is out param, can accept nil
                uint64 propflag = prop->GetPropertyFlags();
                if ((propflag & CPF_OutParm) && lua_isnil(L, i))
                {
                    i++;
                    continue;
                }

                auto checker = checkerInfo.checker;
                *pointer = PTRINT(checker(L, prop, params + checkerInfo.offset, i, false));
                i++;
            }
        }

        callback(params, outParams, objRecorder);
    }

    int LuaFunctionAccelerator::returnValue(lua_State* L, int i, uint8* params, PTRINT* outParams, NewObjectRecorder* objRecorder)
    {
        int32 ret = 0;
        if (bHasReturnParam)
        {
            auto returnProperty = returnPusherInfo.prop;
            ret += returnPusherInfo.pusher(L, returnProperty, params + returnPusherInfo.offset, objRecorder);
        }

        for (auto &pusherInfo : outPropsPusher)
        {
            auto prop = pusherInfo.prop;
            auto propflag = prop->PropertyFlags;
            
            uint8* src = params+pusherInfo.offset;
            int32 index = pusherInfo.index;
            if (pusherInfo.bReference && *(outParams + index))
            {
                pusherInfo.referencePusher(L, prop, src, reinterpret_cast<void*>(*(outParams + index)));
                lua_pushvalue(L, i + index);
                ret++;
            }
            else
            {
                ret += pusherInfo.pusher(L, prop, src, objRecorder);
            }
        }
        
        return ret;
    }
}
