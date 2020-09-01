#pragma once
#include "LuaVar.h"
#include "UObject/Interface.h"
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

	template<class RET, class ...ARGS>
	RET CallLuaFunction(const FString& FunctionName, ARGS&& ...Args) const {
		NS_SLUA::LuaVar selfTable = GetSelfTable();
		if (!selfTable.isValid() || !selfTable.isTable()) {
			NS_SLUA::Log::Error("Lua module not assign to UObject[%s]", TCHAR_TO_UTF8(*Cast<UObject>(this)->GetName()));
			return RET();
		}
		NS_SLUA::LuaVar Func = selfTable.getFromTable<NS_SLUA::LuaVar>(FunctionName, false);
		
		NS_SLUA::LuaVar ret = Func.call(selfTable, std::forward<ARGS>(Args)...);
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
	void CallLuaFunction(const FString& FunctionName, ARGS&& ...Args) const {
		auto selfTable = GetSelfTable();
		if (!selfTable.isValid() || !selfTable.isTable()) {
			NS_SLUA::Log::Error("Lua module not assign to UObject[%s]", TCHAR_TO_UTF8(*Cast<UObject>(this)->GetName()));
			return;
		}
		NS_SLUA::LuaVar Func = selfTable.getFromTable<NS_SLUA::LuaVar>(FunctionName, false);
		Func.call(selfTable, std::forward<ARGS>(Args)...);
	}
};
