#include "LuaActor.h"
#include "LuaState.h"
#include "Net/UnrealNetwork.h"

ALuaActor::ALuaActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void ALuaActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (EnableLuaTick)
    {
        UnRegistLuaTick();
    }
}

FString ALuaActor::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    ILuaOverriderInterface::PostLuaHook();
}

void ALuaActor::RegistLuaTick(float TickInterval)
{
    EnableLuaTick = true;
    auto state = NS_SLUA::LuaState::get();
    state->registLuaTick(this, TickInterval);
}

void ALuaActor::UnRegistLuaTick()
{
    auto state = NS_SLUA::LuaState::get();
    state->unRegistLuaTick(this);
}

void ALuaActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ALuaActor, LuaNetSerialization, COND_None);
    }
}
