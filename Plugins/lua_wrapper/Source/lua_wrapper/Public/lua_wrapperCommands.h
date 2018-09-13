// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "lua_wrapperStyle.h"

class Flua_wrapperCommands : public TCommands<Flua_wrapperCommands>
{
public:

	Flua_wrapperCommands()
		: TCommands<Flua_wrapperCommands>(TEXT("lua_wrapper"), NSLOCTEXT("Contexts", "lua_wrapper", "lua_wrapper Plugin"), NAME_None, Flua_wrapperStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};