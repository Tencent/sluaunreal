// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "lua_wrapperCommands.h"

#define LOCTEXT_NAMESPACE "Flua_wrapperModule"

void Flua_wrapperCommands::RegisterCommands()
{
#if ENGINE_MAJOR_VERSION >=5
    UI_COMMAND(OpenPluginWindow, "LuaWrapper", "Generate Lua Interface (Windows only)", EUserInterfaceActionType::Button, FInputChord());
#else
	UI_COMMAND(OpenPluginWindow, "LuaWrapper", "Generate Lua Interface (Windows only)", EUserInterfaceActionType::Button, FInputGesture());
#endif
}

#undef LOCTEXT_NAMESPACE
