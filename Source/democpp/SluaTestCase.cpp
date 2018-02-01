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

#include "SluaTestCase.h"
#include "lua/lua.hpp"
#include "LuaObject.h"
#include "LuaCppBinding.h"
#include "Log.h"
#include "SluaActor.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Blueprint/UserWidget.h"
#include "Misc/AssertionMacros.h"

namespace slua {

class Foo {
public:
    void bar(const char*,int) {}
    std::string getStr() { return "some text"; }
};

DefLuaClass(Foo)
    DefLuaMethod(bar,&Foo::bar)
    DefLuaMethod(getStr,&Foo::getStr)
EndDef()
}

USluaTestCase::USluaTestCase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TArray<int> USluaTestCase::GetArray() {
    TArray<int> array={1,0,2,4,2,0,4,8};
    return array;
}

UUserWidget* USluaTestCase::GetWidget(FString ui) {
    TArray<FStringFormatArg> Args;
    Args.Add(ui);

    // load blueprint widget from cpp, need add '_C' tail
    auto cui = FString::Format(TEXT("Blueprint'{0}_C'"),Args);
    TSubclassOf<UUserWidget> uclass = LoadClass<UUserWidget>(NULL, *cui);
    if(uclass==nullptr)
        return nullptr;
    if(!ASluaActor::instance)
        return nullptr;
    UWorld* wld = ASluaActor::instance->GetWorld();
    if(!wld)
        return nullptr;
    UUserWidget* widget = CreateWidget<UUserWidget>(wld,uclass);
    return widget;
}

void USluaTestCase::SetButton(UUserWidget* widget) {
    slua::Log::Log("Set Button %p",widget);
}