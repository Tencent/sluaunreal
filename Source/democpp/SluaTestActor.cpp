// Fill out your copyright notice in the Description page of Project Settings.


#include "SluaTestActor.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Paths.h"
#include "GenericPlatformFile.h"
#include "SluaTestCase.h"
#include "Engine/Engine.h"
#include "HAL/FileManager.h"


ASluaTestActor* ASluaTestActor::instance=nullptr;

// Sets default values
ASluaTestActor::ASluaTestActor()
	:state("main")
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	instance = this;
}

// read file content
static uint8* ReadFile(IPlatformFile& PlatformFile, FString path, uint32& len) {
	IFileHandle* FileHandle = PlatformFile.OpenRead(*path);
	if (FileHandle) {
		len = (uint32)FileHandle->Size();
		uint8* buf = new uint8[len];

		FileHandle->Read(buf, len);

		// Close the file again
		delete FileHandle;

		return buf;
	}

	return nullptr;
}

// Called when the game starts or when spawned
void ASluaTestActor::BeginPlay()
{
	Super::BeginPlay();
	state.doFile("Test");
	state.call("begin",this->GetWorld(),this);
}

void ASluaTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	state.close();
}

void ASluaTestActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	state.init();
	state.setLoadFileDelegate([](const char* fn, uint32& len, FString& filepath)->uint8* {

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		FString path = FPaths::ProjectContentDir();
		path += "/Lua/";
		path += UTF8_TO_TCHAR(fn);
		TArray<FString> luaExts = { UTF8_TO_TCHAR(".lua"), UTF8_TO_TCHAR(".luac") };
		for (auto& it : luaExts) {
			auto fullPath = path + *it;
			auto buf = ReadFile(PlatformFile, fullPath, len);
			if (buf) {
				fullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*fullPath);
				filepath = fullPath;
				return buf;
			}
		}

		return nullptr;
	});
}

// Called every frame
void ASluaTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	state.call("update",DeltaTime);
	GEngine->ForceGarbageCollection(true);
	USluaTestCase::callback();
}

void ASluaTestActor::SetFName(FName name) {
	slua::Log::Log("set fname %s", TCHAR_TO_UTF8(*(name.ToString())));	
}

