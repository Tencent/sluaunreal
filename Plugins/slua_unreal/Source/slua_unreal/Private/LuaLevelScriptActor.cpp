#include "LuaLevelScriptActor.h"
#include "LuaState.h"
#include "LuaOverrider.h"
#if WITH_EDITOR
#include "Editor.h"
#endif

ALuaLevelScriptActor::ALuaLevelScriptActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
    {
        NS_SLUA::LuaState::onInitEvent.AddUObject(this, &ALuaLevelScriptActor::onLuaStateInit);
    }
    bReplicates = false;
}

FString ALuaLevelScriptActor::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void ALuaLevelScriptActor::onLuaStateInit(NS_SLUA::lua_State* L)
{
    if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
    {
        TryHook();
    }
}

void ALuaLevelScriptActor::RegistLuaTick(float TickInterval)
{
    EnableLuaTick = true;
    auto state = NS_SLUA::LuaState::get();
    state->registLuaTick(this, TickInterval);
}

void ALuaLevelScriptActor::UnRegistLuaTick()
{
    auto state = NS_SLUA::LuaState::get();
    state->unRegistLuaTick(this);
}

void ALuaLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (EnableLuaTick)
    {
        UnRegistLuaTick();
    }
}