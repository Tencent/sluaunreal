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
#include "LuaOverriderInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/HUD.h"


#include "LuaActor.generated.h"

UCLASS()
class SLUA_UNREAL_API ALuaActor : public AActor, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ALuaPawn : public APawn, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ALuaCharacter : public ACharacter, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ALuaController : public AController, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ALuaPlayerController : public APlayerController, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ULuaActorComponent : public UActorComponent, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ALuaGameModeBase : public AGameMode, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};

UCLASS()
class SLUA_UNREAL_API ALuaHUD : public AHUD, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
};
