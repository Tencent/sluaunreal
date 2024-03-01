#include "LuaOverriderSuper.h"

#include "LuaFunctionAccelerator.h"
#include "LuaObject.h"
#include "LuaOverrider.h"

namespace NS_SLUA
{
    template<typename T>
    UFunction* getSuperFunction(lua_State* L)
    {
        CheckUD(T, L, 1);
        lua_getmetatable(L, 1);
        const char* name = lua_tostring(L, 2);

        lua_getfield(L, -1, name);
        lua_remove(L, -2); // remove mt of ud
        if (!lua_isnil(L, -1))
        {
            return nullptr;
        }

        UObject* obj = UD->base.Get();
        if (!obj)
            luaL_error(L, "Context is invalid");

        UClass* cls = obj->GetClass();
        FString funcName = UTF8_TO_TCHAR(name);
        extern const FString SUPER_CALL_FUNC_NAME_PREFIX;
        UFunction* cachedFunc = cls->FindFunctionByName(FName(*(SUPER_CALL_FUNC_NAME_PREFIX + funcName)));
        if (cachedFunc)
        {
            static UClass* InterfaceClass = UInterface::StaticClass();
            UClass* superClass = (UClass*)cachedFunc->GetSuperStruct();
            UClass* superFuncOuter = superClass ? (UClass*)superClass->GetOuter() : nullptr;
            if (superFuncOuter && superFuncOuter->IsChildOf(InterfaceClass)) // fixed UInterface's UFunction Super Call in lua
            {
                auto superFunc = superFuncOuter->FindFunctionByName(*funcName);
                if (superFunc)
                {
                    cachedFunc = superFunc;
                }
            }
            return cachedFunc;
        }
        luaL_error(L, "Can't find Class %s function %s in super", TCHAR_TO_UTF8(*cls->GetName()), name);
        return nullptr;
    }

    int LuaSuperCall::setupMetatable(lua_State* L)
    {
        LuaObject::setupMTSelfSearch(L);
        RegMetaMethodByName(L, "__index", __superIndex);
        return 0;
    }

    int LuaSuperCall::__superIndex(lua_State* L)
    {
        if (lua_getuservalue(L, 1) != LUA_TNIL)
        {
            lua_pushvalue(L, 2);
            if (lua_rawget(L, -2) != LUA_TNIL)
            {
                return 1;
            }
        }
        lua_pop(L, 1);
        
        UFunction* func = getSuperFunction<LuaSuperCall>(L);
        if (!func) return 1;

        lua_pushlightuserdata(L, LuaFunctionAccelerator::findOrAdd(func));
        lua_pushcclosure(L, __superCall, 1);

        if (lua_getuservalue(L, 1) == LUA_TNIL)
        {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_setuservalue(L, 1);
            L->top++;
        }
        lua_pushvalue(L, 2);
        lua_pushvalue(L, -3);
        lua_rawset(L, -3);

        lua_pop(L, 1);
        
        return 1;
    }

    int LuaSuperCall::__superCall(lua_State* L)
    {
        CheckUD(LuaSuperCall, L, 1);
        auto base = UD->base;
        UObject* obj = base.Get();
        if (!obj)
            luaL_error(L, "Context is invalid");

        lua_pushvalue(L, lua_upvalueindex(1));
        auto* funcAcc = (LuaFunctionAccelerator*)lua_touserdata(L, -1);
        auto func = funcAcc->func;
        if (!IsValid(func) || !func->IsValidLowLevel())
            luaL_error(L, "Super function is invalid");
        lua_pop(L, 1);

        return UD->superCall(L, funcAcc);
    }

    int LuaSuperCall::superCall(lua_State* L, LuaFunctionAccelerator* funcAcc)
    {
        UObject* obj = base.Get();
        if (!obj)
        {
            return 0;
        }

        bool isLatentFunction;
        int outParamCount;
        {
            NewObjectRecorder objectRecorder(L);
            outParamCount = funcAcc->call(L, 2, obj, isLatentFunction, &objectRecorder);
        }

        if (isLatentFunction)
            return lua_yield(L, outParamCount);
        return outParamCount;
    }
}

