#pragma once

#include "CoreMinimal.h"
#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"
#include "GameFramework/Actor.h"

#include "LuaActor.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ALuaActor : public AActor, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual FString GetLuaFilePath_Implementation() const override;
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override
    {
    }

    UFUNCTION(Blueprintcallable)
        void RegistLuaTick(float TickInterval);

    UFUNCTION(Blueprintcallable)
        void UnRegistLuaTick();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated)
        FLuaNetSerialization LuaNetSerialization;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;

private:
    bool EnableLuaTick = false;
};
