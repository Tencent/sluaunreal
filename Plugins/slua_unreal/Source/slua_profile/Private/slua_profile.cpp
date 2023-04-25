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
#include "Containers/Ticker.h"
#include "LuaState.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#include "EditorStyle.h"
#include "EditorStyleSet.h"
#endif

#include "LuaProfiler.h"
#include "slua_remote_profile.h"
#include "ProfileDataDefine.h"
#include "SluaProfilerDataManager.h"

DEFINE_LOG_CATEGORY(LogSluaProfile)
#define LOCTEXT_NAMESPACE "Fslua_profileModule"
#define ROOT_NAME "ROOT"
namespace {
    static const FName slua_profileTabName(TEXT("slua_profile"));

    typedef TMap<int64, NS_SLUA::LuaMemInfo> LuaMemInfoMap;
    LuaMemInfoMap memoryInfo;

    typedef TQueue<MemoryFramePtr, EQueueMode::Mpsc> MemoryFrameQueue;
    MemoryFrameQueue memoryQueue;
    MemoryFramePtr currentMemory = MakeShareable(new MemoryFrame());

    ProfileCallInfoArray profilerStack;
    ProfileNodePtr funcProfilerRoot;
    TQueue<ProfileNodePtr, EQueueMode::Mpsc> funcProfilerNodeQueue;
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
#if ENGINE_MAJOR_VERSION==5
        TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);
#else
        TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
#endif
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
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    FGlobalTabmanager::Get()->InvokeTab(slua_profileTabName);
#else
    FGlobalTabmanager::Get()->TryInvokeTab(slua_profileTabName);
#endif
}

bool Fslua_profileModule::Tick(float DeltaTime)
{
    if (!tabOpened)
    {
        return true;
    }
    //UE_LOG(LogTemp, Warning, TEXT("Fslua_profileModule::Tick"));
    while (!funcProfilerNodeQueue.IsEmpty())
    {
        MemoryFramePtr memoryFrame;
        memoryQueue.Dequeue(memoryFrame);
        TSharedPtr<FunctionProfileNode> funcProfilerNode;
        funcProfilerNodeQueue.Dequeue(funcProfilerNode);
        sluaProfilerInspector->Refresh(funcProfilerNode, memoryInfo, memoryFrame);
    }
    return true;
}

TSharedRef<class SDockTab> Fslua_profileModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    if (sluaProfilerInspector.IsValid())
    {
        sluaProfilerInspector->StartChartRolling();
        auto tab = sluaProfilerInspector->GetSDockTab();

        tab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &Fslua_profileModule::OnTabClosed));
        SluaProfilerDataManager::InitProfileNode(funcProfilerRoot, ROOT_NAME, 0);
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
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
        NSLOCTEXT("Contexts", "slua_profile", "slua_profile Plugin"), NAME_None, FAppStyle::GetAppStyleSetName())
#else
        NSLOCTEXT("Contexts", "slua_profile", "slua_profile Plugin"), NAME_None, FEditorStyle::GetStyleSetName())
#endif
{
}

void Flua_profileCommands::RegisterCommands()
{
    UI_COMMAND(OpenPluginWindow, "slua Profile", "Open slua Profile tool", EUserInterfaceActionType::Button, FInputGesture());
}
#endif

void Fslua_profileModule::ClearCurProfiler()
{
    SluaProfilerDataManager::InitProfileNode(funcProfilerRoot, ROOT_NAME, 0);
    currentMemory = MakeShareable(new MemoryFrame());
    currentMemory->bMemoryTick = false;
    profilerStack.Empty();
}

void Fslua_profileModule::AddMenuExtension(FMenuBuilder& Builder)
{
#if WITH_EDITOR
    Builder.AddMenuEntry(Flua_profileCommands::Get().OpenPluginWindow);
#endif
}

void Fslua_profileModule::OnTabClosed(TSharedRef<SDockTab>)
{
    tabOpened = false;
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
        //UE_LOG(LogTemp, Log, TEXT("Profile Call %s"), *functionName);

        SluaProfilerDataManager::WatchBegin(functionName, nanoseconds, funcProfilerRoot, profilerStack);
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
        //UE_LOG(LogTemp, Log, TEXT("Profile Return %s"), *functionName);

        SluaProfilerDataManager::WatchEnd(functionName, nanoseconds, profilerStack);
    }
    else if (event == NS_SLUA::ProfilerHookEvent::PHE_TICK)
    {
        funcProfilerNodeQueue.Enqueue(funcProfilerRoot);
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
        FString functionName = TEXT("");
        functionName += ":";
        functionName += FString::FromInt(linedefined);
        functionName += " ";
        functionName += name;

        //UE_LOG(LogTemp, Log, TEXT("Profile CoBegin %s"), *functionName);
        
        SluaProfilerDataManager::CoroutineBegin(functionName, nanoseconds, funcProfilerRoot, profilerStack);
    }
    else if (event == NS_SLUA::ProfilerHookEvent::PHE_EXIT_COROUTINE)
    {
        //UE_LOG(LogTemp, Log, TEXT("Profile CoEnd"));
        SluaProfilerDataManager::CoroutineEnd(nanoseconds, profilerStack);
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(Fslua_profileModule, slua_profile)
