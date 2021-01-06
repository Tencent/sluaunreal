#pragma once
#include "WeakObjectPtr.h"
#include "SluaUtil.h"

typedef struct lua_State Lua_State;

namespace  NS_SLUA {
	struct LuaSuperOrRpc {
		LuaSuperOrRpc(class UObject* pBase) :base(pBase) {}

		template<typename T>
		static int genericGC(lua_State* L) {
			CheckUDGC(T, L, 1);
			delete UD;
			return 0;
		}

		static int setupMetatable(lua_State* L);
		static int __superIndex(lua_State* L);
		static int __superCall(lua_State* L);

		int superOrRpcCall(lua_State* L, UFunction* func);

		FWeakObjectPtr base;
	};

	DefTypeName(LuaSuperOrRpc);
}
