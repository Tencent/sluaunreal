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
	maxProfileSamplesCostTime = 0.0f;
	avgProfileSamplesCostTime = 0.0f;
	hasCleared = false;
	needProfilerCleared = false;
	chartValArray.SetNumUninitialized(sampleNum);
}

SProfilerInspector::~SProfilerInspector()
{
	shownProfiler.Empty();
	shownRootProfiler.Empty();
	tmpRootProfiler.Empty();
	tmpProfiler.Empty();
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
	maxProfileSamplesCostTime = 0.0f;
	avgProfileSamplesCostTime = 0.0f;
	lastArrayOffset = arrayOffset;
	int sampleIdx = arrayOffset;
	float totalSampleValue = 0.0f;
	for (int idx = 0; idx<sampleNum; idx++)
	{
		TArray<SluaProfiler> &shownProfilerBar = profilersArraySamples[sampleIdx];
		float totalValue = 0.0f;
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
	}

	avgProfileSamplesCostTime = totalSampleValue / sampleNum;

	profilerWidget->SetArrayValue(chartValArray, maxProfileSamplesCostTime);

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
	for (; nodeIdx < profilers.Num(); nodeIdx++)
	{
		profilers[nodeIdx]->functionName = "";
		profilers[nodeIdx]->brevName = "";
	}

	for (; rootNodeIdx < rootProfilers.Num(); rootNodeIdx++)
	{
		rootProfilers[rootNodeIdx]->functionName = "";
		rootProfilers[rootNodeIdx]->brevName = "";
	}
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

	for (; nodeIdx < dstProfilers.Num(); nodeIdx++)
	{
		dstProfilers[nodeIdx]->functionName = "";
	}
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
		profilerWidget->ClearClickedPoint();
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
	profilerWidget->SetArrayValue(emptyArray, 0);
	profilerWidget->SetToolTipVal(-1);
	profilerWidget->ClearClickedPoint();


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
	FText WidgetText = FText::FromName("============================ CPU profiler ===========================");

	SAssignNew(profilerCheckBox, SCheckBox)
		.OnCheckStateChanged_Raw(this, &SProfilerInspector::CheckBoxChanged)
		.IsChecked(ECheckBoxState::Checked);

	SAssignNew(profilerWidget, SProfilerWidget);

	static bool isMouseButtonDown = false;
	profilerWidget->SetOnMouseButtonDown(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// stop scorlling and show the profiler info which we click
		isMouseButtonDown = true;
		stopChartRolling = true;
		profilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);

		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
		int sampleIdx = profilerWidget->CalcClickSampleIdx(cursorPos);
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

	profilerWidget->SetOnMouseButtonUp(FPointerEventHandler::CreateLambda([=](const FGeometry&, const FPointerEvent&) -> FReply {
		isMouseButtonDown = false;
		return FReply::Handled();
	}));

	profilerWidget->SetOnMouseMove(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
		// calc sampleIdx
		FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
		int sampleIdx = profilerWidget->CalcHoverSampleIdx(cursorPos);
		static float lastToolTipVal = 0.0f;
		if (sampleIdx >= 0 && lastToolTipVal != chartValArray[sampleIdx])
		{
			profilerWidget->SetToolTipVal(chartValArray[sampleIdx]/ perMilliSec);
			lastToolTipVal = chartValArray[sampleIdx];
		}
		else if (sampleIdx < 0)
		{
			profilerWidget->SetToolTipVal(-1.0f);
		}

		////////////////////////////////
		if (isMouseButtonDown == true)
		{
			// calc sampleIdx
			sampleIdx = profilerWidget->CalcClickSampleIdx(cursorPos);
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

	profilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
		isMouseButtonDown = false;
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

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(25.0f)
				[
					profilerCheckBox.ToSharedRef()
				]
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
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
			+ SScrollBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					profilerWidget.ToSharedRef()
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

////////////////////////////// SProfilerWidget //////////////////////////////

void SProfilerWidget::SetArrayValue(TArray<float>& chartValArray, float maxCostTime)
{
	m_arrayVal = chartValArray;
	if (m_arrayVal.Num() == 0)
	{
		// clear line points
		for (int32 i = 0; i < m_cSliceCount; i++)
		{
			FVector2D NewPoint(-1, -1);
			m_arraylinePath[i] = NewPoint;
		}
	}
	m_maxCostTime = maxCostTime;
}

void SProfilerWidget::Construct(const FArguments& InArgs)
{
	m_arraylinePath.SetNumUninitialized(m_cSliceCount);
	m_maxCostTime = 0.0f;
	m_pointInterval = 0.0f;
	m_clickedPoint.X = -1.0f;
	m_toolTipVal = -1.0f;
	m_widgetWidth = 0.0f;

	float maxPointValue = 40 * 1000.f; // set max value as 40ms
	float stdLineValue = 16 * 1000.f;
	FString stdLineName = "16ms(60FPS)";
	AddStdLine(maxPointValue, stdLineValue, stdLineName);

	stdLineValue = 33 * 1000.f;
	stdLineName = "33ms(30FPS)";
	AddStdLine(maxPointValue, stdLineValue, stdLineName);

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
	return FVector2D(m_widgetWidth, 220);
}

void SProfilerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	m_widgetWidth = AllottedGeometry.Size.X;

	if (m_arrayVal.Num() == 0)
	{
		return;
	}

	static float maxVal = 10 * 1000;
	static float highVal = 200;

	// calc standard line level accroding to max cost time
	m_stdPositionY.Empty();
	m_stdStr.Empty();
	if (m_maxCostTime > 0)
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
		else
		{
			float yValue = 0;
			
			if (m_maxCostTime != 0.0f)
			{
				yValue = highVal * (m_arrayVal[i] / maxVal);
			}
			if (yValue > highVal)
			{
				FVector2D NewPoint((5 * i + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth), 0);
				m_arraylinePath[i] = NewPoint;
			}
			else
			{
				FVector2D NewPoint((5 * i + m_cStdLeftPosition) * (m_widgetWidth / m_cStdWidth), highVal - yValue);
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

void SProfilerWidget::ClearClickedPoint()
{
	m_clickedPoint.X = -1.0f;
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
		float maxPointValue = 7 * 1000.f;
		float stdLineValue = 1 * 1000.f;
		FString stdLineName = "1ms(1000FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);

		stdLineValue = 4 * 1000.f;
		stdLineName = "4ms(250FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);
	}
	else if (maxCostTime < 14000)
	{
		float maxPointValue = 15 * 1000.f;
		float stdLineValue = 5 * 1000.f;
		FString stdLineName = "5ms(200FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);

		stdLineValue = 10 * 1000.f;
		stdLineName = "10ms(100FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);
	}
	else if (maxCostTime < 30000)
	{
		float maxPointValue = 40 * 1000.f;
		float stdLineValue = 16 * 1000.f;
		FString stdLineName = "16ms(60FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);

		stdLineValue = 33 * 1000.f;
		stdLineName = "33ms(30FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);
	}
	else
	{
		float maxPointValue = 70 * 1000.f;
		float stdLineValue = 16 * 1000.f;
		FString stdLineName = "16ms(60FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);

		stdLineValue = 33 * 1000.f;
		stdLineName = "33ms(30FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);

		stdLineValue = 66 * 1000.f;
		stdLineName = "66ms(15FPS)";
		AddStdLine(maxPointValue, stdLineValue, stdLineName);
	}
}

void SProfilerWidget::AddStdLine(float &maxPointValue, float &stdLineValue, FString &stdLineName)
{
	float positionY = m_cStdHighVal - m_cStdHighVal / maxPointValue * stdLineValue;
	m_stdPositionY.Add(positionY);
	m_stdStr.Add(stdLineName);
}

int32 SProfilerWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (m_clickedPoint.X != -1.0f)
	{
		TArray<FVector2D> clickedPointArray;
		clickedPointArray.Add(FVector2D(m_clickedPoint.X, 0));
		clickedPointArray.Add(FVector2D(m_clickedPoint.X, 200));
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
	for (int32 i = 0; i < m_stdStr.Num(); i++)
	{
		DrawStdLine(AllottedGeometry, OutDrawElements, LayerId, m_stdPositionY[i], m_stdStr[i]);
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




