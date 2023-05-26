#pragma once

#include "CoreMinimal.h"
#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"
#include "GameFramework/GameMode.h"
#include "LuaGameMode.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ALuaGameMode : public AGameMode, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual FString GetLuaFilePath_Implementation() const override;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
