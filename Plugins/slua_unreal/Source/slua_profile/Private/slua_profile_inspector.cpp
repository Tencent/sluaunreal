// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "SlateColorBrush.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Images/SImage.h"
#include "Public/Brushes/SlateDynamicImageBrush.h"
#include "Public/Brushes/SlateImageBrush.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "UObject/UObjectGlobals.h"
#include "Templates/SharedPointer.h"
#include "Delegates/IDelegateInstance.h"
#include "Internationalization/Regex.h"
#include "Fonts/SlateFontInfo.h"
#include "Math/Vector2D.h"
#include "Math/Color.h"
#include "EditorStyleSet.h"
#include "LuaProfiler.h"
#include "Sockets.h"
#include "Log.h"
#include "slua_profile_inspector.h"

static const FName slua_profileTabNameInspector("slua_profile");
FLinearColor checkLinearColor(float checkNumber);
void SortMemInfo(ShownMemInfoList& list, int beginIndex, int endIndex);
void ExchangeMemInfoNode(ShownMemInfoList& list, int originIndx, int newIndex);
///////////////////////////////////////////////////////////////////////////
SProfilerInspector::SProfilerInspector()
{
	stopChartRolling = false;
    showSnapshotDiff = false;
	arrayOffset = 0;
	lastArrayOffset = 0;
	refreshIdx = 0;
    snapshotID = 0;
    preSnapshotID = 0;
    deleteSnapshotID = 0;
	maxLuaMemory = 0.0f;
	avgLuaMemory = 0.0f;
	luaTotalMemSize = 0.0f;
	maxProfileSamplesCostTime = 0.0f;
	avgProfileSamplesCostTime = 0.0f;
    isMemMouseButtonUp = false;
	hasCleared = false;
	needProfilerCleared = false;
    mouseUpPoint = FVector2D(-1.0f, 0.0f);
    mouseDownPoint = FVector2D(-1.0f, 0.0f);
	initLuaMemChartList();
	snapshotIdArray.Add(MakeShareable(new FString("Choose one snapshot")));
	chartValArray.SetNumUninitialized(sampleNum);
	memChartValArray.SetNumUninitialized(sampleNum);
	luaMemNodeChartList.SetNumUninitialized(sampleNum);
}

SProfilerInspector::~SProfilerInspector()
{
	shownProfiler.Empty();
	shownRootProfiler.Empty();
	tmpRootProfiler.Empty();
	tmpProfiler.Empty();
    shownFileInfo.Empty();
    shownParentFileName.Empty();
	luaMemNodeChartList.Empty();
    tempLuaMemNodeChartList.Empty();
    snapshotIdArray.Empty();
    snapshotInfoArray.Empty();
    snapshotDiffArray.Empty();
    snapshotDiffParentArray.Empty();
}

void SProfilerInspector::StartChartRolling()
{
	stopChartRolling = false;
    isMemMouseButtonUp = false;
}

FString SProfilerInspector::GenBrevFuncName(FString &functionName)
{
	TArray<FString> strArray;
	FString brevName = functionName;
	int32 arrayNum = brevName.ParseIntoArray(strArray, TEXT(" "));
	if (arrayNum > 0)
	{
		brevName = strArray[arrayNum - 1];
	}

	arrayNum = brevName.ParseIntoArray(strArray, TEXT("/"));
	if (arrayNum > 0)
	{
		brevName = strArray[arrayNum - 1];
	}
	return brevName;
}

void SProfilerInspector::initLuaMemChartList()
{
	for(int32 i = 0; i < cMaxSampleNum; i++)
	{
		ProflierMemNode memNode;
        memNode.totalSize = -1.0f;
		luaMemNodeChartList.Add(memNode);
	}

	ProflierMemNode memNode;
	memNode.totalSize = 0.0f;
	luaMemNodeChartList.Add(memNode);
}

void  SProfilerInspector::CopyFunctionNode(TSharedPtr<FunctionProfileInfo>& oldFuncNode, TSharedPtr<FunctionProfileInfo>& newFuncNode)
{
	newFuncNode->functionName = oldFuncNode->functionName;
	newFuncNode->brevName = GenBrevFuncName(oldFuncNode->functionName);
	newFuncNode->begTime = oldFuncNode->begTime;
	newFuncNode->endTime = oldFuncNode->endTime;
	newFuncNode->costTime = oldFuncNode->costTime;
	newFuncNode->mergedCostTime = oldFuncNode->mergedCostTime;
	newFuncNode->layerIdx = oldFuncNode->layerIdx;
	newFuncNode->beMerged = oldFuncNode->beMerged;
	newFuncNode->mergedNum = oldFuncNode->mergedNum;
	newFuncNode->globalIdx = oldFuncNode->globalIdx;
	newFuncNode->isDuplicated = oldFuncNode->isDuplicated;
	newFuncNode->mergeIdxArray = oldFuncNode->mergeIdxArray;
}

void SProfilerInspector::Refresh(TArray<SluaProfiler>& profilersArray, TArray<NS_SLUA::LuaMemInfo> &memoryInfoList,
                                 TArray<SnapshotInfo> snapshotArray, TArray<NS_SLUA::LuaMemInfo> snapshotDifferentArray)
{
	if (stopChartRolling == true || profilersArray.Num() == 0)
	{
        if(!(stopChartRolling || memoryInfoList.Num())) CollectMemoryNode(memoryInfoList);
        if(snapshotArray.Num()) CollectSnapshotInfo(snapshotArray);
        if(snapshotDifferentArray.Num()) CollectSnapshotDiff(snapshotDifferentArray);

		return;
	}

    if(snapshotArray.Num()) CollectSnapshotInfo(snapshotArray);
    if(snapshotDifferentArray.Num()) CollectSnapshotDiff(snapshotDifferentArray);
    if(memoryInfoList.Num()) CollectMemoryNode(memoryInfoList);
	AssignProfiler(profilersArray, tmpRootProfiler, tmpProfiler);

	tmpProfilersArraySamples[arrayOffset] = profilersArray;
	arrayOffset = (arrayOffset + 1) >= sampleNum ? 0 : (arrayOffset + 1);

	if (NeedReBuildInspector() == true && treeview.IsValid() && tmpRootProfiler.Num() != 0)
	{
		// merge tempRootProfiler funcNode
		TArray<int> emptyMergeArray;

		for (int idx = 0; idx < tmpRootProfiler.Num(); idx++)
		{
			TSharedPtr<FunctionProfileInfo> &funcNode = tmpRootProfiler[idx];
			if (funcNode->beMerged == true || funcNode->functionName.IsEmpty())
			{
				continue;
			}
			MergeSiblingNode(tmpRootProfiler, idx, tmpRootProfiler.Num(), emptyMergeArray, 0);
		}

		SortProfiler(tmpRootProfiler);
		AssignProfiler(tmpRootProfiler, shownRootProfiler);
		AssignProfiler(tmpProfiler, shownProfiler);

		if (hasCleared == true)
		{
			treeview->RebuildList();
			memTreeView->RebuildList();
			hasCleared = false;
		}
		treeview->RequestTreeRefresh();
		memTreeView->RequestTreeRefresh();

		// replace tmp samples and update memory node list
		for (int sampleIdx = 0; sampleIdx<sampleNum; sampleIdx++)
		{
			profilersArraySamples[sampleIdx] = tmpProfilersArraySamples[sampleIdx];

			memChartValArray[sampleIdx] = luaMemNodeChartList[sampleIdx].totalSize;
        }

		RefreshBarValue();
		memTreeView->RequestTreeRefresh();
	}
	return;
}

void SProfilerInspector::RefreshBarValue()
{
	int nodeSize = 0;
	int sampleIdx = arrayOffset;
	float totalMemory = 0.0f;
	float totalSampleValue = 0.0f;

	maxLuaMemory = 0.0f;
	avgLuaMemory = 0.0f;
	maxProfileSamplesCostTime = 0.0f;
	avgProfileSamplesCostTime = 0.0f;
	lastArrayOffset = arrayOffset;
	for (int idx = 0; idx<sampleNum; idx++)
	{
		TArray<SluaProfiler> &shownProfilerBar = profilersArraySamples[sampleIdx];
		float totalValue = 0.0f;
		float memorySize = 0.0f;
		if (shownProfilerBar.Num() == 0)
		{
			chartValArray[idx] = -1.0f;
		}
		else
		{
			for (auto &iter : shownProfilerBar)
			{
				for (auto &funcNode : iter)
				{
					totalValue += funcNode->costTime;
					break;
				}
			}
			chartValArray[idx] = totalValue;
		}
		totalSampleValue += totalValue;
		if (maxProfileSamplesCostTime < totalValue)
		{
			maxProfileSamplesCostTime = totalValue;
		}
		sampleIdx = (sampleIdx == (sampleNum - 1)) ? 0 : (sampleIdx + 1);

		memorySize = luaMemNodeChartList[idx].totalSize;
		if(memorySize >= 0)
		{
			totalMemory += memorySize;
			nodeSize ++;
		}
		if (memorySize > maxLuaMemory) maxLuaMemory = memorySize;

	}
    tempLuaMemNodeChartList.Empty();
    tempLuaMemNodeChartList = luaMemNodeChartList;
	avgProfileSamplesCostTime = totalSampleValue / sampleNum;
	cpuProfilerWidget->SetArrayValue(chartValArray, maxProfileSamplesCostTime, maxLuaMemory);

	// Add memory total size into the array;
	if(totalMemory >= 0 && nodeSize > 0) avgLuaMemory = totalMemory / nodeSize;
	memProfilerWidget->SetArrayValue(memChartValArray, maxProfileSamplesCostTime, maxLuaMemory);

	CombineSameFileInfo(luaMemNodeChartList[luaMemNodeChartList.Num() - 1].infoList);
}

void SProfilerInspector::AssignProfiler(TArray<SluaProfiler> &profilerArray, SluaProfiler& rootProfilers, SluaProfiler& profilers)
{
	int nodeIdx = 0;
	int rootNodeIdx = 0;
	for (auto &iter : profilerArray)
	{
		for (auto &funcNode : iter)
		{
			funcNode->globalIdx = nodeIdx;

			// put root layer's function nodes to root profiler
			if (funcNode->layerIdx == 0)
			{
				if (rootNodeIdx >= rootProfilers.Num())
				{
					TSharedPtr<FunctionProfileInfo> newFuncNode = MakeShareable(new FunctionProfileInfo);
					CopyFunctionNode(funcNode, newFuncNode);
					rootProfilers.Add(newFuncNode);
				}
				else
				{
					CopyFunctionNode(funcNode, rootProfilers[rootNodeIdx]);
				}
				rootNodeIdx++;
			}

			if (nodeIdx >= profilers.Num())
			{
				TSharedPtr<FunctionProfileInfo> newFuncNode = MakeShareable(new FunctionProfileInfo);
				CopyFunctionNode(funcNode, newFuncNode);
				profilers.Add(newFuncNode);
			}
			else
			{
				CopyFunctionNode(funcNode, profilers[nodeIdx]);
			}

			nodeIdx++;
		}
	}

	// clear unused element
	profilers.SetNum(nodeIdx);

	rootProfilers.SetNum(rootNodeIdx);
}

void SProfilerInspector::AssignProfiler(SluaProfiler& srcProfilers, SluaProfiler& dstProfilers)
{
	int nodeIdx = 0;
	for (auto &funcNode : srcProfilers)
	{
		if (nodeIdx >= dstProfilers.Num())
		{
			TSharedPtr<FunctionProfileInfo> newFuncNode = MakeShareable(new FunctionProfileInfo);
			CopyFunctionNode(funcNode, newFuncNode);
			dstProfilers.Add(newFuncNode);
		}
		else
		{
			CopyFunctionNode(funcNode, dstProfilers[nodeIdx]);
		}
		nodeIdx++;
	}

	dstProfilers.SetNum(nodeIdx);
}

bool SProfilerInspector::NeedReBuildInspector()
{
	refreshIdx++;
	if (refreshIdx < refreshInterval)
	{
		return false;
	}
	else
	{
		refreshIdx = 0;
		return true;
	}
}

void SProfilerInspector::CheckBoxChanged(ECheckBoxState newState)
{
	if (newState == ECheckBoxState::Checked)
	{
		stopChartRolling = false;
        isMemMouseButtonUp = false;
		memProfilerCheckBox->SetIsChecked(ECheckBoxState::Checked);
		profilerCheckBox->SetIsChecked(ECheckBoxState::Checked);
		memProfilerWidget->ClearClickedPoint();
		cpuProfilerWidget->ClearClickedPoint();
	}
	else
	{
		stopChartRolling = true;
	}
}

void SProfilerInspector::OnClearBtnClicked()
{
	for (int barIdx = 0; barIdx<sampleNum; barIdx++)
	{
		chartValArray[barIdx] = -1.0f;
	}
	
	TArray<float> emptyArray;
	cpuProfilerWidget->SetArrayValue(emptyArray, 0, 0);
	cpuProfilerWidget->SetToolTipVal(-1);
	cpuProfilerWidget->ClearClickedPoint();
	
	memProfilerWidget->SetArrayValue(emptyArray, 0, 0);
	memProfilerWidget->SetToolTipVal(-1);
	memProfilerWidget->ClearClickedPoint();
	
	luaMemNodeChartList.Empty();
    tempLuaMemNodeChartList.Empty();
	shownFileInfo.Empty();
    shownParentFileName.Empty();
	initLuaMemChartList();
    
    luaTotalMemSize = 0.0f;
    maxLuaMemory = 0.0f;
    avgLuaMemory = 0.0f;
	
	for (int sampleIdx = 0; sampleIdx<sampleNum; sampleIdx++)
	{
		tmpProfilersArraySamples[sampleIdx].Empty();
		profilersArraySamples[sampleIdx].Empty();
	}
	
	for (auto &funcNode : shownRootProfiler)
	{
		funcNode->functionName = "";
		funcNode->brevName = "";
	}
	
	if (treeview.IsValid())
	{
		treeview->RebuildList();
		treeview->RequestTreeRefresh();
	}
	
	if (memTreeView.IsValid())
	{
		memTreeView->RebuildList();
		memTreeView->RequestTreeRefresh();
	}
	
	hasCleared = true;
	needProfilerCleared = true;
}

TSharedRef<class SDockTab>  SProfilerInspector::GetSDockTab()
{
	FText WidgetText = FText::FromName("============================ slua profiler ===========================");

	SAssignNew(profilerCheckBox, SCheckBox)
	.OnCheckStateChanged_Raw(this, &SProfilerInspector::CheckBoxChanged)
	.IsChecked(ECheckBoxState::Checked);

	SAssignNew(memProfilerCheckBox, SCheckBox)
	.OnCheckStateChanged_Raw(this, &SProfilerInspector::CheckBoxChanged)
	.IsChecked(ECheckBoxState::Checked);

	SAssignNew(cpuProfilerWidget, SProfilerWidget);
	SAssignNew(memProfilerWidget, SProfilerWidget);

    static int mouseDownMemIdx = -1;
    static int mouseUpMemIdx = -1;
	static bool isMouseButtonDown = false;
	static bool isMemMouseButtonDown = false;
	cpuProfilerWidget->SetOnMouseButtonDown(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// stop scorlling and show the profiler info which we click
		isMouseButtonDown = true;
		stopChartRolling = true;
		profilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		memProfilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
		int sampleIdx = cpuProfilerWidget->CalcClickSampleIdx(cursorPos);
        cpuProfilerWidget->SetMouseClickPoint(cursorPos);
		sampleIdx = lastArrayOffset + sampleIdx;
		if (sampleIdx >= cMaxSampleNum)
		{
			sampleIdx = sampleIdx - cMaxSampleNum;
		}

		if (profilersArraySamples[sampleIdx].Num() == 0)
		{
			TArray<SluaProfiler> tmp;
			ShowProfilerTree(tmp);
			return FReply::Handled();
		}

		if (sampleIdx >= 0)
		{
			ShowProfilerTree(profilersArraySamples[sampleIdx]);
		}

		return FReply::Handled();
	}));


	cpuProfilerWidget->SetOnMouseButtonUp(FPointerEventHandler::CreateLambda([=](const FGeometry&, const FPointerEvent&) -> FReply {
		isMouseButtonDown = false;
		return FReply::Handled();
	}));

	cpuProfilerWidget->SetOnMouseMove(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
		int sampleIdx = cpuProfilerWidget->CalcHoverSampleIdx(cursorPos);
		static float lastToolTipVal = 0.0f;
		if (sampleIdx >= 0 && lastToolTipVal != chartValArray[sampleIdx])
		{
			cpuProfilerWidget->SetToolTipVal(chartValArray[sampleIdx]/ perMilliSec);
			lastToolTipVal = chartValArray[sampleIdx];
		}
		else if (sampleIdx < 0)
		{
			cpuProfilerWidget->SetToolTipVal(-1.0f);
		}

		////////////////////////////////
		if (isMouseButtonDown == true)
		{
			// calc sampleIdx
			sampleIdx = cpuProfilerWidget->CalcClickSampleIdx(cursorPos);
            cpuProfilerWidget->SetMouseClickPoint(cursorPos);
			sampleIdx = lastArrayOffset + sampleIdx;
			if (sampleIdx >= cMaxSampleNum)
			{
				sampleIdx = sampleIdx - cMaxSampleNum;
			}

			if (profilersArraySamples[sampleIdx].Num() == 0)
			{
				TArray<SluaProfiler> tmp;
				ShowProfilerTree(tmp);
				return FReply::Handled();
			}

			if (sampleIdx >= 0)
			{
				ShowProfilerTree(profilersArraySamples[sampleIdx]);
			}
		}

		return FReply::Handled();
	}));
    
    cpuProfilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
        isMouseButtonDown = false;
    }));


	memProfilerWidget->SetOnMouseButtonDown(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// stop scorlling and show the profiler info which we click
		isMemMouseButtonDown = true;
        isMemMouseButtonUp = false;
		stopChartRolling = true;
		memProfilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		profilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
        mouseDownMemIdx = memProfilerWidget->CalcClickSampleIdx(cursorPos);
        memProfilerWidget->SetMouseClickPoint(cursorPos);
		if (mouseDownMemIdx >= 0 && mouseDownMemIdx < cMaxSampleNum)
		{
            mouseDownPoint = cursorPos;
			CombineSameFileInfo(tempLuaMemNodeChartList[mouseDownMemIdx].infoList);
			luaTotalMemSize = tempLuaMemNodeChartList[mouseDownMemIdx].totalSize;
			memTreeView->RequestTreeRefresh();
		}

        memProfilerWidget->SetMouseMovePoint(mouseDownPoint);
		return FReply::Handled();
	}));
    
    memProfilerWidget->SetOnMouseMove(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
        // calc sampleIdx
        FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
        int sampleIdx = memProfilerWidget->CalcHoverSampleIdx(cursorPos);
        static float lastToolTipVal = 0.0f;
        
        if (sampleIdx >= 0 && lastToolTipVal != tempLuaMemNodeChartList[sampleIdx].totalSize)
        {
            memProfilerWidget->SetToolTipVal(tempLuaMemNodeChartList[sampleIdx].totalSize);
            lastToolTipVal = tempLuaMemNodeChartList[sampleIdx].totalSize;
        }
        else if (sampleIdx < 0)
        {
            memProfilerWidget->SetToolTipVal(-1.0f);
        }
        
        if (isMemMouseButtonDown == true)
        {
            // calc sampleIdx
            sampleIdx = memProfilerWidget->CalcClickSampleIdx(cursorPos);
            if (sampleIdx >= 0 && sampleIdx < cMaxSampleNum)
            {
                mouseUpMemIdx = sampleIdx;
                mouseUpPoint = cursorPos;
                memProfilerWidget->SetMouseMovePoint(mouseUpPoint);
                CombineSameFileInfo(tempLuaMemNodeChartList[sampleIdx].infoList);
                luaTotalMemSize = tempLuaMemNodeChartList[sampleIdx].totalSize;
                memTreeView->RequestTreeRefresh();
            }
        }
        
        return FReply::Handled();
    }));

	memProfilerWidget->SetOnMouseButtonUp(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
        isMemMouseButtonUp = true;
        
        if (mouseUpPoint.X != mouseDownPoint.X
            && mouseDownMemIdx >= 0 && mouseDownMemIdx < cMaxSampleNum)
        {
            memProfilerWidget->SetMouseMovePoint(mouseUpPoint);
            CalcPointMemdiff(mouseDownMemIdx, mouseUpMemIdx);
            memTreeView->RequestTreeRefresh();
        }
        
		isMemMouseButtonDown = false;
		return FReply::Handled();
	}));

	memProfilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
		isMemMouseButtonDown = false;
	}));
    
	// init tree view
	SAssignNew(treeview, STreeView<TSharedPtr<FunctionProfileInfo>>)
	.ItemHeight(800)
	.TreeItemsSource(&shownRootProfiler)
	.OnGenerateRow_Raw(this, &SProfilerInspector::OnGenerateRowForList)
	.OnGetChildren_Raw(this, &SProfilerInspector::OnGetChildrenForTree)
	.SelectionMode(ESelectionMode::None)
	.HeaderRow
	(
        SNew(SHeaderRow)
        + SHeaderRow::Column("Overview").DefaultLabel(FText::FromName("Overview")).FixedWidth(fixRowWidth)
        + SHeaderRow::Column("Time ms").DefaultLabel(FText::FromName("Time ms")).FixedWidth(fixRowWidth)
        + SHeaderRow::Column("Calls").DefaultLabel(FText::FromName("Calls")).FixedWidth(fixRowWidth)
	 );

    SAssignNew(memTreeView, STreeView<TSharedPtr<FileMemInfo>>)
    .ItemHeight(800)
    .TreeItemsSource(&shownParentFileName)
    .OnGenerateRow_Raw(this, &SProfilerInspector::OnGenerateMemRowForList)
    .OnGetChildren_Raw(this, &SProfilerInspector::OnGetMemChildrenForTree)
    .SelectionMode(ESelectionMode::None)
    .HeaderRow
    (
        SNew(SHeaderRow)
        + SHeaderRow::Column("Overview").DefaultLabel(FText::FromName("Overview")).FixedWidth(fixRowWidth)
        + SHeaderRow::Column("Memory Size").DefaultLabel(FText::FromName("Memory Size")).FixedWidth(fixRowWidth)
        + SHeaderRow::Column("Compare Two Point").DefaultLabel(FText::FromName("Compare Two Point")).FixedWidth(fixRowWidth)
     );
    
    SAssignNew(snapshotDiffTreeView, STreeView<TSharedPtr<FileMemInfo>>)
    .ItemHeight(800)
    .TreeItemsSource(&snapshotDiffParentArray)
    .OnGenerateRow_Raw(this, &SProfilerInspector::OnGenerateSnapshotDiffList)
    .OnGetChildren_Raw(this, &SProfilerInspector::OnGetSnapshotDiffChildrenForTree)
    .SelectionMode(ESelectionMode::None)
    .HeaderRow
    (
     SNew(SHeaderRow)
     + SHeaderRow::Column("Object Info").DefaultLabel(FText::FromName("Object Info")).FixedWidth(snapshotInfoRowWidth)
     + SHeaderRow::Column("Memory Size").DefaultLabel(FText::FromName("Memory Size")).FixedWidth(fixRowWidth)
     );
    
    SAssignNew(snapshotListView, SListView<TSharedPtr<SnapshotInfo>>)
    .ItemHeight(800)
    .ListItemsSource(&snapshotInfoArray)
    .OnGenerateRow_Raw(this, &SProfilerInspector::OnGenerateSnapshotInfoRowForList)
    .SelectionMode(ESelectionMode::None)
    .HeaderRow
    (
        SNew(SHeaderRow)
        + SHeaderRow::Column("Snapshot Name").DefaultLabel(FText::FromName("Snapshot Name")).FixedWidth(fixRowWidth)
        + SHeaderRow::Column("Allocations (Diff)").DefaultLabel(FText::FromName("Allocations(Diff)")).FixedWidth(fixRowWidth)
        + SHeaderRow::Column("Memory Size (Diff)").DefaultLabel(FText::FromName("Memory Size (Diff)")).FixedWidth(fixRowWidth)
     );

	memProfilerWidget->SetStdLineVisibility(EVisibility::Collapsed);
	cpuProfilerWidget->SetStdLineVisibility(EVisibility::Visible);
	return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[//		 .AutoWidth()
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.FillWidth(0.2)
		[
			SNew(SBorder)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.Padding(8.0, 5.0)
				.MaxHeight(200.0f)
				.Padding(0, 3.0f)
				[
					SAssignNew(cpuTabWidget, SProfilerTabWidget)
					.TabIcon(FEditorStyle::GetBrush("ProfilerCommand.StatsProfiler"))
					.TabName(FText::FromString("CPU Usages"))
					.OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
					tabSwitcher->SetActiveWidgetIndex(0);
					return FReply::Handled();
					}))
				]

				+SVerticalBox::Slot()
				.Padding(8.0, 5.0)
				.MaxHeight(200.0f)
				.Padding(0, 3.0f)
				[
					SAssignNew(memTabWidget, SProfilerTabWidget)
					.TabIcon(FEditorStyle::GetBrush("ProfilerCommand.MemoryProfiler"))
					.TabName(FText::FromString("Memory Usages"))
					.OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
					tabSwitcher->SetActiveWidgetIndex(1);
						return FReply::Handled();
					}))
				]
             
                +SVerticalBox::Slot()
                .Padding(8.0, 5.0)
                .MaxHeight(200.0f)
                .Padding(0, 3.0f)
                [
                    SAssignNew(memTabWidget, SProfilerTabWidget)
                    .TabIcon(FEditorStyle::GetBrush("Matinee.CreateCameraActor"))
                    .TabName(FText::FromString("Lua Memory\nSnapshot"))
                    .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                        tabSwitcher->SetActiveWidgetIndex(2);
                        return FReply::Handled();
                    }))
                ]
			]
		]

		+SHorizontalBox::Slot()
		.FillWidth(0.8)
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		[
			SAssignNew(tabSwitcher, SWidgetSwitcher)
			.WidgetIndex(0)
			+SWidgetSwitcher::Slot()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
					[
						SNew(STextBlock)
						.Text(FText::FromString("CPU	|	"))
					]

					+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(25.0f)
					[
						profilerCheckBox.ToSharedRef()
					]

					+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f).Padding(0, 3.0f, 0, 0)
					[
						SNew(STextBlock).Text(FText::FromName("Animate"))
					]

					+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
					[
						SNew(SButton).Text(FText::FromName("Clear"))
						.ContentPadding(FMargin(2.0, 2.0))
						.OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
						OnClearBtnClicked();
						return FReply::Handled();
						}))
					]
				]

				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill)
					[
						cpuProfilerWidget.ToSharedRef()
					]
				]

				+ SVerticalBox::Slot()
				[
                    SNew(SScrollBox)
                    +SScrollBox::Slot()
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center)
                        [
                            SNew(STextBlock).Text_Lambda([=]() {
                                FString titleStr = FString::Printf(TEXT("============================ CPU profiler Max(%.3f ms), Avg(%.3f ms) ============================"),
                                                               maxProfileSamplesCostTime / perMilliSec, avgProfileSamplesCostTime / perMilliSec);
                                return FText::FromString(titleStr); })
                        ]
                    ]

                    +SScrollBox::Slot()
                    [
                        treeview.ToSharedRef()
                    ]
				]
			]

			+SWidgetSwitcher::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			[

                SNew(SVerticalBox)
                +SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
                    [
                        SNew(STextBlock)
                        .Text(FText::FromString("MEMORY	|   "))
                    ]

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(0, 3.0f, 15.0f, 0).MaxWidth(100.0f)
                    [
                        SNew(STextBlock)
                        .Text_Lambda([=]() {
                        FString totalMemory = TEXT("Total : ") + ChooseMemoryUnit(luaTotalMemSize * 1024.0f);
                        return FText::FromString(totalMemory);
                        })
                    ]

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(25.0f)
                    [
                        memProfilerCheckBox.ToSharedRef()
                    ]

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f).Padding(0, 3.0f, 0, 0)
                    [
                        SNew(STextBlock).Text(FText::FromName("Animate"))
                    ]

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
                    [
                        SNew(SButton).Text(FText::FromName("Clear"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                        OnClearBtnClicked();
                        return FReply::Handled();
                        }))
                    ]
                
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth()
                    [
                        SNew(SButton)
                        .Text(FText::FromName("Forced GC"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                            FArrayWriter messageWriter;
                            int bytesSend = 0;
                            int snapshotSendId = 0;
                            int emptySnapshotID = -1;
                            int hookEvent = NS_SLUA::ProfilerHookEvent::PHE_MEMORY_GC;
                            int connectionsSize = ProfileServer->GetConnections().Num();

                            messageWriter.Empty();
                            messageWriter.Seek(0);
                            messageWriter << hookEvent;
                            messageWriter << snapshotSendId;
                            messageWriter << emptySnapshotID;
                            messageWriter << emptySnapshotID;
                        
                            if(connectionsSize > 0)
                            {
                                FSocket* socket = ProfileServer->GetConnections()[0]->GetSocket();
                                if (socket && socket->GetConnectionState() == SCS_Connected)
                                    socket->Send(messageWriter.GetData(), messageWriter.Num(), bytesSend);
                            }

                            return FReply::Handled();
                        }))
                    ]
                ]

                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill)
                    [
                        memProfilerWidget.ToSharedRef()
                    ]
                ]

                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SVerticalBox)
                    +SVerticalBox::Slot()
                    .Padding(0, 1.0f)
                    .HAlign(EHorizontalAlignment::HAlign_Fill)
                    .MaxHeight(1.0f)
                    [
                        SNew(SBorder)
                        .BorderImage(FEditorStyle::GetBrush("ProgressBar.ThinBackground"))
                    ]
                ]

                + SVerticalBox::Slot()
                [
                    SNew(SScrollBox)
                    +SScrollBox::Slot()
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).Padding(0, 10.0f)
                        [
                            SNew(STextBlock).Text_Lambda([=]() {
                            FString titleStr = TEXT("============================ Memory profiler Max("
                                             + ChooseMemoryUnit(maxLuaMemory * 1024.0f)
                                             +"), Avg("
                                             + ChooseMemoryUnit(avgLuaMemory * 1024.0f)
                                             +") ============================");
                            return FText::FromString(titleStr);
                            })
                        ]
                    ]

                    + SScrollBox::Slot()
                    [
                        memTreeView.ToSharedRef()
                    ]
                ]
            ]
         
            +SWidgetSwitcher::Slot()
            .HAlign(EHorizontalAlignment::HAlign_Fill)
            [
                SNew(SVerticalBox)
                +SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth().Padding(15.0f, 3.0f, 15.0, 0)
                    [
                        SNew(SButton)
                        .Text(FText::FromName("Snapshot"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                            FArrayWriter messageWriter;
                            int bytesSend = 0;
                            int emptySnapshotID = -1;
                            int snapshotSendId = snapshotInfoArray.Num() == 0 ? 1 : snapshotInfoArray[snapshotInfoArray.Num() - 1].Get()->id + 1;
                            int hookEvent = NS_SLUA::ProfilerHookEvent::PHE_MEMORY_SNAPSHOT;
                            int connectionsSize = ProfileServer->GetConnections().Num();

                            messageWriter.Empty();
                            messageWriter.Seek(0);
                            messageWriter << hookEvent;
                            messageWriter << snapshotSendId;
                            messageWriter << emptySnapshotID;
                            messageWriter << emptySnapshotID;

                            if(connectionsSize > 0)
                            {
                                FSocket* socket = ProfileServer->GetConnections()[0]->GetSocket();
                                if (socket && socket->GetConnectionState() == SCS_Connected)
                                {
                                    socket->Send(messageWriter.GetData(), messageWriter.Num(), bytesSend);
                                    if(bytesSend > 0)
                                    {
                                        FString *name = new FString(TEXT("memory snapshot ") + FString::FromInt(snapshotSendId));
										snapshotIdArray.Add(MakeShareable(name));
                                        SnapshotInfo *info = new SnapshotInfo();
                                        info->name = *name;
                                        info->id = snapshotSendId;
//                                        info->preInfoPtr = snapshotSendId == 1 ? NULL : snapshotInfoArray[snapshotSendId - 2].Get();
                                        snapshotInfoArray.Add(MakeShareable(info));
                                    }
                                }
                            }

                            return FReply::Handled();
                            }))
                    ]
                 
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(3.0f, 5.0f, 3.0f, 0).AutoWidth()
                    [
                        SNew(STextBlock)
                        .Text(FText::FromName("Need Compare : "))
                    ]
                 
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(0, 3.0f, 5.0f, 0).AutoWidth()
                    [
                        SNew(STextComboBox)
//                        .Font(IDetailLayoutBuilder::GetDetailFont())
                        .OptionsSource(&snapshotIdArray)
                        .InitiallySelectedItem(snapshotIdArray[0])
                        .OnSelectionChanged_Raw(this, &SProfilerInspector::OnPreSnapshotItemChanged)
                    ]
                 
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(3.0f, 5.0f, 3.0f, 0).AutoWidth()
                    [
                        SNew(STextBlock)
                        .Text(FText::FromName("<->"))
                    ]
                 
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(5.0f, 3.0f, 5.0f, 0).AutoWidth()
                    [
                        SNew(STextComboBox)
//                        .Font(IDetailLayoutBuilder::GetDetailFont())
                        .OptionsSource(&snapshotIdArray)
                        .InitiallySelectedItem(snapshotIdArray[0])
                        .OnSelectionChanged_Raw(this, &SProfilerInspector::OnSnapshotItemChanged)
                    ]
                 
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
                    [
                        SNew(SButton)
                        .Text(FText::FromName("Compare"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                            FArrayWriter messageWriter;
                            int bytesSend = 0;
                            int snapshotSendId = 0;
                            int hookEvent = NS_SLUA::ProfilerHookEvent::PHE_SNAPSHOT_COMPARE;
                            int connectionsSize = ProfileServer->GetConnections().Num();
                        
                            messageWriter.Empty();
                            messageWriter.Seek(0);
                            messageWriter << hookEvent;
                            messageWriter << snapshotSendId;
                            messageWriter << preSnapshotID;
                            messageWriter << snapshotID;
                        
                            if(connectionsSize > 0)
                            {
                                FSocket* socket = ProfileServer->GetConnections()[0]->GetSocket();
                                // if snapshotId or preSnapshotId equals 0, means that user does not choose effective snapshot
                                if (socket && socket->GetConnectionState() == SCS_Connected && snapshotID && preSnapshotID)
                                {
                                    socket->Send(messageWriter.GetData(), messageWriter.Num(), bytesSend);
                                }
                                
                                if(bytesSend > 0) showSnapshotDiff = true;
                            }
                            return FReply::Handled();
                        }))
                    ]
                 
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(5.0f, 3.0f, 5.0f, 0).AutoWidth()
                    [
                        SNew(STextComboBox)
                        //                        .Font(IDetailLayoutBuilder::GetDetailFont())
                        .OptionsSource(&snapshotIdArray)
                        .InitiallySelectedItem(snapshotIdArray[0])
                        .OnSelectionChanged_Raw(this, &SProfilerInspector::OnDeleteSnapshotItem)
                    ]

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
                    [
                        SNew(SButton)
                        .Text(FText::FromName("Delete"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                            FArrayWriter messageWriter;
                            int bytesSend = 0;
                            int emptySnapshotID = -1;
                            int hookEvent = NS_SLUA::ProfilerHookEvent::PHE_SNAPSHOT_DELETE;
                            int connectionsSize = ProfileServer->GetConnections().Num();

                            messageWriter.Empty();
                            messageWriter.Seek(0);
                            messageWriter << hookEvent;
                            messageWriter << deleteSnapshotID;
                            messageWriter << emptySnapshotID;
                            messageWriter << emptySnapshotID;

                            if(connectionsSize > 0)
                            {
                                FSocket* socket = ProfileServer->GetConnections()[0]->GetSocket();
                                // if snapshotId or preSnapshotId equals 0, means that user does not choose effective snapshot
                                if (socket && socket->GetConnectionState() == SCS_Connected && deleteSnapshotID)
                                {
                                    socket->Send(messageWriter.GetData(), messageWriter.Num(), bytesSend);
                                }
                                
                                if(bytesSend > 0)
                                {
                                    int removeIndex = getSnapshotInfoIndex(deleteSnapshotID);
                                    if(removeIndex != -1) {
                                        if(removeIndex != 0 && removeIndex + 1 < snapshotInfoArray.Num()) {
                                            SnapshotInfo *preInfo = snapshotInfoArray[removeIndex - 1].Get();
                                            SnapshotInfo *nextInfo = snapshotInfoArray[removeIndex + 1].Get();
                                            nextInfo->memDiff = nextInfo->memSize - preInfo->memSize;
                                            nextInfo->objDiff = nextInfo->objSize - preInfo->objSize;
                                        } else if(removeIndex == 0 && snapshotInfoArray.Num() != 1) {
                                            SnapshotInfo *nextInfo = snapshotInfoArray[removeIndex + 1].Get();
                                            nextInfo->memDiff = 0;
                                            nextInfo->objDiff = 0;
                                        }
                                        snapshotInfoArray.RemoveAt(removeIndex);
                                    }
                                    
                                    for(int i = 1; i < snapshotIdArray.Num(); i++) {
                                        TArray<FString> stringArray;
                                        snapshotIdArray[i].Get()->ParseIntoArray(stringArray, TEXT(" "), false);
                                        if(FCString::Atoi(*stringArray[stringArray.Num() - 1]) == deleteSnapshotID)
                                        {
                                            snapshotIdArray.RemoveAt(i);
                                        }
                                    }
                                }
                            }
                            deleteSnapshotID = 0;
                            snapshotListView->RequestListRefresh();
                            return FReply::Handled();
                        }))
                    ]
                ]
             
                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SVerticalBox)
                    +SVerticalBox::Slot()
                    .Padding(0, 1.0f)
                    .HAlign(EHorizontalAlignment::HAlign_Fill)
                    .MaxHeight(1.0f)
                    [
                        SNew(SBorder)
                        .BorderImage(FEditorStyle::GetBrush("ProgressBar.ThinBackground"))
                    ]
                ]

                + SVerticalBox::Slot()
                [
                    SNew(SScrollBox)
                    +SScrollBox::Slot()
                    [
                        SNew(SVerticalBox)
                        .Visibility_Lambda([=]() {
                            if(showSnapshotDiff && preSnapshotID && snapshotID)
                            {
                                return EVisibility::Visible;
                            } else {
                                return EVisibility::Collapsed;
                            }
                        })
                     
                        + SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).Padding(0, 10.0f)
                        [
                            SNew(STextBlock).Text_Lambda([=]() {
                                int memDiffSize = 0;
                                int objDiffSize = 0;
                                int index = getSnapshotInfoIndex(snapshotID);
                                int preIndex = getSnapshotInfoIndex(preSnapshotID);
                            
                                if(index != -1 && preIndex != -1) {
                                    SnapshotInfo *info = snapshotInfoArray[index].Get();
                                    SnapshotInfo *preInfo = snapshotInfoArray[preIndex].Get();
                                
                                    memDiffSize = info->memSize - preInfo->memSize;
                                    objDiffSize = info->objSize - preInfo->objSize;
                                }
                            
                                FString titleStr = TEXT("============================ Diff Memory Size("
                                           + ChooseMemoryUnit(memDiffSize * 1024.0f)
                                           +"), Diff Object Num("
                                           + FString::FromInt(objDiffSize)
                                           +") ============================");
                                return FText::FromString(titleStr);
                            })
                        ]
                     
                        +SVerticalBox::Slot().AutoHeight()
                        [
                            snapshotDiffTreeView.ToSharedRef()
                        ]
                     
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(SVerticalBox)
                            +SVerticalBox::Slot()
                            .Padding(0, 1.0f)
                            .HAlign(EHorizontalAlignment::HAlign_Fill)
                            .MaxHeight(1.0f)
                            [
                                SNew(SBorder)
                                .BorderImage(FEditorStyle::GetBrush("ProgressBar.ThinBackground"))
                            ]
                        ]
                    ]

                    + SScrollBox::Slot()
                    [
                        snapshotListView.ToSharedRef()
                    ]
                ]
            ]
        ]
	];
}

void SProfilerInspector::SortProfiler(SluaProfiler &rootProfiler)
{
	rootProfiler.Sort([](const TSharedPtr<FunctionProfileInfo>& LHS, const TSharedPtr<FunctionProfileInfo>& RHS)
					  {
						  if (LHS->mergedCostTime == RHS->mergedCostTime)
						  {
							  return LHS->globalIdx < RHS->globalIdx;
						  }
						  else
						  {
							  return LHS->mergedCostTime > RHS->mergedCostTime;
						  }
					  });

	SluaProfiler duplictedNodeArray;
	for (int idx = 0; idx < rootProfiler.Num(); idx++)//(auto &funcNode : rootProfiler)
	{
		TSharedPtr<FunctionProfileInfo> &funcNode = rootProfiler[idx];
		if (funcNode->isDuplicated == true)
		{
			continue;
		}
		if (funcNode->functionName.IsEmpty())
		{
			funcNode->isDuplicated = true;
			duplictedNodeArray.Add(funcNode);
			continue;
		}
		for (int jdx = idx + 1; jdx < rootProfiler.Num(); jdx++)
		{
			TSharedPtr<FunctionProfileInfo> &funcNode2 = rootProfiler[jdx];
			if (funcNode2->isDuplicated == true)
			{
				continue;
			}
			if (funcNode->functionName == funcNode2->functionName)
			{
				funcNode2->isDuplicated = true;
				duplictedNodeArray.Add(funcNode2);
			}
		}
	}

	for (int idx = 0; idx < rootProfiler.Num(); idx++)
	{
		if (rootProfiler[idx]->isDuplicated == true)
		{
			rootProfiler.RemoveAt(idx);
			idx--;
		}
	}

	for (int idx = 0; idx < duplictedNodeArray.Num(); idx++)
	{
		rootProfiler.Add(duplictedNodeArray[idx]);
	}
}

void SProfilerInspector::ShowProfilerTree(TArray<SluaProfiler> &selectedProfiler)
{
	if (selectedProfiler.Num() == 0)
	{
		shownRootProfiler.Empty();
		shownProfiler.Empty();
		if (treeview.IsValid())
		{
			treeview->RequestTreeRefresh();
		}
		return;
	}

	AssignProfiler(selectedProfiler, tmpRootProfiler, shownProfiler);

	TArray<int> emptyMergeArray;
	for (int idx = 0; idx < tmpRootProfiler.Num(); idx++)
	{
		TSharedPtr<FunctionProfileInfo> &funcNode = tmpRootProfiler[idx];
		if (funcNode->beMerged == true || funcNode->functionName.IsEmpty())
		{
			continue;
		}
		MergeSiblingNode(tmpRootProfiler, idx, tmpRootProfiler.Num(), emptyMergeArray, 0);
	}

	SortProfiler(tmpRootProfiler);
	AssignProfiler(tmpRootProfiler, shownRootProfiler);

	if (treeview.IsValid())
	{
		treeview->RequestTreeRefresh();
	}
	return;
}

TSharedRef<ITableRow> SProfilerInspector::OnGenerateRowForList(TSharedPtr<FunctionProfileInfo> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	// make each row in tree is align
	float rowWidth = fixRowWidth;
	if (Item->layerIdx == 0)
	{
		rowWidth = rowWidth - 12;
	}
	else
	{
		rowWidth = rowWidth - (Item->layerIdx + 1) * 10;
	}

	return
	SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
	.Padding(2.0f).Visibility_Lambda([=]() {
		if (Item->functionName.IsEmpty() || Item->beMerged == true || shownProfiler[Item->globalIdx]->beMerged == true)
			return EVisibility::Hidden;
		else
			return EVisibility::Visible;
	})
	[
	 SNew(SHeaderRow)
	 + SHeaderRow::Column("Overview").DefaultLabel(TAttribute<FText>::Create([=]() {
		if (shownProfiler.Num() > Item->globalIdx)
		{
			return FText::FromString(shownProfiler[Item->globalIdx]->brevName);
		}
		return FText::FromString("");
	}))
	 .FixedWidth(rowWidth).DefaultTooltip(TAttribute<FText>::Create([=]() {
		if (shownProfiler.Num() > Item->globalIdx)
		{
			return FText::FromString(shownProfiler[Item->globalIdx]->functionName);
		}
		return FText::FromString("");
	}))
	 + SHeaderRow::Column("Time ms").DefaultLabel(TAttribute<FText>::Create([=]() {
		if (shownProfiler.Num() > Item->globalIdx)
		{
			return FText::AsNumber(shownProfiler[Item->globalIdx]->mergedCostTime / perMilliSec);
		}
		return FText::FromString("");
	}))
	 .FixedWidth(fixRowWidth)
	 + SHeaderRow::Column("Calls").DefaultLabel(TAttribute<FText>::Create([=]() {
		if (shownProfiler.Num() > Item->globalIdx)
		{
			return FText::AsNumber(shownProfiler[Item->globalIdx]->mergedNum);
		}
		return FText::FromString("");

	}))
	 .FixedWidth(fixRowWidth)
	 ];
}

TSharedRef<ITableRow> SProfilerInspector::OnGenerateMemRowForList(TSharedPtr<FileMemInfo> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
    FText difference;
    
    if(Item->lineNum.Equals("-1", ESearchCase::CaseSensitive))
        difference = FText::FromString("");
    else
        difference = FText::FromString(ChooseMemoryUnit((float)Item->difference));
    
	return
	SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
	.Padding(2.0f)
	[
        SNew(SHeaderRow)
        + SHeaderRow::Column("Overview").DefaultLabel(TAttribute<FText>::Create([=]() {
            if (!Item->hint.IsEmpty())
            {
                FString fileNameInfo;

                if(Item->lineNum.Equals("-1", ESearchCase::CaseSensitive))
                    fileNameInfo = Item->hint;
                else
                    fileNameInfo = Item->hint + ":" + Item->lineNum;
                return FText::FromString(fileNameInfo);
            }
            return FText::FromString("");
        }))
        .FixedWidth(fixRowWidth)

        + SHeaderRow::Column("Memory Size").DefaultLabel(TAttribute<FText>::Create([=]() {
            if (Item->size >= 0)
            {
                if(Item->lineNum.Equals("-1", ESearchCase::CaseSensitive))
                    return FText::FromString("");
                else
                    return FText::FromString(ChooseMemoryUnit((float)Item->size));
            }
            return FText::FromString("");
        }))
        .FixedWidth(fixRowWidth)

        + SHeaderRow::Column("Compare Two Point")
        .FixedWidth(fixRowWidth)
        [
            SNew(STextBlock)
            .Text(difference)
            .ColorAndOpacity_Lambda([=]() {
                return checkLinearColor(Item->difference);
            })
        ]
	 ];
}

void SProfilerInspector::OnGetMemChildrenForTree(TSharedPtr<FileMemInfo> Parent, TArray<TSharedPtr<FileMemInfo>>& OutChildren)
{
    if(!Parent->lineNum.Equals("-1", ESearchCase::CaseSensitive)) return;
    for(auto &item : shownFileInfo)
    {
        if(Parent->hint.Equals(item->hint, ESearchCase::CaseSensitive))
            OutChildren.Add(item);
    }
}

#define LABEL 0
void SProfilerInspector::OnGetSnapshotDiffChildrenForTree(TSharedPtr<FileMemInfo> Parent, TArray<TSharedPtr<FileMemInfo>>& OutChildren)
{
    if(Parent->size != LABEL) return;
    
    for(auto &item : snapshotDiffArray)
    {
        if(Parent->difference == item->difference)
            OutChildren.Add(item);
    }
}

void SProfilerInspector::OnGetChildrenForTree(TSharedPtr<FunctionProfileInfo> Parent, TArray<TSharedPtr<FunctionProfileInfo>>& OutChildren)
{
	TArray<TSharedPtr<FunctionProfileInfo>> unSortedChildrenArray;

	if (Parent.IsValid() && Parent->functionName.IsEmpty() == false
		&& Parent->beMerged == false)
	{
		if (Parent->layerIdx == 0)
		{
			CopyFunctionNode(Parent, shownProfiler[Parent->globalIdx]);
		}

		int globalIdx = Parent->globalIdx + 1;
		int layerIdx = Parent->layerIdx;

		for (; globalIdx < shownProfiler.Num(); globalIdx++)
		{
			if (layerIdx + 1 == shownProfiler[globalIdx]->layerIdx)
			{
				if (shownProfiler[globalIdx]->beMerged == true || shownProfiler[globalIdx]->functionName.IsEmpty())
				{
					continue;
				}
				// find sibling first
				MergeSiblingNode(shownProfiler, globalIdx, shownProfiler.Num(), Parent->mergeIdxArray, 0);

				unSortedChildrenArray.Add(shownProfiler[globalIdx]);
			}
			else if(layerIdx == shownProfiler[globalIdx]->layerIdx)
			{
				break;
			}
		}

		// show the sibling node which has child nodes
		for (size_t mergeIdx = 0; mergeIdx <  Parent->mergeIdxArray.Num(); mergeIdx++)
		{
			int pointIdx = Parent->mergeIdxArray[mergeIdx] + 1;
			while (pointIdx < shownProfiler.Num() && shownProfiler[pointIdx]->layerIdx > Parent->layerIdx)
			{
				TSharedPtr<FunctionProfileInfo> &siblingNextNode = shownProfiler[pointIdx];
				if (siblingNextNode->beMerged == false && siblingNextNode->layerIdx == (Parent->layerIdx + 1) && !siblingNextNode->functionName.IsEmpty())
				{
					unSortedChildrenArray.Add(siblingNextNode);
				}
				MergeSiblingNode(shownProfiler, pointIdx, shownProfiler.Num(), Parent->mergeIdxArray, mergeIdx+1); // Parent->mergeIdxArray.Num() todo
				pointIdx++;
			}
		}

		// sort array by cost time and add to OutChildren
		unSortedChildrenArray.Sort([](const TSharedPtr<FunctionProfileInfo>& LHS, const TSharedPtr<FunctionProfileInfo>& RHS)
								   { return LHS->mergedCostTime > RHS->mergedCostTime; });

		for (int idx=0; idx<unSortedChildrenArray.Num(); idx++)
			OutChildren.Add(unSortedChildrenArray[idx]);
	}
}

TSharedRef<ITableRow> SProfilerInspector::OnGenerateSnapshotInfoRowForList(TSharedPtr<SnapshotInfo> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
    return
    SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
    .Padding(2.0f)
    [
        SNew(SHeaderRow)
        + SHeaderRow::Column("Snapshot Name")
        .FixedWidth(fixRowWidth)
        [
            SNew(STextBlock)
         .Text(FText::FromString(Item->name))
        ]

        + SHeaderRow::Column("Allocations (Diff)")
        .FixedWidth(fixRowWidth)
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot().AutoWidth()
            [
                SNew(STextBlock)
                 .Text_Lambda([=]() {
                    FString objStr = FString::Printf(TEXT("%d"), Item->objSize);
                    return FText::FromString(objStr);
                })
            ]
         
            +SHorizontalBox::Slot().AutoWidth()
            [
                SNew(STextBlock)
                .ColorAndOpacity_Lambda([=]() {
                    return checkLinearColor((float)(Item->objDiff));
                })
                .Text_Lambda([=]() {
                    FString objStr = FString::Printf(TEXT("(%d)"), (Item->objDiff));
                    return FText::FromString(objStr);
                })
            ]
        ]


        + SHeaderRow::Column("Memory Size (Diff)")
        .FixedWidth(fixRowWidth)
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot().AutoWidth()
            [
                SNew(STextBlock)
                .Text_Lambda([=]() {
                    return FText::FromString(ChooseMemoryUnit(Item->memSize * 1024.0f));
                })
            ]
         
            +SHorizontalBox::Slot().AutoWidth()
            [
                SNew(STextBlock)
                .ColorAndOpacity_Lambda([=]() {
                    return checkLinearColor((float)Item->memDiff);
                })
                .Text_Lambda([=]() {
                    FString objStr = FString::Printf(TEXT("(%s)"), *ChooseMemoryUnit(Item->memDiff * 1024.0f));
                    return FText::FromString(objStr);
                })
            ]
        ]
    ];
}

TSharedRef<ITableRow> SProfilerInspector::OnGenerateSnapshotDiffList(TSharedPtr<FileMemInfo> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
    return
    SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
    .Padding(2.0f)
    [
        SNew(SHeaderRow)
        + SHeaderRow::Column("Object Info")
        .FixedWidth(snapshotInfoRowWidth)
        [
            SNew(STextBlock)
            .Text(FText::FromString(Item->hint))
        ]

        + SHeaderRow::Column("Memory Size")
        .FixedWidth(fixRowWidth)
        .DefaultLabel(TAttribute<FText>::Create([=]() {
            if(Item->size == 0)
                return FText::FromString("");
            else
                return FText::FromString(ChooseMemoryUnit((float)Item->size));
        }))
     ];
}

void SProfilerInspector::MergeSiblingNode(SluaProfiler &profiler, int begIdx, int endIdx, TArray<int> parentMergeArray, int mergeArrayIdx)
{
	if (begIdx == endIdx || profiler[begIdx]->beMerged == true)
	{
		return;
	}

	TSharedPtr<FunctionProfileInfo> &node = profiler[begIdx];
	node->mergedNum = 1;
	node->mergedCostTime = node->costTime;
	node->mergeIdxArray.Empty();

	int pointIdx = begIdx + 1;
	SearchSiblingNode(profiler, pointIdx, endIdx, node);

	// merge with other parent nodes' child which function name is the same with self parent
	if (mergeArrayIdx >= parentMergeArray.Num())
	{
		return;
	}
	for (size_t idx = mergeArrayIdx; idx<parentMergeArray.Num(); idx++)
	{
		pointIdx = parentMergeArray[idx] + 1;
		SearchSiblingNode(profiler, pointIdx, endIdx, node);
	}
}

void SProfilerInspector::SearchSiblingNode(SluaProfiler& profiler, int curIdx, int endIdx, TSharedPtr<FunctionProfileInfo> &node)
{
	while (curIdx < endIdx && profiler[curIdx]->layerIdx >= node->layerIdx)
	{
		TSharedPtr<FunctionProfileInfo> &nextNode = profiler[curIdx];
		if (nextNode->layerIdx == node->layerIdx && nextNode->functionName == node->functionName)
		{
			nextNode->beMerged = true;
			node->mergedCostTime = node->mergedCostTime + nextNode->costTime;
			node->mergedNum = node->mergedNum + 1;
			node->mergeIdxArray.Add(nextNode->globalIdx);
		}
		curIdx++;
	}
}

void SProfilerInspector::CollectSnapshotInfo(TArray<SnapshotInfo> snapshotArray)
{
    for(int i =0; i < snapshotArray.Num(); i++)
    {
        SnapshotInfo info = snapshotArray[i];
        int infoIndex = getSnapshotInfoIndex(info.id);
        SnapshotInfo *infoPtr = snapshotInfoArray[infoIndex].Get();
            
        if(info.id ==infoPtr->id)
        {
            infoPtr->objSize = info.objSize;
            infoPtr->memSize = info.memSize;

            // when infoIndex equals 0 or -1, the diff equals 0;
            infoPtr->objDiff = infoIndex > 0 ? info.objSize - snapshotInfoArray[infoIndex - 1].Get()->objSize : 0;
            infoPtr->memDiff = infoIndex > 0 ? info.memSize - snapshotInfoArray[infoIndex - 1].Get()->memSize : 0;
        }
    }
    
    snapshotListView->RequestListRefresh();
}

#define TABLE 1
#define FUNCTION 2
#define THREAD 3
#define USERDATA 4
#define OTHERS 5

void SProfilerInspector::CollectSnapshotDiff(TArray<NS_SLUA::LuaMemInfo> diffArray)
{
    int id = -1;
    int objNum = 0;
    snapshotDiffArray.Empty();
    snapshotDiffParentArray.Empty();
    for(int i = 0; i < diffArray.Num(); i++)
    {
        NS_SLUA::LuaMemInfo item = diffArray[i];
        if(item.size == 0)
        {
            if(item.hint.Equals("Table", ESearchCase::CaseSensitive))
            {
                id = TABLE;
            }
            else if(item.hint.Equals("Function", ESearchCase::CaseSensitive))
            {
                id = FUNCTION;
                if(objNum)
                {
                    FileMemInfo *info = new FileMemInfo();
                    info->hint = FString("Table");
                    info->size = LABEL;
                    info->difference = TABLE;
                    snapshotDiffParentArray.Add(MakeShareable(info));
                }
            }
            else if(item.hint.Equals("Thread", ESearchCase::CaseSensitive))
            {
                id = THREAD;
                if(objNum)
                {
                    FileMemInfo *info = new FileMemInfo();
                    info->hint = FString("Function");
                    info->size = LABEL;
                    info->difference = FUNCTION;
                    snapshotDiffParentArray.Add(MakeShareable(info));
                }
            }
            else if(item.hint.Equals("Userdata", ESearchCase::CaseSensitive))
            {
                id = USERDATA;
                if(objNum) {
                    FileMemInfo *info = new FileMemInfo();
                    info->hint = FString("Thread");
                    info->size = LABEL;
                    info->difference = THREAD;
                    snapshotDiffParentArray.Add(MakeShareable(info));
                }
            }
            else if(item.hint.Equals("OtherType", ESearchCase::CaseSensitive))
            {
                id = OTHERS;
                if(objNum)
                {
                    FileMemInfo *info = new FileMemInfo();
                    info->hint = FString("Userdata");
                    info->size = LABEL;
                    info->difference = USERDATA;
                    snapshotDiffParentArray.Add(MakeShareable(info));
                }
            }
            objNum = 0;
            continue;
        }
        
        FileMemInfo *info = new FileMemInfo();
        info->hint = item.hint;
        info->size = item.size;
        info->difference = id;
        
        snapshotDiffArray.Add(MakeShareable(info));
        objNum++;

        
        if(i == diffArray.Num() - 1 && objNum)
        {
            FileMemInfo *parentInfo = new FileMemInfo();
            info->hint = FString("OtherType");
            info->size = 0;
            info->difference = OTHERS;
            snapshotDiffParentArray.Add(MakeShareable(info));
        }
    }
    
    snapshotDiffTreeView->RequestTreeRefresh();
}

void SProfilerInspector::CollectMemoryNode(TArray<NS_SLUA::LuaMemInfo>& memoryInfoList)
{
	luaTotalMemSize = 0;
	ProflierMemNode memNode;
    
	for(auto& memFileInfo : memoryInfoList)
	{
        TArray<FString> fileInfoList = SplitFlieName(memFileInfo.hint);
        if(fileInfoList.Num() == 0) continue;
        
        FString fileName = fileInfoList[0];
        
        // if the record file have file name and line number, the return array should have two item.
        if(fileInfoList.Num() < 2 || fileName.Contains(TEXT("ProfilerScript"), ESearchCase::CaseSensitive, ESearchDir::FromEnd))
		{
			continue;
		}
        luaTotalMemSize += memFileInfo.size;
        FileMemInfo fileInfo;
        fileInfo.hint = fileName;
        fileInfo.lineNum = fileInfoList[1];
        fileInfo.size = memFileInfo.size;
        memNode.infoList.Add(fileInfo);
	}
    //luaTotalMemSize unit changed from byte to KB
	luaTotalMemSize /= 1024.0f;
    memNode.totalSize = luaTotalMemSize;
	luaMemNodeChartList.Add(memNode);
    luaMemNodeChartList.RemoveAt(0);
}

void SProfilerInspector::CombineSameFileInfo(MemFileInfoList& infoList)
{
	shownFileInfo.Empty();
    shownParentFileName.Empty();
    for(auto& fileInfo : infoList)
    {
        FString fileHint = fileInfo.hint;
        int index = ContainsFile(fileHint.Append(fileInfo.lineNum), shownFileInfo);
        if(index >= 0)
        {
            shownFileInfo[index]->size += fileInfo.size;
        }
        else
        {
            FileMemInfo *info = new FileMemInfo();
            info->hint = fileInfo.hint;
            info->lineNum = fileInfo.lineNum;
            info->size = fileInfo.size;
            shownFileInfo.Add(MakeShareable(info));
            
            fileHint = fileInfo.hint;
            
            if(ContainsFile(fileHint.Append("-1"), shownParentFileName) < 0)
            {
                FileMemInfo *fileParent = new FileMemInfo();
                fileParent->hint = fileInfo.hint;
                fileParent->lineNum = "-1";
                shownParentFileName.Add(MakeShareable(fileParent));
            }
        }
    }
    
    SortShownInfo();
}

void ExchangeMemInfoNode(ShownMemInfoList& list, int originIndx, int newIndex)
{
    list[originIndx]->size = list[newIndex]->size;
    list[originIndx]->hint = list[newIndex]->hint;
    list[originIndx]->lineNum = list[newIndex]->lineNum;
}

void SortMemInfo(ShownMemInfoList& list, int beginIndex, int endIndex)
{
    if (beginIndex < endIndex)
    {
        int left = beginIndex,right = endIndex;
        if(left >= right) return ;
        int key = list[left]->size;
        FString keyHint = list[left]->hint;
        FString keyLineNumber = list[left]->lineNum;
        
        while(left<right)
        {
            while(list[right]->size<=key && left<right) right--;
            ExchangeMemInfoNode(list, left, right);
            
            while(list[left]->size>=key && left<right) left++;
            ExchangeMemInfoNode(list, right, left);
        }
        list[left]->size = key;
        list[left]->hint = keyHint;
        list[left]->lineNum = keyLineNumber;
        
        SortMemInfo(list, beginIndex, left - 1);
        SortMemInfo(list, left + 1, endIndex);
    }
}

void SProfilerInspector::SortShownInfo()
{
    SortMemInfo(shownFileInfo, 0, shownFileInfo.Num()-1);
}

void SProfilerInspector::OnSnapshotItemChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
    for(int32 ItemID = 0; ItemID < snapshotIdArray.Num(); ItemID++)
    {
        if(snapshotIdArray[ItemID] == NewSelection ) snapshotID = ItemID;
    }
    
    if(snapshotID == 0) showSnapshotDiff = false;
}

void SProfilerInspector::OnPreSnapshotItemChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
    for(int32 ItemID = 0; ItemID < snapshotIdArray.Num(); ItemID++)
    {
        if(snapshotIdArray[ItemID] == NewSelection) preSnapshotID = ItemID;
    }
    
    if(preSnapshotID == 0) showSnapshotDiff = false;
}
void SProfilerInspector::OnDeleteSnapshotItem(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
    for(int32 ItemID = 0; ItemID < snapshotIdArray.Num(); ItemID++)
    {
        if(snapshotIdArray[ItemID] == NewSelection) {
            TArray<FString> stringArray;
            snapshotIdArray[ItemID].Get()->ParseIntoArray(stringArray, TEXT(" "), false);
            deleteSnapshotID = FCString::Atoi(*stringArray[stringArray.Num() - 1]);
        }
    }
}

void SProfilerInspector::CalcPointMemdiff(int beginIndex, int endIndex)
{
    // Always use new record of memory as the compareing data;
    if(beginIndex > endIndex)
    {
        int temp = beginIndex;
        beginIndex = endIndex;
        endIndex = temp;
        
        CombineSameFileInfo(tempLuaMemNodeChartList[endIndex].infoList);
    }
    
    // initialize the difference in shownFileInfo to avoid the consequence that the item did not have the file record but the difference is 0
    for(auto &info : shownFileInfo) info->difference = info->size;

    for(auto &info : tempLuaMemNodeChartList[beginIndex].infoList)
    {
        FString fileHint = info.hint;

        int index = ContainsFile(fileHint.Append(info.lineNum), shownFileInfo);
        if(index >= 0)
        {
            shownFileInfo[index].Get()->difference -= info.size;
        }
        else
        {
            FileMemInfo *newInfo = new FileMemInfo();
            newInfo->hint = info.hint;
            newInfo->size = 0;
            newInfo->lineNum = info.lineNum;
            newInfo->difference -= info.size;
            shownFileInfo.Add(MakeShareable(newInfo));
        }
    }
    
    float diff = 0;
    for(auto &info : shownFileInfo) diff += info->difference;
    NS_SLUA::Log::Log("The difference between two Point is %.3f KB", (float)diff/1024.0f);
}

int SProfilerInspector::ContainsFile(FString& fileName, ShownMemInfoList &list)
{
    int index = -1;
    for(auto& fileInfo : list)
    {
        index ++;
        
        FString fileHint = fileInfo->hint;
        if(fileName.Equals(fileHint.Append(fileInfo->lineNum), ESearchCase::CaseSensitive)) return index;
    }
    index = -1;
    return index;
}

FString SProfilerInspector::ChooseMemoryUnit(float memorySize)
{
    int absMemSize = FGenericPlatformMath::Abs(memorySize);
    
    if(absMemSize < 1024.0f)
    {
        return FString::Printf(TEXT("%d Bytes"), (int)memorySize);
    }
    
    // form byte to KB
    memorySize /= 1024.0f;
    absMemSize /= 1024.0f;
    
	if (absMemSize < 1024.0f) return FString::Printf(TEXT("%.3f KB"), memorySize);
	else if (absMemSize >= 1024.0f) return FString::Printf(TEXT("%.3f MB"), (memorySize / 1024.0f));
	return FString::Printf(TEXT("%.3f"), memorySize);
}

TArray<FString> SProfilerInspector::SplitFlieName(FString filePath)
{
    TArray<FString> stringArray;
    if(&filePath == NULL) return stringArray;
    FString fileInfo;
	filePath.ParseIntoArray(stringArray, TEXT("/"), false);

    if(stringArray.Num() == 0)
    {
        stringArray.Add("");
        return stringArray;
    }
    
    fileInfo = stringArray[stringArray.Num() - 1];
    stringArray.Empty();
    fileInfo.ParseIntoArray(stringArray, TEXT(":"), false);
    // to avoid the ProfilerScript case which does not have line number
    if(stringArray.Num() == 0) stringArray.Add(fileInfo);
    
    return stringArray;
}

int SProfilerInspector::getSnapshotInfoIndex(int id)
{
    for(int i = 0; i < snapshotInfoArray.Num(); i++) {
        if(snapshotInfoArray[i].Get()->id == id)
        {
            return i;
        }
    }
    return -1;
}

FLinearColor checkLinearColor(float checkNumber)
{
    FLinearColor linearColor;

    if (checkNumber > 0)
    {
        linearColor = FLinearColor(1, 0, 0, 1);
    }
    else if (checkNumber < 0)
    {
        linearColor = FLinearColor(0, 1, 0, 1);
    }
    else
    {
        linearColor = FLinearColor(1, 1, 1, 1);
    }
    
    return linearColor;
}

////////////////////////////// SProfilerWidget //////////////////////////////

void SProfilerWidget::SetArrayValue(TArray<float>& chartValArray, float maxCostTime, float maxMemSize)
{
	m_arrayVal = chartValArray;
	if (m_arrayVal.Num() == 0)
	{
		// clear line points
		for (int32 i = 0; i < m_cSliceCount; i++)
		{
			m_arraylinePath[i].Set(-1, -1);
		}
	}
	m_maxCostTime = maxCostTime;
    m_maxMemSize = maxMemSize;
}

void SProfilerWidget::SetMouseMovePoint(FVector2D mouseDownPoint)
{
    m_mouseDownPoint = mouseDownPoint;
}

void SProfilerWidget::SetMouseClickPoint(FVector2D mouseClickPoint)
{
    m_clickedPoint = mouseClickPoint;
}

void SProfilerWidget::Construct(const FArguments& InArgs)
{
	m_arraylinePath.SetNumUninitialized(m_cSliceCount);
    m_memStdScale = 1;
    m_pathArrayNum = 0;
    m_maxMemSize = 0.0f;
	m_maxCostTime = 0.0f;
	m_pointInterval = 0.0f;
	m_clickedPoint.X = -1.0f;
	m_toolTipVal = -1.0f;
	m_widgetWidth = 0.0f;
    m_mouseDownPoint = FVector2D(-1.0f, 0.0f);
	m_stdLineVisibility = InArgs._StdLineVisibility;

    float maxPointValue = 40 * 1000.f; // set max value as 40ms
    float stdLineValue = 16 * 1000.f;
    FString stdLineName = "16ms(60FPS)";
    AddStdLine(maxPointValue, stdLineValue, stdLineName);

    stdLineValue = 33 * 1000.f;
    stdLineName = "33ms(30FPS)";
    AddStdLine(maxPointValue, stdLineValue, stdLineName);
    
    CalcMemStdText(m_maxMemSize);

	SetToolTipText(TAttribute<FText>::Create([=]() {
		if (m_toolTipVal < 0)
			return FText::FromString("");
		else
			return FText::AsNumber(m_toolTipVal);
	}));
}

void SProfilerWidget::SetToolTipVal(float val)
{
	m_toolTipVal = val;
}

FVector2D SProfilerWidget::ComputeDesiredSize(float size) const
{
	return FVector2D(m_widgetWidth, cMaxViewHeight);
}

void SProfilerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	m_widgetWidth = AllottedGeometry.Size.X;
    m_pathArrayNum = 0;

	if (m_arrayVal.Num() == 0)
	{
		return;
	}

	// calc standard line level accroding to max cost time
	m_stdPositionY.Empty();
	m_stdStr.Empty();

	if (m_maxCostTime > 0 && m_stdLineVisibility.Get() == EVisibility::Visible)
	{
		CalcStdLine(m_maxCostTime);
    }
    else if (m_maxMemSize > 0 && m_stdLineVisibility.Get() != EVisibility::Visible)
    {
        CalcMemStdText(m_maxMemSize);
    }

	for (int32 i = 0; i < m_cSliceCount; i++)
	{
		if (m_arrayVal[i] < 0)
		{
			FVector2D NewPoint(-1, -1);
			m_arraylinePath[i] = NewPoint;
		}
		else if(m_stdLineVisibility.Get() == EVisibility::Visible)
		{
			float yValue = 0;

			if (m_maxCostTime != 0.0f)
			{
				yValue = cMaxViewHeight * (m_arrayVal[i] / m_maxPointHeight);
			}
			if (yValue > cMaxViewHeight)
			{
				FVector2D NewPoint((5 * i + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth), 0);
				m_arraylinePath[i] = NewPoint;
			}
			else
			{
				FVector2D NewPoint((5 * i + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth), cMaxViewHeight - yValue);
				m_arraylinePath[i] = NewPoint;
			}
		}
		else if(m_stdLineVisibility.Get() != EVisibility::Visible)
		{
			float yValue = 0;
            
			if (m_maxCostTime != 0.0f)
			{
				yValue = cMaxViewHeight * (m_arrayVal[i] / (1024 * m_memStdScale));
			}
			if (yValue > cMaxViewHeight)
			{
				FVector2D NewPoint((5 * i + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth), 0);
				m_arraylinePath[i] = NewPoint;
			}
			else
			{
                if(m_pathArrayNum < m_cSliceCount && cMaxViewHeight - yValue != -1.0f)m_pathArrayNum ++;
				FVector2D NewPoint((5 * i + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth), cMaxViewHeight - yValue);
				m_arraylinePath[i] = NewPoint;
			}
		}
	}

	m_pointInterval = 5 * (m_widgetWidth / m_cStdWidth);
}

int SProfilerWidget::CalcHoverSampleIdx(const FVector2D cursorPos)
{
	for (int32 i = 0; i< m_cSliceCount; i++)
	{
		if (m_arraylinePath[i].X < 0)
		{
			continue;
		}
		int interval = m_arraylinePath[i].X - cursorPos.X;
		if (interval >(-m_pointInterval / 2) && interval < (m_pointInterval / 2))
		{
			return i;
		}
	}

	return -1;
}

void SProfilerWidget::ClearClickedPoint()
{
	m_clickedPoint.X = -1.0f;
    m_mouseDownPoint.X = -1.0f;
}

int SProfilerWidget::CalcClickSampleIdx(FVector2D &cursorPos)
{
	for (int32 i = 0; i< m_cSliceCount; i++)
	{
		int interval = m_arraylinePath[i].X - cursorPos.X;
		if (interval > (-m_pointInterval / 2) && interval < (m_pointInterval / 2))
		{
			cursorPos = m_arraylinePath[i];
			return i;
		}
	}

    // check if the point is in front of the chart
    if(m_pathArrayNum != 0 && m_arraylinePath[m_arraylinePath.Num() - m_pathArrayNum].X > cursorPos.X)
    {
        cursorPos = m_arraylinePath[m_arraylinePath.Num() - m_pathArrayNum];
        return m_arraylinePath.Num() - m_pathArrayNum;
    }
    // check if the point is behind the chart
    else if(m_pathArrayNum != 0 && m_arraylinePath[m_arraylinePath.Num() - 1].X < cursorPos.X)
    {
        cursorPos = m_arraylinePath[m_arraylinePath.Num() - 1];
        return m_arraylinePath.Num() - 1;
    }
    // no chart in the profiler
    cursorPos.X = -1.0f;
    cursorPos.Y = -1.0f;
    return -1;
}

void SProfilerWidget::CalcMemStdText(float &maxMemorySize)
{
    m_stdMemStr.Empty();
    
    if(maxMemorySize < 1024)
    {
        m_memStdScale = 1;
        m_stdMemStr.Add("512 KB");
        m_stdMemStr.Add("1  MB");
    }
    else if (maxMemorySize < (1024 * 2))
    {
        m_memStdScale = 2;
        m_stdMemStr.Add("1 MB");
        m_stdMemStr.Add("2 MB");
    }
    else if (maxMemorySize < (1024 * 10))
    {
        m_memStdScale = 10;
        m_stdMemStr.Add("5 MB");
        m_stdMemStr.Add("10 MB");
    }
    else if (maxMemorySize < (1024 * 100))
    {
        m_memStdScale = 100;
        m_stdMemStr.Add("50 MB");
        m_stdMemStr.Add("100 MB");
    }
    else if (maxMemorySize < (1024 * 1024))
    {
        m_memStdScale = 1024;
        m_stdMemStr.Add("512 MB");
        m_stdMemStr.Add("1  GB");
    }
}

void SProfilerWidget::DrawStdLine(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, float positionY, FString stdStr) const
{
	TArray<FVector2D> valLineArray;
	valLineArray.Add(FVector2D(30, positionY));
	valLineArray.Add(FVector2D(m_widgetWidth, positionY));
	FSlateDrawElement::MakeLines(
					 OutDrawElements,
					 LayerId,
					 AllottedGeometry.ToPaintGeometry(),
					 valLineArray,
					 ESlateDrawEffect::None,
					 FLinearColor::White,
					 true,
					 1.0f
					);

//    FSlateColorBrush stBrushWhite_1 = FSlateColorBrush(FColorList::White);
//    FSlateDrawElement::MakeBox(
//                    OutDrawElements,
//                    LayerId,
//                    AllottedGeometry.ToPaintGeometry(FVector2D(0, positionY - 10), FVector2D(80, 15)),
//                    &stBrushWhite_1,
//                    ESlateDrawEffect::None,
//                    FLinearColor::Black
//                    );

	FSlateFontInfo FontInfo = FCoreStyle::Get().GetFontStyle("NormalFont");
	FontInfo.Size = 10.0f;

	FSlateDrawElement::MakeText(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(FVector2D(0, positionY - 10), AllottedGeometry.Size),
					stdStr,
					FontInfo,
					ESlateDrawEffect::None,
					FLinearColor::White
					);
}

void SProfilerWidget::CalcStdLine(float &maxCostTime)
{
	if (maxCostTime < 6000)
	{
		m_maxPointHeight = 7 * 1000.f;
		float stdLineValue = 1 * 1000.f;
		FString stdLineName = "1ms(1000FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);

		stdLineValue = 4 * 1000.f;
		stdLineName = "4ms(250FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);
	}
	else if (maxCostTime < 14000)
	{
		m_maxPointHeight = 15 * 1000.f;
		float stdLineValue = 5 * 1000.f;
		FString stdLineName = "5ms(200FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);

		stdLineValue = 10 * 1000.f;
		stdLineName = "10ms(100FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);
	}
	else if (maxCostTime < 30000)
	{
		m_maxPointHeight = 40 * 1000.f;
		float stdLineValue = 16 * 1000.f;
		FString stdLineName = "16ms(60FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);

		stdLineValue = 33 * 1000.f;
		stdLineName = "33ms(30FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);
	}
	else
	{
		m_maxPointHeight = 70 * 1000.f;
		float stdLineValue = 16 * 1000.f;
		FString stdLineName = "16ms(60FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);

		stdLineValue = 33 * 1000.f;
		stdLineName = "33ms(30FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);

		stdLineValue = 66 * 1000.f;
		stdLineName = "66ms(15FPS)";
		AddStdLine(m_maxPointHeight, stdLineValue, stdLineName);
	}
}

void SProfilerWidget::AddStdLine(float &maxPointValue, float &stdLineValue, FString &stdLineName)
{
	float positionY = m_cStdHighVal - m_cStdHighVal * (stdLineValue / maxPointValue);
	m_stdPositionY.Add(positionY);
	m_stdStr.Add(stdLineName);
}

int32 SProfilerWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (m_clickedPoint.X != -1.0f)
	{
		TArray<FVector2D> clickedPointArray;
		clickedPointArray.Add(FVector2D(m_clickedPoint.X, 0));
		clickedPointArray.Add(FVector2D(m_clickedPoint.X, cMaxViewHeight));
		FSlateDrawElement::MakeLines(
						 OutDrawElements,
						 LayerId,
						 AllottedGeometry.ToPaintGeometry(),
						 clickedPointArray,
						 ESlateDrawEffect::None,
						 FLinearColor::White,
						 true,
						 2.0f
						);
	}

	// draw std value line
	if (m_stdLineVisibility.Get() == EVisibility::Visible)
	{
		for (int32 i = 0; i < m_stdStr.Num(); i++)
		{
			DrawStdLine(AllottedGeometry, OutDrawElements, LayerId, m_stdPositionY[i], m_stdStr[i]);
		}
	}
    else
    {
        FSlateFontInfo FontInfo = FCoreStyle::Get().GetFontStyle("NormalFont");
        FontInfo.Size = 9.0f;
        
        FSlateDrawElement::MakeText(
                                    OutDrawElements,
                                    LayerId,
                                    AllottedGeometry.ToPaintGeometry(FVector2D(0, 95.0f), AllottedGeometry.Size),
                                    m_stdMemStr[0] + TEXT(" —"),
                                    FontInfo,
                                    ESlateDrawEffect::None,
                                    FLinearColor::White
                                    );
        
        FSlateDrawElement::MakeText(
                                    OutDrawElements,
                                    LayerId,
                                    AllottedGeometry.ToPaintGeometry(FVector2D(0, 0), AllottedGeometry.Size),
                                    m_stdMemStr[1],
                                    FontInfo,
                                    ESlateDrawEffect::None,
                                    FLinearColor::White
                                    );
        
        float chartMaxPosition = (m_arraylinePath.Num() * 5 + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth);
        if(m_mouseDownPoint.X != m_clickedPoint.X
           &&m_clickedPoint.X != -1.0f && m_mouseDownPoint.X != -1.0f
           && m_clickedPoint.X <= chartMaxPosition && m_mouseDownPoint.X <= chartMaxPosition)
        {
            // draw the selected area between the position from mouse up and down
            FLinearColor boxColor;
            FVector2D boxBeginPoint;
            TArray<FVector2D> clickedPointArray;
            
            FSlateColorBrush stBrushWhite_1 = FSlateColorBrush(FColorList::White);
            float length = FGenericPlatformMath::Abs(m_clickedPoint.X - m_mouseDownPoint.X);
            
            boxColor.R = 0.0f;
            boxColor.G = 1.0f;
            boxColor.B = 1.0f;
            boxColor.A = 0.2f;
            
            clickedPointArray.Add(FVector2D(m_mouseDownPoint.X, 0));
            clickedPointArray.Add(FVector2D(m_mouseDownPoint.X, cMaxViewHeight));
            
            boxBeginPoint = FVector2D(FGenericPlatformMath::Abs(FGenericPlatformMath::Min(m_mouseDownPoint.X, m_clickedPoint.X)), 0.0f);
            
            FSlateDrawElement::MakeBox(
                                       OutDrawElements,
                                       LayerId,
                                       AllottedGeometry.ToPaintGeometry(boxBeginPoint, FVector2D(length, cMaxViewHeight)),
                                       &stBrushWhite_1,
                                       ESlateDrawEffect::None,
                                       boxColor
                                       );
            
            FSlateDrawElement::MakeLines(
                                         OutDrawElements,
                                         LayerId,
                                         AllottedGeometry.ToPaintGeometry(),
                                         clickedPointArray,
                                         ESlateDrawEffect::None,
                                         FLinearColor::White,
                                         true,
                                         2.0f
                                         );
        }
	}

	if (m_arrayVal.Num() == 0)
	{
		return LayerId;
	}

	for (int32 i=0; i< m_cSliceCount-1; i++)
	{
		if ((m_arraylinePath[i].X < 0 && m_arraylinePath[i].Y < 0)
			|| (m_arraylinePath[i+1].X < 0 && m_arraylinePath[i+1].Y < 0))
		{
			continue;
		}

		TArray<FVector2D> circlePath;
		FVector2D leftPoint(m_arraylinePath[i].X, m_arraylinePath[i].Y);
		FVector2D rightPoint(m_arraylinePath[i+1].X, m_arraylinePath[i+1].Y);
		circlePath.Add(leftPoint);
		circlePath.Add(rightPoint);
		FSlateDrawElement::MakeLines(
						 OutDrawElements,
						 LayerId,
						 AllottedGeometry.ToPaintGeometry(),
						 circlePath,
						 ESlateDrawEffect::None,
						 FLinearColor::Yellow,
						 true,
						 1.0f
						);
	}

	return LayerId;
}

void SProfilerWidget::SetStdLineVisibility(TAttribute<EVisibility> InVisibility)
{
	m_stdLineVisibility = InVisibility;
}


void SProfilerTabWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SButton)
		.ContentPadding(-3)
		.OnClicked(InArgs._OnClicked)
		[
			SNew(SBorder)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(5.0f, 10.0f)
				[	
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Top)
					.AutoWidth()
					[
						SNew(SImage)
						.Image(InArgs._TabIcon)
				]

					+SHorizontalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Left)
					.Padding(15.0f, 15.0f)
					[
						SNew(STextBlock)
						.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 13))
						.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
						.Text(InArgs._TabName)
					]
				]
			]	
		]
	];
}
