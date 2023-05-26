#include "LuaActorComponent.h"
#include "Net/UnrealNetwork.h"

ULuaActorComponent::ULuaActorComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , EnableLuaTick(false)
{
    bWantsInitializeComponent = true;
}

void ULuaActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    if (EnableLuaTick)
    {
        UnRegistLuaTick();
    }
}

FString ULuaActorComponent::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ULuaActorComponent::RegistLuaTick(float TickInterval)
{
    EnableLuaTick = true;
    auto state = NS_SLUA::LuaState::get();
    state->registLuaTick(this, TickInterval);
}

void ULuaActorComponent::UnRegistLuaTick()
{
    auto state = NS_SLUA::LuaState::get();
    state->unRegistLuaTick(this);
}

void ULuaActorComponent::InitializeComponent()
{
    Super::InitializeComponent();

    TryHook();
}

void ULuaActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ULuaActorComponent, LuaNetSerialization, COND_None);
    }
}
