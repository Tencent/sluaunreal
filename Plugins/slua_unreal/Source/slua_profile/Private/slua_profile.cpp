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
#include "EditorStyle.h"
#endif

#include "slua_remote_profile.h"
#include "SluaUtil.h"
#include "LuaProfiler.h"

DEFINE_LOG_CATEGORY(LogSluaProfile)
#define LOCTEXT_NAMESPACE "Fslua_profileModule"

namespace {
	static const FName slua_profileTabName(TEXT("slua_profile"));


	static const FString CoroutineName(TEXT("coroutine"));
	SluaProfiler curProfiler;
	
    TArray<NS_SLUA::LuaMemInfo> memoryInfo;
	TSharedPtr<TArray<SluaProfiler>, ESPMode::ThreadSafe> curProfilersArray = MakeShareable(new TArray<SluaProfiler>());
	TQueue<TSharedPtr<TArray<SluaProfiler>, ESPMode::ThreadSafe>, EQueueMode::Mpsc> profilerArrayQueue;

	uint32_t currentLayer = 0;
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
		return true;
	}

	while (!profilerArrayQueue.IsEmpty())
	{
		TSharedPtr<TArray<SluaProfiler>, ESPMode::ThreadSafe> profilesArray;
		profilerArrayQueue.Dequeue(profilesArray);
		sluaProfilerInspector->Refresh(*profilesArray.Get(), memoryInfo);
	}

	return true;
}

TSharedRef<class SDockTab> Fslua_profileModule::OnSpawnPluginTab(const FSpawnTabArgs & SpawnTabArgs)
{
	if (sluaProfilerInspector.IsValid())
	{
		sluaProfilerInspector->StartChartRolling();
		auto tab = sluaProfilerInspector->GetSDockTab();
		 
		tab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &Fslua_profileModule::OnTabClosed));

        sluaProfilerInspector->ProfileServer = MakeShareable(new slua::FProfileServer());
		sluaProfilerInspector->ProfileServer->OnProfileMessageRecv().BindLambda([this](slua::FProfileMessagePtr Message) {
			this->debug_hook_c(Message->Event, Message->Time, Message->Linedefined, Message->Name, Message->ShortSrc,  Message->memoryInfoList);
		});
        
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

void Profiler::BeginWatch(const FString& funcName, double nanoseconds)
{
	TSharedPtr<FunctionProfileInfo> funcInfo = MakeShareable(new FunctionProfileInfo);
	funcInfo->functionName = funcName;
	FDateTime Time = FDateTime::Now();
	funcInfo->begTime = nanoseconds;
	funcInfo->endTime = -1;
	funcInfo->costTime = 0;
	funcInfo->layerIdx = currentLayer;
	funcInfo->beMerged = false;
	funcInfo->mergedNum = 1;
	curProfiler.Add(funcInfo);
	currentLayer++;
}

void Profiler::EndWatch(double nanoseconds)
{
	if (currentLayer <= 0)
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
			funcInfo->endTime = nanoseconds;
			funcInfo->costTime = funcInfo->endTime - funcInfo->begTime;
			funcInfo->mergedCostTime = funcInfo->costTime;
			break;
		}
	}
	
	if (idx <= 0)
	{
		return;
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
		curProfilersArray->Add(curProfiler);
		curProfiler.Empty();
	}
}

void Fslua_profileModule::ClearCurProfiler()
{
	currentLayer = 0;

	curProfilersArray = MakeShareable(new TArray<SluaProfiler>());
}

void Fslua_profileModule::AddMenuExtension(FMenuBuilder & Builder)
{
#if WITH_EDITOR
	Builder.AddMenuEntry(Flua_profileCommands::Get().OpenPluginWindow);
#endif
}

void Fslua_profileModule::OnTabClosed(TSharedRef<SDockTab>)
{
//    if (sluaProfilerInspector->ProfileServer)
//    {
//        delete sluaProfilerInspector->ProfileServer;
//        sluaProfilerInspector->ProfileServer = nullptr;
//    }
	tabOpened = false;
}

void Fslua_profileModule::debug_hook_c(int event, double nanoseconds, int linedefined, const FString& name, const FString& short_src, TArray<NS_SLUA::LuaMemInfo> memoryInfoList)
{
	if (event == NS_SLUA::ProfilerHookEvent::PHE_CALL)
	{
		if (linedefined == -1 && name.IsEmpty())
		{
			return;
		}
		FString functionName = short_src;
		functionName += ":";
		functionName += FString::FromInt(linedefined);
		functionName += " ";
		functionName += name;
		PROFILER_BEGIN_WATCHER_WITH_FUNC_NAME(functionName, nanoseconds)
	}
	else if (event == NS_SLUA::ProfilerHookEvent::PHE_RETURN)
	{
		if (linedefined == -1 && name.IsEmpty())
		{
			return;
		}
		FString functionName = short_src;
		functionName += ":";
		functionName += FString::FromInt(linedefined);
		functionName += " ";
		functionName += name;
		PROFILER_END_WATCHER(functionName, nanoseconds)
	}
	else if (event == NS_SLUA::ProfilerHookEvent::PHE_TICK)
	{
		profilerArrayQueue.Enqueue(curProfilersArray);

		ClearCurProfiler();
	}
    else if (event == NS_SLUA::ProfilerHookEvent::PHE_MEMORY_TICK)
    {
        memoryInfo = memoryInfoList;
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fslua_profileModule, slua_profile)
