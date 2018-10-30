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

namespace slua {

    void SluaUtil::openLib(lua_State* L) {
        lua_newtable(L);
        RegMetaMethod(L,loadUI);
        RegMetaMethod(L,createDelegate);
        lua_setglobal(L,"slua");
    }

    void SluaUtil::reg(lua_State* L,const char* fn,lua_CFunction f) {
        lua_getglobal(L,"slua");
        lua_pushcclosure(L,f,0);
        lua_setfield(L,-2,fn);
        lua_pop(L,1);
    }
    
    int SluaUtil::loadUI(lua_State* L) {
        
        UGameInstance* GameInstance = nullptr;
        #if WITH_EDITOR
        UUnrealEdEngine* engine = Cast<UUnrealEdEngine>(GEngine);
        if(engine && engine->PlayWorld) GameInstance = engine->PlayWorld->GetGameInstance();
        #else
        UGameEngine* engine = Cast<UGameEngine>(GEngine);
        if(engine) GameInstance = engine->GameInstance;
        #endif
        
        if(!GameInstance)
            luaL_error(L,"GameInstance is null");

        const char* ui = luaL_checkstring(L,1);

        TArray<FStringFormatArg> Args;
        Args.Add(UTF8_TO_TCHAR(ui));

        // load blueprint widget from cpp, need add '_C' tail
        auto cui = FString::Format(TEXT("Blueprint'{0}_C'"),Args);
        TSubclassOf<UUserWidget> uclass = LoadClass<UUserWidget>(NULL, *cui);
        if(uclass==nullptr) luaL_error(L,"Can't find ui named %s",ui);
        
        UUserWidget* widget = CreateWidget<UUserWidget>(GameInstance,uclass);
        return LuaObject::push(L,widget);
    }

    int SluaUtil::createDelegate(lua_State* L) {
        luaL_checktype(L,1,LUA_TFUNCTION);
        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(),ULuaDelegate::StaticClass());
        obj->bindFunction(L,1);
        return LuaObject::push(L,obj);
    }
}