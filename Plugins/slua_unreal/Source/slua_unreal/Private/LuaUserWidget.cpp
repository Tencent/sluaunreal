// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaUserWidget.h"

bool ULuaUserWidget::Initialize()
{
    bool bIsInited = Super::Initialize();
    if (bIsInited)
    {
        UE_LOG(Slua, Verbose, TEXT("ULuaUserWidget[%s] Initialize [%s]!"), *GetName(), *LuaFilePath);

        if (GetSelfTable().isValid())
        {
            CallLuaFunction(TEXT("Initialize"));
        }
    }

    return bIsInited;
}

void ULuaUserWidget::BeginDestroy()
{
    auto SelfTable = GetSelfTable();
    if (SelfTable.isValid())
    {
        auto OnDestroyFunc = SelfTable.getFromTable<NS_SLUA::LuaVar>("OnDestroy");
        if (OnDestroyFunc.isFunction())
        {
            OnDestroyFunc.call(SelfTable);
        }
        else
        {
            NS_SLUA::Log::Error("ULuaUserWidget[%s] missing OnDestroy function [%s]!", TCHAR_TO_UTF8(*GetName()), TCHAR_TO_UTF8(*LuaFilePath));
        }
    }

    UE_LOG(Slua, Log, TEXT("ULuaUserWidget[%s] BeginDestroy [%s]!"), *GetName(), *LuaFilePath);
    
    Super::BeginDestroy();
}

FString ULuaUserWidget::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}
