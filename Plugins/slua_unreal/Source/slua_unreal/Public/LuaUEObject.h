#pragma once

#include "CoreMinimal.h"
#include "LuaOverriderInterface.h"
#include "LuaUEObject.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SLUA_UNREAL_API ULuaObject : public UObject, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    FString GetLuaFilePath_Implementation() const override;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
