// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "SluaLib.h"
#include "LuaObject.h"
#include "LuaState.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Blueprint/UserWidget.h"
#include "Misc/AssertionMacros.h"
#include "LuaDelegate.h"
#include "Blueprint/WidgetTree.h"
#if WITH_EDITOR
// Fix compile issue when using unity build
#ifdef G
#undef G
#endif
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif
#include "LuaMemoryProfile.h"

namespace slua {

    void SluaUtil::openLib(lua_State* L) {
        lua_newtable(L);
        RegMetaMethod(L, loadUI);
        RegMetaMethod(L, createDelegate);
		RegMetaMethod(L, loadClass);
		RegMetaMethod(L, dumpUObjects);
		RegMetaMethod(L, loadObject);
        lua_setglobal(L,"slua");
    }

    void SluaUtil::reg(lua_State* L,const char* fn,lua_CFunction f) {
        lua_getglobal(L,"slua");
        lua_pushcclosure(L,f,0);
        lua_setfield(L,-2,fn);
        lua_pop(L,1);
    }

    template<typename T>
    UClass* loadClassT(const char* cls) {
        TArray<FStringFormatArg> Args;
        Args.Add(UTF8_TO_TCHAR(cls));

		FString path(UTF8_TO_TCHAR(cls));
		int32 index;
		if (!path.FindChar(TCHAR('\''),index)) {
			// load blueprint widget from cpp, need add '_C' tail
			path = FString::Format(TEXT("Blueprint'{0}_C'"), { path });
		}
		else
		// auto add _C suffix
		{
			// remove last '
			path = path.Left(path.Len()-1);
			path += TEXT("_C'");
		}
        
		UClass* uclass = LoadClass<T>(NULL, *path);
        return uclass;
    }

    int SluaUtil::loadClass(lua_State* L) {
        const char* cls = luaL_checkstring(L,1);
		UClass* uclass = loadClassT<UObject>(cls);
        if(uclass==nullptr) luaL_error(L,"Can't find class named %s",cls);
        return LuaObject::pushClass(L,uclass);
    }

	int SluaUtil::loadObject(lua_State* L) {
		const char* objname = luaL_checkstring(L, 1);
		UObject* outter = LuaObject::checkValueOpt<UObject*>(L, 2, nullptr);
		return LuaObject::push(L, LoadObject<UObject>(outter, UTF8_TO_TCHAR(objname)));
	}
    
    int SluaUtil::loadUI(lua_State* L) {
      
        const char* cls = luaL_checkstring(L,1);
		UObject* obj = LuaObject::checkValueOpt<UObject*>(L, 2, nullptr);
        auto uclass = loadClassT<UUserWidget>(cls);
        if(uclass==nullptr) luaL_error(L,"Can't find class named %s",cls);
        
		UUserWidget* widget = nullptr;
		// obj can be 5 type
		if (obj) {
			if (obj->IsA<UWorld>())
				widget = CreateWidget<UUserWidget>(Cast<UWorld>(obj), uclass);
			else if (obj->IsA<UWidget>())
				widget = CreateWidget<UUserWidget>(Cast<UWidget>(obj), uclass);
			else if (obj->IsA<UWidgetTree>())
				widget = CreateWidget<UUserWidget>(Cast<UWidgetTree>(obj), uclass);
			else if (obj->IsA<APlayerController>())
				widget = CreateWidget<UUserWidget>(Cast<APlayerController>(obj), uclass);
			else if (obj->IsA<UGameInstance>())
				widget = CreateWidget<UUserWidget>(Cast<UGameInstance>(obj), uclass);
			else
				luaL_error(L, "arg 2 expect UWorld or UWidget or UWidgetTree or APlayerController or UGameInstance, but got %s",
					TCHAR_TO_UTF8(*obj->GetName()));
		}

		if(!widget) {
			// using GameInstance as default
			UGameInstance* GameInstance = nullptr;
#if WITH_EDITOR
			UUnrealEdEngine* engine = Cast<UUnrealEdEngine>(GEngine);
			if (engine && engine->PlayWorld) GameInstance = engine->PlayWorld->GetGameInstance();
#else
			UGameEngine* engine = Cast<UGameEngine>(GEngine);
			if (engine) GameInstance = engine->GameInstance;
#endif

			if (!GameInstance) luaL_error(L, "gameinstance missing");
			widget = CreateWidget<UUserWidget>(GameInstance, uclass);
		}

		
        return LuaObject::push(L,widget);
    }

    int SluaUtil::createDelegate(lua_State* L) {
        luaL_checktype(L,1,LUA_TFUNCTION);
        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(),ULuaDelegate::StaticClass());
        obj->bindFunction(L,1);
        return LuaObject::push(L,obj);
    }
	int SluaUtil::dumpUObjects(lua_State * L)
	{
		auto state = LuaState::get(L);
		auto& map = state->cacheSet();
		lua_newtable(L);
		int index = 1;
		for (auto& it : map) {
			LuaObject::push(L, getUObjName(it));
			lua_seti(L, -2, index++);
		}
		return 1;
	}

#if WITH_EDITOR
	void dumpUObjects() {
		auto state = LuaState::get();
		if (!state) return;
		auto& map = state->cacheSet();
		for (auto& it : map) {
			Log::Log("Pushed UObject %s", TCHAR_TO_UTF8(*getUObjName(it)));
		}
	}

	void garbageCollect() {
		auto state = LuaState::get();
		lua_gc(state->getLuaState(), LUA_GCCOLLECT, 0);
		Log::Log("Performed full lua gc");
	}

	void memUsed() {
		auto state = LuaState::get();
		int kb = lua_gc(state->getLuaState(), LUA_GCCOUNT, 0);
		Log::Log("Lua use memory %d kb",kb);
	}

	static FAutoConsoleCommand CVarDumpUObjects(
		TEXT("slua.DumpUObjects"),
		TEXT("Dump all uobject that referenced by lua in main state"),
		FConsoleCommandDelegate::CreateStatic(dumpUObjects),
		ECVF_Cheat);

	static FAutoConsoleCommand CVarGC(
		TEXT("slua.GC"),
		TEXT("Collect lua garbage"),
		FConsoleCommandDelegate::CreateStatic(garbageCollect),
		ECVF_Cheat);

	static FAutoConsoleCommand CVarMem(
		TEXT("slua.Mem"),
		TEXT("Print memory used"),
		FConsoleCommandDelegate::CreateStatic(memUsed),
		ECVF_Cheat);
#endif
}