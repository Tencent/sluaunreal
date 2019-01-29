// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "Components/ActorComponent.h"
#include "LuaComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLUA_UNREAL_API ULuaComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    ULuaComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void ProcessEvent(UFunction * func, void * params) override final;

    virtual bool luaImplemented(UFunction * func, void * params);

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua|LuaComponent")
    FString LuaFilePath;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua|LuaComponent")
    FString LuaStateName;

private:
    slua::LuaVar luaComponentTable;
    slua::LuaVar tickFunction;

    static slua::LuaVar metatable;

    static int __index(slua::lua_State* L);
    void init();
};
