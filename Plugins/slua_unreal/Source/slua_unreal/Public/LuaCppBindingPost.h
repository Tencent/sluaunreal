#pragma once

#include "LuaVar.h"

namespace slua
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
		LuaVar func(L, p);
		if (func.isValid() && func.isFunction())
		{
			return [=](ArgTypes&& ... args) mutable -> ReturnType
			{
				LuaVar result = func.call(std::forward<ArgTypes>(args) ...);
				return resultCast<ReturnType>(std::move(result));
			};
		}
		else
		{
			return nullptr;
		}
	}
}