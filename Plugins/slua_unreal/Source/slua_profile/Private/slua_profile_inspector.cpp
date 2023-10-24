// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "Brushes/SlateColorBrush.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Images/SImage.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Templates/SharedPointer.h"
#include "Delegates/IDelegateInstance.h"
#include "Internationalization/Regex.h"
#include "Fonts/SlateFontInfo.h"
#include "Math/Vector2D.h"
#include "Math/Color.h"
#include "LuaProfiler.h"
#include "Sockets.h"
#include "Log.h"
#include "slua_profile.h"
#include "slua_profile_inspector.h"

#include <algorithm>

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif
#include "Serialization/ArrayWriter.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSlider.h"
#include "Stats/Stats2.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "SluaProfilerDataManager.h"
#include "Runtime/Launch/Resources/Version.h"

///////////////////////////////////////////////////////////////////////////
SProfilerInspector::SProfilerInspector()
{
    stopChartRolling = false;
    cpuViewBeginIndex = 0;
    maxLuaMemory = 0.0f;
    avgLuaMemory = 0.0f;
    luaTotalMemSize = 0.0f;
    lastLuaTotalMemSize = 0.0f;
    maxProfileSamplesCostTime = 0.0f;
    avgProfileSamplesCostTime = 0.0f;
    isMemMouseButtonUp = false;
    hasCleared = false;
    needProfilerCleared = false;
    mouseUpPoint = FVector2D(-1.0f, 0.0f);
    mouseDownPoint = FVector2D(-1.0f, 0.0f);
    initLuaMemChartList();
    chartValArray.SetNumUninitialized(sampleNum);
    memChartValArray.SetNumUninitialized(sampleNum);
    allLuaMemNodeList.SetNumUninitialized(sampleNum);
}

SProfilerInspector::~SProfilerInspector()
{
    profileRootArr.Empty();
    allProfileData.Empty();
    cpuViewBeginIndex = 0;
    memViewBeginIndex = 0;
    allLuaMemNodeList.Empty();
}

void SProfilerInspector::StartChartRolling()
{
    stopChartRolling = false;
    isMemMouseButtonUp = false;
}

FString SProfilerInspector::GenBrevFuncName(const FString &functionName)
{
    TArray<FString> strArray;
    FString brevName = functionName;
    brevName.ReplaceInline(TEXT("\\"), TEXT("/"));
    int32 arrayNum = brevName.ParseIntoArray(strArray, TEXT("/"));
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
        TSharedPtr<FProflierMemNode> memNode = MakeShareable(new FProflierMemNode);
        memNode->totalSize = -1.0f;
        allLuaMemNodeList.Add(memNode);
    }

    TSharedPtr<FProflierMemNode> memNode = MakeShareable(new FProflierMemNode);
    memNode->totalSize = 0.0f;
    allLuaMemNodeList.Add(memNode);
    memViewBeginIndex = 0;
}

void SProfilerInspector::RestartMemoryStatistis()
{
    allLuaMemNodeList.Empty();
    shownFileInfo.Empty();
    memViewBeginIndex = 0;
    shownParentFileName.Empty();
    luaTotalMemSize = 0.0f;
    lastLuaTotalMemSize = 0.0f;
    maxLuaMemory = 0.0f;
    avgLuaMemory = 0.0f;

    initLuaMemChartList();
}

void SProfilerInspector::Refresh(TSharedPtr<FunctionProfileNode> funcInfoRoot, TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame)
{
    QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_Refresh)
    
    if (funcInfoRoot->childNode->Num() == 0)
    {
        return;
    }
    CollectMemoryNode(memoryInfoMap, memoryFrame);
    TArray<TSharedPtr<FunctionProfileNode>> tempProfileRootArr;
    tempProfileRootArr.Reserve(funcInfoRoot->childNode->Num());
    for (auto& Item : *funcInfoRoot->childNode) {
        tempProfileRootArr.Add(Item.Value);
    }
    tempProfileRootArr.StableSort([](const TSharedPtr<FunctionProfileNode>& lhs, const TSharedPtr<FunctionProfileNode>& rhs)
        {
            return lhs->costTime > rhs->costTime;
        });
    allProfileData.Add(tempProfileRootArr);
    if(!bIsTouching)
    {
        cpuSlider->SetValue(std::min(1.0f,(cpuViewBeginIndex + cMaxSampleNum)* 1.0f / allProfileData.Num()));
        memSlider->SetValue(std::min(1.0f,(memViewBeginIndex + cMaxSampleNum)*1.0f / allLuaMemNodeList.Num()));
    }
    
    allLuaMemNodeList.Add(lastLuaMemNode);
    if (cpuViewBeginIndex + cMaxSampleNum + cRefreshDisCount > allProfileData.Num() && treeview.IsValid())
    {
        if(allProfileData.Num() > cMaxSampleNum + cpuViewBeginIndex && !stopChartRolling)
        {
            cpuViewBeginIndex++;
            profileRootArr = tempProfileRootArr;
            treeview->RequestTreeRefresh();
        }
        
        // merge tempRootProfiler funcNode
        if (hasCleared == true)
        {
            treeview->RebuildList();
            hasCleared = false;
        }
        
        RefreshBarValue();
    }
    if(memViewBeginIndex + cMaxSampleNum + cRefreshDisCount > allLuaMemNodeList.Num() && memTreeView.IsValid())
    {
        if (hasCleared == true)
        {
            memTreeView->RebuildList();
            hasCleared = false;
        }

        if(allLuaMemNodeList.Num() > cMaxSampleNum + memViewBeginIndex && !stopChartRolling)
        {
            memViewBeginIndex++;
            luaTotalMemSize = lastLuaMemNode->totalSize;
            memTreeView->RequestTreeRefresh();
        }

        RefreshBarValue();
    }
}

void SProfilerInspector::RefreshBarValue()
{
    QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_RefreshBarValue)
    int nodeSize = 0;
    float totalMemory = 0.0f;
    float totalSampleValue = 0.0f;

    maxLuaMemory = 0.0f;
    avgLuaMemory = 0.0f;
    maxProfileSamplesCostTime = 0.0f;
    avgProfileSamplesCostTime = 0.0f;

    {
        QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_RefreshBarValue_Loop)
        for (int idx = 0; idx < sampleNum; idx++)
        {
            TArray<TSharedPtr<FunctionProfileNode>> shownProfilerBar;
            if(cpuViewBeginIndex + idx < allProfileData.Num())
            {
                shownProfilerBar = allProfileData[cpuViewBeginIndex + idx];
            }
            
            float totalValue = 0.0f;
            float memorySize = 0.0f;
            
            // replace tmp samples and update memory node list
            for (int sampleIdx = 0; sampleIdx<sampleNum; sampleIdx++)
            {
                if(memViewBeginIndex + sampleIdx < allLuaMemNodeList.Num())
                {
                    memChartValArray[sampleIdx] = allLuaMemNodeList[memViewBeginIndex + sampleIdx]->totalSize;
                }
                else
                {
                    memChartValArray[sampleIdx] = 0;
                }
            }
            
            if (shownProfilerBar.Num() == 0)
            {
                chartValArray[idx] = -1.0f;
            }
            else
            {
                QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_RefreshBarValue_Loop_AddTime)
                for (auto &iter : shownProfilerBar)
                {
                    totalValue += iter->costTime;
                }
                chartValArray[idx] = totalValue;
            }
            totalSampleValue += totalValue;
            if (maxProfileSamplesCostTime < totalValue)
            {
                maxProfileSamplesCostTime = totalValue;
            }
            if(memViewBeginIndex + idx < allLuaMemNodeList.Num())
            {
                memorySize = allLuaMemNodeList[memViewBeginIndex + idx]->totalSize;
            }
            
            if (memorySize >= 0)
            {
                totalMemory += memorySize;
                nodeSize++;
            }
            if (memorySize > maxLuaMemory) maxLuaMemory = memorySize;

        }
    }

    {
        QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_RefreshBarValue_CopyChartList)
    }
    avgProfileSamplesCostTime = totalSampleValue / (allLuaMemNodeList.Num());
    cpuProfilerWidget->SetArrayValue(chartValArray, maxProfileSamplesCostTime, maxLuaMemory);

    // Add memory total size into the array;
    if(totalMemory >= 0 && nodeSize > 0) avgLuaMemory = totalMemory / nodeSize;
    memProfilerWidget->SetArrayValue(memChartValArray, maxProfileSamplesCostTime, maxLuaMemory);

    CombineSameFileInfo(*allLuaMemNodeList.Top());
}

void SProfilerInspector::CheckBoxChanged(ECheckBoxState newState)
{
    if (newState == ECheckBoxState::Checked)
    {
        stopChartRolling = false;
        isMemMouseButtonUp = false;
        memProfilerWidget->ClearClickedPoint();
        cpuProfilerWidget->ClearClickedPoint();
    }
    else
    {
        stopChartRolling = true;
    }
}

void SProfilerInspector::OnSaveFileBtnClicked()
{
    SluaProfilerDataManager::SaveDataWithData(cpuViewBeginIndex, memViewBeginIndex, allProfileData, allLuaMemNodeList);
}

void SProfilerInspector::OnCpuSliderValueChanged(float Value)
{
    int32 viewEndIndex = (int32)(Value*allProfileData.Num());
    cpuViewBeginIndex = std::max(0, viewEndIndex - cMaxSampleNum);

    if (Value >= 1.0f)
    {
        stopChartRolling = false;
        cpuProfilerWidget->SetMouseClickPoint(FVector2D(-1.0f, 0.0f));
    }
    
    if (hasCleared == true)
    {
        treeview->RebuildList();
        hasCleared = false;
    }
    
    treeview->RequestTreeRefresh();
    RefreshBarValue();
}

void SProfilerInspector::OnMemSliderValueChanged(float Value)
{
    int32 viewEndIndex = (int32)(Value*allLuaMemNodeList.Num());
    memViewBeginIndex = std::max(0, viewEndIndex - cMaxSampleNum);

    if (Value >= 1.0f)
    {
        stopChartRolling = false;
        memProfilerWidget->SetMouseClickPoint(FVector2D(-1.0f, 0.0f));
    }
    
    if (hasCleared == true)
    {
        memTreeView->RebuildList();
        hasCleared = false;
    }
    
    memTreeView->RequestTreeRefresh();
    RefreshBarValue();
}

void SProfilerInspector::OnLoadFileBtnClicked()
{
    FString loadPath;
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        FString Filter = TEXT("slua stat file|*.sluastat");
        TArray<FString> OutFiles;
        if (DesktopPlatform->OpenFileDialog(nullptr, TEXT("open slua stat file"), FPaths::ProjectSavedDir(), TEXT(""), Filter, EFileDialogFlags::None, OutFiles))
        {
            loadPath = OutFiles[0];
        }
    }
    if (loadPath == "")
    {
        NS_SLUA::Log::Log("DeserializeSave no select file");
        return;
    }

    FBufferArchive BufAr;
    TArray<uint8> CompressData;
    if (!FFileHelper::LoadFileToArray(CompressData, *loadPath))
    {
        return;
    }

    OnClearBtnClicked();
    NS_SLUA::Log::Log("DeserializeSave filePath:%s", *loadPath);
    SluaProfilerDataManager::LoadData(CompressData, cpuViewBeginIndex, memViewBeginIndex, allProfileData, allLuaMemNodeList);
    RefreshBarValue();
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
    
    RestartMemoryStatistis();
    profileRootArr.Empty();
    allProfileData.Empty();
    cpuViewBeginIndex = 0;
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
    SluaProfilerDataManager::ClearData();
}

TSharedRef<class SDockTab>  SProfilerInspector::GetSDockTab()
{
    FText WidgetText = FText::FromName("============================ slua profiler ===========================");


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

        // calc sampleIdx
        FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
        int sampleIdx = cpuProfilerWidget->CalcClickSampleIdx(cursorPos);
        cpuProfilerWidget->SetMouseClickPoint(cursorPos);
        sampleIdx = cpuViewBeginIndex + sampleIdx;
        if (sampleIdx < 0 || sampleIdx >= allProfileData.Num() || allProfileData[sampleIdx].Num() == 0)
        {
            TArray<TSharedPtr<FunctionProfileNode>> tmp;
            ShowProfilerTree(tmp);
            return FReply::Handled();
        }else if (sampleIdx >= 0)
        {
            ShowProfilerTree(allProfileData[sampleIdx]);
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
            sampleIdx = cpuViewBeginIndex + sampleIdx;
            if (sampleIdx <= 0 || sampleIdx >= allProfileData.Num() || allProfileData[sampleIdx].Num() == 0)
            {
                TArray<TSharedPtr<FunctionProfileNode>> tmp;
                ShowProfilerTree(tmp);
                return FReply::Handled();
            }else if (sampleIdx >= 0)
            {
                ShowProfilerTree(allProfileData[sampleIdx]);
            }
        }

        return FReply::Handled();
    }));
    
#if PLATFORM_WINDOWS
    cpuProfilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
        isMouseButtonDown = false;
    }));
#endif

    memProfilerWidget->SetOnMouseButtonDown(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
        // stop scorlling and show the profiler info which we click
        isMemMouseButtonDown = true;
        isMemMouseButtonUp = false;
        stopChartRolling = true;

        // calc sampleIdx
        FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
        mouseDownMemIdx = memProfilerWidget->CalcClickSampleIdx(cursorPos);
        mouseDownMemIdx = mouseDownMemIdx + memViewBeginIndex;
        memProfilerWidget->SetMouseClickPoint(cursorPos);
        if (mouseDownMemIdx >= 0 && mouseDownMemIdx < allLuaMemNodeList.Num())
        {
            mouseDownPoint = cursorPos;
            CombineSameFileInfo(*allLuaMemNodeList[mouseDownMemIdx]);
            luaTotalMemSize = allLuaMemNodeList[mouseDownMemIdx]->totalSize;
            memTreeView->RequestTreeRefresh();
        }

        memProfilerWidget->SetMouseMovePoint(mouseDownPoint);
        return FReply::Handled();
    }));
    
    memProfilerWidget->SetOnMouseMove(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
        // calc sampleIdx
        FVector2D cursorPos = inventoryGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
        int sampleIdx = memProfilerWidget->CalcHoverSampleIdx(cursorPos) + memViewBeginIndex;
        static float lastToolTipVal = 0.0f;
        
        if (sampleIdx >= 0 && sampleIdx < allLuaMemNodeList.Num() && lastToolTipVal != allLuaMemNodeList[sampleIdx]->totalSize)
        {
            memProfilerWidget->SetToolTipVal(allLuaMemNodeList[sampleIdx]->totalSize);
            lastToolTipVal = allLuaMemNodeList[sampleIdx]->totalSize;
        }
        else if (sampleIdx < 0)
        {
            memProfilerWidget->SetToolTipVal(-1.0f);
        }
        
        if (isMemMouseButtonDown)
        {
            // calc sampleIdx
            sampleIdx = memProfilerWidget->CalcClickSampleIdx(cursorPos) + memViewBeginIndex;
            if (sampleIdx >= 0 && sampleIdx < allLuaMemNodeList.Num())
            {
                mouseUpMemIdx = sampleIdx;
                mouseUpPoint = cursorPos;
                memProfilerWidget->SetMouseMovePoint(mouseUpPoint);
                CombineSameFileInfo(*allLuaMemNodeList[sampleIdx]);
                luaTotalMemSize = allLuaMemNodeList[sampleIdx]->totalSize;
                memTreeView->RequestTreeRefresh();
            }
        }
        
        return FReply::Handled();
    }));


    memProfilerWidget->SetOnMouseButtonUp(FPointerEventHandler::CreateLambda([=](const FGeometry& inventoryGeometry, const FPointerEvent& mouseEvent) -> FReply {
        isMemMouseButtonUp = true;
        
        if (mouseUpPoint.X != mouseDownPoint.X
            && mouseDownMemIdx >= 0 && mouseDownMemIdx < allLuaMemNodeList.Num())
        {
            memProfilerWidget->SetMouseMovePoint(mouseUpPoint);
            CalcPointMemdiff(mouseDownMemIdx, mouseUpMemIdx);
            memTreeView->RequestTreeRefresh();
        }
        
        isMemMouseButtonDown = false;
        return FReply::Handled();
    }));

#if PLATFORM_WINDOWS
    memProfilerWidget->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateLambda([=](const FPointerEvent&) {
        isMemMouseButtonDown = false;
    }));
#endif

    // init tree view
    SAssignNew(treeview, STreeView<TSharedPtr<FunctionProfileNode>>)
    .ItemHeight(800)
    .TreeItemsSource(&profileRootArr)
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

    SAssignNew(cpuSlider, SSlider).Value(0).StepSize(0.00001)
    .OnMouseCaptureEnd_Lambda(
        [this]()->void
        {
            this->OnCpuSliderValueChanged(this->cpuSlider->GetValue());
            this->bIsTouching = false;
        })
    .OnMouseCaptureBegin_Lambda(
        [this]()->void
        {
            this->bIsTouching = true;
        }
    )
    .OnValueChanged_Lambda(
        [this](float Value)->void
        {
            this->OnCpuSliderValueChanged(Value);
        }
    );

    SAssignNew(memSlider, SSlider).Value(0).StepSize(0.001).OnMouseCaptureEnd_Lambda(
        [this]()->void
        {
            this->OnMemSliderValueChanged(this->memSlider->GetValue());
            this->bIsTouching = false;
        })
    .OnMouseCaptureBegin_Lambda(
        [this]()->void
        {
            this->bIsTouching = true;
        })
    .OnValueChanged_Lambda(
        [this](float Value)->void
        {
            this->OnMemSliderValueChanged(Value);
        }
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

    memProfilerWidget->SetStdLineVisibility(EVisibility::Collapsed);
    cpuProfilerWidget->SetStdLineVisibility(EVisibility::Visible);
    return SNew(SDockTab)
    .TabRole(ETabRole::NomadTab)
    [//         .AutoWidth()
        SNew(SHorizontalBox)
        +SHorizontalBox::Slot()
        .FillWidth(0.2)
        [
            SNew(SBorder)
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
            .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
#else
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
#endif
            [
                SNew(SVerticalBox)
                +SVerticalBox::Slot()
                .Padding(8.0, 5.0)
                .MaxHeight(200.0f)
                .Padding(0, 3.0f)
                [
                    SAssignNew(cpuTabWidget, SProfilerTabWidget)
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
                    .TabIcon(FAppStyle::GetBrush("ProfilerCommand.StatsProfiler"))
#else
                    .TabIcon(FEditorStyle::GetBrush("ProfilerCommand.StatsProfiler"))
#endif
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
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
                    .TabIcon(FAppStyle::GetBrush("ProfilerCommand.MemoryProfiler"))
#else
                    .TabIcon(FEditorStyle::GetBrush("ProfilerCommand.MemoryProfiler"))
#endif
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
                SNew(SVerticalBox)
                +SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).AutoWidth().Padding(5.0f, 3.0f, 0, 0)
                    [
                        SNew(STextBlock)
                        .Text(FText::FromString("CPU    |    "))
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

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
                    [
                        SNew(SButton).Text(FText::FromName("SaveFile"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                        OnSaveFileBtnClicked();
                        return FReply::Handled();
                        }))
                    ]

                    + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
                    [
                        SNew(SButton).Text(FText::FromName("LoadFile"))
                        .ContentPadding(FMargin(2.0, 2.0))
                        .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                        OnLoadFileBtnClicked();
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
                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left)
                    [
                        SNew(STextBlock).Text_Lambda([=]() {
                            FString titleStr = FString::Printf(TEXT("Tick Index:%d"),cpuViewBeginIndex);
                            return FText::FromString(titleStr); })
                    ]
                ]
                
                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SHorizontalBox)
                    +SHorizontalBox::Slot().FillWidth(1)
                    [
                        cpuSlider.ToSharedRef()
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
                            .Text(FText::FromString("MEMORY    |   "))
                        ]

                        + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Right).Padding(0, 3.0f, 15.0f, 0).AutoWidth()
                        [
                            SNew(STextBlock)
                            .Text_Lambda([=]() {
                            FString totalMemory = TEXT("Total : ") + ChooseMemoryUnit(luaTotalMemSize);
                            return FText::FromString(totalMemory);
                            })
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

                        + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
                        [
                            SNew(SButton).Text(FText::FromName("SaveFile"))
                            .ContentPadding(FMargin(2.0, 2.0))
                            .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                            OnSaveFileBtnClicked();
                            return FReply::Handled();
                                }))
                        ]

                        + SHorizontalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left).MaxWidth(60.0f)
                        [
                            SNew(SButton).Text(FText::FromName("LoadFile"))
                            .ContentPadding(FMargin(2.0, 2.0))
                            .OnClicked(FOnClicked::CreateLambda([=]() -> FReply {
                            OnLoadFileBtnClicked();
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
                                 int hookEvent = NS_SLUA::ProfilerHookEvent::PHE_MEMORY_GC;
                                 int connectionsSize = ProfileServer->GetConnections().Num();
                                 
                                 messageWriter.Empty();
                                 messageWriter.Seek(0);
                                 messageWriter << hookEvent;
                                 
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
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
                            .BorderImage(FAppStyle::GetBrush("ProgressBar.ThinBackground"))
#else
                            .BorderImage(FEditorStyle::GetBrush("ProgressBar.ThinBackground"))
#endif
                        ]
                    ]
                    + SVerticalBox::Slot().AutoHeight()
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot().HAlign(EHorizontalAlignment::HAlign_Left)
                        [
                            SNew(STextBlock).Text_Lambda([=]() {
                                FString titleStr = FString::Printf(TEXT("Tick Index:%d"),memViewBeginIndex);
                                return FText::FromString(titleStr); })
                        ]
                    ]
                
                    + SVerticalBox::Slot().AutoHeight()
                    [
                        SNew(SHorizontalBox)
                        +SHorizontalBox::Slot().FillWidth(1)
                        [
                            memSlider.ToSharedRef()
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
                                                 + ChooseMemoryUnit(maxLuaMemory)
                                                 +"), Avg("
                                                 + ChooseMemoryUnit(avgLuaMemory)
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
            ]
        ]
    ];
}

void SProfilerInspector::ShowProfilerTree(TArray<TSharedPtr<FunctionProfileNode>> &selectedProfiler)
{
    profileRootArr = selectedProfiler;
    if (treeview.IsValid())
    {
        treeview->RequestTreeRefresh();
    }
    return;
}

TSharedRef<ITableRow> SProfilerInspector::OnGenerateMemRowForList(TSharedPtr<FileMemInfo> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
    FText difference;
    FLinearColor linearColor;
    
    if(Item->lineNumber.Equals("-1", ESearchCase::CaseSensitive))
        difference = FText::FromString("");
    else
        difference = FText::FromString(ChooseMemoryUnit(Item->difference / 1024.0));
    
    if (Item->difference > 0) {
        linearColor = FLinearColor(1, 0, 0, 1);
    } else if (Item->difference < 0) {
        linearColor = FLinearColor(0, 1, 0, 1);
    } else {
        linearColor = FLinearColor(1, 1, 1, 1);
    }
    
    return
    SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
    .Padding(2.0f)
    [
         SNew(SHeaderRow)
         + SHeaderRow::Column("Overview").DefaultLabel(TAttribute<FText>::Create([=]() {
            if (!Item->hint.IsEmpty())
            {
                FString fileNameInfo = FPaths::GetCleanFilename(Item->hint);
                
                if(!Item->lineNumber.Equals("-1", ESearchCase::CaseSensitive))
                    fileNameInfo += ":" + Item->lineNumber;
                return FText::FromString(fileNameInfo);
            }
            return FText::FromString("");
        }))
         .FixedWidth(fixRowWidth)

         + SHeaderRow::Column("Memory Size").DefaultLabel(TAttribute<FText>::Create([=]() {
            if (Item->size >= 0)
            {
                return FText::FromString(ChooseMemoryUnit(Item->size / 1024.0));
            }
            return FText::FromString("");
        }))
         .FixedWidth(fixRowWidth)
     
         + SHeaderRow::Column("Compare Two Point")
         .FixedWidth(fixRowWidth)
         [
              SNew(STextBlock)
              .Text(difference)
              .ColorAndOpacity(linearColor)
         ]
     ];
}

void SProfilerInspector::OnGetMemChildrenForTree(TSharedPtr<FileMemInfo> Parent, TArray<TSharedPtr<FileMemInfo>>& OutChildren)
{
    if(!Parent->lineNumber.Equals("-1", ESearchCase::CaseSensitive)) return;

    FString fileName = Parent->hint;
    auto &fileInfos = shownFileInfo.FindChecked(fileName);
    for (auto &line:fileInfos)
    {
        OutChildren.Add(line.Value);
    }

    OutChildren.StableSort([](const TSharedPtr<FileMemInfo>& lhs, const TSharedPtr<FileMemInfo>& rhs)
        {
            return lhs->size > rhs->size;
        });
}

void SProfilerInspector::OnGetChildrenForTree(TSharedPtr<FunctionProfileNode> parent, TArray<TSharedPtr<FunctionProfileNode>>& OutChildren)
{
    int64 childNodeCostTime = 0;
    if (parent->childNode->Num() == 0) {
        return;
    }

    for (auto& Item : *parent->childNode) {
        TSharedPtr<struct FunctionProfileNode> x = Item.Value;
        OutChildren.Add(Item.Value);
        childNodeCostTime += Item.Value->costTime;
    }

    TSharedPtr<FunctionProfileNode> otherNode = MakeShareable(new FunctionProfileNode);
    SluaProfilerDataManager::InitProfileNode(otherNode, "Other", parent->layerIdx + 1);
    otherNode->costTime = parent->costTime - childNodeCostTime;
    OutChildren.Add(otherNode);
    OutChildren.StableSort([](const TSharedPtr<FunctionProfileNode>& lhs, const TSharedPtr<FunctionProfileNode>& rhs)
    {
        return lhs->costTime > rhs->costTime;
    });
}

TSharedRef<ITableRow> SProfilerInspector::OnGenerateRowForList(TSharedPtr<FunctionProfileNode> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
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
        .Padding(2.0f)
        [
            SNew(SHeaderRow)
            + SHeaderRow::Column("Overview").DefaultLabel(TAttribute<FText>::Create([=]() {
                FString Name = GenBrevFuncName(Item->functionName);
                return FText::FromString(Name);
            }))
            .FixedWidth(rowWidth).DefaultTooltip(TAttribute<FText>::Create([=]() {
                return FText::FromString(Item->functionName);
            }))
            + SHeaderRow::Column("Time ms").DefaultLabel(TAttribute<FText>::Create([=]() {
                return FText::AsNumber(Item->costTime / perMilliSec);
            }))
            .FixedWidth(fixRowWidth)
                + SHeaderRow::Column("Calls").DefaultLabel(TAttribute<FText>::Create([=]() {
            return FText::AsNumber(Item->countOfCalls);
            }))
            .FixedWidth(fixRowWidth)
        ];
}

void SProfilerInspector::CollectMemoryNode(TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame)
{
    QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_CollectMemoryNode)
    if (!memoryFrame.IsValid())
        return;
    
    TSharedPtr<FProflierMemNode> memNode = MakeShareable(new FProflierMemNode());

    auto OnAllocMemory = [&](const NS_SLUA::LuaMemInfo& memFileInfo)
    {
        memoryInfoMap.Add(memFileInfo.ptr, memFileInfo);
        lastLuaTotalMemSize += memFileInfo.size;

        auto* fileInfos = memNode->infoList.Find(memFileInfo.hint);
        if (!fileInfos)
        {
#if ENGINE_MAJOR_VERSION==5
            TMap<int, TSharedPtr<FileMemInfo, ESPMode::ThreadSafe>> newFileInfos;
#else
            TMap<int, TSharedPtr<FileMemInfo, ESPMode::Fast>> newFileInfos;
#endif
            fileInfos = &memNode->infoList.Add(memFileInfo.hint, newFileInfos);
        }

        auto lineInfo = fileInfos->Find(memFileInfo.lineNumber);
        if (lineInfo)
        {
            (*lineInfo)->size += memFileInfo.size;
        }
        else
        {
            FileMemInfo* fileInfo = new FileMemInfo();
            fileInfo->hint = memFileInfo.hint;
            fileInfo->lineNumber = FString::Printf(TEXT("%d"), memFileInfo.lineNumber);
            fileInfo->size = memFileInfo.size;
            fileInfos->Add(memFileInfo.lineNumber, MakeShareable(fileInfo));
        }

        auto* parentFileInfo = memNode->parentFileMap.Find(memFileInfo.hint);
        if (!parentFileInfo)
        {
            FileMemInfo* fileInfo = new FileMemInfo();
            fileInfo->hint = memFileInfo.hint;
            fileInfo->lineNumber = TEXT("-1");
            fileInfo->size = memFileInfo.size;
            memNode->parentFileMap.Add(memFileInfo.hint, MakeShareable(fileInfo));
        }
        else
        {
            (*parentFileInfo)->size += memFileInfo.size;
        }
    };

    auto OnFreeMemory = [&](const NS_SLUA::LuaMemInfo& memFileInfo)
    {
        if (memoryInfoMap.Contains(memFileInfo.ptr))
        {
            memoryInfoMap.Remove(memFileInfo.ptr);
            lastLuaTotalMemSize -= memFileInfo.size;

            auto fileInfos = memNode->infoList.Find(memFileInfo.hint);
            if (fileInfos)
            {
                auto* lineInfo = fileInfos->Find(memFileInfo.lineNumber);
                if (lineInfo)
                {
                    (*lineInfo)->size -= memFileInfo.size;
                    ensureMsgf((*lineInfo)->size >= 0, TEXT("Error: %s line[%d] size is negative!"), *(*lineInfo)->hint, memFileInfo.lineNumber);
                    if ((*lineInfo)->size <= 0)
                    {
                        fileInfos->Remove(memFileInfo.lineNumber);
                    }
                }
            }

            auto& parentFileInfo = memNode->parentFileMap.FindChecked(memFileInfo.hint);
            parentFileInfo->size -= memFileInfo.size;
        }
    };

    if (memoryFrame->bMemoryTick)
    {
        memoryInfoMap.Empty();
        lastLuaMemNode.Reset();
        RestartMemoryStatistis();
        
        for (auto &memoInfo : memoryFrame->memoryInfoList)
        {
            OnAllocMemory(memoInfo);
        }
    }
    else if (lastLuaMemNode.IsValid())
    {
        //copy lastLuaMemNode to memNode
        // *(memNode.Get()) = *(lastLuaMemNode.Get());
        QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_CollectMemoryNode_CopyLastLuaMemNode)
        FProflierMemNode &last = *lastLuaMemNode;
        FProflierMemNode &current = *memNode;
        current.totalSize = last.totalSize;

        current.infoList.Reserve(last.infoList.Num());
        for (auto &fileInfoIter : last.infoList)
        {
            auto &newInfoList = current.infoList.Add(fileInfoIter.Key);
            newInfoList.Reserve(fileInfoIter.Value.Num());
            for (auto& lineInfo : fileInfoIter.Value)
            {
                FileMemInfo* memInfo = new FileMemInfo();
                *memInfo = *lineInfo.Value;
                newInfoList.Add(lineInfo.Key, MakeShareable(memInfo));
            }
        }

        current.parentFileMap.Reserve(last.parentFileMap.Num());
        for (auto &parentFileIter : last.parentFileMap)
        {
            FileMemInfo* memInfo = new FileMemInfo();
            *memInfo = *parentFileIter.Value;
            current.parentFileMap.Add(parentFileIter.Key, MakeShareable(memInfo));
        }
    }

    for (auto& memoInfo : memoryFrame->memoryIncrease)
    {
        if (memoInfo.bAlloc)
        {
            OnAllocMemory(memoInfo);
        }
        else
        {
            OnFreeMemory(memoInfo);
        }
    }
    
    //lastLuaTotalMemSize unit changed from byte to KB
    memNode->totalSize = lastLuaTotalMemSize / 1024.0f;
    lastLuaMemNode = memNode;
}

void SProfilerInspector::CombineSameFileInfo(FProflierMemNode& proflierMemNode)
{
    QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_CombineSameFileInfo)

    {
        QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_CombineSameFileInfo_CopyInfoList)
        shownFileInfo = proflierMemNode.infoList;
    }

    {
        QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_CombineSameFileInfo_CopyShownParentFileName)
        shownParentFileName.Empty();
        for (auto& iter : proflierMemNode.parentFileMap)
        {
            auto& parentMemInfo = iter.Value;
            shownParentFileName.Add(parentMemInfo);
        }
    }

    {
        QUICK_SCOPE_CYCLE_COUNTER(SProfilerInspector_CombineSameFileInfo_Sort)
        shownParentFileName.StableSort([](const TSharedPtr<FileMemInfo>& lhs, const TSharedPtr<FileMemInfo>& rhs)
            {
                return lhs->size > rhs->size;
            });
    }

    if (shownParentFileName.Num() > maxMemoryFile)
    {
        shownParentFileName.RemoveAt(maxMemoryFile, shownParentFileName.Num() - maxMemoryFile, false);
    }
}

void SProfilerInspector::CalcPointMemdiff(int beginIndex, int endIndex)
{
    beginIndex = beginIndex < 0 ? 0 : beginIndex;
    endIndex = endIndex < 0 ? 0 : endIndex;
    // Always use new record of memory as the compareing data;
    if(beginIndex > endIndex) {
        int temp = beginIndex;
        beginIndex = endIndex;
        endIndex = temp;
        
        CombineSameFileInfo(*allLuaMemNodeList[endIndex]);
    }

    for (auto& fileInfoIter : shownFileInfo)
    {
        for (auto& infoIter : fileInfoIter.Value)
        {
            infoIter.Value->difference = infoIter.Value->size;
        }
    }

    for (auto& fileInfoIter : allLuaMemNodeList[beginIndex]->infoList)
    {
        const FString& fileHint = fileInfoIter.Key;
        auto *showInfo = shownFileInfo.Find(fileHint);
        if (showInfo)
        {
            for (auto& lineInfo : fileInfoIter.Value)
            {
                int lineNumber = lineInfo.Key;
                auto *showLineInfo = showInfo->Find(lineNumber);
                if (showLineInfo)
                {
                    (*showLineInfo)->difference -= lineInfo.Value->size;
                }
                else
                {
                    FileMemInfo *newInfo = new FileMemInfo();
                    newInfo->hint = lineInfo.Value->hint;
                    newInfo->lineNumber = lineInfo.Value->lineNumber;
                    newInfo->size = 0.0f;
                    newInfo->difference -= lineInfo.Value->size;
                    showInfo->Add(lineNumber, MakeShareable(newInfo));
                }
            }
        }
    }

    float diff = 0.0f;
    for (auto& fileInfoIter : shownFileInfo)
    {
        for (auto& infoIter : fileInfoIter.Value)
        {
            diff += infoIter.Value->difference;
        }
    }
    NS_SLUA::Log::Log("The difference between two Point is %.3f KB", diff/1024.0f);
}

int SProfilerInspector::ContainsFile(FString& fileName, MemInfoIndexMap &list)
{
    const int* indexPtr = list.Find(fileName);
    if (indexPtr)
    {
        return *indexPtr;
    }

    return -1;
}

FString SProfilerInspector::ChooseMemoryUnit(float memorySize)
{
    if (memorySize < 1024) return FString::Printf(TEXT("%.3f KB"), memorySize);
    else if (memorySize >= 1024) return FString::Printf(TEXT("%.3f MB"), (memorySize / 1024.0f));
    return FString::Printf(TEXT("%.3f"), memorySize);
}

////////////////////////////// SProfilerWidget //////////////////////////////

void SProfilerWidget::SetArrayValue(TArray<float>& chartValArray, float maxCostTime, float maxMemSize)
{
    QUICK_SCOPE_CYCLE_COUNTER(SProfilerWidget_SetArrayValue)
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
    else if(m_pathArrayNum != 0 && m_arraylinePath[m_arraylinePath.Num() - 1].X < cursorPos.X){
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

    FSlateFontInfo FontInfo = FCoreStyle::Get().GetFontStyle("NormalFont");
    FontInfo.Size = 10.0f;

    FSlateDrawElement::MakeText(
                    OutDrawElements,
                    LayerId,
#if (ENGINE_MINOR_VERSION>=2) && (ENGINE_MAJOR_VERSION==5)
                    AllottedGeometry.ToPaintGeometry(AllottedGeometry.Size, FSlateLayoutTransform(1.0f, TransformPoint(1.0f, FVector2D(0, positionY - 10)))),
#else
                    AllottedGeometry.ToPaintGeometry(FVector2D(0, positionY - 10), AllottedGeometry.Size),
#endif
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
#if (ENGINE_MINOR_VERSION>=2) && (ENGINE_MAJOR_VERSION==5)
                                    AllottedGeometry.ToPaintGeometry(AllottedGeometry.Size, FSlateLayoutTransform(1.0f, TransformPoint(1.0f, FVector2D(0, 95.0f)))),
#else 
                                    AllottedGeometry.ToPaintGeometry(FVector2D(0, 95.0f), AllottedGeometry.Size),
#endif
                                    m_stdMemStr[0] + TEXT(" —"),
                                    FontInfo,
                                    ESlateDrawEffect::None,
                                    FLinearColor::White
                                    );
        
        FSlateDrawElement::MakeText(
                                    OutDrawElements,
                                    LayerId,
#if (ENGINE_MINOR_VERSION>=2) && (ENGINE_MAJOR_VERSION==5)
                                    AllottedGeometry.ToPaintGeometry(AllottedGeometry.Size, FSlateLayoutTransform(1.0f, TransformPoint(1.0f, FVector2D(0, 0)))),
#else 
                                    AllottedGeometry.ToPaintGeometry(FVector2D(0, 0), AllottedGeometry.Size),
#endif
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
#if (ENGINE_MINOR_VERSION>=2) && (ENGINE_MAJOR_VERSION==5)
                                        AllottedGeometry.ToPaintGeometry(FVector2D(length, cMaxViewHeight), FSlateLayoutTransform(1.0f, TransformPoint(1.0f, boxBeginPoint))),
#else 
                                        AllottedGeometry.ToPaintGeometry(boxBeginPoint, FVector2D(length, cMaxViewHeight)),
#endif
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
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
            .BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
#else
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
#endif
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