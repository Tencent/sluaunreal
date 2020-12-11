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
#include "HAL/FileManager.h"
#include "Engine/GameEngine.h"
#include "Containers/Ticker.h"
#include "LuaState.h"
#include "lua.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#include "EditorStyle.h"
#endif

#include "slua_remote_profile.h"
#include "LuaProfiler.h"
#include "LuaMemoryProfile.h"

DEFINE_LOG_CATEGORY(LogSluaProfile)
#define LOCTEXT_NAMESPACE "Fslua_profileModule"

namespace {
	static const FName slua_profileTabName(TEXT("slua_profile"));


	static const FString CoroutineName(TEXT("coroutine"));
	SluaProfiler curProfiler;
	
	typedef TMap<int64, NS_SLUA::LuaMemInfo> LuaMemInfoMap;
	LuaMemInfoMap memoryInfo;
	typedef TSharedPtr<TArray<SluaProfiler>, ESPMode::ThreadSafe> ProfilerArrayPtr;
	typedef TQueue<ProfilerArrayPtr, EQueueMode::Mpsc> ProfilerArrayQueue;
	ProfilerArrayQueue profilerArrayQueue;
	ProfilerArrayPtr currentProfilersArray = MakeShareable(new TArray<SluaProfiler>());

	typedef TQueue<MemoryFramePtr, EQueueMode::Mpsc> MemoryFrameQueue;
	MemoryFrameQueue memoryQueue;
	MemoryFramePtr currentMemory = MakeShareable(new MemoryFrame());

	int32 currentLayer = 0;
	TArray<int32> coroutineLayers;
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
		ProfilerArrayPtr profilesArray;
		profilerArrayQueue.Dequeue(profilesArray);

		MemoryFramePtr memoryFrame;
		memoryQueue.Dequeue(memoryFrame);

		sluaProfilerInspector->Refresh(*profilesArray.Get(), memoryInfo, memoryFrame);
	}

	return true;
}

TSharedRef<class SDockTab> Fslua_profileModule::OnSpawnPluginTab(const FSpawnTabArgs & SpawnTabArgs)
{
	NS_SLUA::LuaMemoryProfile::start();
	if (sluaProfilerInspector.IsValid())
	{
		sluaProfilerInspector->StartChartRolling();
		auto tab = sluaProfilerInspector->GetSDockTab();
		 
		tab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &Fslua_profileModule::OnTabClosed));

        sluaProfilerInspector->ProfileServer = MakeShareable(new NS_SLUA::FProfileServer());
		sluaProfilerInspector->ProfileServer->OnProfileMessageRecv().BindLambda([this](NS_SLUA::FProfileMessagePtr Message) {
			this->debug_hook_c(Message);
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

	int32 lastCoroutineLayer = -1;
	if (coroutineLayers.Num())
	{
		lastCoroutineLayer = coroutineLayers[coroutineLayers.Num() - 1];
	}

	// find the end watch function node
	int32 idx = 0;
	for (idx = curProfiler.Num(); idx > 0 && idx > lastCoroutineLayer; idx--)
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
	for (; idx < (size_t)curProfiler.Num(); idx++)
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
	currentLayer = FMath::Max(lastCoroutineLayer, currentLayer);

	if (currentLayer == 0)
	{
		currentProfilersArray->Add(curProfiler);
		curProfiler.Empty();
	}
}

void Fslua_profileModule::ClearCurProfiler()
{
	currentLayer = 0;
	curProfiler.Empty();
	
	coroutineLayers.Empty();
	currentProfilersArray = MakeShareable(new TArray<SluaProfiler>());
	currentMemory = MakeShareable(new MemoryFrame());
	currentMemory->bMemoryTick = false;
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
	NS_SLUA::LuaMemoryProfile::stop();
}

void Fslua_profileModule::debug_hook_c(NS_SLUA::FProfileMessagePtr Message)
{
	//int event, double nanoseconds, int linedefined, const FString& name, const FString& short_src, TArray<NS_SLUA::LuaMemInfo> memoryInfoList
	int event = Message->Event;
	double nanoseconds = Message->Time;
	int linedefined = Message->Linedefined;
	const FString& name = Message->Name;
	const FString& short_src = Message->ShortSrc;

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
		if (curProfiler.Num() > 0)
		{
			for (int layer = currentLayer; layer > 0; layer--)
			{
				PROFILER_END_WATCHER(short_src, nanoseconds)
			}
			
			currentProfilersArray->Add(curProfiler);
			curProfiler.Empty();
		}
		profilerArrayQueue.Enqueue(currentProfilersArray);
		memoryQueue.Enqueue(currentMemory);

		ClearCurProfiler();
	}
    else if (event == NS_SLUA::ProfilerHookEvent::PHE_MEMORY_TICK)
    {
		currentMemory->memoryInfoList = Message->memoryInfoList;
		currentMemory->bMemoryTick = true;
    }
	else if (event == NS_SLUA::ProfilerHookEvent::PHE_MEMORY_INCREACE)
	{
		currentMemory->memoryIncrease = Message->memoryIncrease;
	}
	else if (event == NS_SLUA::ProfilerHookEvent::PHE_ENTER_COROUTINE)
	{
		coroutineLayers.Add(currentLayer);

		FString functionName = TEXT("coroutine.resume");
		functionName += ":";
		functionName += FString::FromInt(linedefined);
		functionName += " ";
		functionName += name;
		PROFILER_BEGIN_WATCHER_WITH_FUNC_NAME(functionName, nanoseconds)
	}
	else if (event == NS_SLUA::ProfilerHookEvent::PHE_EXIT_COROUTINE)
	{
		FString functionName = TEXT("coroutine.resume");
		functionName += ":";
		functionName += FString::FromInt(linedefined);
		functionName += " ";
		functionName += name;
		PROFILER_END_WATCHER(functionName, nanoseconds)

		if (coroutineLayers.Num())
		{
			int lastCoroutineLayer = coroutineLayers.Pop();
			for (int layer = currentLayer; layer > lastCoroutineLayer; layer--)
			{
				PROFILER_END_WATCHER(functionName, nanoseconds)
			}
			currentLayer = lastCoroutineLayer;
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fslua_profileModule, slua_profile)
