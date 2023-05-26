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
#include "LuaObject.h"

namespace NS_SLUA {
    class SLUA_UNREAL_API LuaFunctionAccelerator
    {
    public:
        typedef TFunctionRef<void (uint8* params, PTRINT* outParams, NewObjectRecorder* ObjectRecorder)> PostFillParamCallback;
        
        LuaFunctionAccelerator(UFunction* inFunc);

        static LuaFunctionAccelerator* findOrAdd(UFunction* inFunc);
        static bool remove(UFunction* inFunc);
        static void clear();

        int call(lua_State* L, int offset, UObject* obj, bool& isLatentFunction, NewObjectRecorder* objRecorder);

        void fillParam(lua_State* L, int i, NewObjectRecorder* objRecorder, const PostFillParamCallback& callback, bool &isLatentFunction);
        int returnValue(lua_State* L, int i, uint8* params, PTRINT* outParams, NewObjectRecorder* objRecorder);

    public:
        UFunction* func;
        const bool bLuaOverride;

    protected:
        static TMap<UFunction*, LuaFunctionAccelerator*> cache;

        struct AutoDestructor
        {
            AutoDestructor(FProperty** propertys, uint8* params, uint16 numParams)
                : propertyList(propertys)
                  , paramAddress(params)
                  , paramsMax(numParams)
            {
            }

            ~AutoDestructor()
            {
                if (propertyList)
                {
                    uint16 paramIndex = 0;
                    for (FProperty* it = *propertyList; it && paramIndex < paramsMax; it = *(++propertyList), ++
                         paramIndex)
                    {
                        it->DestroyValue_InContainer(paramAddress);
                    }
                }
            }

            FProperty** propertyList;
            uint8* paramAddress;
            uint16 paramsMax;
        };

        bool bNativeFunc;
        
        TArray<FProperty*> outParmRecProps;

        struct FCheckerInfo
        {
            bool bLatent : 1;
            bool bInit : 1;
            bool bReference : 1;
            bool bCheck : 1;
            int32 index;
            int32 offset;
            FProperty* prop;
            LuaObject::CheckPropertyFunction checker;
        };

        TArray<FCheckerInfo> paramsChecker;

        struct FPusherInfo
        {
            bool bReference;
            int32 index;
            int32 offset;
            FProperty* prop;

            LuaObject::ReferencePropertyFunction referencePusher;
            LuaObject::PushPropertyFunction pusher;
        };

        bool bHasReturnParam;
        FPusherInfo returnPusherInfo;
        TArray<FPusherInfo> outPropsPusher;
    };
    
}
