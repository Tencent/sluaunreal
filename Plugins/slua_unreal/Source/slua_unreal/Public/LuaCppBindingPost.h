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

#include "LuaVar.h"

namespace NS_SLUA
{
	template<typename T>
	inline static T resultCast(LuaVar&& Var, typename std::enable_if<!std::is_void<T>::value, int>::type = 0)
	{
		return Var.castTo<T>();
	}

	template<typename T>
	inline static T resultCast(LuaVar&& Var, typename std::enable_if<std::is_void<T>::value, int>::type = 0) {}

	template<typename CallableType, typename ReturnType, typename ... ArgTypes>
	typename CallableExpand<CallableType, ReturnType, ArgTypes...>::TFunctionType
	CallableExpand<CallableType, ReturnType, ArgTypes...>::makeTFunctionProxy(lua_State* L, int p)
	{
		luaL_checktype(L, p, LUA_TFUNCTION);
		LuaVar func(L, p);
		if (func.isValid() && func.isFunction())
		{
			return [=](ArgTypes&& ... args) -> ReturnType
			{
				LuaVar result = func.call(std::forward<ArgTypes>(args) ...);
				return resultCast<ReturnType>(MoveTemp(result));
			};
		}
		else
		{
			return nullptr;
		}
	}
}