#pragma once

#include "CoreMinimal.h"
#include "LuaOverriderInterface.h"
#include "LuaUEObject.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ULuaObject : public UObject, public ILuaOverriderInterface, public IInstancedLuaInterface
{
    GENERATED_UCLASS_BODY()

public:
    FString GetLuaFilePath_Implementation() const override;

    virtual void PostInitProperties() override;
    void PostDuplicate(bool bDuplicateForPIE) override;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
