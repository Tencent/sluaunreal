#include "LuaOverriderInterface.h"
#include "LuaOverrider.h"

UInstancedLuaInterface::UInstancedLuaInterface(const class FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void ILuaOverriderInterface::TryHook()
{
    if (bTryHookSuccess)
    {
        return;
    }
    // if no LuaState exist, maybe not playing.
    NS_SLUA::LuaState* state = NS_SLUA::LuaState::get();
    if (!state)
    {
        return;
    }
    UObject* obj = Cast<UObject>(this);
    if (!obj)
    {
        return;
    }
    if (obj->HasAnyFlags(RF_ArchetypeObject))
    {
        return;
    }
    const FString luaFilePath = NS_SLUA::LuaOverrider::getLuaFilePath(obj, obj->GetClass(), false);
    if (luaFilePath.IsEmpty())
    {
        return;
    }
    UE_LOG(Slua, Log, TEXT("ILuaOverriderInterface::TryHook %s"), *obj->GetFName().ToString());
    NS_SLUA::LuaState::hookObject(nullptr, obj, false, false, true);
    bTryHookSuccess = true;
}

void ILuaOverriderInterface::TryHookActorComponents()
{
    AActor* self = Cast<AActor>(this);
    if (nullptr == self)
    {
        return;
    }

    for (UActorComponent* component : self->GetComponents())
    {
        if (component && component->GetClass() && component->GetClass()->ImplementsInterface(UInstancedLuaInterface::StaticClass()))
        {
            if (ILuaOverriderInterface* luaInterface = Cast<ILuaOverriderInterface>(component))
            {
                luaInterface->TryHook();
            }
        }
    }
}

ULuaOverriderInterface::ULuaOverriderInterface(const class FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

NS_SLUA::LuaVar ILuaOverriderInterface::GetSelfTable() const
{
    NS_SLUA::LuaVar* luaSelfTable = ULuaOverrider::getObjectLuaTable(Cast<UObject>(this));
    if (luaSelfTable)
    {
        return *luaSelfTable;
    }
    else
    {
        return NS_SLUA::LuaVar();
    }
}

bool ILuaOverriderInterface::CallReceivePreRep(const FString& LuaFilePath)
{
    if (!LuaFilePath.IsEmpty())
    {
        NS_SLUA::LuaVar selfTable = GetSelfTable();
        if (!selfTable.isValid() || !selfTable.isTable())
        {
            return false;
        }
        static FString ReceivePreRepFunction = TEXT("ReceivePreRep");
        NS_SLUA::LuaVar selfLuaFunc = selfTable.getFromTable<NS_SLUA::LuaVar>(ReceivePreRepFunction, false);
        if (!selfLuaFunc.isValid() || !selfLuaFunc.isFunction())
        {
            return false;
        }

        CallLuaFunctionIfExist(ReceivePreRepFunction);
        return true;
    }
    return false;
}
