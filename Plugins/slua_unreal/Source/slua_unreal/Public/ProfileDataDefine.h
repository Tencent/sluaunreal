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
typedef TMap<uint32, TMap<int, TSharedPtr<FileMemInfo>>> MemFileInfoMap;
typedef TArray<TSharedPtr<FProflierMemNode>> MemNodeInfoList;
typedef TArray<TSharedPtr<FileMemInfo>> ShownMemInfoList;
typedef TMap<uint32, TSharedPtr<FileMemInfo>> ParentFileMap;
typedef TArray<TArray<TSharedPtr<FunctionProfileNode>>> ProfileNodeArrayArray;

static const int cMaxSampleNum = 250;
static const int cMaxViewHeight = 200;
static const int cRefreshDisCount = 10;
static int32 ProfileVersion = 4;

USTRUCT()
struct SLUA_UNREAL_API FProfileNodeArray
{
    GENERATED_BODY();

public:
    TArray<TSharedPtr<FunctionProfileNode>> NodeArray;

    void Serialize(FArchive& Ar);
};

USTRUCT()
struct SLUA_UNREAL_API FProfileNameSet
{
    GENERATED_BODY()

    static constexpr uint32 InvalidIndex = 0;
    static FProfileNameSet* GlobalProfileNameSet;

    UPROPERTY()
    TMap<uint32, FString> indexToString;

    UPROPERTY()
    TMap<FString, uint32> stringToIndex;

    UPROPERTY()
    TSet<uint32> indexSet;

    uint32 GetOrCreateIndex(const FString& content)
    {
        uint32* indexPtr = stringToIndex.Find(content);
        if (indexPtr)
        {
            return *indexPtr;
        }

        uint32 hashKey = GetTypeHash(content);
        while (indexSet.Contains(hashKey) && hashKey != InvalidIndex)
        {
            hashKey++;
        }

        stringToIndex.Emplace(content, hashKey);
        indexToString.Emplace(hashKey, content);

        return hashKey;
    }

    uint32 GetIndex(const FString& content)
    {
        uint32* indexPtr = stringToIndex.Find(content);
        if (indexPtr)
        {
            return *indexPtr;
        }

        return InvalidIndex;
    }

    FString GetStringByIndex(uint32 index)
    {
        FString* content = indexToString.Find(index);
        if (content)
        {
            return *content;
        }

        return TEXT("");
    }

    friend FArchive& operator<<(FArchive& Ar, FProfileNameSet& ProfileNameSet)
    {
        Ar << ProfileNameSet.indexToString;
        Ar << ProfileNameSet.stringToIndex;
        Ar << ProfileNameSet.indexSet;
        return Ar;
    }
};

USTRUCT()
struct SLUA_UNREAL_API FileMemInfo {
    GENERATED_BODY();

public:
    UPROPERTY()
        uint32 fileNameIndex = 0;
    UPROPERTY()
        int32 lineNumber = 0;
    UPROPERTY()
        float size = 0;

    // one line memory difference between two point
    UPROPERTY()
        float difference = 0;

    friend uint32 GetTypeHash(const FileMemInfo& fileMemInfo)
    {
        return fileMemInfo.fileNameIndex;
    }

    bool operator == (const FileMemInfo& other) const
    {
        return fileNameIndex == other.fileNameIndex;
    }

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
struct SLUA_UNREAL_API FLuaFunctionDefine
{
    GENERATED_BODY()

public:
    static FLuaFunctionDefine* Root;
    static FLuaFunctionDefine* Other;

    UPROPERTY()
    uint32 fileNameIndex = 0;

    UPROPERTY()
    uint32 functionNameIndex = 0;

    UPROPERTY()
    int32 lineDefined = -1;

    FString GetFileName() const
    {
        ensure(FProfileNameSet::GlobalProfileNameSet);
        return FProfileNameSet::GlobalProfileNameSet->GetStringByIndex(fileNameIndex);
    }

    FString GetFunctionName() const
    {
        ensure(FProfileNameSet::GlobalProfileNameSet);
        return FProfileNameSet::GlobalProfileNameSet->GetStringByIndex(functionNameIndex);
    }

    FString GetFullName() const
    {
        if (this == Other)
        {
            return TEXT("Other");
        }
        else if (this == Root)
        {
            return TEXT("ROOT");
        }
        return FString::Printf(TEXT("%s:%d %s"), *GetFileName(), lineDefined, *GetFunctionName());
    }

    static FLuaFunctionDefine MakeLuaFunctionDefine(const FString& fileName, const FString& functionName, int32 lineDefined)
    {
        ensure(FProfileNameSet::GlobalProfileNameSet);
        uint32 fileNameIndex = FProfileNameSet::GlobalProfileNameSet->GetOrCreateIndex(fileName);
        uint32 functionNameIndex = FProfileNameSet::GlobalProfileNameSet->GetOrCreateIndex(functionName);
        return {fileNameIndex, functionNameIndex, lineDefined};
    }

    friend uint32 GetTypeHash(const FLuaFunctionDefine& luaFunctionDefine)
    {
        return luaFunctionDefine.fileNameIndex * luaFunctionDefine.functionNameIndex + luaFunctionDefine.lineDefined;
    }

    bool operator == (const FLuaFunctionDefine& other) const
    {
        return fileNameIndex == other.fileNameIndex && functionNameIndex == other.functionNameIndex && lineDefined == other.lineDefined;
    }

    friend FArchive& operator<<(FArchive& Ar, FLuaFunctionDefine& A)
    {
        Ar << A.fileNameIndex;
        Ar << A.functionNameIndex;
        Ar << A.lineDefined;
        return Ar;
    }
};

USTRUCT()
struct SLUA_UNREAL_API FunctionProfileNode
{
    GENERATED_BODY();

    typedef TMap<FLuaFunctionDefine, TSharedPtr<FunctionProfileNode>> FChildNode;
    typedef TSharedPtr<TMap<FLuaFunctionDefine, TSharedPtr<FunctionProfileNode>>> FChildNodePtr;

    UPROPERTY()
        FLuaFunctionDefine functionDefine;
    UPROPERTY()
        int64 costTime = 0;
    UPROPERTY()
        int32 countOfCalls = 0;
    UPROPERTY()
        int32 layerIdx = 0;

    FChildNodePtr childNode = MakeShareable(new FChildNode());

    void Serialize(FArchive& Ar);

    void CopyData(TSharedPtr<FunctionProfileNode> NewData);
};


USTRUCT()
struct SLUA_UNREAL_API FunctionProfileCallInfo
{
    GENERATED_BODY();
    UPROPERTY()
        FLuaFunctionDefine functionDefine;

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
