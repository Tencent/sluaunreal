// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatformFile.h"
#include "HAL/FileManager.h"



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

UMyGameInstance::UMyGameInstance() :state("main") {

}

void UMyGameInstance::Init()
{
	state.onInitEvent.AddUObject(this, &UMyGameInstance::LuaStateInitCallback);
	state.init();

	state.setLoadFileDelegate([](const char* fn, uint32& len, FString& filepath)->uint8* {

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		FString path = FPaths::ProjectContentDir();
		FString filename = UTF8_TO_TCHAR(fn);
		path /= "Lua";
		path /= filename.Replace(TEXT("."), TEXT("/"));

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

void UMyGameInstance::Shutdown()
{
	state.close();
}

static int32 PrintLog(NS_SLUA::lua_State *L)
{
	FString str;
	size_t len;
	const char* s = luaL_tolstring(L, 1, &len);
	if (s) str += UTF8_TO_TCHAR(s);
	NS_SLUA::Log::Log("PrintLog %s", TCHAR_TO_UTF8(*str));
	return 0;
}

void UMyGameInstance::LuaStateInitCallback()
{
	NS_SLUA::lua_State *L = state.getLuaState();
	lua_pushcfunction(L, PrintLog);
	lua_setglobal(L, "PrintLog");
}
