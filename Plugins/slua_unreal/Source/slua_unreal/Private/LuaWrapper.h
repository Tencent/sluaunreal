#pragma once

#include "LuaObject.h"
#include "Log.h"

#define LUA_WRAPPER_DEBUG

namespace slua {

	struct LuaWrapper {

		static void init(lua_State* L);
		static int pushValue(lua_State* L, UStructProperty* p, UScriptStruct* uss, uint8* parms);
		static int checkValue(lua_State* L, UStructProperty* p, UScriptStruct* uss, uint8* parms, int i);

	};

}

