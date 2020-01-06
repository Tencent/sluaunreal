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
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/Views/STreeView.h"
#include "slua_remote_profile.h"
#include "slua_unreal/Private/LuaMemoryProfile.h"
#include "Input/Reply.h"


#define IsMemoryProfiler (m_stdLineVisibility.Get() != EVisibility::Visible)

struct FunctionProfileInfo;
struct FileMemInfo;
struct ProflierMemNode;
struct SnapshotInfo;

typedef TArray<TSharedPtr<FunctionProfileInfo>> SluaProfiler;
typedef TArray<FileMemInfo> MemFileInfoList;
typedef TArray<ProflierMemNode> MemNodeInfoList;
typedef TArray<TSharedPtr<FileMemInfo>> ShownMemInfoList;

class SProfilerWidget;
class SProfilerTabWidget;

const int cMaxSampleNum = 250;
const int cMaxViewHeight = 200;

struct FileMemInfo {
    FString hint;
    FString lineNum;
    int size;
    // one line memory difference between two point
    int difference;
};

struct ProflierMemNode {
    MemFileInfoList infoList;
    float totalSize;
};

struct SnapshotInfo {
    int id;
    int objSize;
    int memSize;
    int objDiff;
    int memDiff;
    FString name;
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

class SLUA_PROFILE_API SProfilerInspector
{
public:
    SProfilerInspector();
    ~SProfilerInspector();
    
    void Refresh(TArray<SluaProfiler>& curProfilersArray, TArray<NS_SLUA::LuaMemInfo>& memoryInfoList,
                 TArray<SnapshotInfo> snapshotArray, TArray<NS_SLUA::LuaMemInfo> snapshotDifferentArray);
    TSharedRef<class SDockTab> GetSDockTab();
    TSharedRef<ITableRow> OnGenerateMemRowForList(TSharedPtr<FileMemInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
    TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FunctionProfileInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
    TSharedRef<ITableRow> OnGenerateSnapshotInfoRowForList(TSharedPtr<SnapshotInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
    TSharedRef<ITableRow> OnGenerateSnapshotDiffList(TSharedPtr<FileMemInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
    void OnGetMemChildrenForTree(TSharedPtr<FileMemInfo> Parent, TArray<TSharedPtr<FileMemInfo>>& OutChildren);
    void OnGetSnapshotDiffChildrenForTree(TSharedPtr<FileMemInfo> Parent, TArray<TSharedPtr<FileMemInfo>>& OutChildren);
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
    
    TSharedPtr<slua::FProfileServer> ProfileServer;
    
private:
    const static int sampleNum = cMaxSampleNum;
    const static int fixRowWidth = 300;
    const static int snapshotInfoRowWidth = 600;
    const static int refreshInterval = 50;
    const float perMilliSec = 1000.0f;
    
    TSharedPtr<STreeView<TSharedPtr<FunctionProfileInfo>>> treeview;
    TSharedPtr<STreeView<TSharedPtr<FileMemInfo>>> memTreeView;
    TSharedPtr<STreeView<TSharedPtr<FileMemInfo>>> snapshotDiffTreeView;
    TSharedPtr<SListView<TSharedPtr<SnapshotInfo>>> snapshotListView;
    TSharedPtr<SCheckBox> profilerCheckBox;
    TSharedPtr<SCheckBox> memProfilerCheckBox;
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
    bool showSnapshotDiff;
    int refreshIdx;
    int arrayOffset;
    int lastArrayOffset;
    int snapshotID;
    int preSnapshotID;
    int deleteSnapshotID;
    float maxLuaMemory;
    float avgLuaMemory;
    float luaTotalMemSize;
    float maxProfileSamplesCostTime;
    float avgProfileSamplesCostTime;
    bool hasCleared;
    bool needProfilerCleared;
    bool isMemMouseButtonUp;
    FVector2D mouseUpPoint;
    FVector2D mouseDownPoint;
    
    TArray<SluaProfiler> tmpProfilersArraySamples[sampleNum];
    TArray<SluaProfiler> profilersArraySamples[sampleNum];
    SluaProfiler shownRootProfiler;
    SluaProfiler shownProfiler;
    SluaProfiler tmpRootProfiler;
    SluaProfiler tmpProfiler;
    /* holding all of the memory node which are showed on Profiler chart */
    MemNodeInfoList luaMemNodeChartList;
    /* refresh with the chart line, when mouse clicks down, it'll get point from this array */
    MemNodeInfoList tempLuaMemNodeChartList;
    ShownMemInfoList shownFileInfo;
    /* store the file name as the parent item in memory treeview */
    ShownMemInfoList shownParentFileName;
    /* store the different item between two snapshots for snapshot diff treeview */
    ShownMemInfoList snapshotDiffArray;
    /* store the item's label(like Table/Func/Userdata etc.) for snapshot diff treeview */
    ShownMemInfoList snapshotDiffParentArray;
    /* store each snapshot's name for TextComboBox to be chosen */
    TArray<TSharedPtr<FString>> snapshotIdArray;
    /* store each snapshot's basic info(allocations and mem size) for snapshot Info treeview */
    TArray<TSharedPtr<SnapshotInfo>> snapshotInfoArray;
    
    void initLuaMemChartList();
    bool NeedReBuildInspector();
    void RefreshBarValue();
    void AddProfilerBarOnMouseMoveEvent();
    void RemoveProfilerBarOnMouseMoveEvent();
    void ShowProfilerTree(TArray<SluaProfiler> &selectedProfiler);
    void CheckBoxChanged(ECheckBoxState newState);
    void MemoryCheckBoxChanged(ECheckBoxState newState);
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
    void SortShownInfo();
    void CalcPointMemdiff(int beginIndex, int endIndex);
    void CombineSameFileInfo(MemFileInfoList& infoList);
    void CollectSnapshotInfo(TArray<SnapshotInfo> snapshotArray);
    void CollectSnapshotDiff(TArray<NS_SLUA::LuaMemInfo> diffArray);
    void CollectMemoryNode(TArray<NS_SLUA::LuaMemInfo>& memoryInfoList);
    void OnSnapshotItemChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
    void OnPreSnapshotItemChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
    void OnDeleteSnapshotItem(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
    int ContainsFile(FString& fileName, ShownMemInfoList &list);
    int getSnapshotInfoIndex(int id);
    FString ChooseMemoryUnit(float memoryKBSize);
    TArray<FString> SplitFlieName(FString filePath);   
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
    float m_widgetWidth;
    const int32 m_cStdLeftPosition = 30;
    float m_maxCostTime;
    float m_maxMemSize;
    float m_maxPointHeight;
    float m_pointInterval;
    float m_toolTipVal;
    int32 m_memStdScale;
    int32 m_pathArrayNum;
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
