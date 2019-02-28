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

void ULuaUserWidget::NativeConstruct()
{
	if (!init(this, "LuaUserWidget", LuaStateName, LuaFilePath)) return;
	Super::NativeConstruct();
#if (ENGINE_MINOR_VERSION==18)
	bCanEverTick = postInit("bHasScriptImplementedTick", false);
#else
	bHasScriptImplementedTick = postInit("bHasScriptImplementedTick", false);
#endif
}

void ULuaUserWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// store current tick parameter MyGeometry
	currentGeometry = MyGeometry;
	tick(InDeltaTime);
}

void ULuaUserWidget::ProcessEvent(UFunction * func, void * params)
{
	if (luaImplemented(func, params))
		return;
	Super::ProcessEvent(func, params);
}

void ULuaUserWidget::superTick()
{
	Super::NativeTick(currentGeometry, deltaTime);
}
