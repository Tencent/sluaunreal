#pragma once
#include "UObject/WeakObjectPtr.h"
#include "lua.h"
#include "LuaObject.h"
#include "SluaUtil.h"

namespace  NS_SLUA {
    struct LuaSuperCall {
        LuaSuperCall(class UObject* pBase) :base(pBase) {}
        
        static int genericGC(lua_State* L) {
            CheckUDGC(LuaSuperCall, L, 1);
            delete UD;
            return 0;
        }

        static int setupMetatable(lua_State* L);
        static int __superIndex(lua_State* L);
        static int __superCall(lua_State* L);

        int superCall(lua_State* L, class LuaFunctionAccelerator* func);

        FWeakObjectPtr base;
    };

    DefTypeName(LuaSuperCall);
}
