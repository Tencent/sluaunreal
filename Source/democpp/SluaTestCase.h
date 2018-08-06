// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

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
    static void StaticFunc();


    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    TArray<int> GetArray();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    TArray<FString> GetArrayStr();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void SetArrayStr(const TArray<FString>& array);

    // reg as extension method
    void SetArrayStrEx(const TArray<FString>& array);
    

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


    DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAssetClassLoaded, int, P);

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
	static void LoadAssetClass(FOnAssetClassLoaded OnLoaded);

    static void callback();
};
