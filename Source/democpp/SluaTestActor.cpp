// Fill out your copyright notice in the Description page of Project Settings.


#include "SluaTestActor.h"
#include "SluaTestCase.h"
#include "Engine/Engine.h"
#include "slua_profile.h"


ASluaTestActor* ASluaTestActor::instance=nullptr;
// Sets default values
ASluaTestActor::ASluaTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	instance = this;
}

// Called when the game starts or when spawned
void ASluaTestActor::BeginPlay()
{
	Super::BeginPlay();
	state().set("some.field.x", 101);
	state().set("somefield", 102);
	state().doFile("Test");
	state().set("some.field.z", 104);
	state().call("begin",this->GetWorld(),this);
}

// Called every frame
void ASluaTestActor::Tick(float DeltaTime)
{
	PROFILER_WATCHER(x);
	Super::Tick(DeltaTime);

	state().call("update",DeltaTime);
	GEngine->ForceGarbageCollection(true);
	USluaTestCase::callback();
}

void ASluaTestActor::SetFName(FName name) {
	slua::Log::Log("set fname %s", TCHAR_TO_UTF8(*(name.ToString())));	
}

slua::LuaState & ASluaTestActor::state()
{
	return *slua::LuaState::get();
}

