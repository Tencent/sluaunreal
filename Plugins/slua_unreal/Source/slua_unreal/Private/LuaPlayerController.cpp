#include "LuaPlayerController.h"
#include "Net/UnrealNetwork.h"

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

    ILuaOverriderInterface::PostLuaHook();
}

void ALuaPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ALuaPlayerController, LuaNetSerialization, COND_None);
    }
}
