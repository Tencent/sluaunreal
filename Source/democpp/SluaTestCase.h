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

#include "LuaBlueprintLibrary.h"
#include "slua.h"
#include "Styling/SlateBrush.h"
#include "SluaTestCase.generated.h"

USTRUCT(BlueprintType)
struct FUserInfo2 {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> p1;
};

USTRUCT(BlueprintType)
struct FUserInfo1 {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> p2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int,FUserInfo2> p3;
};

USTRUCT(BlueprintType)
struct FUserInfo {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* obj;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUserInfo1 others;
};

USTRUCT(BlueprintType)
struct FArrayToBinStringTest
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<uint8> binString;
};

namespace NS_SLUA {
	DefTypeName(FUserInfo);
	DefTypeName(FUserInfo1);
	DefTypeName(FUserInfo2);
}

UCLASS()
class UTestObject : public UObject {
	GENERATED_UCLASS_BODY()
};

UCLASS()
class USluaTestCase : public UObject {
    GENERATED_UCLASS_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    static void StaticFunc();

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UObject> weakptr;

    UPROPERTY(BlueprintReadOnly)
    TArray<UObject*> foos;

    UPROPERTY(BlueprintReadWrite)
    TMap<FString,FString> maps;

    UPROPERTY(BlueprintReadWrite)
    TArray<FString> strs;

	UPROPERTY(BlueprintReadWrite)
	TMap<int,FUserInfo> userInfo;

	UPROPERTY(BlueprintReadWrite)
	TArray<FUserInfo> userArray;

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void setupfoo(UObject* obj);

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void delfoo();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    TArray<int> GetArray();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    TMap<int, FString> GetMap(/*TMap<int, FString> _map*/);

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    TArray<FString> GetArrayStr();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void SetArrayStr(const TArray<FString>& array);

    // reg as extension method
    void SetArrayStrEx(const TArray<FString>& array);
    
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
	const FUserInfo& GetUserInfo();

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

    // for performance test
    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    void EmptyFunc();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    int ReturnInt();

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    int ReturnIntWithInt(int i);

    UFUNCTION(BlueprintCallable, Category="Lua|TestCase")
    int FuncWithStr(FString str);

    const USluaTestCase* constRetFunc() { return nullptr; }

	FORCEINLINE int inlineFunc() { return 1; }

	UPROPERTY(BlueprintReadWrite)
	FUserInfo info;

    DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(int32, FOnTestGetCount, FString, str);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (IsBindableEvent = "True"))
    FOnTestGetCount OnTestGetCount;

    UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
    void TestUnicastDelegate(FString str);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTestAAA, FString, str);
	UPROPERTY(BlueprintAssignable)
	FOnTestAAA OnTestAAA;

	UFUNCTION(BlueprintCallable, Category = "Lua|TestCase")
		void TestAAA(FString str)
	{
		OnTestAAA.Broadcast(str);
	}

	UFUNCTION()
	void TestLuaCallback(FLuaBPVar callback) {
		if (callback.value.isFunction())
			callback.value.call();
	}
    
};
