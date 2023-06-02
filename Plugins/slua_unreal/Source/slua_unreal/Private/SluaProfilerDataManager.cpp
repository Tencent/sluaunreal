#include "SluaProfilerDataManager.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Misc/FileHelper.h"
#include "Log.h"
#include "LuaProfiler.h"
#include "Serialization/MemoryReader.h"
#include "Misc/Paths.h"
#include <LuaState.h>

#include "HAL/RunnableThread.h"
#define ROOT_NAME "ROOT"

FProfileDataProcessRunnable* SluaProfilerDataManager::ProcessRunnable;

void SluaProfilerDataManager::StartManager()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void SluaProfilerDataManager::StopManager()
{
        // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
        // we call this function before unloading the module.
    if (ProcessRunnable)
    {
        ProcessRunnable->StopStreamingRunnable();
        ProcessRunnable = nullptr;
    }
}


void SluaProfilerDataManager::ReceiveProfileData(int hookEvent, int64 time, int lineDefined, FString funcName, FString shortSrc)
{
    if (ProcessRunnable)
    {
        ProcessRunnable->ReceiveProfileData(hookEvent, time, lineDefined, funcName, shortSrc);
    }
}

void SluaProfilerDataManager::ReceiveMemoryData(int hookEvent, TArray<slua::LuaMemInfo>& memInfoList)
{
    if (ProcessRunnable)
    {
        ProcessRunnable->ReceiveMemoryData(hookEvent, memInfoList);
    }
}

void SluaProfilerDataManager::OnClearDataWithCallBack(TFunction<void()>&& Callback)
{
    if (ProcessRunnable)
    {
        ProcessRunnable->OnClearDataWithCallBack(MoveTemp(Callback));
    }
}

void SluaProfilerDataManager::ClearData()
{
    if (ProcessRunnable)
    {
        ProcessRunnable->ClearData();
    }
}


void SluaProfilerDataManager::SaveDataWithData(int CpuViewBeginIndex, int MemViewBeginIndex, ProfileNodeArrayArray& ProfileData, MemNodeInfoList LuaMemNodeList, FString SavePath)
{
    if (!ProcessRunnable)
    {
        ProcessRunnable = new FProfileDataProcessRunnable();
    }
    if (ProcessRunnable)
    {
        ProcessRunnable->SaveDataWithData(CpuViewBeginIndex, MemViewBeginIndex, ProfileData, LuaMemNodeList, SavePath);
    }
}

void SluaProfilerDataManager::BeginRecord()
{
    if (!ProcessRunnable)
    {
        ProcessRunnable = new FProfileDataProcessRunnable();
    }
    if (ProcessRunnable)
    {
        ProcessRunnable->bIsRecording = true;
    }
}

void SluaProfilerDataManager::EndRecord()
{
    if (ProcessRunnable)
    {
        ProcessRunnable->SaveData();
        ProcessRunnable->bIsRecording = false;

    }
}

void SluaProfilerDataManager::SaveData()
{
    if (ProcessRunnable)
    {
        ProcessRunnable->SaveData();
    }
}

//打开保存的sluastat文件
void SluaProfilerDataManager::LoadData(const TArray<uint8>& FileData, int& CpuViewBeginIndex, int& MemViewBeginIndex, ProfileNodeArrayArray& ProfileData, MemNodeInfoList& LuaMemNodeList)
{
    if (!ProcessRunnable)
    {
        ProcessRunnable = new FProfileDataProcessRunnable();
    }
    if (ProcessRunnable)
    {
        ProcessRunnable->LoadData(FileData, CpuViewBeginIndex, MemViewBeginIndex, ProfileData, LuaMemNodeList);
    }
}

void SluaProfilerDataManager::InitProfileNode(TSharedPtr<FunctionProfileNode>& funcNode, const FString& funcName, int32 layerIdx)
{
    funcNode = MakeShared<FunctionProfileNode>();
    funcNode->functionName = funcName;
    funcNode->costTime = 0;
    funcNode->childNode = MakeShared<TMap<FString, TSharedPtr<FunctionProfileNode>>>();
    funcNode->layerIdx = layerIdx;
    funcNode->countOfCalls = 0;
}

void SluaProfilerDataManager::WatchBegin(const FString& funcName, double nanoseconds, ProfileNodePtr funcProfilerRoot, ProfileCallInfoArray& profilerStack)
{
    TSharedPtr<FunctionProfileCallInfo> funcInfo = MakeShared<FunctionProfileCallInfo>();
    funcInfo->functionName = funcName;
    funcInfo->begTime = nanoseconds;
    funcInfo->bIsCoroutineBegin = false;
    TSharedPtr<FunctionProfileNode> funcInfoNode = funcProfilerRoot;
    if (profilerStack.Num()) {
        funcInfoNode = profilerStack.Top()->ProfileNode;
    }
    AddToParentNode(funcInfoNode, funcInfo);
    profilerStack.Add(funcInfo);
}

void SluaProfilerDataManager::WatchEnd(const FString& functionName, double nanoseconds, ProfileCallInfoArray& profilerStack) {
    if (!profilerStack.Num())return;
    TSharedPtr<FunctionProfileCallInfo> callInfo = profilerStack.Top();
    if (callInfo->bIsCoroutineBegin)
    {
        //Return时候遇到协程不对称，可以插入到树的节点之间。
        TSharedPtr<FunctionProfileNode> funcNode = MakeShared<FunctionProfileNode>();
        funcNode->functionName = functionName;
        funcNode->costTime = nanoseconds - callInfo->begTime;
        funcNode->countOfCalls = 1;
        funcNode->layerIdx = callInfo->ProfileNode->layerIdx + 1;
        funcNode->childNode = callInfo->ProfileNode->childNode;
        callInfo->ProfileNode->childNode = MakeShared<TMap<FString, TSharedPtr<FunctionProfileNode>>>();
        callInfo->ProfileNode->childNode->Add(functionName, funcNode);

        return;
    }

    TSharedPtr<FunctionProfileNode> funcInfoNode = callInfo->ProfileNode;
    funcInfoNode->costTime += nanoseconds - callInfo->begTime;
    funcInfoNode->countOfCalls++;

    profilerStack.Pop();
}


void SluaProfilerDataManager::CoroutineBegin(const FString& funcName, double nanoseconds, ProfileNodePtr funcProfilerRoot, ProfileCallInfoArray& profilerStack)
{
    FString functionName = TEXT("coroutine.resume");
    functionName += funcName;
    TSharedPtr<FunctionProfileCallInfo> funcInfo = MakeShared<FunctionProfileCallInfo>();
    funcInfo->functionName = functionName;
    funcInfo->begTime = nanoseconds;
    funcInfo->bIsCoroutineBegin = true;
    TSharedPtr<FunctionProfileNode> funcInfoNode = funcProfilerRoot;
    if (profilerStack.Num()) {
        funcInfoNode = profilerStack.Top()->ProfileNode;
    }
    AddToParentNode(funcInfoNode, funcInfo);
    profilerStack.Add(funcInfo);
}

void SluaProfilerDataManager::CoroutineEnd(double nanoseconds, ProfileCallInfoArray& profilerStack) {
    while (true) {
        if (!profilerStack.Num())break;
        TSharedPtr<FunctionProfileCallInfo> callInfo = profilerStack.Top();

        TSharedPtr<FunctionProfileNode> funcInfoNode = callInfo->ProfileNode;
        funcInfoNode->costTime += nanoseconds - callInfo->begTime;
        funcInfoNode->countOfCalls++;
        profilerStack.Pop();

        if (callInfo->bIsCoroutineBegin)break;
    }
}

void SluaProfilerDataManager::AddToParentNode(TSharedPtr<FunctionProfileNode> patentNode, TSharedPtr<FunctionProfileCallInfo> callInfo)
{
    auto funcName = callInfo->functionName;
    if (funcName.IsEmpty())
    {

    }
    TSharedPtr<FunctionProfileNode> childNode;
    if (patentNode->childNode->Contains(funcName)) {
        childNode = *patentNode->childNode->Find(funcName);
    }
    else
    {
        childNode = MakeShared<FunctionProfileNode>();
        SluaProfilerDataManager::InitProfileNode(childNode, funcName, patentNode->layerIdx + 1);
        patentNode->childNode->Add(funcName, childNode);
    }
    callInfo->ProfileNode = childNode;
}

//////////////////// FProfileDataProcessRunnable BEGIN //////////////////////////////////////////////
FProfileDataProcessRunnable::FProfileDataProcessRunnable()
{
    currentMemory = MakeShared<MemoryFrame>();
    RunnableStart = true;
    cpuViewBeginIndex = 0;
    memViewBeginIndex = 0;
    SluaProfilerDataManager::InitProfileNode(funcProfilerRoot, ROOT_NAME, 0);
    WorkerThread = FRunnableThread::Create(this, TEXT("FProfileDataProcessRunnable"));
}

void FProfileDataProcessRunnable::StopStreamingRunnable()
{
    RunnableStart = false;
    ClearCurProfiler();
    if (WorkerThread)
    {
        WorkerThread->Kill(true);
        delete WorkerThread;
        WorkerThread = nullptr;
    }
}

bool FProfileDataProcessRunnable::Init()
{
    return true;
}

uint32 FProfileDataProcessRunnable::Run()
{
    while (RunnableStart)
    {
        while (!funcProfilerNodeQueue.IsEmpty())
        {
            MemoryFramePtr memoryFrame;
            memoryQueue.Dequeue(memoryFrame);
            TSharedPtr<FunctionProfileNode> funcProfilerNode;
            funcProfilerNodeQueue.Dequeue(funcProfilerNode);
            PreProcessData(funcProfilerNode, memoryInfo, memoryFrame);

            FProfileNodeArray LastProfileData;
            LastProfileData.NodeArray = allProfileData.Last(0);
        }
    }

    return 0;
}

void FProfileDataProcessRunnable::ReceiveProfileData(int hookEvent, int64 time, int lineDefined, FString funcName, FString shortSrc)
{
    if (!bIsRecording)
    {
        return;
    }
    if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_CALL)
    {
        if (lineDefined == -1 && funcName.IsEmpty())
        {
            return;
        }
        FString functionName = shortSrc;
        functionName += ":";
        functionName += FString::FromInt(lineDefined);
        functionName += " ";
        functionName += funcName;
        //UE_LOG(Slua, Log, TEXT("Profile Call %s"), *functionName);

        SluaProfilerDataManager::WatchBegin(functionName, time, funcProfilerRoot, profilerStack);
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_RETURN)
    {
        if (lineDefined == -1 && funcName.IsEmpty())
        {
            return;
        }

        FString functionName = shortSrc;
        functionName += ":";
        functionName += FString::FromInt(lineDefined);
        functionName += " ";
        functionName += funcName;
        //UE_LOG(Slua, Log, TEXT("Profile Return %s"), *functionName);

        SluaProfilerDataManager::WatchEnd(functionName, time, profilerStack);
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_TICK)
    {
        funcProfilerNodeQueue.Enqueue(funcProfilerRoot);
        memoryQueue.Enqueue(currentMemory);
        ClearCurProfiler();
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_ENTER_COROUTINE)
    {
        FString functionName = TEXT("");
        functionName += ":";
        functionName += FString::FromInt(lineDefined);
        functionName += " ";
        functionName += funcName;

        //UE_LOG(Slua, Log, TEXT("Profile CoBegin %s"), *functionName);

        SluaProfilerDataManager::CoroutineBegin(functionName, time, funcProfilerRoot, profilerStack);
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_EXIT_COROUTINE)
    {
        //UE_LOG(Slua, Log, TEXT("Profile CoEnd"));
        SluaProfilerDataManager::CoroutineEnd(time, profilerStack);
    }
}

void FProfileDataProcessRunnable::ReceiveMemoryData(int hookEvent, TArray<slua::LuaMemInfo>& memInfoList)
{
    if (!bIsRecording)
    {
        return;
    }

    if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_MEMORY_TICK)
    {
        currentMemory->memoryInfoList = memInfoList;
        currentMemory->bMemoryTick = true;
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_MEMORY_INCREACE)
    {
        currentMemory->memoryIncrease = memInfoList;
    }
}

void FProfileDataProcessRunnable::OnClearDataWithCallBack(TFunction<void()>&& Callback)
{
    if (RunnableStart)
    {
        ClearData();
        Callback();
    }
}

void FProfileDataProcessRunnable::ClearData()
{
    RestartMemoryStatistis();
    profileRootArr.Empty();
    allProfileData.Empty();
    cpuViewBeginIndex = 0;
    memViewBeginIndex = 0;
    funcProfilerNodeQueue.Empty();
}


void FProfileDataProcessRunnable::SaveData()
{
    SaveDataWithData(cpuViewBeginIndex, memViewBeginIndex, allProfileData, allLuaMemNodeList, "");
}


void FProfileDataProcessRunnable::SaveDataWithData(int CpuViewBeginIndex, int MemViewBeginIndex, ProfileNodeArrayArray& ProfileData, MemNodeInfoList& LuaMemNodeList, FString SavePath)
{
    UE_LOG(Slua, Log, TEXT("BEGIN SAVE DATA"));
    bool tempRecording = bIsRecording;
    bIsRecording = false;
    FDateTime Now = FDateTime::Now();
    FString FilePath = FPaths::ProfilingDir() + "/Sluastats/"
        / FString::FromInt(Now.GetYear()) + FString::FromInt(Now.GetMonth()) + FString::FromInt(Now.GetDay())
        + FString::FromInt(Now.GetHour()) + FString::FromInt(Now.GetMinute()) + FString::FromInt(Now.GetSecond())
        + FString::FromInt(Now.GetMillisecond()) + SavePath + ".sluastat";
    FBufferArchive* BufferArchive = new FBufferArchive();

    SerializeSave(BufferArchive, CpuViewBeginIndex, MemViewBeginIndex, ProfileData, LuaMemNodeList);

    TArray<uint8> CompressDateLZ4;

    UE_LOG(Slua, Log, TEXT("BEGIN COMPRESSED DATA"));

    //FArchiveSaveCompressedProxy( TArray<uint8>& InCompressedData, FName InCompressionFormat, ECompressionFlags InCompressionFlags=COMPRESS_None);
#if (ENGINE_MINOR_VERSION<21) && (ENGINE_MAJOR_VERSION==4)
FArchiveSaveCompressedProxy CompressProxyLZ4 = FArchiveSaveCompressedProxy(CompressDateLZ4, ECompressionFlags::COMPRESS_ZLIB);
#else
    FArchiveSaveCompressedProxy CompressProxyLZ4 = FArchiveSaveCompressedProxy(CompressDateLZ4, NAME_Zlib, ECompressionFlags::COMPRESS_ZLIB);
#endif
    
    CompressProxyLZ4 << *BufferArchive;
    CompressProxyLZ4.Flush();
    UE_LOG(Slua, Log, TEXT("BEGIN SAVE FILE "));

    if (FFileHelper::SaveArrayToFile(CompressDateLZ4, *FilePath))
    {
        CompressProxyLZ4.FlushCache();
        CompressDateLZ4.Empty();
    }

    BufferArchive->FlushCache();
    BufferArchive->Empty();

    BufferArchive->Close();
    CompressProxyLZ4.Close();
    bIsRecording = tempRecording;
    UE_LOG(Slua, Log, TEXT("END SAVE DATA %s"), *FilePath);

}

void FProfileDataProcessRunnable::LoadData(const TArray<uint8>& FileData, int& CpuViewBeginIndex, int& MemViewBeginIndex, ProfileNodeArrayArray& ProfileData, MemNodeInfoList& LuaMemNodeList)
{
    if (RunnableStart)
    {
        bool tempRecording = bIsRecording;
        bIsRecording = false;
        FBufferArchive BufAr;
#if (ENGINE_MINOR_VERSION<19) && (ENGINE_MAJOR_VERSION==4)
        FArchiveLoadCompressedProxy DecompressProxy = FArchiveLoadCompressedProxy(FileData, ECompressionFlags::COMPRESS_ZLIB);
#else
        FArchiveLoadCompressedProxy DecompressProxy = FArchiveLoadCompressedProxy(FileData, NAME_Zlib, ECompressionFlags::COMPRESS_ZLIB);
#endif
        DecompressProxy << BufAr;
        DeserializeCompressedSave(&BufAr, CpuViewBeginIndex, MemViewBeginIndex, ProfileData, LuaMemNodeList);
        bIsRecording = tempRecording;
    }
}

void FProfileDataProcessRunnable::SerializeSave(FBufferArchive* BufferArchive, int CpuViewBeginIndex, int MemViewBeginIndex, ProfileNodeArrayArray& ProfileData, MemNodeInfoList& LuaMemNodeList)
{
    UE_LOG(Slua, Log, TEXT("BEGIN SerializeSave ProfileNum : %d, CpuViewBeginIndex: %d, "), ProfileData.Num(), CpuViewBeginIndex);
    BufferArchive->Seek(0);
    *BufferArchive << ProfileVersion;
    *BufferArchive << CpuViewBeginIndex;
    int32 allDataLen = ProfileData.Num();
    *BufferArchive << allDataLen;
    TSharedPtr<FunctionProfileNode> emptyNode = MakeShared<FunctionProfileNode>();
    //cpu
    for (int i = 0; i < allDataLen; i++) {
        auto& arr = ProfileData[i];
        int32 arrLen = ProfileData[i].Num();
        *BufferArchive << arrLen;
        for (int j = 0; j < arrLen; j++)
        {
            arr[j]->Serialize(*BufferArchive);
        }
    }

    // mem
    int MemLen = LuaMemNodeList.Num();
    *BufferArchive << MemLen;
    *BufferArchive << MemViewBeginIndex;

    UE_LOG(Slua, Log, TEXT("BEGIN SerializeSave MemLen : %d"), MemLen);

    for (int32 i = 0; i < MemLen; ++i)
    {
        FProflierMemNode* MemNode = LuaMemNodeList[i].Get();
        *BufferArchive << MemNode->totalSize;

        TMap<FString, TMap<int, TSharedPtr<FileMemInfo>>> InfoMap = MemNode->infoList;
        int32 InfoMapNum = InfoMap.Num();
        *BufferArchive << InfoMapNum;

        for (auto Iter = InfoMap.CreateIterator(); Iter; ++Iter)
        {
            *BufferArchive << Iter->Key;

            TMap<int, TSharedPtr<FileMemInfo>> InnerMap = Iter->Value;
            int32 InnerMapNum = InnerMap.Num();
            *BufferArchive << InnerMapNum;
            for (auto InnerIter = InnerMap.CreateIterator(); InnerIter; ++InnerIter)
            {
                *BufferArchive << InnerIter->Key;
                InnerIter->Value->Serialize(*BufferArchive);
            }
        }
        TMap<FString, TSharedPtr<FileMemInfo>> ParentFileMap = MemNode->parentFileMap;
        int32 ParentFileMapNum = InfoMap.Num();;
        *BufferArchive << ParentFileMapNum;
        for (auto Iter = ParentFileMap.CreateIterator(); Iter; ++Iter)
        {
            *BufferArchive << Iter->Key;
            Iter->Value->Serialize(*BufferArchive);
        }
    }
    int64 BufferSize = BufferArchive->TotalSize();
    *BufferArchive << BufferSize;
    UE_LOG(Slua, Log, TEXT("SerializeSave end Buffer:%d"), BufferSize);
}

void FProfileDataProcessRunnable::DeserializeCompressedSave(FBufferArchive* BufAr, int& CpuViewBeginIndex, int& MemViewBeginIndex, ProfileNodeArrayArray& ProfileData, MemNodeInfoList& LuaMemNodeList)
{
    UE_LOG(Slua, Log, TEXT("DeserializeCompressedSave"));
    FMemoryReader* MemoryReader = new FMemoryReader(*BufAr, true);
    MemoryReader->Seek(0);
    int32 Version;
    *MemoryReader << Version;
    int64 ArSize = MemoryReader->TotalSize();
    if (Version != ProfileVersion)
    {
        UE_LOG(Slua, Warning, TEXT("DeserializeCompressedSave version mismatch: %d, %d"), Version, ProfileVersion);
        return;
    }

    //cpu
    *MemoryReader << CpuViewBeginIndex;

    int32 allDataLen = 0;
    *MemoryReader << allDataLen;
    ProfileData.Empty(allDataLen);
    //cpu
    for (int i = 0; i < allDataLen; i++) {
        TArray<TSharedPtr<FunctionProfileNode>> arr;
        int32 arrLen = 0;
        *MemoryReader << arrLen;

        for (int j = 0; j < arrLen; j++)
        {
            TSharedPtr<FunctionProfileNode> node = MakeShared<FunctionProfileNode>();
            node->Serialize(*MemoryReader);
            arr.Add(node);
        }
        ProfileData.Add(MoveTemp(arr));
    }

    // mem

    int32 MemNodeCount;
    *MemoryReader << MemNodeCount;
    *MemoryReader << MemViewBeginIndex;
    LuaMemNodeList.Empty();
    for (int32 i = 0; i < MemNodeCount; ++i)
    {
        float MemNodeTotalSize;
        *MemoryReader << MemNodeTotalSize;

        int32 InfoMapNum;
        *MemoryReader << InfoMapNum;

        TMap<FString, TMap<int, TSharedPtr<FileMemInfo>>> InfoMap;
        for (int j = 0; j < InfoMapNum; ++j)
        {
            FString InfoMapKey;
            *MemoryReader << InfoMapKey;

            int32 InnerMapNum;
            *MemoryReader << InnerMapNum;

            TMap<int, TSharedPtr<FileMemInfo>> InnerMap;
            for (int k = 0; k < InnerMapNum; ++k)
            {
                int InnerMapKey;
                *MemoryReader << InnerMapKey;

                FileMemInfo* Info = new FileMemInfo();
                Info->Serialize(*MemoryReader);
                InnerMap.Add(InnerMapKey, MakeShareable(Info));
            }
            InfoMap.Add(InfoMapKey, InnerMap);
        }

        int32 ParentFileMapNum;
        *MemoryReader << ParentFileMapNum;

        TMap<FString, TSharedPtr<FileMemInfo>> ParentFileMap;
        for (int j = 0; j < ParentFileMapNum; ++j)
        {
            FString ParentFileMapKey;
            *MemoryReader << ParentFileMapKey;
            FileMemInfo* Info = new FileMemInfo();
            Info->Serialize(*MemoryReader);
            ParentFileMap.Add(ParentFileMapKey, MakeShareable(Info));
        }


        FProflierMemNode* Node = new FProflierMemNode();
        Node->infoList = InfoMap;
        Node->parentFileMap = ParentFileMap;
        Node->totalSize = MemNodeTotalSize;
        LuaMemNodeList.Add(MakeShareable(Node));
    }
    UE_LOG(Slua, Warning, TEXT("DeserializeSave end: %d"), ArSize);
}

void FProfileDataProcessRunnable::ClearCurProfiler()
{
    SluaProfilerDataManager::InitProfileNode(funcProfilerRoot, ROOT_NAME, 0);
    currentMemory = MakeShared<MemoryFrame>();
    currentMemory->bMemoryTick = false;
    profilerStack.Empty();
}

void FProfileDataProcessRunnable::initLuaMemChartList()
{
    for (int32 i = 0; i < cMaxSampleNum; i++)
    {
        TSharedPtr<FProflierMemNode> memNode = MakeShared<FProflierMemNode>();
        memNode->totalSize = -1.0f;
        allLuaMemNodeList.Add(memNode);
    }

    TSharedPtr<FProflierMemNode> memNode = MakeShared<FProflierMemNode>();
    memNode->totalSize = 0.0f;
    allLuaMemNodeList.Add(memNode);
    memViewBeginIndex = 0;
}

void FProfileDataProcessRunnable::RestartMemoryStatistis()
{
    allLuaMemNodeList.Empty();
    memViewBeginIndex = 0;
    lastLuaTotalMemSize = 0.0f;

    initLuaMemChartList();
}

void FProfileDataProcessRunnable::CollectMemoryNode(TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame)
{

    if (!memoryFrame.IsValid())
        return;

    TSharedPtr<FProflierMemNode> memNode = MakeShared<FProflierMemNode>();

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

        for (auto& memoInfo : memoryFrame->memoryInfoList)
        {
            OnAllocMemory(memoInfo);
        }
    }
    else if (lastLuaMemNode.IsValid())
    {
        //copy lastLuaMemNode to memNode
        FProflierMemNode& last = *lastLuaMemNode;
        FProflierMemNode& current = *memNode;
        current.totalSize = last.totalSize;

        current.infoList.Reserve(last.infoList.Num());
        for (auto& fileInfoIter : last.infoList)
        {
            auto& newInfoList = current.infoList.Add(fileInfoIter.Key);
            newInfoList.Reserve(fileInfoIter.Value.Num());
            for (auto& lineInfo : fileInfoIter.Value)
            {
                FileMemInfo* memInfo = new FileMemInfo();
                *memInfo = *lineInfo.Value;
                newInfoList.Add(lineInfo.Key, MakeShareable(memInfo));
            }
        }

        current.parentFileMap.Reserve(last.parentFileMap.Num());
        for (auto& parentFileIter : last.parentFileMap)
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

//处理传过来的数据,Tick里调用
void FProfileDataProcessRunnable::PreProcessData(TSharedPtr<FunctionProfileNode> funcInfoRoot, TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame)
{
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
    allLuaMemNodeList.Add(lastLuaMemNode);
    if (cpuViewBeginIndex + cMaxSampleNum + cRefreshDisCount > allProfileData.Num())
    {
        if (allProfileData.Num() > cMaxSampleNum + cpuViewBeginIndex)
        {
            cpuViewBeginIndex++;
            profileRootArr = tempProfileRootArr;
        }
    }
    if (memViewBeginIndex + cMaxSampleNum + cRefreshDisCount > allLuaMemNodeList.Num())
    {
        if (allLuaMemNodeList.Num() > cMaxSampleNum + memViewBeginIndex)
        {
            memViewBeginIndex++;
        }
    }
}

//////////////////// FProfileDataProcessRunnable  END //////////////////////////////////////////////