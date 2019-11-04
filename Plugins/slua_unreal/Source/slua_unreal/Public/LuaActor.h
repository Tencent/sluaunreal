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
#include "LuaState.h"
#include "LuaBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "LuaBlueprintLibrary.h"
#include "LuaActor.generated.h"

#define LUABASE_BODY(NAME) \
protected: \
	virtual void BeginPlay() override { \
	if (!init(this, #NAME, LuaStateName, LuaFilePath)) return; \
		Super::BeginPlay(); \
		PrimaryActorTick.SetTickFunctionEnable(postInit("bCanEverTick")); \
	} \
	virtual void Tick(float DeltaTime) override { \
		tick(DeltaTime); \
	} \
public:	\
	virtual void ProcessEvent(UFunction* func, void* params) override { \
	if (luaImplemented(func, params))  \
		return; \
		Super::ProcessEvent(func, params); \
	} \
	void superTick() override { \
		Super::Tick(deltaTime); \
	} \
	NS_SLUA::LuaVar getSelfTable() const { \
		return luaSelfTable; \
	} \

using slua_Luabase = NS_SLUA::LuaBase;

UCLASS()
class SLUA_UNREAL_API ALuaActor : public AActor, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
	LUABASE_BODY(LuaActor)
public:
	ALuaActor()
		: AActor() 
	{
		PrimaryActorTick.bCanEverTick = true;
	}
	ALuaActor(const FObjectInitializer& ObjectInitializer) 
		: AActor(ObjectInitializer) 
	{
		PrimaryActorTick.bCanEverTick = true;
	}
public:
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua") 
	FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};

UCLASS()
class SLUA_UNREAL_API ALuaPawn : public APawn, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
	LUABASE_BODY(LuaPawn)
public:
	ALuaPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) 
		: APawn(ObjectInitializer)
	{
		PrimaryActorTick.bCanEverTick = true;
	}
public:
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};

UCLASS()
class SLUA_UNREAL_API ALuaCharacter : public ACharacter, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
	LUABASE_BODY(LuaCharacter)
public:
	ALuaCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
		: ACharacter(ObjectInitializer)
	{
		PrimaryActorTick.bCanEverTick = true;
	}
public:
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};

UCLASS()
class SLUA_UNREAL_API ALuaController : public AController, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
	LUABASE_BODY(LuaController)
public:
	ALuaController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
		: AController(ObjectInitializer)
	{
		PrimaryActorTick.bCanEverTick = true;
	}
public:
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};

UCLASS()
class SLUA_UNREAL_API ALuaPlayerController : public APlayerController, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
	LUABASE_BODY(LuaPlayerController)
public:
	ALuaPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
		: APlayerController(ObjectInitializer)
	{
		PrimaryActorTick.bCanEverTick = true;
	}
public:
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLUA_UNREAL_API ULuaActorComponent : public UActorComponent, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()

	struct TickTmpArgs {
		float deltaTime;
		enum ELevelTick tickType;
		FActorComponentTickFunction *thisTickFunction;
	};
protected:
	virtual void BeginPlay() override {
		Super::BeginPlay();
		if (!init(this, "LuaActorComponent", LuaStateName, LuaFilePath)) 
			return;
		if (!GetClass()->HasAnyClassFlags(CLASS_CompiledFromBlueprint))
			ReceiveBeginPlay();
		PrimaryComponentTick.SetTickFunctionEnable(postInit("bCanEverTick"));
	}
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override {
		Super::EndPlay(EndPlayReason);
		if (!GetClass()->HasAnyClassFlags(CLASS_CompiledFromBlueprint))
			ReceiveEndPlay(EndPlayReason);
	}
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override {
		tickTmpArgs.deltaTime = DeltaTime;
		tickTmpArgs.tickType = TickType;
		tickTmpArgs.thisTickFunction = ThisTickFunction;
		if (!tickFunction.isValid()) {
			superTick();
			return;
		}
		tickFunction.call(luaSelfTable, DeltaTime);
	}
public:
	virtual void ProcessEvent(UFunction* func, void* params) override {
	if (luaImplemented(func, params)) 
		return;
		Super::ProcessEvent(func, params);
	}
	void superTick() override {
		Super::TickComponent(tickTmpArgs.deltaTime, tickTmpArgs.tickType, tickTmpArgs.thisTickFunction);
		if (!GetClass()->HasAnyClassFlags(CLASS_CompiledFromBlueprint))
			ReceiveTick(tickTmpArgs.deltaTime);
	}
	NS_SLUA::LuaVar getSelfTable() const {
		return luaSelfTable;
	}
public:
	ULuaActorComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
		: UActorComponent(ObjectInitializer)
	{
		PrimaryComponentTick.bCanEverTick = true;
	}
public:
	struct TickTmpArgs tickTmpArgs;
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}

};

UCLASS()
class SLUA_UNREAL_API ALuaGameModeBase : public AGameModeBase, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
	LUABASE_BODY(LuaGameModeBase)
public:
	// below UPROPERTY and UFUNCTION can't be put to macro LUABASE_BODY
	// so copy & paste them
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
	FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};

UCLASS()
class SLUA_UNREAL_API ALuaHUD : public AHUD, public slua_Luabase, public ILuaTableObjectInterface {
	GENERATED_BODY()
		LUABASE_BODY(LuaHUD)
public:
	ALuaHUD(const FObjectInitializer & ObjectInitializer = FObjectInitializer::Get())
		:AHUD(ObjectInitializer)
	{
		PrimaryActorTick.bCanEverTick = true;
	}
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaFilePath;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
		FString LuaStateName;
	UFUNCTION(BlueprintCallable, Category = "slua")
		FLuaBPVar CallLuaMember(FString FunctionName, const TArray<FLuaBPVar>& Args) {
		return callMember(FunctionName, Args);
	}
};
