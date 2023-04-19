#include "LuaPlayerController.h"
#include "UnrealNetwork.h"

ALuaPlayerController::ALuaPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ALuaPlayerController::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    CallReceivePreRep(LuaFilePath);
    TryHookActorComponents();
}

void ALuaPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    if (!FLuaNetSerialization::bEnableLuaNetReplicate)
    {
        DOREPLIFETIME_CONDITION(ALuaPlayerController, LuaNetSerialization, COND_Max);
    }
}
