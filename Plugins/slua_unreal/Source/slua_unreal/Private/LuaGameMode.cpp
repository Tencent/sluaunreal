#include "LuaGameMode.h"
#include "Net/UnrealNetwork.h"

ALuaGameMode::ALuaGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString ALuaGameMode::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    CallReceivePreRep(LuaFilePath);
    TryHookActorComponents();
}
