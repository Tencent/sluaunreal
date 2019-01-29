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
#include "LuaState.h"

class LuaBase {
public:
	virtual bool luaImplemented(UFunction* func, void* params);
	virtual ~LuaBase() {}
protected:
	template<typename T>
    bool init(T* ptrT,const char* typeName,const FString& stateName,const FString& luaPath)
	{
		auto ls = slua::LuaState::get();
		if (stateName.Len() != 0) ls = slua::LuaState::get(stateName);
		if (!ls) return false;

		luaSelfTable = ls->doFile(TCHAR_TO_UTF8(*luaPath));
		if (!luaSelfTable.isTable())
			return false;

		auto L = ls->getLuaState();
		// setup __cppinst
		luaSelfTable.push(L);

		slua::LuaObject::push(L, ptrT);
		lua_setfield(L, -2, "__cppinst");

		// setup metatable
		if (!metaTable.isValid()) {
			luaL_newmetatable(L, typeName);
			lua_pushcfunction(L, __index);
			lua_setfield(L, -2, "__index");
			metaTable.set(L, -1);
			lua_pop(L, 1);
		}
		metaTable.push(L);
		lua_setmetatable(L, -2);

		// pop luaSelfTable
		lua_pop(L, 1);
		return true;
	}

	bool postInit(const char* tickFlag);
	void tick(float DeltaTime);
    static int __index(slua::lua_State* L);
    slua::LuaVar luaSelfTable;
	slua::LuaVar tickFunction;
	static slua::LuaVar metaTable;
};