#include "LuaGameMode.h"

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
    
    ILuaOverriderInterface::PostLuaHook();
}
