// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ProfileDataDefine.h"
#include "Modules/ModuleManager.h"
#include "Containers/Queue.h"
#include "Containers/Array.h"
#include "Containers/Ticker.h"
#include "Serialization/BufferArchive.h"
#include "HAL/Runnable.h"

class SLUA_UNREAL_API FProfileDataProcessRunnable : public FRunnable
{
public:
    FProfileDataProcessRunnable();

    void StopStreamingRunnable();

    // Begin FRunnable overrides
    virtual bool Init() override;
    virtual uint32 Run() override;

    //接收性能数据
    void ReceiveProfileData(int hookEvent, int64 time, int lineDefined, const FString& funcName, const FString& shortSrc);

    //接收内存数据
    void ReceiveMemoryData(int hookEvent, const TArray<NS_SLUA::LuaMemInfo>& memInfoList);

    //用外部数据存储数据
    void SaveDataWithData(int inCpuViewBeginIndex, int inMemViewBeginIndex,ProfileNodeArrayArray& inProfileData, const MemNodeInfoList& inLuaMemNodeList);

    static FString GenerateStatFilePath();

    //解压数据
    void LoadData(const FString& filePath, int& inCpuViewBeginIndex, int& inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, MemNodeInfoList& inLuaMemNodeList);

    //清除数据
    void OnClearDataWithCallBack(TFunction<void()>&& Callback);

    void ClearData();

    void StartRecord();
    void StopRecord();

    bool IsRecording() const;

private:
    void SerializeFrameData(FArchive& ar, TArray<TSharedPtr<FunctionProfileNode>>& frameFuncRootArr, TSharedPtr<FProflierMemNode>& frameMemNode, const TSharedPtr<FProflierMemNode>& preFrameMemNode);
    static constexpr int32 CompressedSize = 1024 * 1024;
    FRunnableThread* WorkerThread;

    struct FCPUCommand
    {
        int hookEvent;
        int64 time;
        int lineDefined;
        FString funcName;
        FString shortSrc;
    };
    TQueue<FCPUCommand, EQueueMode::Mpsc> cpuCommandQueue;

    struct FMemoryCommand
    {
        int hookEvent;
        TArray<NS_SLUA::LuaMemInfo> memInfoList;
    };
    TQueue<FMemoryCommand, EQueueMode::Mpsc> memoryCommandQueue;

    enum FCommandType
    {
        ECPU,
        EMemory,
    };
    TQueue<FCommandType, EQueueMode::Mpsc> commandTypeQueue;

    void ProcessCommands();
    void ProcessCPUCommand(const FCPUCommand& cpuCommand);
    void ProcessMemoryCommand(const FMemoryCommand& memoryCommand) const;

    bool bIsRecording = false;
    bool RunnableStart = false;

    double lastLuaTotalMemSize;

    ProfileNodeArrayArray allProfileData;
    TArray<TSharedPtr<FunctionProfileNode>> profileRootArr;
    TQueue<TSharedPtr<FunctionProfileNode>, EQueueMode::Mpsc> funcProfilerNodeQueue;
    TSharedPtr<FProflierMemNode> lastLuaMemNode;

    MemoryFrameQueue memoryQueue;
    ProfileNodePtr funcProfilerRoot;
    ProfileCallInfoArray profilerStack;
    MemoryFramePtr currentMemory;
    LuaMemInfoMap memoryInfo;
    int32 memoryFrameNum = -1;

    FArchive* frameArchive = nullptr;
    bool bCanStartFrameRecord = false;
    bool bFrameFirstRecord = false;
    TArray<uint8> dataToCompress;

    void PreProcessData(TSharedPtr<FunctionProfileNode> funcInfoRoot, TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame);
    void SerializeCompreesedDataToFile(FArchive& ar);

    void CollectMemoryNode(TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame);

    void RestartMemoryStatistis();
    void ClearCurProfiler();

    void SerializeLoad(FArchive& inAR, int& inCpuViewBeginIndex, int& inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, MemNodeInfoList& inLuaMemNodeList);
};

class SLUA_UNREAL_API SluaProfilerDataManager
{
public:

    static void StartManager();
    static void StopManager();

    //接收性能数据
    static void ReceiveProfileData(int hookEvent, int64 time, int lineDefined, const FString& funcName, const FString& shortSrc);
    //接收内存数据
	static void ReceiveMemoryData(int hookEvent, const TArray<NS_SLUA::LuaMemInfo>& memInfoList);

    //用外部数据存储数据
    static void SaveDataWithData(int inCpuViewBeginIndex, int inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, const MemNodeInfoList& inLuaMemNodeList);

    //开始录制
    static void BeginRecord();

    //结束录制
    static void EndRecord();

    static bool IsRecording();

    //解压数据
    static void LoadData(const FString& filePath, int& inCpuViewBeginIndex, int& inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, MemNodeInfoList& inLuaMemNodeList);

    //清除数据
    static void OnClearDataWithCallBack(TFunction<void()>&& Callback);

    static void ClearData();

    static void WatchBegin(const FString& fileName, int32 lineDefined, const FString& funcName, double nanoseconds, ProfileNodePtr funcProfilerRoot, ProfileCallInfoArray& profilerStack);
    static void WatchEnd(const FString& fileName, int32 lineDefined, const FString& functionName, double nanoseconds, ProfileCallInfoArray& profilerStack);
    static void CoroutineBegin(int32 lineDefined, const FString& funcName, double nanoseconds, ProfileNodePtr funcProfilerRoot, ProfileCallInfoArray& profilerStack);
    static void CoroutineEnd(double nanoseconds, ProfileCallInfoArray& profilerStack);

    static void InitProfileNode(TSharedPtr<FunctionProfileNode>& funcNode, const FLuaFunctionDefine& funcDefine, int32 layerIdx);
    static void AddToParentNode(TSharedPtr<FunctionProfileNode> patentNode, TSharedPtr<FunctionProfileCallInfo> callInfo);
    
    static FProfileNameSet* ProfileNameSet;
private:
    static FProfileDataProcessRunnable* ProcessRunnable;
};
