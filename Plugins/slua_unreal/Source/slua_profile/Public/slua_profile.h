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

#include "Containers/Ticker.h"
#include "InputCoreTypes.h"
#include "ModuleManager.h"
#include "slua_profile_inspector.h"

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

class SLUA_PROFILE_API Fslua_profileModule : public IModuleInterface
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
	int stateIndex = -1;
	bool tabOpened = false;
	void OnTabClosed(TSharedRef<SDockTab> tab);
	void openHook();
};

struct SLUA_PROFILE_API FunctionProfileInfo
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
	bool isDuplicated = false;
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

