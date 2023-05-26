#pragma once
#include "LuaVar.h"
#include "LuaCppBindingPost.h"
#include "UObject/Interface.h"
#include "LuaObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LuaOverriderInterface.generated.h"

UINTERFACE()
class SLUA_UNREAL_API ULuaOverriderInterface : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class SLUA_UNREAL_API ILuaOverriderInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
        FString GetLuaFilePath() const;

    NS_SLUA::LuaVar GetSelfTable() const;

    virtual void PostLuaHook();

    void TryHook();

    NS_SLUA::LuaVar GetCachedLuaFunc(NS_SLUA::lua_State* L, const NS_SLUA::LuaVar selfTable, const FString& FunctionName) {
#if WITH_EDITOR
        if (Cast<UBlueprintFunctionLibrary>(this)) {
            return getFromTableIndex<NS_SLUA::LuaVar>(L, selfTable, FunctionName);
        }
#endif
        if (!FuncMap.Contains(FunctionName))
        {
            return FuncMap.Add(FunctionName, getFromTableIndex<NS_SLUA::LuaVar>(L, selfTable, FunctionName));
        }
        return FuncMap[FunctionName];
    }

    bool IsLuaFunctionExist(const FString& FunctionName) {
        const NS_SLUA::LuaVar selfTable = GetSelfTable();
        if (!selfTable.isValid() || !selfTable.isTable()) {
            return false;
        }

        return GetCachedLuaFunc(nullptr, selfTable, FunctionName).isFunction();
    }

    template<class RET, class ...ARGS>
    RET CallLuaFunction(const FString& FunctionName, ARGS&& ...Args) {
        NS_SLUA::LuaVar selfTable = GetSelfTable();
        if (!selfTable.isValid() || !selfTable.isTable()) {
            NS_SLUA::Log::Error("Lua module not assign to UObject[%s]", TCHAR_TO_UTF8(*Cast<UObject>(this)->GetName()));
            return RET();
        }

        NS_SLUA::LuaVar ret = GetCachedLuaFunc(nullptr, selfTable, FunctionName).call(selfTable, std::forward<ARGS>(Args)...);
        if (ret.isValid()) {
            return ret.castTo<RET>();
        }
        else {
            NS_SLUA::Log::Error("Type mismatch or have no return value! ObjectName: [%s], FunctionName[%s]",
                TCHAR_TO_UTF8(*Cast<UObject>(this)->GetName()), TCHAR_TO_UTF8(*FunctionName));
            return RET();
        }
    }


    template<class ...ARGS>
    void CallLuaFunction(const FString& FunctionName, ARGS&& ...Args) {
        Call<void>(false, FunctionName, std::forward<ARGS>(Args)...);
    }

    template<class RET, class ...ARGS>
    RET CallLuaFunctionIfExist(const FString& FunctionName, ARGS&& ...Args) {
        return Call<RET>(true, FunctionName, std::forward<ARGS>(Args)...);
    }
    
    template<class ...ARGS>
    void CallLuaFunctionIfExist(const FString& FunctionName, ARGS&& ...Args) {
        Call<void>(true, FunctionName, std::forward<ARGS>(Args)...);
    }

    template<typename R, typename T>
    static R getFromTableIndex(NS_SLUA::lua_State* L, const NS_SLUA::LuaVar& table, T key) {
        if (!L) {
            L = table.getState();
        }
        if (!L) {
            return R();
        }
        NS_SLUA::AutoStack as(L);
        table.push(L);
        if (lua_getmetatable(L, -1)) {
            int top = lua_gettop(L);
            if (lua_getfield(L, -1, "__index") != LUA_TNIL) {
                table.push(L);
                lua_pushstring(L, TCHAR_TO_UTF8(*key));
                lua_pushboolean(L, true); // lua first

                if (lua_pcall(L, 3, 1, 0))
                    lua_pop(L, 1);

                int ret = lua_gettop(L) - top;
                return NS_SLUA::LuaVar(L, -ret);
            }
        }
        return R();
    }

private:
    template<class RET, class ...ARGS>
    RET Call(bool checkExist, const FString& FunctionName, ARGS&& ...Args) {
        auto selfTable = GetSelfTable();
        if (!checkExist && (!selfTable.isValid() || !selfTable.isTable())) {
            NS_SLUA::Log::Error("Lua module not assign to UObject[%s]", TCHAR_TO_UTF8(*Cast<UObject>(this)->GetName()));
            return RET();
        }

        const NS_SLUA::LuaVar& Func = GetCachedLuaFunc(nullptr, selfTable, FunctionName);
        if (!checkExist)
        {
            NS_SLUA::LuaVar ret = Func.call(selfTable, std::forward<ARGS>(Args)...);
            if (ret.isValid())
            {
                return ret.castTo<RET>();
            }
        }
        else
        {
            if (Func.isFunction())
            {
                NS_SLUA::LuaVar ret = Func.call(selfTable, std::forward<ARGS>(Args)...);
                if (ret.isValid())
                {
                    return ret.castTo<RET>();
                }
            }
        }

        return RET();
    }

public:
    TMap<FString, NS_SLUA::LuaVar> FuncMap;
};
