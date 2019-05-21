// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "slua_profile.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "FileManager.h"
#include "Engine/GameEngine.h"
#include "Containers/Ticker.h"
#include "LuaState.h"
#include "lua.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#endif

#define LOCTEXT_NAMESPACE "Fslua_profileModule"

namespace {
	static const FName slua_profileTabName(TEXT("slua_profile"));
	SluaProfiler curProfiler;
	TArray<SluaProfiler> curProfilersArray;
	uint32_t currentLayer = 0;
	uint32_t profilerThreadId = 0;


	enum slua_profiler_hook_event
	{
		CALL = 0,
		RETURN = 1,
		LINE = 2,
		TAILRET = 4
	};

	static void debug_hook_c(NS_SLUA::lua_State *L, NS_SLUA::lua_Debug *ar)
	{
		if (ar->event == slua_profiler_hook_event::CALL)
		{
			if (lua_getinfo(L, "nSl", ar) != 0)
			{
				if (ar->linedefined == -1 && ar->name == nullptr)
				{
					return;
				}
				FString functionName = ar->short_src;
				functionName += ":";
				functionName += FString::FromInt(ar->linedefined);
				functionName += " ";
				functionName += ar->name;
				PROFILER_BEGIN_WATCHER_WITH_FUNC_NAME(functionName)
			}
		}
		else if (ar->event == slua_profiler_hook_event::RETURN)
		{
			if (lua_getinfo(L, "nSl", ar) != 0)
			{
				if (ar->linedefined == -1 && ar->name == nullptr)
				{
					return;
				}
				FString functionName = ar->short_src;
				functionName += ":";
				functionName += FString::FromInt(ar->linedefined);
				functionName += " ";
				functionName += ar->name;
				PROFILER_END_WATCHER()
			}
		}
	}

}

void Fslua_profileModule::StartupModule()
{
#if WITH_EDITOR
	Flua_profileCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		Flua_profileCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &Fslua_profileModule::PluginButtonClicked),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &Fslua_profileModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}


	if (GIsEditor && !IsRunningCommandlet())
	{
		InitProfilerWatchThread();
		sluaProfilerInspector = MakeShareable(new SProfilerInspector);
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(slua_profileTabName,
			FOnSpawnTab::CreateRaw(this, &Fslua_profileModule::OnSpawnPluginTab))
			.SetDisplayName(LOCTEXT("Flua_wrapperTabTitle", "slua Profiler"))
			.SetMenuType(ETabSpawnerMenuType::Hidden);
		TickDelegate = FTickerDelegate::CreateRaw(this, &Fslua_profileModule::Tick);
		TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
	}
#endif
}

void Fslua_profileModule::ShutdownModule()
{
#if WITH_EDITOR
	sluaProfilerInspector = nullptr;
	ClearCurProfiler();

	slua::LuaState *state = slua::LuaState::get();
	if (state != nullptr)
	{
		NS_SLUA::lua_sethook(state->getLuaState(), NULL, 0, 0);
		stateIndex = -1;
	}

	Flua_profileCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(slua_profileTabName);
#endif
}

void Fslua_profileModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(slua_profileTabName);
}

bool Fslua_profileModule::Tick(float DeltaTime)
{
	if (!tabOpened)
	{
		ClearCurProfiler();
		return true;
	}		
	
	openHook();
	sluaProfilerInspector->Refresh(curProfilersArray);
	ClearCurProfiler();
	return true;
}

TSharedRef<class SDockTab> Fslua_profileModule::OnSpawnPluginTab(const FSpawnTabArgs & SpawnTabArgs)
{
	if (sluaProfilerInspector.IsValid())
	{
		sluaProfilerInspector->StartChartRolling();
		auto tab = sluaProfilerInspector->GetSDockTab();

		openHook();

		tab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &Fslua_profileModule::OnTabClosed));
		tabOpened = true;
		return tab;
	}
	else
	{
		return SNew(SDockTab).TabRole(ETabRole::NomadTab);
	}
}

//////////////////////////////////////////////////////////////////////////
#if WITH_EDITOR
Flua_profileCommands::Flua_profileCommands()
	: TCommands<Flua_profileCommands>(slua_profileTabName,
		NSLOCTEXT("Contexts", "slua_profile", "slua_profile Plugin"), NAME_None, FEditorStyle::GetStyleSetName())
{

}

void Flua_profileCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "slua Profile", "Open slua Profile tool", EUserInterfaceActionType::Button, FInputGesture());
}
#endif
/////////////////////////////////////////////////////////////////////////////////////

bool isWatchThread()
{	
	uint32_t pid = FPlatformTLS::GetCurrentThreadId();
	if (profilerThreadId == 0)
	{
		profilerThreadId = pid;
		return true;
	}
	else if (pid != profilerThreadId)
	{
		return false;
	}
	return true;
}

void Profiler::BeginWatch(FString funcName)
{
	if (isWatchThread() != true)
	{
		return;
	}

	TSharedPtr<FunctionProfileInfo> funcInfo = MakeShareable(new FunctionProfileInfo);
	funcInfo->functionName = funcName;
	FDateTime Time = FDateTime::Now();
	funcInfo->begTime = Time.GetTicks()/ ETimespan::NanosecondsPerTick;
	funcInfo->endTime = -1;
	funcInfo->costTime = 0;
	funcInfo->layerIdx = currentLayer;
	funcInfo->beMerged = false;
	funcInfo->mergedNum = 1;
	curProfiler.Add(funcInfo);
	currentLayer++;
}

void Profiler::EndWatch()
{
	if (isWatchThread() != true || currentLayer <= 0)
	{
		return;
	}

	// find the end watch function node
	size_t idx = 0;
	for (idx = curProfiler.Num(); idx > 0; idx--)
	{
		TSharedPtr<FunctionProfileInfo> &funcInfo = curProfiler[idx - 1];
		if (funcInfo->endTime == -1)
		{
			FDateTime Time = FDateTime::Now();
			funcInfo->endTime = Time.GetTicks() / ETimespan::NanosecondsPerTick;
			funcInfo->costTime = funcInfo->endTime - funcInfo->begTime;
			funcInfo->mergedCostTime = funcInfo->costTime;
			break;
		}
	}

	// check wether node has child
	TSharedPtr<FunctionProfileInfo> &funcInfo = curProfiler[idx - 1];
	int64_t childCostTime = 0;
	bool hasChild = false;
	for (; idx < curProfiler.Num(); idx++)
	{
		TSharedPtr<FunctionProfileInfo> &nextFuncInfo = curProfiler[idx];
		if (nextFuncInfo->layerIdx <= funcInfo->layerIdx)
		{
			break;
		}
		if (nextFuncInfo->layerIdx == (funcInfo->layerIdx + 1))
		{
			hasChild = true;
			childCostTime += nextFuncInfo->costTime;
		}
	}

	if (hasChild == true)
	{
		TSharedPtr<FunctionProfileInfo> otherFuncInfo = MakeShareable(new FunctionProfileInfo);
		otherFuncInfo->functionName = "(other)";
		otherFuncInfo->begTime = 0;
		otherFuncInfo->endTime = 0;
		otherFuncInfo->costTime = funcInfo->costTime - childCostTime;
		otherFuncInfo->mergedCostTime = otherFuncInfo->costTime;
		otherFuncInfo->layerIdx = currentLayer;
		otherFuncInfo->beMerged = false;
		otherFuncInfo->mergedNum = 1;
		curProfiler.Add(otherFuncInfo);
	}
	currentLayer--;
	if (currentLayer == 0)
	{
		curProfilersArray.Add(curProfiler);
		curProfiler.Empty();
	}
}

void Fslua_profileModule::ClearCurProfiler()
{
	if (sluaProfilerInspector.IsValid() && sluaProfilerInspector->GetNeedProfilerCleared())
	{
		curProfiler.Empty();
		currentLayer = 0;
		sluaProfilerInspector->SetNeedProfilerCleared(false);
	}

	for (auto &iter : curProfilersArray)
	{
		iter.Empty();
	}
	curProfilersArray.Empty();
}

void Fslua_profileModule::AddMenuExtension(FMenuBuilder & Builder)
{
#if WITH_EDITOR
	Builder.AddMenuEntry(Flua_profileCommands::Get().OpenPluginWindow);
#endif
}

void Fslua_profileModule::OnTabClosed(TSharedRef<SDockTab>)
{
	// disable lua hook
	slua::LuaState *state = slua::LuaState::get();
	if (state != nullptr)
		NS_SLUA::lua_sethook(state->getLuaState(), nullptr, 0, 0);
	stateIndex = -1;
	tabOpened = false;
}

void Fslua_profileModule::openHook()
{
	// enable lua hook
	slua::LuaState *state = slua::LuaState::get();
	if (state) {
		if (stateIndex == state->stateIndex()) return;
		NS_SLUA::lua_sethook(state->getLuaState(), debug_hook_c, LUA_MASKCALL | LUA_MASKRET, 0);
		stateIndex = state->stateIndex();
	}
}

void InitProfilerWatchThread()
{
	profilerThreadId = FPlatformTLS::GetCurrentThreadId();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fslua_profileModule, slua_profile)
