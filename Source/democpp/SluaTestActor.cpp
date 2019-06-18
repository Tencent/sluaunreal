// Fill out your copyright notice in the Description page of Project Settings.


#include "SluaTestActor.h"
#include "SluaTestCase.h"
#include "Engine/Engine.h"
#include "slua_profile.h"


// Sets default values
ASluaTestActor::ASluaTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASluaTestActor::BeginPlay()
{
	Super::BeginPlay();
	NS_SLUA::LuaState* ls = NS_SLUA::LuaState::get();
	ls->set("some.field.x", 101);
	ls->set("somefield", 102);
	ls->doFile("Test");
	ls->set("some.field.z", 104);
	ls->call("begin",this->GetWorld(),this);
}

// Called every frame
void ASluaTestActor::Tick(float DeltaTime)
{
	PROFILER_WATCHER(x);
	Super::Tick(DeltaTime);

	NS_SLUA::LuaState* ls = NS_SLUA::LuaState::get();
	ls->call("update",DeltaTime);
	GEngine->ForceGarbageCollection(true);
	USluaTestCase::callback();
}

void ASluaTestActor::SetFName(FName name) {
	NS_SLUA::Log::Log("set fname %s", TCHAR_TO_UTF8(*(name.ToString())));	
}

