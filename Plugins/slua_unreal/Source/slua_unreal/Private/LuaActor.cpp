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

slua::LuaVar ALuaActor::metaTable;

ALuaActor::ALuaActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALuaActor::BeginPlay()
{	
	init();
	Super::BeginPlay();

	bool tickEnabled = luaActorTable.getFromTable<bool>("bCanEverTick");
	PrimaryActorTick.SetTickFunctionEnable(tickEnabled);

	if (tickEnabled && luaActorTable.isTable()) {
		tickFunction = luaActorTable.getFromTable<slua::LuaVar>("Tick");
		if (!tickFunction.isValid())
			slua::Log::Error("LuaActor can't find Tick function");
	}
}

void ALuaActor::ProcessEvent(UFunction * func, void * params)
{
	if (luaImplemented(func, params))
		return;
	Super::ProcessEvent(func, params);
}

bool ALuaActor::luaImplemented(UFunction * func, void * params)
{
	if (!luaActorTable.isTable())
		return false;

	if (!func->HasAnyFunctionFlags(EFunctionFlags::FUNC_BlueprintEvent))
		return false;

	slua::LuaVar lfunc = luaActorTable.getFromTable<slua::LuaVar>((const char*)TCHAR_TO_UTF8(*func->GetDisplayNameText().ToString()));
	if (!lfunc.isValid()) return false;
	
	return lfunc.callByUFunction(func, (uint8*)params,&luaActorTable);
}

// Called every frame
void ALuaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!tickFunction.isValid())
		return;
	tickFunction.call(luaActorTable, DeltaTime);
}

int ALuaActor::__index(slua::lua_State * L)
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

void ALuaActor::init()
{
	auto ls = slua::LuaState::get();
	if (LuaStateName.Len() != 0) ls = slua::LuaState::get(LuaStateName);
	if (!ls) return;

	luaActorTable = ls->doFile(TCHAR_TO_UTF8(*LuaFilePath));
	if (!luaActorTable.isTable())
		return;

	auto L = ls->getLuaState();
	// setup __cppinst
	luaActorTable.push(L);

	slua::LuaObject::push(L, this);
	lua_setfield(L, -2, "__cppinst");

	// setup metatable
	if (!metaTable.isValid()) {
		luaL_newmetatable(L, "LuaActor");
		lua_pushcfunction(L, __index);
		lua_setfield(L, -2, "__index");
		metaTable.set(L, -1);
		lua_pop(L, 1);
	}
	metaTable.push(L);
	lua_setmetatable(L, -2);

	// pop luaActorTable
	lua_pop(L, 1);
}
