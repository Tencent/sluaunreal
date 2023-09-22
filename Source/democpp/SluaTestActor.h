// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SluaTestActor.generated.h"

UCLASS()
class DEMOCPP_API ASluaTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASluaTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void SetFName(FName name);

	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> objs;
};
