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

namespace slua {

	slua::LuaVar LuaBase::metaTable;

	struct UFunctionParamScope {
		LuaBase* pBase;
		UFunctionParamScope(LuaBase* lb,UFunction* func, void* params) {
			pBase = lb;
			pBase->currentFunc = func;
			pBase->currentParams = params;
		}
		UFunctionParamScope(LuaBase* lb, UFunction* func, float dt) {
			pBase = lb;
			pBase->currentFunc = func;
			pBase->deltaTime = dt;
		}
		~UFunctionParamScope() {
			pBase->currentFunc = nullptr;
			pBase->currentParams = nullptr;
		}
	};

	bool LuaBase::luaImplemented(UFunction * func, void * params)
	{
		if (!func->HasAnyFunctionFlags(EFunctionFlags::FUNC_BlueprintEvent))
			return false;

		if (!luaSelfTable.isTable())
			return false;

		slua::LuaVar lfunc = luaSelfTable.getFromTable<slua::LuaVar>((const char*)TCHAR_TO_UTF8(*func->GetName()), true);
		if (!lfunc.isValid()) return false;

		UFunctionParamScope scope(this, func, params);
		return lfunc.callByUFunction(func, (uint8*)params, &luaSelfTable);
	}

	// Called every frame
	void LuaBase::tick(float DeltaTime)
	{
		UFunctionParamScope scope(this, UFUNCTION_TICK, DeltaTime);
		if (!tickFunction.isValid()) {
			superTick();
			return;
		}
		tickFunction.call(luaSelfTable, DeltaTime);
	}

	int LuaBase::__index(slua::lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		if (!lua_isuserdata(L, -1))
			luaL_error(L, "expect LuaBase table at arg 1");
		// push key
		lua_pushvalue(L, 2);
		// get field from real actor
		lua_gettable(L, -2);
		return 1;
	}

	static int setParent(slua::lua_State* L) {
		// set field to obj, may raise an error
		lua_settable(L, 1);
		return 0;
	}

	int LuaBase::__newindex(slua::lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		if (!lua_isuserdata(L, -1))
			luaL_error(L, "expect LuaBase table at arg 1");

		lua_pushcfunction(L, setParent);
		// push cpp inst
		lua_pushvalue(L, -2);
		// push key
		lua_pushvalue(L, 2);
		// push value
		lua_pushvalue(L, 3);
		// set ok?
		if (lua_pcall(L, 3, 0, 0)) {
			lua_pop(L, 1);
			// push key
			lua_pushvalue(L, 2);
			// push value
			lua_pushvalue(L, 3);
			// rawset to table
			lua_rawset(L, 1);
		}
		return 0;
	}

	LuaVar LuaBase::callMember(FString func, const TArray<FLuaBPVar>& args)
	{
		slua::LuaVar lfunc = luaSelfTable.getFromTable<slua::LuaVar>((const char*)TCHAR_TO_UTF8(*func), true);
		if (!lfunc.isFunction()) {
			Log::Error("Can't find lua member function named %s to call", TCHAR_TO_UTF8(*func));
			return false;
		}
		
		auto L = luaSelfTable.getState();
		// push self
		luaSelfTable.push(L);
		// push arg to lua
		for (auto& arg : args) {
			arg.value.push(L);
		}
		return lfunc.callWithNArg(args.Num()+1);
	}

	bool LuaBase::postInit(const char* tickFlag,bool rawget)
	{
		if (!luaSelfTable.isTable())
			return false;

		bool tickEnabled = luaSelfTable.getFromTable<bool>(tickFlag, rawget);

		if (tickEnabled && luaSelfTable.isTable()) {
			tickFunction = luaSelfTable.getFromTable<slua::LuaVar>("Tick", true);
			return tickEnabled;
		}
		return false;
	}
}