#include "SluaProfilerDataManager.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Misc/FileHelper.h"
#include "Log.h"
#include "LuaProfiler.h"
#include "Serialization/MemoryReader.h"
#include "Misc/Paths.h"
#include "Misc/ScopedSlowTask.h"
#include <LuaState.h>

#include "HAL/RunnableThread.h"
#define ROOT_NAME "ROOT"

FProfileDataProcessRunnable* SluaProfilerDataManager::ProcessRunnable;
FProfileNameSet* SluaProfilerDataManager::ProfileNameSet;

void SluaProfilerDataManager::StartManager()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    FProfileNameSet::GlobalProfileNameSet = new FProfileNameSet();
    *FLuaFunctionDefine::Root = FLuaFunctionDefine::MakeLuaFunctionDefine(ROOT_NAME, TEXT(""), -1);
    *FLuaFunctionDefine::Other = FLuaFunctionDefine::MakeLuaFunctionDefine(TEXT("Other"), TEXT(""), -1);
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

    if (FProfileNameSet::GlobalProfileNameSet)
    {
        delete FProfileNameSet::GlobalProfileNameSet;
        FProfileNameSet::GlobalProfileNameSet = nullptr;
    }
}


void SluaProfilerDataManager::ReceiveProfileData(int hookEvent, int64 time, int lineDefined, const FString& funcName, const FString& shortSrc)
{
    if (ProcessRunnable)
    {
        ProcessRunnable->ReceiveProfileData(hookEvent, time, lineDefined, funcName, shortSrc);
    }
}

void SluaProfilerDataManager::ReceiveMemoryData(int hookEvent, const TArray<NS_SLUA::LuaMemInfo>& memInfoList)
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


void SluaProfilerDataManager::SaveDataWithData(int inCpuViewBeginIndex, int inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, const MemNodeInfoList& inLuaMemNodeList)
{
    if (!ProcessRunnable)
    {
        ProcessRunnable = new FProfileDataProcessRunnable();
    }
    if (ProcessRunnable)
    {
        ProcessRunnable->SaveDataWithData(inCpuViewBeginIndex, inMemViewBeginIndex, inProfileData, inLuaMemNodeList);
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
        ProcessRunnable->StartRecord();
    }
}

void SluaProfilerDataManager::EndRecord()
{
    if (ProcessRunnable)
    {
        ProcessRunnable->StopRecord();

    }
}

bool SluaProfilerDataManager::IsRecording()
{
    if (ProcessRunnable)
    {
        return ProcessRunnable->IsRecording();
    }

    return false;
}

//打开保存的sluastat文件
void SluaProfilerDataManager::LoadData(const FString& filePath, int& inCpuViewBeginIndex, int& inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, MemNodeInfoList& inLuaMemNodeList)
{
    if (!ProcessRunnable)
    {
        ProcessRunnable = new FProfileDataProcessRunnable();
    }
    if (ProcessRunnable)
    {
        ProcessRunnable->LoadData(filePath, inCpuViewBeginIndex, inMemViewBeginIndex, inProfileData, inLuaMemNodeList);
    }
}

void SluaProfilerDataManager::InitProfileNode(TSharedPtr<FunctionProfileNode>& funcNode, const FLuaFunctionDefine& funcDefine, int32 layerIdx)
{
    funcNode = MakeShared<FunctionProfileNode>();
    funcNode->functionDefine = funcDefine;
    funcNode->costTime = 0;
    funcNode->childNode = MakeShared<FunctionProfileNode::FChildNode>();
    funcNode->layerIdx = layerIdx;
    funcNode->countOfCalls = 0;
}

void SluaProfilerDataManager::WatchBegin(const FString& fileName, int32 lineDefined, const FString& funcName, double nanoseconds, ProfileNodePtr funcProfilerRoot, ProfileCallInfoArray& profilerStack)
{
    TSharedPtr<FunctionProfileCallInfo> funcInfo = MakeShared<FunctionProfileCallInfo>();
    funcInfo->functionDefine = FLuaFunctionDefine::MakeLuaFunctionDefine(fileName, funcName, lineDefined);
    funcInfo->begTime = nanoseconds;
    funcInfo->bIsCoroutineBegin = false;
    TSharedPtr<FunctionProfileNode> funcInfoNode = funcProfilerRoot;
    if (profilerStack.Num()) {
        funcInfoNode = profilerStack.Top()->ProfileNode;
    }
    AddToParentNode(funcInfoNode, funcInfo);
    profilerStack.Add(funcInfo);
}

void SluaProfilerDataManager::WatchEnd(const FString& fileName, int32 lineDefined, const FString& functionName, double nanoseconds, ProfileCallInfoArray& profilerStack) {
    if (!profilerStack.Num())return;
    TSharedPtr<FunctionProfileCallInfo> callInfo = profilerStack.Top();
    if (callInfo->bIsCoroutineBegin)
    {
        //Return时候遇到协程不对称，可以插入到树的节点之间。
        TSharedPtr<FunctionProfileNode> funcNode = MakeShared<FunctionProfileNode>();
        funcNode->functionDefine = FLuaFunctionDefine::MakeLuaFunctionDefine(fileName, functionName, lineDefined);;
        funcNode->costTime = nanoseconds - callInfo->begTime;
        funcNode->countOfCalls = 1;
        funcNode->layerIdx = callInfo->ProfileNode->layerIdx + 1;
        funcNode->childNode = callInfo->ProfileNode->childNode;
        callInfo->ProfileNode->childNode = MakeShared<FunctionProfileNode::FChildNode>();
        callInfo->ProfileNode->childNode->Add(funcNode->functionDefine, funcNode);

        return;
    }

    TSharedPtr<FunctionProfileNode> funcInfoNode = callInfo->ProfileNode;
    funcInfoNode->costTime += nanoseconds - callInfo->begTime;
    funcInfoNode->countOfCalls++;

    profilerStack.Pop();
}


void SluaProfilerDataManager::CoroutineBegin(int32 lineDefined, const FString& funcName, double nanoseconds, ProfileNodePtr funcProfilerRoot, ProfileCallInfoArray& profilerStack)
{
    FString functionName = TEXT("coroutine.resume");
    functionName += funcName;
    TSharedPtr<FunctionProfileCallInfo> funcInfo = MakeShared<FunctionProfileCallInfo>();
    funcInfo->functionDefine = FLuaFunctionDefine::MakeLuaFunctionDefine(TEXT(""), funcName, lineDefined);
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

        if (callInfo->bIsCoroutineBegin)
        {
            break;
        }
    }
}

void SluaProfilerDataManager::AddToParentNode(TSharedPtr<FunctionProfileNode> patentNode, TSharedPtr<FunctionProfileCallInfo> callInfo)
{
    auto funcDefine = callInfo->functionDefine;
    TSharedPtr<FunctionProfileNode> childNode;
    if (patentNode->childNode->Contains(funcDefine)) {
        childNode = *patentNode->childNode->Find(funcDefine);
    }
    else
    {
        childNode = MakeShared<FunctionProfileNode>();
        SluaProfilerDataManager::InitProfileNode(childNode, funcDefine, patentNode->layerIdx + 1);
        patentNode->childNode->Add(funcDefine, childNode);
    }
    callInfo->ProfileNode = childNode;
}

//////////////////// FProfileDataProcessRunnable BEGIN //////////////////////////////////////////////
FProfileDataProcessRunnable::FProfileDataProcessRunnable()
{
    currentMemory = MakeShared<MemoryFrame>();
    RunnableStart = true;
    SluaProfilerDataManager::InitProfileNode(funcProfilerRoot, *FLuaFunctionDefine::Root, 0);
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
        ProcessCommands();

        while (bCanStartFrameRecord && frameArchive && !funcProfilerNodeQueue.IsEmpty())
        {
            MemoryFramePtr memoryFrame;
            memoryQueue.Dequeue(memoryFrame);
            TSharedPtr<FunctionProfileNode> funcProfilerNode;
            funcProfilerNodeQueue.Dequeue(funcProfilerNode);
            PreProcessData(funcProfilerNode, memoryInfo, memoryFrame);
        }

        if (!bIsRecording && bCanStartFrameRecord && frameArchive)
        {
            uint8 saveMode = FSaveMode::EndOfFrame;
            FMemoryWriter memoryWriter(dataToCompress);
            memoryWriter.Seek(dataToCompress.Num());
            memoryWriter << saveMode;

            // Save the remaining data.
            SerializeCompreesedDataToFile(*frameArchive);

            frameArchive->Close();
            delete frameArchive;
            frameArchive = nullptr;
        }
    }

    return 0;
}

void FProfileDataProcessRunnable::ReceiveProfileData(int hookEvent, int64 time, int lineDefined, const FString& funcName, const FString& shortSrc)
{
    if (!bIsRecording)
    {
        return;
    }
    cpuCommandQueue.Enqueue({hookEvent, time, lineDefined, funcName, shortSrc});
    commandTypeQueue.Enqueue(FCommandType::ECPU);
}

void FProfileDataProcessRunnable::ReceiveMemoryData(int hookEvent, const TArray<NS_SLUA::LuaMemInfo>& memInfoList)
{
    if (!bIsRecording)
    {
        return;
    }
    memoryCommandQueue.Enqueue({hookEvent, memInfoList});
    commandTypeQueue.Enqueue(FCommandType::EMemory);
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
    funcProfilerNodeQueue.Empty();
}

void FProfileDataProcessRunnable::StartRecord()
{
    if (bIsRecording || frameArchive)
    {
        return;
    }

    bCanStartFrameRecord = false;
    memoryFrameNum = -1;
    bIsRecording = true;
    memoryInfo.Empty();
    lastLuaMemNode.Reset();
    memoryQueue.Empty();
    funcProfilerNodeQueue.Empty();
    
    FString filePath = GenerateStatFilePath();
    frameArchive = IFileManager::Get().CreateFileWriter(*filePath);

    *frameArchive << ProfileVersion;
    int beginIndex = 0;
    *frameArchive << beginIndex << beginIndex;

    bFrameFirstRecord = true;
    bCanStartFrameRecord = true;
}

void FProfileDataProcessRunnable::StopRecord()
{
    bIsRecording = false;
}

bool FProfileDataProcessRunnable::IsRecording() const
{
    return bIsRecording;
}

void FProfileDataProcessRunnable::ProcessCommands()
{
    while (!commandTypeQueue.IsEmpty())
    {
        FCommandType commandType;
        commandTypeQueue.Dequeue(commandType);
        switch (commandType)
        {
        case ECPU:
            {
                FCPUCommand cpuCommand;
                cpuCommandQueue.Dequeue(cpuCommand);
                ProcessCPUCommand(cpuCommand);
            }
            break;
        case EMemory:
            {
                FMemoryCommand memoryCommand;
                memoryCommandQueue.Dequeue(memoryCommand);
                ProcessMemoryCommand(memoryCommand);
            }
            break;
        default:
            break;
        }
    }
}

void FProfileDataProcessRunnable::ProcessCPUCommand(const FCPUCommand& cpuCommand)
{
    auto hookEvent = cpuCommand.hookEvent;
    auto time = cpuCommand.time;
    auto lineDefined = cpuCommand.lineDefined;
    auto& funcName = cpuCommand.funcName;
    auto& shortSrc = cpuCommand.shortSrc;

    if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_CALL)
    {
        if (lineDefined == -1 && funcName.IsEmpty())
        {
            return;
        }

        SluaProfilerDataManager::WatchBegin(shortSrc, lineDefined, funcName, time, funcProfilerRoot, profilerStack);
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_RETURN)
    {
        if (lineDefined == -1 && funcName.IsEmpty())
        {
            return;
        }

        SluaProfilerDataManager::WatchEnd(shortSrc, lineDefined, funcName, time, profilerStack);
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_TICK)
    {
        funcProfilerNodeQueue.Enqueue(funcProfilerRoot);
        memoryQueue.Enqueue(currentMemory);

        ClearCurProfiler();
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_ENTER_COROUTINE)
    {
        //UE_LOG(Slua, Log, TEXT("Profile CoBegin %s"), *functionName);
        SluaProfilerDataManager::CoroutineBegin(lineDefined, funcName, time, funcProfilerRoot, profilerStack);
    }
    else if (hookEvent == NS_SLUA::ProfilerHookEvent::PHE_EXIT_COROUTINE)
    {
        //UE_LOG(Slua, Log, TEXT("Profile CoEnd"));
        SluaProfilerDataManager::CoroutineEnd(time, profilerStack);
    }
}

void FProfileDataProcessRunnable::ProcessMemoryCommand(const FMemoryCommand& memoryCommand) const
{
    auto hookEvent = memoryCommand.hookEvent;
    auto& memInfoList = memoryCommand.memInfoList;
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

void FProfileDataProcessRunnable::SerializeFrameData(FArchive& ar, TArray<TSharedPtr<FunctionProfileNode>>& frameFuncRootArr, TSharedPtr<FProflierMemNode>& frameMemNode, const TSharedPtr<FProflierMemNode>& preFrameMemNode)
{
    auto& profileNameSet = *FProfileNameSet::GlobalProfileNameSet;
    {
        FScopeLock lock(&profileNameSet.mutex);
        TMap<uint32, FString>& increaseString = profileNameSet.increaseString;
        if (bFrameFirstRecord)
        {
            increaseString = profileNameSet.indexToString;
            bFrameFirstRecord = false;
        }
        ar << increaseString;
        
        if (ar.IsLoading())
        {
            auto& stringToIndex = profileNameSet.stringToIndex;
            auto& indexToString = profileNameSet.indexToString;
            auto& indexSet = profileNameSet.indexSet;
            for (auto iter = increaseString.CreateConstIterator(); iter; ++iter)
            {
                uint32 key = iter.Key();
                const FString& value = iter.Value();
                stringToIndex.Emplace(value, key);
                indexToString.Emplace(key, value);
                indexSet.Add(key);
            }
        }

        increaseString.Empty();
    }

    int32 functionNodeNum = frameFuncRootArr.Num();
    ar << functionNodeNum;
    if (ar.IsLoading())
    {
        frameFuncRootArr.SetNum(functionNodeNum);
        for (int i = 0; i < functionNodeNum; ++i)
        {
            frameFuncRootArr[i] = MakeShared<FunctionProfileNode>();
        }
    }
    for (int i = 0; i < functionNodeNum; ++i)
    {
        auto node = frameFuncRootArr[i];
        node->Serialize(ar);
    }

    bool bCheckPoint = memoryFrameNum % FProflierMemNode::CheckPointSize == 0;
    if (ar.IsLoading())
    {
        double memNodeTotalSize;
        ar << memNodeTotalSize;

        int32 infoMapNum;
        ar << infoMapNum;

        MemFileInfoMap infoMap;
        infoMap.Reserve(infoMapNum);
        for (int j = 0; j < infoMapNum; ++j)
        {
            uint32 infoMapKey;
            ar << infoMapKey;

            int32 innerMapNum;
            ar << innerMapNum;

            TMap<int, TSharedPtr<FileMemInfo>> innerMap;
            innerMap.Reserve(innerMapNum);
            for (int k = 0; k < innerMapNum; ++k)
            {
                int innerMapKey;
                ar << innerMapKey;

                FileMemInfo* info = new FileMemInfo();
                info->Serialize(ar);
                innerMap.Add(innerMapKey, MakeShareable(info));
            }
            infoMap.Add(infoMapKey, innerMap);
        }

        int32 parentFileMapNum;
        ar << parentFileMapNum;

        ParentFileMap parentFileMap;
        parentFileMap.Reserve(parentFileMapNum);
        for (int j = 0; j < parentFileMapNum; ++j)
        {
            uint32 parentFileMapKey;
            ar << parentFileMapKey;
            FileMemInfo* info = new FileMemInfo();
            info->Serialize(ar);
            parentFileMap.Add(parentFileMapKey, MakeShareable(info));
        }

        if (bCheckPoint)
        {
            frameMemNode->infoList = infoMap;
        }
        else
        {
            frameMemNode->changeInfoList = infoMap;
        }

        frameMemNode->parentFileMap = parentFileMap;
        frameMemNode->totalSize = memNodeTotalSize;
    }
    else
    {
        auto memNode = frameMemNode;
        if (!memNode.IsValid())
        {
            memNode = MakeShared<FProflierMemNode>();
        }
        ar << memNode->totalSize;

        MemFileInfoMap& infoMap = bCheckPoint ? memNode->infoList : memNode->changeInfoList;

        int32 infoMapNum = infoMap.Num();
        ar << infoMapNum;

        for (auto Iter = infoMap.CreateIterator(); Iter; ++Iter)
        {
            ar << Iter->Key;

            TMap<int, TSharedPtr<FileMemInfo>>& innerMap = Iter->Value;
            int32 InnerMapNum = innerMap.Num();
            ar << InnerMapNum;
            for (auto innerIter = innerMap.CreateIterator(); innerIter; ++innerIter)
            {
                ar << innerIter->Key;
                innerIter->Value->Serialize(ar);
            }
        }
        ParentFileMap& parentFileMap = memNode->parentFileMap;
        int32 parentFileMapNum = parentFileMap.Num();;
        ar << parentFileMapNum;
        for (auto Iter = parentFileMap.CreateIterator(); Iter; ++Iter)
        {
            ar << Iter->Key;
            Iter->Value->Serialize(ar);
        }
    }
}


void FProfileDataProcessRunnable::SaveDataWithData(int inCpuViewBeginIndex, int inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, const MemNodeInfoList& inLuaMemNodeList)
{
    if (bIsRecording)
    {
        return;
    }
    FString filePath = GenerateStatFilePath();

    FArchive* ar = IFileManager::Get().CreateFileWriter(*filePath);
    *ar << ProfileVersion;
    *ar << inCpuViewBeginIndex << inMemViewBeginIndex;

    dataToCompress.Empty();
    for (int index = 0; index < inProfileData.Num(); ++index)
    {
        auto &tempProfileRootArr = inProfileData[index];
        auto &frameMemNode = inLuaMemNodeList.IsValidIndex(index) ? inLuaMemNodeList[index] : nullptr;
        uint8 saveMode = FSaveMode::Frame;
        FMemoryWriter memoryWriter(dataToCompress);
        memoryWriter.Seek(dataToCompress.Num());
        memoryWriter << saveMode;
        memoryFrameNum = index;
        SerializeFrameData(memoryWriter, tempProfileRootArr, *const_cast<TSharedPtr<FProflierMemNode>*>(&frameMemNode), nullptr);

        if (dataToCompress.Num() > CompressedSize)
        {
            SerializeCompreesedDataToFile(*ar);
        }
    }
    
    uint8 saveMode = FSaveMode::EndOfFrame;
    FMemoryWriter memoryWriter(dataToCompress);
    memoryWriter.Seek(dataToCompress.Num());
    memoryWriter << saveMode;

    // Save the remaining data.
    SerializeCompreesedDataToFile(*ar);
    
    ar->Close();

    delete ar;

    memoryFrameNum = -1;
    UE_LOG(Slua, Log, TEXT("END SAVE DATA %s"), *filePath);
}

FString FProfileDataProcessRunnable::GenerateStatFilePath()
{
    FDateTime now = FDateTime::Now();
    FString filePath = FPaths::ProfilingDir() + "/Sluastats/"
        / FString::FromInt(now.GetYear()) + FString::FromInt(now.GetMonth()) + FString::FromInt(now.GetDay())
        + FString::FromInt(now.GetHour()) + FString::FromInt(now.GetMinute()) + FString::FromInt(now.GetSecond())
        + FString::FromInt(now.GetMillisecond()) + ".sluastat";
    return filePath;
}

void FProfileDataProcessRunnable::LoadData(const FString& filePath, int& inCpuViewBeginIndex, int& inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, MemNodeInfoList& inLuaMemNodeList)
{
    if (bIsRecording)
    {
        return;
    }
    if (RunnableStart)
    {
        FArchive* ar = IFileManager::Get().CreateFileReader(*filePath);

        int32 version;
        *ar << version;
        if (version != ProfileVersion)
        {
            UE_LOG(Slua, Warning, TEXT("sluastat file version mismatch: %d, %d"), version, ProfileVersion);
            return;
        }

        *ar << inCpuViewBeginIndex << inMemViewBeginIndex;

        inProfileData.Empty();
        inLuaMemNodeList.Empty();
        memoryFrameNum = -1;

        TArray<uint8> uncompressedBuffer;
        FScopedSlowTask slowTask(ar->TotalSize());
        slowTask.MakeDialogDelayed(1.0f);
        int64 prePos = 0;
        
        while (!ar->AtEnd())
        {
            int32 uncompressedSize;
            int32 compressedSize;
            *ar << uncompressedSize;
            *ar << compressedSize;
            uncompressedBuffer.Reserve(uncompressedSize);
            uncompressedBuffer.SetNum(uncompressedSize);

            auto compressedBuffer = (uint8*)FMemory::Malloc(compressedSize);
            ar->Serialize(compressedBuffer, compressedSize);
#if (ENGINE_MINOR_VERSION<=21) && (ENGINE_MAJOR_VERSION==4)
            FCompression::UncompressMemory(COMPRESS_ZLIB, uncompressedBuffer.GetData(), uncompressedSize, compressedBuffer, compressedSize);
#else
            FCompression::UncompressMemory(NAME_Oodle, uncompressedBuffer.GetData(), uncompressedSize, compressedBuffer, compressedSize);
#endif
            FMemory::Free(compressedBuffer);

            FMemoryReader memoryReader(uncompressedBuffer);
            SerializeLoad(memoryReader, inCpuViewBeginIndex, inMemViewBeginIndex, inProfileData, inLuaMemNodeList);
            slowTask.EnterProgressFrame(ar->Tell() - prePos, FText::FromString(TEXT("Loading slua stat...")));
            prePos = ar->Tell();
        }
        ar->Close();
        delete ar;
    }
}

void FProfileDataProcessRunnable::SerializeLoad(FArchive& inAR, int& inCpuViewBeginIndex, int& inMemViewBeginIndex, ProfileNodeArrayArray& inProfileData, MemNodeInfoList& inLuaMemNodeList)
{
    uint8 saveMode;
    inAR << saveMode;

    if (saveMode == FSaveMode::Frame)
    {
        TSharedPtr<FProflierMemNode> preNode;
        while (saveMode != FSaveMode::EndOfFrame && !inAR.AtEnd())
        {
            memoryFrameNum++;
            TArray<TSharedPtr<FunctionProfileNode>> arr;
            TSharedPtr<FProflierMemNode> node = MakeShareable(new FProflierMemNode());
            if (inLuaMemNodeList.Num() > 0)
            {
                preNode = inLuaMemNodeList.Last();
            }
            SerializeFrameData(inAR, arr, node, preNode);

            inProfileData.Add(MoveTemp(arr));
            inLuaMemNodeList.Add(node);
            inAR << saveMode;
        }
    }
}

void FProfileDataProcessRunnable::ClearCurProfiler()
{
    SluaProfilerDataManager::InitProfileNode(funcProfilerRoot, *FLuaFunctionDefine::Root, 0);
    currentMemory = MakeShared<MemoryFrame>();
    currentMemory->bMemoryTick = false;
    profilerStack.Empty();
}

void FProfileDataProcessRunnable::RestartMemoryStatistis()
{
    lastLuaTotalMemSize = 0.0f;
}

void FProfileDataProcessRunnable::CollectMemoryNode(TMap<int64, NS_SLUA::LuaMemInfo>& memoryInfoMap, MemoryFramePtr memoryFrame)
{
    if (!memoryFrame.IsValid())
        return;

    memoryFrameNum++;
    TSharedPtr<FProflierMemNode> memNode = MakeShared<FProflierMemNode>();

    auto OnAlloc = [&](uint32 fileNameIndex, MemFileInfoMap& memFileInfoMap, const NS_SLUA::LuaMemInfo& memFileInfo)
    {
        auto& fileInfos = memFileInfoMap.FindOrAdd(fileNameIndex);

        auto lineInfo = fileInfos.Find(memFileInfo.lineNumber);
        if (lineInfo)
        {
            (*lineInfo)->size += memFileInfo.size;
        }
        else
        {
            FileMemInfo* fileInfo = new FileMemInfo();
            fileInfo->fileNameIndex = fileNameIndex;
            fileInfo->lineNumber = memFileInfo.lineNumber;
            fileInfo->size = memFileInfo.size;
            fileInfos.Add(memFileInfo.lineNumber, MakeShareable(fileInfo));
        }
    };

    auto OnAllocMemory = [&](const NS_SLUA::LuaMemInfo& memFileInfo)
    {
        memoryInfoMap.Add(memFileInfo.ptr, memFileInfo);
        lastLuaTotalMemSize += memFileInfo.size;
        uint32 fileNameIndex = FProfileNameSet::GlobalProfileNameSet->GetOrCreateIndex(memFileInfo.hint);
        OnAlloc(fileNameIndex, memNode->infoList, memFileInfo);
        OnAlloc(fileNameIndex, memNode->changeInfoList, memFileInfo);

        auto* parentFileInfo = memNode->parentFileMap.Find(fileNameIndex);
        if (!parentFileInfo)
        {
            FileMemInfo* fileInfo = new FileMemInfo();
            fileInfo->fileNameIndex = fileNameIndex;
            fileInfo->lineNumber = -1;
            fileInfo->size = memFileInfo.size;
            memNode->parentFileMap.Add(fileNameIndex, MakeShareable(fileInfo));
        }
        else
        {
            (*parentFileInfo)->size += memFileInfo.size;
        }
    };

    auto OnFree = [&](uint32 fileNameIndex, MemFileInfoMap& memFileInfoMap, const NS_SLUA::LuaMemInfo& memFileInfo, bool bCheckSize)
    {
        auto fileInfos = memFileInfoMap.Find(fileNameIndex);
        if (fileInfos)
        {
            auto* lineInfo = fileInfos->Find(memFileInfo.lineNumber);
            if (lineInfo)
            {
                (*lineInfo)->size -= memFileInfo.size;
                if (bCheckSize)
                {
                    ensureMsgf((*lineInfo)->size >= 0, TEXT("Error: %s line[%d] size is negative!"), *FProfileNameSet::GlobalProfileNameSet->GetStringByIndex((*lineInfo)->fileNameIndex), memFileInfo.lineNumber);
                    if ((*lineInfo)->size <= 0)
                    {
                        fileInfos->Remove(memFileInfo.lineNumber);
                    }
                }
            }
        }
    };

    auto OnFreeMemory = [&](const NS_SLUA::LuaMemInfo& memFileInfo)
    {
        if (memoryInfoMap.Contains(memFileInfo.ptr))
        {
            memoryInfoMap.Remove(memFileInfo.ptr);
            lastLuaTotalMemSize -= memFileInfo.size;

            uint32 fileNameIndex = FProfileNameSet::GlobalProfileNameSet->GetOrCreateIndex(memFileInfo.hint);
            OnFree(fileNameIndex, memNode->infoList, memFileInfo, true);
            OnFree(fileNameIndex, memNode->changeInfoList, memFileInfo, false);

            auto& parentFileInfo = memNode->parentFileMap.FindChecked(fileNameIndex);
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

    uint8 saveMode = FSaveMode::Frame;
    FMemoryWriter memoryWriter(dataToCompress);
    memoryWriter.Seek(dataToCompress.Num());
    memoryWriter << saveMode;
    SerializeFrameData(memoryWriter, tempProfileRootArr, lastLuaMemNode, nullptr);

    if (dataToCompress.Num() > CompressedSize)
    {
        SerializeCompreesedDataToFile(*frameArchive);
    }
}

void FProfileDataProcessRunnable::SerializeCompreesedDataToFile(FArchive& ar)
{
    int32 uncompressedSize = dataToCompress.Num();
#if (ENGINE_MINOR_VERSION<=21) && (ENGINE_MAJOR_VERSION==4)
    int32 compressedSize = FCompression::CompressMemoryBound(COMPRESS_ZLIB, uncompressedSize);
#else
    int32 compressedSize = FCompression::CompressMemoryBound(NAME_Oodle, uncompressedSize);
#endif
    auto compressedBuffer = (uint8*)FMemory::Malloc(compressedSize);
#if (ENGINE_MINOR_VERSION<=21) && (ENGINE_MAJOR_VERSION==4)
    FCompression::CompressMemory(COMPRESS_ZLIB, compressedBuffer, compressedSize, dataToCompress.GetData(), uncompressedSize);
#else
    FCompression::CompressMemory(NAME_Oodle, compressedBuffer, compressedSize, dataToCompress.GetData(), uncompressedSize);
#endif
    ar << uncompressedSize;
    ar << compressedSize;
    ar.Serialize(compressedBuffer, compressedSize);
    FMemory::Free(compressedBuffer);

    dataToCompress.Empty(dataToCompress.Num());
}

//////////////////// FProfileDataProcessRunnable  END //////////////////////////////////////////////
