// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatformFile.h"
#include "HAL/FileManager.h"

using namespace slua;

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

static int32 PrintLog(slua::lua_State *L)
{
	FString str;
	size_t len;
	const char* s = luaL_tolstring(L, 1, &len);
	if (s) str += UTF8_TO_TCHAR(s);
	slua::Log::Log("PrintLog %s", TCHAR_TO_UTF8(*str));
	return 0;
}

static int32 NewLuaLib(lua_State *L)
{
	luaL_Reg _LuaFuncs[] = {
		{"LuaNamePrintLog", PrintLog},
		{NULL, NULL}
	};
	lua_newtable(L);
	luaL_setfuncs(L, _LuaFuncs, 0);
	return 1;
}

void UMyGameInstance::LuaStateInitCallback()
{
	slua::lua_State *L = state.getLuaState();

	// 添加全局函数
	lua_pushcfunction(L, PrintLog);
	lua_setglobal(L, "PrintLog");

	// 以前是直接使用luaL_requiref, 现在要改成如下方式注册
	luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);
	lua_pushcfunction(L, NewLuaLib);
	lua_setfield(L, -2, "LuaNameTestNewLib");
	lua_pop(L, 1);
}
