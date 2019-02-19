// Fill out your copyright notice in the Description page of Project Settings.

#include "democppGameModeBase.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatformFile.h"
#include "HAL/FileManager.h"

AdemocppGameModeBase::AdemocppGameModeBase() :state("main")
{

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

void AdemocppGameModeBase::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
 	Super::InitGame(MapName,Options,ErrorMessage);
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

void AdemocppGameModeBase::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	state.close();
}
