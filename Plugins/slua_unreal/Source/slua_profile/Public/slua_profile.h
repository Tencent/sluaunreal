// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "InputCoreTypes.h"
#include "ModuleManager.h"
#include "Private/slua_profile_inspector.h"

#ifdef ENABLE_PROFILER
#define PROFILER_WATCHER(x)  Profiler x(__FUNCTION__);
#define PROFILER_WATCHER_WITH_FUNC_NAME(x, functionName)  Profiler x(functionName);
#define PROFILER_BEGIN_WATCHER_WITH_FUNC_NAME(functionName)  Profiler::BeginWatch(functionName);
#define PROFILER_END_WATCHER()  Profiler::EndWatch();
#else
#define PROFILER_WATCHER(x)
#define PROFILER_WATCHER_WITH_FUNC_NAME(x, functionName)
#define PROFILER_BEGIN_WATCHER_WITH_FUNC_NAME(functionName)
#define PROFILER_END_WATCHER()
#endif

class Fslua_profileModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	bool Tick(float DeltaTime);
	void ClearCurProfiler();

	FTickerDelegate TickDelegate;
	FDelegateHandle TickDelegateHandle;
	TSharedPtr<SProfilerInspector> sluaProfilerInspector;
	bool sluaProfilerSetHook;
};

struct functionProfileInfo
{
	FString functionName;
	FString brevName;
	int64_t begTime;
	int64_t endTime;
	int64_t costTime;
	int64_t mergedCostTime;
	int globalIdx;
	int layerIdx;
	int mergedNum;
	bool beMerged;
	TArray<int> mergeIdxArray;
};

class SLUA_PROFILE_API Profiler
{
public:
	Profiler(FString funcName)
	{
		BeginWatch(funcName);
	}

	~Profiler()
	{
		EndWatch();
	}

public:
	static void BeginWatch(FString funcName);
	static void EndWatch();
};

void InitProfilerWatchThread();   // unsupport multi-thread function profile

