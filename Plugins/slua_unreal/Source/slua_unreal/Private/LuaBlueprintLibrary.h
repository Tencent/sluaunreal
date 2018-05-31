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
#include "lua/lua.hpp"
#include "UObject/UnrealType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LuaVar.h"
#include "LuaBlueprintLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLuaBPVar {
	GENERATED_USTRUCT_BODY()
public:
	FLuaBPVar(const slua::LuaVar& v):value(v) {}
	FLuaBPVar() {}

	slua::LuaVar value;
};

UCLASS()
class UMG_API ULuaBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	/** Call a lua function with args */
	UFUNCTION(BlueprintCallable, meta=( DisplayName="Call To Lua" ), Category="slua")
	static FLuaBPVar CallToLua(FString FunctionName,const TArray<FLuaBPVar>& Args);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromInt(int Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromString(FString Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromNumber(float Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromBool(bool Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromObject(UObject* Value);
};