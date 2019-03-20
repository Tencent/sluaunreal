// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

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
	int sampleIdx = (arrayOffset == sampleNum - 1) ? 0 : arrayOffset + 1;
	float totalSampleValue = 0.0f;
	for (int idx = 0; idx<sampleNum; idx++)
	{
		TArray<SluaProfiler> &shownProfilerBar = profilersArraySamples[sampleIdx];
		float totalValue = 0.0f;
		for (auto &iter : shownProfilerBar)
		{
			for (auto &funcNode : iter)
			{
				totalValue += funcNode->costTime;
				break;
			}
		}
		chartValArray[idx] = totalValue;
		totalSampleValue += totalValue;
		if (maxProfileSamplesCostTime < totalValue)
		{
			maxProfileSamplesCostTime = totalValue;
		}
		sampleIdx = (sampleIdx == sampleNum - 1) ? 0 : sampleIdx + 1;
	}

	avgProfileSamplesCostTime = totalSampleValue / sampleNum;

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

void SProfilerInspector::ClearProfilerCharFillImage()
{
	for (int barIdx = 0; barIdx<sampleNum; barIdx++)
	{
		profilerBarArray[barIdx]->SetFillImage(nullptr);
	}
}

void SProfilerInspector::CheckBoxChanged(ECheckBoxState newState)
{
	if (newState == ECheckBoxState::Checked)
	{
		stopChartRolling = false;
		ClearProfilerCharFillImage();
	}
	else
	{
		stopChartRolling = true;
	}
}

void SProfilerInspector::InitProfilerBar(int barIdx, TSharedPtr<SHorizontalBox>& horBox)
{
	static FSlateBrush bgColor;
	bgColor.TintColor = FLinearColor(FColor(34, 34, 34));

	SAssignNew(profilerBarArray[barIdx], SProgressBar)
		.ToolTipText(TAttribute<FText>::Create([=]() {
		return FText::AsNumber(chartValArray[barIdx] / perMilliSec);
	}))
		.BackgroundImage(&bgColor)
		.BarFillType(EProgressBarFillType::BottomToTop).BorderPadding(FVector2D(0, 0))
		.Percent(TAttribute<TOptional<float>>::Create([=]() {
		if (maxProfileSamplesCostTime == 0.0f)
		{
			return 0.0f;
		}
		else
		{
			return chartValArray[barIdx] / maxProfileSamplesCostTime;
		}
	}));

	profilerBarArray[barIdx]->SetOnMouseButtonDown(FPointerEventHandler::CreateLambda([=](const FGeometry&, const FPointerEvent&) -> FReply {
		// stop scorlling and show the profiler info which we click
		stopChartRolling = true;
		profilerCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		AddProfilerBarOnMouseMoveEvent();

		int sampleIdx = lastArrayOffset + barIdx + 1;
		if (sampleIdx >= sampleNum)
		{
			sampleIdx = sampleIdx - sampleNum;
		}

		ShowProfilerTree(profilersArraySamples[sampleIdx]);

		ClearProfilerCharFillImage();
		static FSlateBrush fillColor;
		fillColor.TintColor = FLinearColor::Red;
		profilerBarArray[barIdx]->SetFillImage(&fillColor);

		return FReply::Handled();
	}));

	profilerBarArray[barIdx]->SetOnMouseButtonUp(FPointerEventHandler::CreateLambda([=](const FGeometry&, const FPointerEvent&) -> FReply {
		RemoveProfilerBarOnMouseMoveEvent();
		return FReply::Handled();
	}));

	horBox->AddSlot().HAlign(HAlign_Left).MaxWidth(5.0f)
		[
			profilerBarArray[barIdx].ToSharedRef()
		];
}

void SProfilerInspector::OnClearBtnClicked()
{
	for (int barIdx = 0; barIdx<sampleNum; barIdx++)
	{
		chartValArray[barIdx] = 0.0f;
	}

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

	TSharedPtr<SHorizontalBox> horBox = SNew(SHorizontalBox);
	// init bar chart with many progress bar
	for (int idx = 0; idx < sampleNum; idx++)
	{
		InitProfilerBar(idx, horBox);
	}
	horBox->AddSlot().HAlign(HAlign_Left).MaxWidth(5.0f).Padding(0, 200, 10, 0);

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
				horBox.ToSharedRef()
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

void SProfilerInspector::AddProfilerBarOnMouseMoveEvent()
{
	for (int progBarIdx = 0; progBarIdx < sampleNum; progBarIdx++)
	{
		profilerBarArray[progBarIdx]->SetOnMouseEnter(FNoReplyPointerEventHandler::CreateLambda([=](const FGeometry&, const FPointerEvent&){
			// stop scorlling and show the profiler info which we click
			stopChartRolling = true;
			int sampleIdx = lastArrayOffset + progBarIdx + 1;
			if (sampleIdx >= sampleNum)
			{
				sampleIdx = sampleIdx - sampleNum;
			}

			ShowProfilerTree(profilersArraySamples[sampleIdx]);

			ClearProfilerCharFillImage();
			static FSlateBrush fillColor;
			fillColor.TintColor = FLinearColor::Red;
			profilerBarArray[progBarIdx]->SetFillImage(&fillColor);
		}));

		profilerBarArray[progBarIdx]->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
			profilerBarArray[progBarIdx]->SetFillImage(nullptr);
		}));
	}
}

void SProfilerInspector::RemoveProfilerBarOnMouseMoveEvent()
{
	for (int progBarIdx = 0; progBarIdx < sampleNum; progBarIdx++)
	{
		profilerBarArray[progBarIdx]->SetOnMouseEnter(FNoReplyPointerEventHandler::CreateLambda([progBarIdx](const FGeometry&, const FPointerEvent&) {
		}));
		profilerBarArray[progBarIdx]->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
		}));
	}
}

void SProfilerInspector::SortProfiler(SluaProfiler &rootProfiler)
{
	SluaProfiler duplictedNodeArray;
	for (int idx = 0; idx < rootProfiler.Num(); idx++)//(auto &funcNode : rootProfiler)
	{
		TSharedPtr<FunctionProfileInfo> &funcNode = rootProfiler[idx];
		if (funcNode->isDuplicated == true)
		{
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

	for (int idx = 0; idx < shownRootProfiler.Num(); idx++)
	{
		if (shownRootProfiler[idx]->isDuplicated == true)
		{
			shownRootProfiler.RemoveAt(idx);
			idx--;
		}
	}

	for (int idx = 0; idx < duplictedNodeArray.Num(); idx++)
	{
		shownRootProfiler.Add(duplictedNodeArray[idx]);
	}
}

void SProfilerInspector::ShowProfilerTree(TArray<SluaProfiler> &selectedProfiler)
{
	AssignProfiler(selectedProfiler, tmpRootProfiler, shownProfiler);
	SortProfiler(tmpRootProfiler);
	AssignProfiler(tmpRootProfiler, shownRootProfiler);

	auto curDockTab = FGlobalTabmanager::Get()->FindExistingLiveTab(slua_profileTabNameInspector);
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
								return FText::FromString(shownProfiler[Item->globalIdx]->brevName);								
							}))
							.FixedWidth(rowWidth).DefaultTooltip(TAttribute<FText>::Create([=]() {
								return FText::FromString(shownProfiler[Item->globalIdx]->functionName);
							}))
			+ SHeaderRow::Column("Time ms").DefaultLabel(TAttribute<FText>::Create([=]() {
								return FText::AsNumber(shownProfiler[Item->globalIdx]->mergedCostTime / perMilliSec);
							}))
							.FixedWidth(fixRowWidth)
			+ SHeaderRow::Column("Calls").DefaultLabel(TAttribute<FText>::Create([=]() {
								return FText::AsNumber(shownProfiler[Item->globalIdx]->mergedNum);
							}))
							.FixedWidth(fixRowWidth)
		];
}

void SProfilerInspector::OnGetChildrenForTree(TSharedPtr<FunctionProfileInfo> Parent, TArray<TSharedPtr<FunctionProfileInfo>>& OutChildren)
{
	TArray<TSharedPtr<FunctionProfileInfo>> unSortedChildrenArray;

	if (Parent.IsValid() && Parent->functionName.IsEmpty() == false
		&& shownProfiler[Parent->globalIdx]->beMerged == false)
	{
		if (Parent->layerIdx == 0)
		{
			Parent->mergeIdxArray.Empty();
			MergeSiblingNode(Parent->globalIdx, shownProfiler.Num(), Parent->mergeIdxArray, 0);
			CopyFunctionNode(shownProfiler[Parent->globalIdx], Parent);
			Parent->mergeIdxArray = shownProfiler[Parent->globalIdx]->mergeIdxArray;
		}

		int globalIdx = Parent->globalIdx + 1;
		int layerIdx = Parent->layerIdx;

		for (; globalIdx < shownProfiler.Num(); globalIdx++)
		{
			if (layerIdx + 1 == shownProfiler[globalIdx]->layerIdx)
			{
				if (shownProfiler[globalIdx]->beMerged == true)
				{
					continue;
				}
				// find sibling first
				MergeSiblingNode(globalIdx, shownProfiler.Num(), Parent->mergeIdxArray, 0);

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
				if (siblingNextNode->beMerged == false && siblingNextNode->layerIdx == (Parent->layerIdx + 1))
				{
					unSortedChildrenArray.Add(siblingNextNode);
				}
				MergeSiblingNode(pointIdx, Parent->mergeIdxArray.Num(), Parent->mergeIdxArray, mergeIdx+1);
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

void SProfilerInspector::MergeSiblingNode(int begIdx, int endIdx, TArray<int> parentMergeArray, int mergeArrayIdx)
{
	if (begIdx == endIdx || shownProfiler[begIdx]->beMerged == true)
	{
		return;
	}

	TSharedPtr<FunctionProfileInfo> &node = shownProfiler[begIdx];
	node->mergedNum = 1;
	node->mergedCostTime = node->costTime;
	node->mergeIdxArray.Empty();

	int pointIdx = begIdx + 1;
	SearchSiblingNode(shownProfiler, pointIdx, endIdx, node);

	// merge with other parent nodes' child which function name is the same with self parent
	if (mergeArrayIdx >= parentMergeArray.Num())
	{
		return;
	}
	for (size_t idx = mergeArrayIdx; idx<parentMergeArray.Num(); idx++)
	{
		pointIdx = parentMergeArray[idx] + 1;
		SearchSiblingNode(shownProfiler, pointIdx, endIdx, node);
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
			node->mergeIdxArray.Add(curIdx);
		}
		curIdx++;
	}
}




