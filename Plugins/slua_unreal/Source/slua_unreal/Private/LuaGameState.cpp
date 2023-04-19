#include "LuaGameState.h"
#include "UnrealNetwork.h"

ALuaGameState::ALuaGameState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ALuaGameState::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaGameState::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    CallReceivePreRep(LuaFilePath);
    TryHookActorComponents();
}

void ALuaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    if (!FLuaNetSerialization::bEnableLuaNetReplicate)
    {
        DOREPLIFETIME_CONDITION(ALuaGameState, LuaNetSerialization, COND_Max);
    }
}
