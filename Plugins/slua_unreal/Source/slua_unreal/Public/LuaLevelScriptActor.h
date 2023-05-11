#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/LevelScriptActor.h"
#include "LuaOverriderInterface.h"
#include "LuaLevelScriptActor.generated.h"

UCLASS(notplaceable, meta=(KismetHideOverrides = "ReceiveAnyDamage,ReceivePointDamage,ReceiveRadialDamage,ReceiveActorBeginOverlap,ReceiveActorEndOverlap,ReceiveHit,ReceiveDestroyed,ReceiveActorBeginCursorOver,ReceiveActorEndCursorOver,ReceiveActorOnClicked,ReceiveActorOnReleased,ReceiveActorOnInputTouchBegin,ReceiveActorOnInputTouchEnd,ReceiveActorOnInputTouchEnter,ReceiveActorOnInputTouchLeave"), HideCategories=(Collision,Rendering,"Utilities|Transformation"))
class SLUA_UNREAL_API ALuaLevelScriptActor : public ALevelScriptActor, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    FString GetLuaFilePath_Implementation() const override;

    UFUNCTION(Blueprintcallable)
    void RegistLuaTick(float TickInterval);

    UFUNCTION(Blueprintcallable)
    void UnRegistLuaTick();
    
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
protected:
    void onLuaStateInit(NS_SLUA::lua_State* L);

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;

private:
    bool EnableLuaTick;
};
