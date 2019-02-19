// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LuaState.h"
#include "democppGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMOCPP_API AdemocppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:	
	AdemocppGameModeBase();
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void Logout(AController* Exiting) override;
	
	// create global state, freed on app exit
	slua::LuaState state;
};
