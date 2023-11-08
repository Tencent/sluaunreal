#include "LuaCharacter.h"
#include "Net/UnrealNetwork.h"

ALuaCharacter::ALuaCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ALuaCharacter::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void ALuaCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ALuaCharacter, LuaNetSerialization, COND_None);
    }
}
