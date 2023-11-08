#pragma once

#include "CoreMinimal.h"
#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"
#include "GameFramework/PlayerState.h"
#include "LuaPlayerState.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ALuaPlayerState : public APlayerState, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override
    {
    }

    virtual FString GetLuaFilePath_Implementation() const override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated)
        FLuaNetSerialization LuaNetSerialization;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
