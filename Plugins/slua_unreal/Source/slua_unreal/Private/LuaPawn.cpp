#include "LuaPawn.h"
#include "Net/UnrealNetwork.h"

ALuaPawn::ALuaPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ALuaPawn::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void ALuaPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(ALuaPawn, LuaNetSerialization, COND_None);
    }
}
