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
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STreeView.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "slua_remote_profile.h"
#include "LuaMemoryProfile.h"
#include "ProfileDataDefine.h"
#include "slua_profile_inspector.h"

#define IsMemoryProfiler (m_stdLineVisibility.Get() != EVisibility::Visible)
class SProfilerWidget;
class SProfilerTabWidget;
class Profiler;
class SSlider;

class SLUA_PROFILE_API SProfilerInspector
{
public:
    SProfilerInspector();
    ~SProfilerInspector();
    
    void Refresh(TSharedPtr<FunctionProfileNode> funcInfoRoot, TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoList, MemoryFramePtr memoryFrame);
    TSharedRef<class SDockTab> GetSDockTab();
    TSharedRef<ITableRow> OnGenerateMemRowForList(TSharedPtr<FileMemInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
    void OnGetMemChildrenForTree(TSharedPtr<FileMemInfo> Parent, TArray<TSharedPtr<FileMemInfo>>& OutChildren);
    
    void OnGetChildrenForTree(TSharedPtr<FunctionProfileNode> Parent, TArray<TSharedPtr<FunctionProfileNode>>& OutChildren);
    TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FunctionProfileNode> Item, const TSharedRef<STableViewBase>& OwnerTable);
    void StartChartRolling();
    bool GetNeedProfilerCleared() const
    {
        return needProfilerCleared;
    }
    void SetNeedProfilerCleared(const bool needClear)
    {
        needProfilerCleared = needClear;
    }
    
    TSharedPtr<NS_SLUA::FProfileServer> ProfileServer;
    
private:
    const static int sampleNum = cMaxSampleNum;
    const static int fixRowWidth = 600;
    const static int refreshInterval = 1;
    const float perMilliSec = 1000.0f;
    const static int maxMemoryFile = 30;
    bool bIsTouching = false;
    typedef TMap<FString, int> MemInfoIndexMap;
    
    TSharedPtr<STreeView<TSharedPtr<FunctionProfileNode>>> treeview;
    TSharedPtr<SListView<TSharedPtr<FileMemInfo>>> listview;
    TSharedPtr<STreeView<TSharedPtr<FileMemInfo>>> memTreeView;
    TSharedPtr<SSlider> cpuSlider,memSlider;

    TSharedPtr<SProgressBar> profilerBarArray[sampleNum];
    TSharedPtr<SProfilerWidget> cpuProfilerWidget;
    TSharedPtr<SProfilerWidget> memProfilerWidget;
    TSharedPtr<SProfilerTabWidget> cpuTabWidget;
    TSharedPtr<SProfilerTabWidget> memTabWidget;
    TSharedPtr<SProfilerTabWidget> fpsTabWidget;
    TSharedPtr<SWidgetSwitcher> tabSwitcher;
    
    
    TArray<float> chartValArray;
    TArray<float> memChartValArray;
    bool stopChartRolling;
    int cpuViewBeginIndex;
    int memViewBeginIndex;
    
    float maxLuaMemory;
    float avgLuaMemory;
    float luaTotalMemSize;
    float lastLuaTotalMemSize;
    float maxProfileSamplesCostTime;
    float avgProfileSamplesCostTime;
    bool hasCleared;
    bool needProfilerCleared;
    bool isMemMouseButtonUp;
    FVector2D mouseUpPoint;
    FVector2D mouseDownPoint;

    
    TArray<TArray<TSharedPtr<FunctionProfileNode>>> allProfileData;

    TArray<TSharedPtr<FunctionProfileNode>> profileRootArr;    
    TSharedPtr<FProflierMemNode> lastLuaMemNode;
    /* holding all of the memory node which are showed on Profiler chart */
    MemNodeInfoList allLuaMemNodeList;
    
    /* refresh with the chart line, when mouse clicks down, it'll get point from this array */
    MemFileInfoMap shownFileInfo;
    /* store the file name as the parent item in memory treeview */
    ShownMemInfoList shownParentFileName;
    
    void initLuaMemChartList();
    void RefreshBarValue();
    
    void ShowProfilerTree(TArray<TSharedPtr<FunctionProfileNode>>&selectedProfiler);
    void CheckBoxChanged(ECheckBoxState newState);
    
    FString GenBrevFuncName(const FString &functionName);
    
    void RestartMemoryStatistis();
    void OnClearBtnClicked();
    void CalcPointMemdiff(int beginIndex, int endIndex);
    void CollectMemoryNode(TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame);
    void CombineSameFileInfo(FProflierMemNode& proflierMemNode);
    int ContainsFile(FString& fileName, MemInfoIndexMap &list);
    FString ChooseMemoryUnit(float memorySize);

    // save/load disk profile file
    void OnLoadFileBtnClicked();
    void OnSaveFileBtnClicked();
    void OnCpuSliderValueChanged(float Value);
    void OnMemSliderValueChanged(float Value);
};

class SLUA_PROFILE_API SProfilerWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SProfilerWidget)
    :_StdLineVisibility(EVisibility::Visible)
    {}
    
    SLATE_ATTRIBUTE(EVisibility, StdLineVisibility)
    
    SLATE_END_ARGS()
    
    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);
    void SetMouseMovePoint(FVector2D mouseDownPoint);
    void SetMouseClickPoint(FVector2D mouseClickPoint);
    void SetArrayValue(TArray<float> &chartValArray, float maxCostTime, float maxMemSize);
    int CalcClickSampleIdx(FVector2D &cursorPos);
    int CalcHoverSampleIdx(const FVector2D cursorPos);
    void SetToolTipVal(float val);
    void ClearClickedPoint();
    void SetStdLineVisibility(TAttribute<EVisibility> InVisibility);
    
    // SWidget interface
    virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
    virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
protected:
    virtual FVector2D ComputeDesiredSize(float size) const override;
    
private:
    void DrawStdLine(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, float positionY, FString stdStr) const;
    void AddStdLine(float &maxPointValue, float &stdLineValue, FString &stdLineName);
    void CalcStdLine(float &maxCostTime);
    void CalcMemStdText(float &maxMemorySize);
    
    TArray<FVector2D> m_arraylinePath;
    TArray<float> m_arrayVal;

    TArray<float> m_stdPositionY;
    TArray<FString> m_stdStr;
    TArray<FString> m_stdMemStr;
    TAttribute<EVisibility> m_stdLineVisibility;
    const int32 m_cSliceCount = cMaxSampleNum;
    const float m_cStdWidth = 1300;
    float m_widgetWidth = 0;
    const int32 m_cStdLeftPosition = 30;
    float m_maxCostTime = 0;
    float m_maxMemSize = 0;
    float m_maxPointHeight = 0;
    float m_pointInterval = 0;
    float m_toolTipVal = 0;
    int32 m_memStdScale = 1;
    int32 m_pathArrayNum = 0;
    FVector2D m_clickedPoint;
    FVector2D m_mouseDownPoint;
    const float m_cStdHighVal = cMaxViewHeight;
};

class SLUA_PROFILE_API SProfilerTabWidget : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SProfilerTabWidget)
    : _TabName(FText::FromString(""))
    , _TabIcon(FCoreStyle::Get().GetDefaultBrush())
    {}
    
    SLATE_ATTRIBUTE(FText, TabName)
    
    SLATE_ATTRIBUTE(const FSlateBrush*, TabIcon)
    
    SLATE_EVENT(FOnClicked, OnClicked)
    
    /** The visual style of the button */
    SLATE_END_ARGS()
    
public:
    int32 activeTabIndex = 0;
    
    void Construct(const FArguments& InArgs);
};
