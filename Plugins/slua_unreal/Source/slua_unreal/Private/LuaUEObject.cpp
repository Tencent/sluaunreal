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

void ULuaObject::PostInitProperties()
{
    Super::PostInitProperties();
    TryHook();
}

void ULuaObject::PostDuplicate(bool bDuplicateForPIE)
{
    Super::PostDuplicate(bDuplicateForPIE);

    if (HasAnyFlags(RF_ArchetypeObject))
    {
        return;
    }
    if (LuaFilePath.IsEmpty())
    {
        return;
    }

    NS_SLUA::LuaState::hookObject(nullptr, this, false, false, true);
}