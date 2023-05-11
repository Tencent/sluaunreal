#include "LuaInstancedActorComponent.h"
#include "LuaState.h"

ULuaInstancedActorComponent::ULuaInstancedActorComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void ULuaInstancedActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    if (EnableLuaTick)
    {
        UnRegistLuaTick();
    }
}

FString ULuaInstancedActorComponent::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ULuaInstancedActorComponent::RegistLuaTick(float TickInterval)
{
    EnableLuaTick = true;
    auto state = NS_SLUA::LuaState::get();
    state->registLuaTick(this, TickInterval);
}

void ULuaInstancedActorComponent::UnRegistLuaTick()
{
    auto state = NS_SLUA::LuaState::get();
    state->unRegistLuaTick(this);
}

void ULuaInstancedActorComponent::PostInitProperties()
{
    Super::PostInitProperties();
    TryHook();
}

void ULuaInstancedActorComponent::PostDuplicate(bool bDuplicateForPIE)
{
    Super::PostDuplicate(bDuplicateForPIE);

    // if place Actor in Level, PostDuplicate will be called when open Level in editor.
    // if no LuaState exist, maybe not playing.
    NS_SLUA::LuaState* State = NS_SLUA::LuaState::get();
    if (!State)
    {
        return;
    }
    if (HasAnyFlags(RF_ArchetypeObject))
    {
        return;
    }
    if (LuaFilePath.IsEmpty())
    {
        return;
    }

    UE_LOG(Slua, Log, TEXT("ULuaInstancedActorComponent::hookObject %s"), *GetFName().ToString());
    NS_SLUA::LuaState::hookObject(nullptr, this, false, false, true);
}