#include "LuaPlayerState.h"
#include "Net/UnrealNetwork.h"

ALuaPlayerState::ALuaPlayerState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ALuaPlayerState::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaPlayerState::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    CallReceivePreRep(LuaFilePath);
    TryHookActorComponents();
}

void ALuaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ALuaPlayerState, LuaNetSerialization, COND_None);
    }
}
