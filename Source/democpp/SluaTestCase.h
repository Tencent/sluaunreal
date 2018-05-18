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

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "Styling/SlateBrush.h"
#include "Blueprint/UserWidget.h"
#include "SluaTestCase.generated.h"


UCLASS()
class USluaTestCase : public UObject {
    GENERATED_UCLASS_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    TArray<int> GetArray();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    UUserWidget* GetWidget(FString name);

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void TwoArgs(FString a,int b,float c,FString d,UObject* widget);   

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void SetButton(UUserWidget* widget);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	FVector TestStruct(FVector v , ESlateVisibility e, FVector& v2, int i, int& i2, FString str);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	int TestInt_int(int i);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	FString TestIntStr_Str(int i, FString s);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	ESlateVisibility TestIntStrEnum_Enum(int i, FString s, ESlateVisibility e);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	TArray<int> TestIntStrEnum_Arr(int i, FString s, ESlateVisibility e);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	void TestOIntOStrOEnum(int i, int& oi, FString s, FString& os, ESlateVisibility e, ESlateVisibility& oe);

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    FSlateBrush GetBrush();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, meta=( DisplayName="Brush" ))
    FSlateBrush Brush;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance, meta=( DisplayName="Value" ))
    int Value;
};
