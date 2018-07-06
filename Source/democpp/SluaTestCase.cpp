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
    FString getStr() { return FString(UTF8_TO_TCHAR("some text")); }
};

DefLuaClass(Foo)
    DefLuaMethod(bar,&Foo::bar)
    DefLuaMethod(getStr,&Foo::getStr)
EndDef()
}

USluaTestCase::USluaTestCase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    this->Value=2048;
}

TArray<int> USluaTestCase::GetArray() {
    TArray<int> array={1,0,2,4,2,0,4,8};
    return array;
}

FVector USluaTestCase::TestStruct(FVector v, ESlateVisibility e, FVector& v2, int i, int& i2, FString str) {
	slua::Log::Log("v.X=%f, v.Y=%f, v.Z=%f", v.X, v.Y, v.Z);
	slua::Log::Log("i = %d", i);
	slua::Log::Log("s = %s", TCHAR_TO_UTF8(*str));
	slua::Log::Log("e = %d", (int)e);
	v2 = v * 2;
	return v2 * 2;
}

int USluaTestCase::TestInt_int(int i) {
	slua::Log::Log("TestInt_int i=%d", i);
	return i * 2;
}

FString USluaTestCase::TestIntStr_Str(int i, FString s) {
	slua::Log::Log("TestIntStr_Str i=%d, s=%s", i, TCHAR_TO_UTF8(*s));
	return FString(UTF8_TO_TCHAR("TestIntStr_Str"));
}

ESlateVisibility USluaTestCase::TestIntStrEnum_Enum(int i, FString s, ESlateVisibility e) {
	slua::Log::Log("TestIntStrEnum_Enum i=%d, s=%s, e=%d", i, TCHAR_TO_UTF8(*s), (int)e);
	return ESlateVisibility((int)e + 1);
}

TArray<int> USluaTestCase::TestIntStrEnum_Arr(int i, FString s, ESlateVisibility e) {
	slua::Log::Log("TestIntStrEnum_Arr i=%d, s=%s, e=%d", i, TCHAR_TO_UTF8(*s), (int)e);
	TArray<int> arr = { 123, 321 };
	return arr;
}

void USluaTestCase::TestOIntOStrOEnum(int i, int& oi, FString s, FString& os, ESlateVisibility e, ESlateVisibility& oe) {
	slua::Log::Log("TestOIntOStrOEnum i=%d, s=%s, e=%d", i, TCHAR_TO_UTF8(*s), (int)e);
	slua::Log::Log("TestOIntOStrOEnum oi=%d, os=%s, oe=%d", oi, TCHAR_TO_UTF8(*os), (int)oe);
}

void USluaTestCase::TwoArgs(FString a,int b,float c,FString d,UObject* widget) {
	slua::Log::Log("We get 5 args %s,%d,%f,%s,%p", TCHAR_TO_UTF8(*a),b,c,TCHAR_TO_UTF8(*d),widget);    
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

FSlateBrush USluaTestCase::GetBrush() {
    return FSlateBrush();
}

void USluaTestCase::StaticFunc() {
    slua::Log::Log("static function call");
}

static USluaTestCase::FOnAssetClassLoaded s_onloaded;
void USluaTestCase::LoadAssetClass(FOnAssetClassLoaded OnLoaded) {
    s_onloaded = OnLoaded;
}

void USluaTestCase::callback() {
    s_onloaded.ExecuteIfBound(1024);
}