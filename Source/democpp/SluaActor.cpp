// Fill out your copyright notice in the Description page of Project Settings.


#include "SluaActor.h"
#include "SluaComponent.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Paths.h"
#include "GenericPlatformFile.h"
#include "SluaTestCase.h"
#include "Engine/Engine.h"


ASluaActor* ASluaActor::instance=nullptr;

// Sets default values
ASluaActor::ASluaActor()
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
void ASluaActor::BeginPlay()
{
	Super::BeginPlay();
	
	auto slua = FindComponentByClass<USluaComponent>();
	if(!slua) return;

	auto state = slua->State();
	state->setLoadFileDelegate([](const char* fn,uint32& len,FString& filepath)->uint8* {

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		FString path = FPaths::ProjectContentDir();
		path+="/Lua/";
		path+=UTF8_TO_TCHAR(fn);
		TArray<FString> luaExts = { UTF8_TO_TCHAR(".lua"), UTF8_TO_TCHAR(".luac") };
		for (auto ptr = luaExts.CreateConstIterator(); ptr; ++ptr) {
			auto fullPath = path + *ptr;
			auto buf = ReadFile(PlatformFile, fullPath, len);
			if (buf) {
				filepath = fullPath;
				return buf;
			}
		}

		return nullptr;
	});
	slua::LuaVar v = state->doFile("Test");
	if(!v.isNil()) {
		ensure(v.isTuple());
		ensure(v.count()==5);
		ensure(v.getAt(1).asInt()==1024);
		slua::Log::Log("first return value is %d",v.getAt(1).asInt());

		slua::LuaVar t = v.getAt(4);
		ensure(t.isTable());
		ensure(t.getAt<int>(1)==1);
		t.setToTable(5,1024);
		ensure(t.getFromTable<int>(5)==1024);
		t.setToTable("this",this);

		// test iterator function
		slua::LuaVar key,value;
		while(t.next(key,value)) {
			slua::Log::Log("for each table %s,%s",key.toString(),value.toString());
		}
	}

	state->call("xx.text",this->GetWorld());
}

// Called every frame
void ASluaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto slua = FindComponentByClass<USluaComponent>();
	if(!slua) return;
	
	auto state = slua->State();
	slua::LuaVar v = state->call("update",DeltaTime,this);
	if(!v.isNil()) {
		// test copy constructor
		slua::LuaVar v2 = v;
		slua::LuaVar v3 = v2;
		ensure(v.isTuple());
		ensure(v.count()==5);
		ensure(v.getAt(1).asInt()==1024);
	}

	GEngine->ForceGarbageCollection(true);
	USluaTestCase::callback();
}

void ASluaActor::SetFName(FName name) {
	slua::Log::Log("set fname %s", TCHAR_TO_UTF8(*(name.ToString())));	
}

