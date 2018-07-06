
// The MIT License (MIT)

// Copyright 2015 Siney/Pangweiwei siney@yeah.net
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "SluaLib.h"
#include "LuaObject.h"
#include "LuaState.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Blueprint/UserWidget.h"
#include "Misc/AssertionMacros.h"
#include "LuaDelegate.h"

namespace slua {

    void SluaUtil::openLib(lua_State* L) {
        lua_newtable(L);
        RegMetaMethod(L,loadUI);
        RegMetaMethod(L,createDelegate);

        lua_setglobal(L,"slua");
    }
    
    int SluaUtil::loadUI(lua_State* L) {
        const char* ui = luaL_checkstring(L,1);

        TArray<FStringFormatArg> Args;
		Args.Add(UTF8_TO_TCHAR(ui));

        // load blueprint widget from cpp, need add '_C' tail
        auto cui = FString::Format(TEXT("Blueprint'{0}_C'"),Args);
        TSubclassOf<UUserWidget> uclass = LoadClass<UUserWidget>(NULL, *cui);
        if(uclass==nullptr) luaL_error(L,"Can't find ui named %s",ui);
        
        auto ls = LuaState::get(L);
        UWorld* wld = ls->sluaComponent?ls->sluaComponent->GetWorld():nullptr;
        if(!wld) luaL_error(L,"World missed");
        UGameInstance* instance = wld->GetGameInstance();
        UUserWidget* widget = CreateWidget<UUserWidget>(instance,uclass);
        return LuaObject::push(L,widget);
    }

    int SluaUtil::createDelegate(lua_State* L) {
        luaL_checktype(L,1,LUA_TFUNCTION);
        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(),ULuaDelegate::StaticClass());
        obj->bindFunction(L,1);
        return LuaObject::push(L,obj);
    }
}