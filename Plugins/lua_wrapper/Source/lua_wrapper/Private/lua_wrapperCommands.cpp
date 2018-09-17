// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "lua_wrapperCommands.h"

#define LOCTEXT_NAMESPACE "Flua_wrapperModule"

void Flua_wrapperCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "LuaWrapper", "Generate Lua Interface (Windows only)", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
