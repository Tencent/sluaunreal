// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#if WITH_EDITOR
#include "LuaSimulate.h"
#endif
#include "Modules/ModuleManager.h"

class Fslua_unrealModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

#if WITH_EDITOR
private:
    NS_SLUA::LuaSimulate Simulate;
#endif
};