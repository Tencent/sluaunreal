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

#if (ENGINE_MINOR_VERSION>20) && (ENGINE_MAJOR_VERSION>=4)
void ULuaUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	init(this, "LuaUserWidget", LuaStateName, LuaFilePath);
}
#endif

void ULuaUserWidget::NativeConstruct()
{
	if (!LuaFilePath.IsEmpty() && !getSelfTable().isValid())
		init(this,"LuaUserWidget", LuaStateName, LuaFilePath);
	Super::NativeConstruct();
	if (getSelfTable().isValid()) {
#if (ENGINE_MINOR_VERSION==18)
		bCanEverTick = postInit("bHasScriptImplementedTick", false);
#else
		bHasScriptImplementedTick = postInit("bHasScriptImplementedTick", false);
#endif
	}
}

void ULuaUserWidget::NativeDestruct() {
	Super::NativeDestruct();
	luaSelfTable.free();
}

void ULuaUserWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
#if (ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4)
	if (ensureMsgf(GetDesiredTickFrequency() != EWidgetTickFrequency::Never, TEXT("SObjectWidget and UUserWidget have mismatching tick states or UUserWidget::NativeTick was called manually (Never do this)")))
#endif
	{
		GInitRunaway();
		TickActionsAndAnimation(MyGeometry, InDeltaTime);
#if (ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4)
		if (bHasScriptImplementedTick) {
#else
		if (bCanEverTick) {
#endif
			currentGeometry = MyGeometry;
			tick(InDeltaTime);
		}
	}
}

void ULuaUserWidget::tick(float dt) {
	if (!tickFunction.isValid()) {
		superTick();
		return;
	}
	tickFunction.call(luaSelfTable, &currentGeometry, dt);
}

void ULuaUserWidget::ProcessEvent(UFunction * func, void * params)
{
	if (luaImplemented(func, params))
		return;
	Super::ProcessEvent(func, params);
}

void ULuaUserWidget::superTick()
{
	Super::Tick(currentGeometry, deltaTime);
}

void ULuaUserWidget::superTick(NS_SLUA::lua_State* L)
{
	currentGeometry = NS_SLUA::LuaObject::checkValue<FGeometry>(L, 2);
	deltaTime = luaL_checknumber(L, 3);
	superTick();
}
