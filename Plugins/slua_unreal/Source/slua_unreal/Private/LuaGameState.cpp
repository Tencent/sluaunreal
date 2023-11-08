#include "LuaGameState.h"
#include "Net/UnrealNetwork.h"

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

    ILuaOverriderInterface::PostLuaHook();
}

void ALuaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ALuaGameState, LuaNetSerialization, COND_None);
    }
}
