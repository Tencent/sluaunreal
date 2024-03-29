// Fill out your copyright notice in the Description page of Project Settings.

#include "democppGameModeBase.h"

void AdemocppGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    TArray<FPlayerData> PlayerDataArray;
    PlayerDataArray.Add({TEXT("LiLei"), TEXT("1")});
    PlayerDataArray.Add({ TEXT("HanMeiMei"), TEXT("2") });
    CallLuaFunction(TEXT("CppCallLuaFunctionWithArray"), PlayerDataArray);

    TSet<FPlayerData> PlayerDataSet;
    PlayerDataSet.Add({ TEXT("LiLei"), TEXT("3") });
    PlayerDataSet.Add({ TEXT("HanMeiMei"), TEXT("4") });
    CallLuaFunction(TEXT("CppCallLuaFunctionWithSet"), PlayerDataSet);

    TMap<int32, FPlayerData> PlayerDataMap;
    PlayerDataMap.Add(3, { TEXT("LiLei"), TEXT("5") });
    PlayerDataMap.Add(5, { TEXT("HanMeiMei"), TEXT("6") });
    CallLuaFunction(TEXT("CppCallLuaFunctionWithMap"), PlayerDataMap);
}
