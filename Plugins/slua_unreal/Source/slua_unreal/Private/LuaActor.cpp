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

ALuaActor::ALuaActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALuaActor::BeginPlay()
{	
	if (!init(this,"LuaActor",LuaStateName, LuaFilePath)) return;
	Super::BeginPlay();
	// read bCanEverTick to enable tick function if it's true
	PrimaryActorTick.SetTickFunctionEnable(postInit("bCanEverTick"));
}

void ALuaActor::ProcessEvent(UFunction * func, void * params)
{
	if (luaImplemented(func, params))
		return;
	Super::ProcessEvent(func, params);
}

// Called every frame
void ALuaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	tick(DeltaTime);
}
