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
#include "Widgets/Images/SImage.h"
#include "Public/Brushes/SlateDynamicImageBrush.h"
#include "Public/Brushes/SlateImageBrush.h"
#include "UObject/UObjectGlobals.h"
#include "Math/Vector2D.h"
#include "EditorStyleSet.h"
#include "Widgets/Input/SCheckBox.h"
#include "Templates/SharedPointer.h"
#include "Fonts/SlateFontInfo.h"
#include "Math/Color.h"
#include "Internationalization/Regex.h"
#include "slua_profile_inspector.h"
#include "slua_profile.h"

static const FName slua_profileTabNameInspector("slua_profile");
///////////////////////////////////////////////////////////////////////////
SProfilerInspector::SProfilerInspector()
{
	stopChartRolling = false;
	arrayOffset = 0;
	lastArrayOffset = 0;
	refreshIdx = 0;
	maxLuaMemory = 0.0f;
	avgLuaMemory = 0.0f;
	luaTotalMemSize = 0.0f;
	maxProfileSamplesCostTime = 0.0f;
	avgProfileSamplesCostTime = 0.0f;
	hasCleared = false;
	needProfilerCleared = false;
	chartValArray.SetNumUninitialized(sampleNum);
	memChartValArray.SetNumUninitialized(sampleNum);
//	memUpdateInfoArray.SetNumUninitialized(sampleNum);
	luaMemNodeList.SetNumUninitialized(sampleNum);
	initLuaMemNodeList();
	luaMemNodeChartList.SetNumUninitialized(sampleNum);
	luaMemoryProfile.start();
}

SProfilerInspector::~SProfilerInspector()
{
	shownProfiler.Empty();
	shownRootProfiler.Empty();
	tmpRootProfiler.Empty();
	tmpProfiler.Empty();
	luaMemoryProfile.stop();
	luaMemInfoMap.Empty();
	luaMemInfoList.Empty();
	luaMemNodeList.Empty();
	luaMemNodeChartList.Empty();
}

void SProfilerInspector::StartChartRolling()
{
	stopChartRolling = false;
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

void SProfilerInspector::initLuaMemNodeList() {
	for(int32 i = 0; i < cMaxSampleNum; i++) {
		ProflierMemNode *memNode = new ProflierMemNode();
		memNode->totalSize = -1.0f;
		luaMemNodeList.Add(memNode);
	}
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

void SProfilerInspector::Refresh(TArray<SluaProfiler>& profilersArray)
{
	if (stopChartRolling == true || profilersArray.Num() == 0)
	{
		return;
	}

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
			hasCleared = false;
		}
		treeview->RequestTreeRefresh();

		// replace tmp samples
		for (int sampleIdx = 0; sampleIdx<sampleNum; sampleIdx++)
		{
			profilersArraySamples[sampleIdx] = tmpProfilersArraySamples[sampleIdx];
		}

		RefreshBarValue();
	}
	return;
}

void SProfilerInspector::RefreshBarValue()
{
	int32 memArraySize;
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
		float tempMemory = 0.0f;
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

		memArraySize = luaMemNodeList.Num();

		tempMemory = luaMemNodeList[memArraySize - (sampleNum - idx)]->totalSize;

		if (tempMemory >= 0)totalMemory += tempMemory;
		if (tempMemory > maxLuaMemory) maxLuaMemory = tempMemory;
		memChartValArray[idx] = tempMemory;


		luaMemNodeChartList.RemoveAt(0);
		luaMemNodeChartList.Add(luaMemNodeList[memArraySize - (sampleNum - idx)]);

		if(luaMemNodeList.Num() >= 800) luaMemNodeList.RemoveAt(0);
	}

	avgProfileSamplesCostTime = totalSampleValue / sampleNum;
	cpuProfilerWidget->SetArrayValue(chartValArray, maxProfileSamplesCostTime);

	// Add memory total size into the array;
	if(totalMemory > 0) avgLuaMemory = totalMemory / sampleNum;
	memProfilerWidget->SetArrayValue(memChartValArray, maxProfileSamplesCostTime);

	combineSameFileInfo(luaMemNodeChartList[luaMemNodeChartList.Num() - 1]->infoList);
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
		cpuProfilerWidget->ClearClickedPoint();
	}
	else
	{
		stopChartRolling = true;
	}
}

void SProfilerInspector::MemoryCheckBoxChanged(ECheckBoxState newState)
{
	if (newState == ECheckBoxState::Checked)
	{
		stopChartRolling = false;
		memProfilerWidget->ClearClickedPoint();
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
	cpuProfilerWidget->SetArrayValue(emptyArray, 0);
	cpuProfilerWidget->SetToolTipVal(-1);
	cpuProfilerWidget->ClearClickedPoint();


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

	hasCleared = true;
	needProfilerCleared = true;
}

TSharedRef<class SDockTab> SProfilerInspector::GetSDockTab()
{
	FText WidgetText = FText::FromName("============================ slua profiler ===========================");

	SAssignNew(profilerCheckBox, SCheckBox)
		.OnCheckStateChanged_Raw(this, &SProfilerInspector::CheckBoxChanged)
		.IsChecked(ECheckBoxState::Checked);

	SAssignNew(memProfilerCheckBox, SCheckBox)
	.OnCheckStateChanged_Raw(this, &SProfilerInspector::MemoryCheckBoxChanged)
	.IsChecked(ECheckBoxState::Checked);

	SAssignNew(cpuProfilerWidget, SProfilerWidget);
	SAssignNew(memProfilerWidget, SProfilerWidget);

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

	memProfilerWidget->SetOnMouseButtonDown(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// stop scorlling and show the profiler info which we click
		isMemMouseButtonDown = true;
		stopChartRolling = true;
		memProfilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		profilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
		int sampleIdx = memProfilerWidget->CalcClickSampleIdx(cursorPos);

		if (sampleIdx >= 0 && sampleIdx < cMaxSampleNum)
		{
			combineSameFileInfo(luaMemNodeChartList[sampleIdx]->infoList);
			luaTotalMemSize = luaMemNodeChartList[sampleIdx]->totalSize;
			listview->RequestListRefresh();
		}

		return FReply::Handled();
	}));

	memProfilerWidget->SetOnMouseButtonUp(FPointerEventHandler::CreateLambda([=](const FGeometry&, const FPointerEvent&) -> FReply {
		isMemMouseButtonDown = false;
		return FReply::Handled();
	}));

	memProfilerWidget->SetOnMouseMove(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
		int sampleIdx = memProfilerWidget->CalcHoverSampleIdx(cursorPos);
		static float lastToolTipVal = 0.0f;

		if (sampleIdx >= 0 && lastToolTipVal != luaMemNodeChartList[sampleIdx]->totalSize)
		{
			memProfilerWidget->SetToolTipVal(luaMemNodeChartList[sampleIdx]->totalSize);
			lastToolTipVal = luaMemNodeChartList[sampleIdx]->totalSize;
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
				combineSameFileInfo(luaMemNodeChartList[sampleIdx]->infoList);
				luaTotalMemSize = luaMemNodeChartList[sampleIdx]->totalSize;
				listview->RequestListRefresh();
			}
		}

		return FReply::Handled();
	}));

	cpuProfilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
		isMouseButtonDown = false;
	}));

	memProfilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
		isMemMouseButtonDown =false;
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

	for(int32 i = 0; i < 1; i++) {
		FileMemInfo *memInfo = new FileMemInfo();
		memInfo->hint = " ";
		memInfo->size = -1.0f;
		shownFileInfo.Add(MakeShareable(memInfo));
	}

	SAssignNew(listview, SListView<TSharedPtr<FileMemInfo>>)
	.ItemHeight(800)
	.ListItemsSource(&shownFileInfo)
	.OnGenerateRow_Raw(this, &SProfilerInspector::OnGenerateMemRowForList)
	.SelectionMode(ESelectionMode::None)
	.HeaderRow
	(
	 SNew(SHeaderRow)
	 + SHeaderRow::Column("Overview").DefaultLabel(FText::FromName("Overview")).FixedWidth(fixRowWidth)
	 + SHeaderRow::Column("Memory Size").DefaultLabel(FText::FromName("Memory Size")).FixedWidth(fixRowWidth)
	 );

	memProfilerWidget->SetStdLineVisibility(EVisibility::Collapsed);
	cpuProfilerWidget->SetStdLineVisibility(EVisibility::Visible);return SNew(SDockTab)
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
			SNew(SScrollBox)
			.ScrollBarAlwaysVisible(true)+ SScrollBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
					[
						SNew(STextBlock)
						.Text(FText::FromString("CPU	|	"))
					]

					+SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(25.0f)
				[
					profilerCheckBox.ToSharedRef()
				]
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f).Padding(0, 3.0f, 0, 0)
				[
					SNew(STextBlock).Text(FText::FromName("Animate"))]

				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
				[
					SNew(SButton).Text(FText::FromName("Clear"))
					.ContentPadding(FMargin(2.0, 2.0))
					.OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
						OnClearBtnClicked();
						return FReply::Handled();}))
					]
				]

			+ SScrollBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					cpuProfilerWidget.ToSharedRef()
				]
			]
			+ SScrollBox::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center)
				[
					SNew(STextBlock).Text_Lambda([=]() {
						FString titleStr = FString::Printf(TEXT("============================ CPU profiler Max(%.2f ms), Avg(%.2f ms) ============================"),
							maxProfileSamplesCostTime / perMilliSec, avgProfileSamplesCostTime / perMilliSec);
						return FText::FromString(titleStr); })
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					treeview.ToSharedRef()
				]
			]
		]+SWidgetSwitcher::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			[
				SAssignNew(tabSwitcher, SWidgetSwitcher)
				.WidgetIndex(0)
				+SWidgetSwitcher::Slot()
				[
					SNew(SScrollBox)
					+SScrollBox::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
						[
							SNew(STextBlock)
							.Text(FText::FromString("MEMORY	|   "))
						]

						+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(0, 3.0f, 15.0f, 0).AutoWidth()
						[
							SNew(STextBlock)
							.Text_Lambda([=]() {
							if(!stopChartRolling) {
								luaTotalMemSize = 0;
								ProflierMemNode *memNode = new ProflierMemNode();
								for(auto& memFileInfo : slua::LuaMemoryProfile::memDetail()) {
									FString fileName = splitFlieName(memFileInfo.Value.hint);
									if(fileName.Contains(TEXT("slua_profile.lua"), ESearchCase::CaseSensitive, ESearchDir::FromEnd)) {
										luaTotalMemSize -= memFileInfo.Value.size;
										continue;
									}
									 FileMemInfo *fileInfo = new FileMemInfo();
									 fileInfo->hint = splitFlieName(memFileInfo.Value.hint);
									 fileInfo->size = memFileInfo.Value.size;
									 memNode->infoList.Add((fileInfo));
								}
								luaTotalMemSize += luaMemoryProfile.total();
								luaTotalMemSize /= 2048.0f;
								memNode->totalSize = luaTotalMemSize;
								luaMemNodeList.Add(memNode);
							}

							FString totalMemory = TEXT("Total : ") + chooseMemoryUnit(luaTotalMemSize);
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

						+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth()
						[
							SNew(SButton)
							.Text(FText::FromName("Forced GC"))
							.ContentPadding(FMargin(2.0, 2.0))
							.OnClicked(FOnClicked::CreateLambda([=]() -> FReply {

								return FReply::Handled();
							}))
						]
					]

					+ SScrollBox::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill)
						[
							memProfilerWidget.ToSharedRef()
						]
					]

					+ SScrollBox::Slot()
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

					+ SScrollBox::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Center).Padding(0, 10.0f)
						[
							SNew(STextBlock).Text_Lambda([=]() {
							FString titleStr = TEXT("============================ Memory profiler Max("
												 + chooseMemoryUnit(maxLuaMemory)
												 +"), Avg("
												 + chooseMemoryUnit(avgLuaMemory)
												 +") ============================");
							return FText::FromString(titleStr);
							})
						]

						+ SVerticalBox::Slot().AutoHeight()
						[
							listview.ToSharedRef()
						]
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
	return
	SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
	.Padding(2.0f)
	[
	 SNew(SHeaderRow)
	 + SHeaderRow::Column("Overview").DefaultLabel(TAttribute<FText>::Create([=]() {
		if (Item->hint != nil)
		{
			return FText::FromString(Item->hint);
		}
		return FText::FromString("");
	}))
	 .FixedWidth(fixRowWidth)

	 + SHeaderRow::Column("Memory Size").DefaultLabel(TAttribute<FText>::Create([=]() {
		if (Item->size >= 0)
		{
			return FText::FromString(chooseMemoryUnit(Item->size / 2048.0));
		}
		return FText::FromString("");
	}))
	 .FixedWidth(fixRowWidth)
	 ];
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

void SProfilerInspector::combineSameFileInfo(MemFileInfoList& infoList) {
	shownFileInfo.Empty();

	for(auto& fileInfo : infoList) {
		int index = ContainsFile(fileInfo->hint);
		if(index >= 0){
			float lineMemSize= shownFileInfo[index]->size;
			lineMemSize = shownFileInfo[index]->size + fileInfo->size;
			shownFileInfo[index]->size = lineMemSize;
		} else {
			FileMemInfo *info = new FileMemInfo();
			info->hint = fileInfo->hint;
			info->size = fileInfo->size;
			shownFileInfo.Add(MakeShareable(info));
		}
	}
}

int SProfilerInspector::ContainsFile(FString& fileName) {
	int index = -1;
	for(auto& fileInfo : shownFileInfo) {
		index ++;
		if(fileName.Equals(fileInfo->hint, ESearchCase::CaseSensitive)) return index;
	}
	index = -1;
	return index;
}

FString SProfilerInspector::chooseMemoryUnit(float memorySize)
{
	if (memorySize < 1024) return FString::Printf(TEXT("%.2f KB"), memorySize);
	else if (memorySize >= 1024) return FString::Printf(TEXT("%.2f MB"), (memorySize / 1024.0f));
	return FString::Printf(TEXT("%.2f"), memorySize);
}

FString SProfilerInspector::splitFlieName(FString filePath) {
	TArray<FString> stringArray;

	filePath.ParseIntoArray(stringArray, TEXT("/"), false);
	return stringArray[stringArray.Num()-1];
}

////////////////////////////// SProfilerWidget //////////////////////////////

void SProfilerWidget::SetArrayValue(TArray<float>& chartValArray, float maxCostTime)
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
}

//void SProfilerWidget::SetArrayValue(MemNodeInfoList& nodeList, float maxCostTime)
//{
//	m_nodeList = nodeList;
//	if (m_nodeList.Num() == 0)
//	{
//		// clear line points
//		for (int32 i = 0; i < m_cSliceCount; i++)
//		{
//			ProflierMemNode *node = new ProflierMemNode();
//			node->totalSize = 0.0f;
//			m_nodeList.Add(MakeShareable(node));
//		}
//	}
//	m_maxCostTime = maxCostTime;
//}

void SProfilerWidget::Construct(const FArguments& InArgs)
{
	m_arraylinePath.SetNumUninitialized(m_cSliceCount);
	m_maxCostTime = 0.0f;
	m_pointInterval = 0.0f;
	m_clickedPoint.X = -1.0f;
	m_toolTipVal = -1.0f;
	m_widgetWidth = 0.0f;
	m_stdLineVisibility = InArgs._StdLineVisibility;

	if(m_stdLineVisibility.Get() == EVisibility::Visible)
	{
		float maxPointValue = 40 * 1000.f; // set max value as 40ms
		float stdLineValue = 16 * 1000.f;
		FString stdLineName = "16ms(60FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);

		stdLineValue = 33 * 1000.f;
		stdLineName = "33ms(30FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);
	}

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
				yValue = cMaxViewHeight * (m_arrayVal[i] / 1024);
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
}

int SProfilerWidget::CalcClickSampleIdx(const FVector2D cursorPos)
{
	for (int32 i = 0; i< m_cSliceCount; i++)
	{
		int interval = m_arraylinePath[i].X - cursorPos.X;
		if (interval > (-m_pointInterval / 2) && interval < (m_pointInterval / 2))
		{
			m_clickedPoint = m_arraylinePath[i];
			return i;
		}
	}

	return -1;
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

	FSlateColorBrush stBrushWhite_1 = FSlateColorBrush(FColorList::White);
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(FVector2D(0, positionY - 10), FVector2D(80, 15)),
		&stBrushWhite_1,
		ESlateDrawEffect::None,
		FLinearColor::Black
	);

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
			6.0f
		);
	}


	// draw std value line
	if (m_stdLineVisibility.Get() == EVisibility::Visible)
	{
		for (int32 i = 0; i < m_stdStr.Num(); i++)
		{
			DrawStdLine(AllottedGeometry, OutDrawElements, LayerId, m_stdPositionY[i], m_stdStr[i]);
		}
	} else {
		FSlateFontInfo FontInfo = FCoreStyle::Get().GetFontStyle("NormalFont");
		FontInfo.Size = 9.0f;

		FSlateDrawElement::MakeText(
									OutDrawElements,
									LayerId,
									AllottedGeometry.ToPaintGeometry(FVector2D(0, 95.0f), AllottedGeometry.Size),
									TEXT("512 KB  —"),
									FontInfo,
									ESlateDrawEffect::None,
									FLinearColor::White
									);

		FSlateDrawElement::MakeText(
									OutDrawElements,
									LayerId,
									AllottedGeometry.ToPaintGeometry(FVector2D(0, 0), AllottedGeometry.Size),
									TEXT(" 1  MB  —"),
									FontInfo,
									ESlateDrawEffect::None,
									FLinearColor::White
									);
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
						.Font(FSlateFontInfo("Veranda", 13))
						.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
						.Text(InArgs._TabName)
					]
				]
			]
		]
	 ];
}
