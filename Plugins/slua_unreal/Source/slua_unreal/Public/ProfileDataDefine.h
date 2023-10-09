// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "LuaMemoryProfile.h"
#include "Containers/Queue.h"
#include "ProfileDataDefine.generated.h"

struct FileMemInfo;
struct FProflierMemNode;
struct MemoryFrame;
struct FunctionProfileNode;
struct FunctionProfileCallInfo;
typedef TSharedPtr<MemoryFrame> MemoryFramePtr;
typedef TQueue<MemoryFramePtr, EQueueMode::Mpsc> MemoryFrameQueue;
typedef TSharedPtr<FunctionProfileNode> ProfileNodePtr;
typedef TMap<int64, NS_SLUA::LuaMemInfo> LuaMemInfoMap;
typedef TArray<TSharedPtr<FunctionProfileCallInfo>> ProfileCallInfoArray;
typedef TMap<FString, TMap<int, TSharedPtr<FileMemInfo>>> MemFileInfoMap;
typedef TArray<TSharedPtr<FProflierMemNode>> MemNodeInfoList;
typedef TArray<TSharedPtr<FileMemInfo>> ShownMemInfoList;
typedef TMap<FString, TSharedPtr<FileMemInfo>> ParentFileMap;
typedef TArray<TArray<TSharedPtr<FunctionProfileNode>>> ProfileNodeArrayArray;

static const int cMaxSampleNum = 250;
static const int cMaxViewHeight = 200;
static const int cRefreshDisCount = 10;
static int32 ProfileVersion = 3;

USTRUCT()
struct SLUA_UNREAL_API FProfileNodeArray
{
    GENERATED_BODY();

public:
    TArray<TSharedPtr<FunctionProfileNode>> NodeArray;

    void Serialize(FArchive& Ar);
};

USTRUCT()
struct SLUA_UNREAL_API FileMemInfo {
    GENERATED_BODY();

public:
    UPROPERTY()
        FString hint = "";
    UPROPERTY()
        FString lineNumber = "";
    UPROPERTY()
        float size = 0;

    // one line memory difference between two point
    UPROPERTY()
        float difference = 0;

    void Serialize(FArchive& Ar);
};


USTRUCT()
struct SLUA_UNREAL_API FProflierMemNode {
    GENERATED_BODY();
public:
    MemFileInfoMap infoList;
	ParentFileMap parentFileMap;
    float totalSize;

    void Serialize(FArchive& Ar);
};

USTRUCT()
struct SLUA_UNREAL_API FunctionProfileNode
{
    GENERATED_BODY();
    UPROPERTY()
        FString functionName = "";
    UPROPERTY()
        int64 costTime = 0;
    UPROPERTY()
        int32 countOfCalls = 0;
    UPROPERTY()
        int32 layerIdx = 0;

    TSharedPtr<TMap<FString, TSharedPtr<FunctionProfileNode>>> childNode = MakeShareable(new TMap<FString, TSharedPtr<FunctionProfileNode>>);

    void Serialize(FArchive& Ar);

    void CopyData(TSharedPtr<FunctionProfileNode> NewData);
};


USTRUCT()
struct SLUA_UNREAL_API FunctionProfileCallInfo
{
    GENERATED_BODY();
    UPROPERTY()
        FString functionName;

    UPROPERTY()
        int64 begTime = 0;

    UPROPERTY()
        bool bIsCoroutineBegin = false;

    TSharedPtr<FunctionProfileNode> ProfileNode;
};


struct SLUA_UNREAL_API MemoryFrame
{
    bool bMemoryTick;
    TArray<NS_SLUA::LuaMemInfo> memoryInfoList;
    TArray<NS_SLUA::LuaMemInfo> memoryIncrease;
    TArray<NS_SLUA::LuaMemInfo> memoryDecrease;
};

USTRUCT()
struct SLUA_UNREAL_API FunctionProfileInfo
{
    GENERATED_BODY();

    UPROPERTY()
        FString functionName;
    UPROPERTY()
        FString brevName;
    UPROPERTY()
        int64 begTime;
    UPROPERTY()
        int64 endTime;
    UPROPERTY()
        int64 costTime;
    UPROPERTY()
        int64 mergedCostTime;
    UPROPERTY()
        int globalIdx;
    UPROPERTY()
        int layerIdx;
    UPROPERTY()
        int mergedNum;
    UPROPERTY()
        bool beMerged;
    UPROPERTY()
        bool isDuplicated = false;
    UPROPERTY()
        TArray<int> mergeIdxArray;

    FunctionProfileInfo():
        begTime(0),
        endTime(0),
        costTime(0),
        mergedCostTime(0),
        globalIdx(0),
        layerIdx(0),
        mergedNum(0),
        beMerged(false)
    {
    }
};