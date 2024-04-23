// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LuaGameMode.h"
#include "democppGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FString PlayerName;
    UPROPERTY()
    FString PlayerId;

    friend int32 GetTypeHash(const FPlayerData& Item)
    {
        return GetTypeHash(Item.PlayerName) * GetTypeHash(Item.PlayerId);
    }

    FORCEINLINE bool operator == (const FPlayerData& Other) const
    {
        return PlayerName == Other.PlayerName && PlayerId == Other.PlayerId;
    }
};

namespace NS_SLUA
{
    DefTypeName(FPlayerData);
    DefDeduceType(FPlayerData, Struct);
}

/**
 * 
 */
UCLASS()
class DEMOCPP_API AdemocppGameModeBase : public ALuaGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

    UFUNCTION()
    void CallWithArray(const TArray<FPlayerData>& Array);

    UFUNCTION()
    void CallWithSet(const TSet<FPlayerData>& Set);

    UFUNCTION()
    void CallWithMap(const TMap<int32, FPlayerData>& Map);
};
