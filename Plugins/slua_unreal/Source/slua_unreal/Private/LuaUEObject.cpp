#include "LuaUEObject.h"
#include "LuaState.h"

ULuaObject::ULuaObject(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ULuaObject::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}