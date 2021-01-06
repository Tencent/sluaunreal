// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaActor.h"

ALuaActor::ALuaActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaActor::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ALuaPawn::ALuaPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaPawn::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ALuaCharacter::ALuaCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaCharacter::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ALuaController::ALuaController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaController::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ALuaPlayerController::ALuaPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaPlayerController::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ULuaActorComponent::ULuaActorComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ULuaActorComponent::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ALuaGameModeBase::ALuaGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaGameModeBase::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}

ALuaHUD::ALuaHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ALuaHUD::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}
