// Fill out your copyright notice in the Description page of Project Settings.


#include "SluaActor.h"
#include "SluaComponent.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Paths.h"


// Sets default values
ASluaActor::ASluaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASluaActor::BeginPlay()
{
	Super::BeginPlay();
	
	auto slua = FindComponentByClass<USluaComponent>();
	auto state = slua->State();
	state->setLoadFileDelegate([](const char* fn,uint32& len)->uint8* {

		FString path = FPaths::ProjectContentDir();
		path+="/Lua/";
		path+=UTF8_TO_TCHAR(fn);
		path+=".lua";

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
 
		IFileHandle* FileHandle = PlatformFile.OpenRead(*path);
		if(FileHandle)
		{
			len = (uint32) FileHandle->Size();
			uint8* buf = new uint8[len];

			FileHandle->Read(buf, len);
		
			// Close the file again
			delete FileHandle;

			return buf;
		}

		return nullptr;
	});
	state->doFile("Test");
}

// Called every frame
void ASluaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto slua = FindComponentByClass<USluaComponent>();
	auto state = slua->State();
	state->call("update",DeltaTime);
}

