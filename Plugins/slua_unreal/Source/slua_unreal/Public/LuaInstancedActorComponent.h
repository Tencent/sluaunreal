#pragma once

#include "CoreMinimal.h"
#include "LuaOverriderInterface.h"
#include "Components/ActorComponent.h"
#include "LuaInstancedActorComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ULuaInstancedActorComponent : public UActorComponent, public ILuaOverriderInterface, public IInstancedLuaInterface
{
    GENERATED_UCLASS_BODY()

public:
    FString GetLuaFilePath_Implementation() const override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(Blueprintcallable)
        void RegistLuaTick(float TickInterval);

    UFUNCTION(Blueprintcallable)
        void UnRegistLuaTick();

    virtual void PostInitProperties() override;
    virtual void PostDuplicate(bool bDuplicateForPIE) override;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;

private:
    bool EnableLuaTick = false;
};
