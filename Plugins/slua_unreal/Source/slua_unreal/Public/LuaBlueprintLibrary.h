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
#define LUA_LIB
#include "CoreMinimal.h"
#include "lua/lua.hpp"
#include "UObject/UnrealType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LuaVar.h"
#include "LuaBlueprintLibrary.generated.h"

USTRUCT(BlueprintType)
struct SLUA_UNREAL_API FLuaBPVar {
	GENERATED_USTRUCT_BODY()
public:
	FLuaBPVar(const NS_SLUA::LuaVar& v) :value(v) {}
	FLuaBPVar(NS_SLUA::LuaVar&& v) :value(MoveTemp(v)) {}
	FLuaBPVar() {}

	NS_SLUA::LuaVar value;

	static int checkValue(NS_SLUA::lua_State* L, FStructProperty* p, uint8* params, int i);
};

UCLASS()
class SLUA_UNREAL_API ULuaBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	/** Call a lua function with args */
	UFUNCTION(BlueprintCallable, meta=( DisplayName="Call To Lua With Arguments", WorldContext = "WorldContextObject"), Category="slua")
	static FLuaBPVar CallToLuaWithArgs(UObject* WorldContextObject, FString FunctionName,const TArray<FLuaBPVar>& Args,FString StateName);

	UFUNCTION(BlueprintCallable, meta=( DisplayName="Call To Lua", WorldContext = "WorldContextObject"), Category="slua")
	static FLuaBPVar CallToLua(UObject* WorldContextObject, FString FunctionName,FString StateName);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromInt(int Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromString(FString Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromNumber(float Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FLuaBPVar CreateVarFromBool(bool Value);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category="slua")
	static FLuaBPVar CreateVarFromObject(UObject* WorldContextObject, UObject* Value);

	UFUNCTION(BlueprintCallable, Category="slua")
	static int GetIntFromVar(FLuaBPVar Value,int Index=1);
	
	UFUNCTION(BlueprintCallable, Category="slua")
	static float GetNumberFromVar(FLuaBPVar Value,int Index=1);

	UFUNCTION(BlueprintCallable, Category="slua")
	static FString GetStringFromVar(FLuaBPVar Value,int Index=1);

	UFUNCTION(BlueprintCallable, Category="slua")
	static bool GetBoolFromVar(FLuaBPVar Value,int Index=1);

	UFUNCTION(BlueprintCallable, Category="slua")
	static UObject* GetObjectFromVar(FLuaBPVar Value,int Index=1);
};