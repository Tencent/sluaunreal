// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STreeView.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/Views/STreeView.h"
#include "slua_profile.h"

struct functionProfileInfo;
typedef TArray<TSharedPtr<functionProfileInfo>> SluaProfiler;

class SProfilerInspector
{
public:
	SProfilerInspector();
	~SProfilerInspector();

	void Refresh(TArray<SluaProfiler>& curProfilersArray);
	TSharedRef<class SDockTab> GetSDockTab();
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<functionProfileInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetChildrenForTree(TSharedPtr<functionProfileInfo> Parent, TArray<TSharedPtr<functionProfileInfo>>& OutChildren);
	void StartChartRolling();

private:
	const static int sampleNum = 250;
	const static int fixRowWidth = 300;
	const static int refreshInterval = 50;

	TSharedPtr<STreeView<TSharedPtr<functionProfileInfo>>> treeview;
	TSharedPtr<SCheckBox> profilerCheckBox;
	TSharedPtr<SProgressBar> profilerBarArray[sampleNum];

	float chartValArray[sampleNum];
	bool stopChartRolling;
	int refreshIdx;
	int arrayOffset;
	int lastArrayOffset;
	float maxProfileSamplesCostTime;
	bool hasCleared;

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
	void MergeSiblingNode(int begIdx, int endIdx, TArray<int> parentMergeArray, int mergeArrayIdx);
	void SearchSiblingNode(SluaProfiler& profiler, int curIdx, int endIdx, TSharedPtr<functionProfileInfo> &node);
	FString GenBrevFuncName(FString &functionName);
	void CopyFunctionNode(TSharedPtr<functionProfileInfo>& oldFuncNode, TSharedPtr<functionProfileInfo>& newFuncNode);
	void InitProfilerBar(int barIdx, TSharedPtr<SHorizontalBox>& horBox);
	void OnClearBtnClicked();
};




