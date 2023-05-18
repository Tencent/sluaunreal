#pragma once

#include "CoreMinimal.h"
#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"
#include "GameFramework/PlayerController.h"
#include "LuaPlayerController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ALuaPlayerController : public APlayerController, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual FString GetLuaFilePath_Implementation() const override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated)
        FLuaNetSerialization LuaNetSerialization;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
