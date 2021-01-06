#include "LuaOverriderInterface.h"
#include "LuaOverrider.h"

ULuaOverriderInterface::ULuaOverriderInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

NS_SLUA::LuaVar ILuaOverriderInterface::GetSelfTable() const
{
	NS_SLUA::LuaVar* luaSelfTable = ULuaOverrider::getObjectTable(Cast<UObject>(this));
	if (luaSelfTable)
	{
		return *luaSelfTable;
	}
	else
	{
		return NS_SLUA::LuaVar();
	}
}
