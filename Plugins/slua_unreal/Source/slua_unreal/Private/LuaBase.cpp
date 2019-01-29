// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "LuaBase.h"

slua::LuaVar LuaBase::metaTable;

bool LuaBase::luaImplemented(UFunction * func, void * params)
{
	if (!luaSelfTable.isTable())
		return false;

	if (!func->HasAnyFunctionFlags(EFunctionFlags::FUNC_BlueprintEvent))
		return false;

	FString funcName = func->GetDisplayNameText().ToString();
	// should remove space in display name
	funcName.RemoveSpacesInline();
	slua::LuaVar lfunc = luaSelfTable.getFromTable<slua::LuaVar>((const char*)TCHAR_TO_UTF8(*funcName),true);
	if (!lfunc.isValid()) return false;
	
	return lfunc.callByUFunction(func, (uint8*)params,&luaSelfTable);
}

// Called every frame
void LuaBase::tick(float DeltaTime)
{
	if (!tickFunction.isValid())
		return;
	tickFunction.call(luaSelfTable, DeltaTime);
}

int LuaBase::__index(slua::lua_State * L)
{
	lua_pushstring(L, "__cppinst");
	lua_rawget(L, 1);
	if (!lua_isuserdata(L, -1))
		luaL_error(L, "expect LuaActor table at arg 1");
	// push key
	lua_pushvalue(L, 2);
	// get field from real actor
	lua_gettable(L, -2);
	return 1;
}

bool LuaBase::postInit(const char* tickFlag)
{
	if (!luaSelfTable.isTable())
		return false;

	bool tickEnabled = luaSelfTable.getFromTable<bool>(tickFlag);

	if (tickEnabled && luaSelfTable.isTable()) {
		tickFunction = luaSelfTable.getFromTable<slua::LuaVar>("Tick");
		if (!tickFunction.isValid()) {
			return false;
		}
		return tickEnabled;
	}
	return false;
}
