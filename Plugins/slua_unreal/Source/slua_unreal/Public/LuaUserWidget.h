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
#include "Blueprint/UserWidget.h"
#include "LuaOverriderInterface.h"

#include "LuaUserWidget.generated.h"

UCLASS()
class SLUA_UNREAL_API ULuaUserWidget : public UUserWidget, public ILuaOverriderInterface {
    GENERATED_BODY()

public:
    // below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
    // so copy & paste them
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;

    virtual bool Initialize() override;
    virtual void BeginDestroy() override;

    FString GetLuaFilePath_Implementation() const override;
};

