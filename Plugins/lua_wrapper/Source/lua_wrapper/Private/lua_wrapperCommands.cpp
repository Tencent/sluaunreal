// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "lua_wrapperCommands.h"

#define LOCTEXT_NAMESPACE "Flua_wrapperModule"

void Flua_wrapperCommands::RegisterCommands()
{
#ifdef _MSC_VER
	UI_COMMAND(OpenPluginWindow, "LuaWrapper", "Generate Lua Interface", EUserInterfaceActionType::Button, FInputGesture());
#endif
}

#undef LOCTEXT_NAMESPACE
