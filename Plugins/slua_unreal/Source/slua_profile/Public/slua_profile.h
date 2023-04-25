// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"
#include "Framework/Commands/Commands.h"
#include "slua_profile_inspector.h"
#include "LuaMemoryProfile.h"
#include "slua_profile.h"

/** Declares a log category for this module. */
DECLARE_LOG_CATEGORY_EXTERN(LogSluaProfile, Log, All);

namespace NS_SLUA
{
    class FProfileServer;
}

class SLUA_PROFILE_API Fslua_profileModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;


    void PluginButtonClicked();
private:
    // fields
    FTickerDelegate TickDelegate;
#if ENGINE_MAJOR_VERSION==5
    FTSTicker::FDelegateHandle TickDelegateHandle;
#else
    FDelegateHandle TickDelegateHandle;
#endif

    TSharedPtr<SProfilerInspector> sluaProfilerInspector;
    bool tabOpened = false;
    TSharedPtr<class FUICommandList> PluginCommands;

    // functions
    void OnTabClosed(TSharedRef<SDockTab> tab);

    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
    bool Tick(float DeltaTime);
    void ClearCurProfiler();
    void AddMenuExtension(FMenuBuilder& Builder);

    void debug_hook_c(NS_SLUA::FProfileMessagePtr Message);
};

#if WITH_EDITOR
class Flua_profileCommands : public TCommands<Flua_profileCommands>
{
public:

    Flua_profileCommands();

    // TCommands<> interface
    virtual void RegisterCommands() override;

public:
    TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
#endif
