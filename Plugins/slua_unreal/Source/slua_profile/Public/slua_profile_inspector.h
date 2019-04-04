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

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STreeView.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/Views/STreeView.h"

struct FunctionProfileInfo;
typedef TArray<TSharedPtr<FunctionProfileInfo>> SluaProfiler;

class SLUA_PROFILE_API SProfilerInspector
{
public:
	SProfilerInspector();
	~SProfilerInspector();

	void Refresh(TArray<SluaProfiler>& curProfilersArray);
	TSharedRef<class SDockTab> GetSDockTab();
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FunctionProfileInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetChildrenForTree(TSharedPtr<FunctionProfileInfo> Parent, TArray<TSharedPtr<FunctionProfileInfo>>& OutChildren);
	void StartChartRolling();
	bool GetNeedProfilerCleared() const
	{
		return needProfilerCleared;
	}
	void SetNeedProfilerCleared(const bool needClear)
	{
		needProfilerCleared = needClear;
	}

private:
	const static int sampleNum = 250;
	const static int fixRowWidth = 300;
	const static int refreshInterval = 50;
	const float perMilliSec = 1000.0f;

	TSharedPtr<STreeView<TSharedPtr<FunctionProfileInfo>>> treeview;
	TSharedPtr<SCheckBox> profilerCheckBox;
	TSharedPtr<SProgressBar> profilerBarArray[sampleNum];

	float chartValArray[sampleNum];
	bool stopChartRolling;
	int refreshIdx;
	int arrayOffset;
	int lastArrayOffset;
	float maxProfileSamplesCostTime;
	float avgProfileSamplesCostTime;
	bool hasCleared;
	bool needProfilerCleared;

	TArray<SluaProfiler> tmpProfilersArraySamples[sampleNum];
	TArray<SluaProfiler> profilersArraySamples[sampleNum];
	SluaProfiler shownRootProfiler;
	SluaProfiler shownProfiler;
	SluaProfiler tmpRootProfiler;
	SluaProfiler tmpProfiler;


	bool NeedReBuildInspector();
	void RefreshBarValue();
	void AddProfilerBarOnMouseMoveEvent();
	void RemoveProfilerBarOnMouseMoveEvent();
	void ShowProfilerTree(TArray<SluaProfiler> &selectedProfiler);
	void CheckBoxChanged(ECheckBoxState newState);
	void ClearProfilerCharFillImage();
	void AssignProfiler(TArray<SluaProfiler> &profilerArray, SluaProfiler& rootProfilers, SluaProfiler& profilers);
	void AssignProfiler(SluaProfiler& srcProfilers, SluaProfiler& dstProfilers);
	void MergeSiblingNode(SluaProfiler& profiler, int begIdx, int endIdx, TArray<int> parentMergeArray, int mergeArrayIdx);
	void SearchSiblingNode(SluaProfiler& profiler, int curIdx, int endIdx, TSharedPtr<FunctionProfileInfo> &node);
	FString GenBrevFuncName(FString &functionName);
	void CopyFunctionNode(TSharedPtr<FunctionProfileInfo>& oldFuncNode, TSharedPtr<FunctionProfileInfo>& newFuncNode);
	void InitProfilerBar(int barIdx, TSharedPtr<SHorizontalBox>& horBox);
	void OnClearBtnClicked();
	void SortProfiler(SluaProfiler &shownRootProfiler);
};




