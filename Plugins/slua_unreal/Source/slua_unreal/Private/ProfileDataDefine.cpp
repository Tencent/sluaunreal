#include "ProfileDataDefine.h"

void FProfileNodeArray::Serialize(FArchive& Ar)
{
    if (Ar.IsLoading())
    {
        int32 childNum = 0;
        Ar << childNum;
        NodeArray.Reserve(childNum);

        for (int i = 0; i < childNum; ++i)
        {
            FString name;
            TSharedPtr<FunctionProfileNode> node = MakeShared<FunctionProfileNode>();
            node->Serialize(Ar);
            NodeArray.Add(node);
        }
    }
    else if (Ar.IsSaving())
    {
        int32 childNum = NodeArray.Num();
        Ar << childNum;

        for (auto node : NodeArray)
        {
            if(node.IsValid())
            {
                node->Serialize(Ar);
            }
            else
            {
                TSharedPtr<FunctionProfileNode> emptyNode = MakeShared<FunctionProfileNode>();
                emptyNode->Serialize(Ar);
            }
        }
    }
}

void FileMemInfo::Serialize(FArchive& Ar)
{
    Ar << hint;
    Ar << lineNumber;
    Ar << size;
    Ar << difference;
}


void FProflierMemNode::Serialize(FArchive& Ar)
{
    Ar << totalSize;

    if (Ar.IsLoading())
    {
        infoList.Empty();
        int32 infoChildNum = 0;
        Ar << infoChildNum;
        for (int i = 0; i < infoChildNum; ++i)
        {
        	TMap<int, TSharedPtr<FileMemInfo>> node;
            int32 nodeChildeNum = 0;
            Ar << nodeChildeNum;
            for (int childIndex = 0; childIndex < nodeChildeNum; ++childIndex)
            {
                int key;
                Ar << key;

                TSharedPtr<FileMemInfo> fielMemInfo = MakeShared<FileMemInfo>();
                fielMemInfo->Serialize(Ar);

                node.Add(key, fielMemInfo);
            }
            FString outKey;
            Ar << outKey;
            infoList.Add(outKey, node);
        }

        parentFileMap.Empty();
        TMap<FString, TSharedPtr<FileMemInfo>> ParentFileMap;
        int32 ParentFileChildNum = 0;
        Ar << ParentFileChildNum;
        for (int i = 0; i < ParentFileChildNum; ++i)
        {
            FString key;
            Ar << key;
            TSharedPtr<FileMemInfo> value;
            value->Serialize(Ar);
            ParentFileMap.Add(key, value);
        }
    }
    else if (Ar.IsSaving())
    {

        int32 infoListNum = infoList.Num();
        Ar << infoListNum;

        for (auto infoMap : infoList)
        {
            int32 mapNum = infoMap.Value.Num();
            Ar << mapNum;

            for (auto infoItem : infoMap.Value)
            {
                Ar << infoItem.Key;
                infoItem.Value->Serialize(Ar);
            }
            Ar << infoMap.Key;
        }

        int32 ParentFileChildNum = parentFileMap.Num();
        Ar << ParentFileChildNum;

        for (auto fileMap : parentFileMap)
        {
            Ar << fileMap.Key;
            if (fileMap.Value.IsValid())
            {
                fileMap.Value->Serialize(Ar);
            }
            else
            {
                TSharedPtr<FileMemInfo> emptyFileInfo = MakeShared<FileMemInfo>();
                emptyFileInfo->Serialize(Ar);
            }
        }
    }
}


void FunctionProfileNode::Serialize(FArchive& Ar)
{
    Ar << functionName;
    Ar << costTime;
    Ar << countOfCalls;
    Ar << layerIdx;

    if (Ar.IsLoading())
    {
        childNode = MakeShared<TMap<FString, TSharedPtr<FunctionProfileNode>>>();
        int32 childNum = 0;
        Ar << childNum;

        for (int i = 0; i < childNum; ++i)
        {
            FString name;
            TSharedPtr<FunctionProfileNode> node = MakeShared<FunctionProfileNode>();
            Ar << name;
            node->Serialize(Ar);
            childNode->Add(name, node);
        }
    }
    else if (Ar.IsSaving() && childNode.IsValid())
    {
        int32 childNum = childNode->Num();
        Ar << childNum;

        for (auto iter : *childNode)
        {
            auto name = iter.Key;
            auto node = iter.Value;
            Ar << name;
            if (iter.Value.IsValid())
            {
                node->Serialize(Ar);
            }
            else
            {
                TSharedPtr<FunctionProfileNode> emptyNode = MakeShared<FunctionProfileNode>();
                emptyNode->Serialize(Ar);
            }
        }
    }
}

void FunctionProfileNode::CopyData(TSharedPtr<FunctionProfileNode> NewData)
{
    NewData->functionName = this->functionName;
    NewData->costTime = this->costTime;
    NewData->countOfCalls = this->countOfCalls;
    NewData->layerIdx = this->layerIdx;
    for (auto ChildNodeInfo : *this->childNode)
    {
        TSharedPtr<FunctionProfileNode> NewChildNode = MakeShared<FunctionProfileNode>();
        ChildNodeInfo.Value->CopyData(NewData);

        TMap<FString, TSharedPtr<FunctionProfileNode>> NewMapNode;
        NewData->childNode->Add(ChildNodeInfo.Key, NewData);
    }
}
