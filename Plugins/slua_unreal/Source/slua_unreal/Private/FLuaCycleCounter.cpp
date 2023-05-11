// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

// Tencent is pleased to support the open source community by making sluaunreal available.

#include "FLuaCycleCounter.h"

#if STATS
#include "Stats/Stats.h"
DECLARE_STATS_GROUP(TEXT("LuaCounterGroup"), STATGROUP_LuaCouter, STATCAT_Advanced);

static TArray<FCycleCounter*> counterStack;
static TArray<FString> counterFunction;

bool FLuaCycleCounter::bOpenLog;

void FLuaCycleCounter::counterStart(const FString& CounterName,int Type,int Level)
{
    FCycleCounter* counter = new FCycleCounter();
    static TMap<FString, TStatId> luaFunctionStatIdMap;
    auto statIdPtr = luaFunctionStatIdMap.Find(CounterName);
    if (statIdPtr)
    {
        counter->Start(*statIdPtr);
    }
    else
    {
        TStatId statId = FDynamicStats::CreateStatId<FStatGroup_STATGROUP_LuaCouter>(CounterName);
        counter->Start(statId);
        luaFunctionStatIdMap.Add(CounterName, statId);
    }
    
    counterStack.Push(counter);
    counterFunction.Push(CounterName);

    if (bOpenLog)
    {
        UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] FLuaCycleCounterStart CouterName %s, StartType is %d, Level is %d"), *CounterName, Type,Level);
    }
}

void FLuaCycleCounter::counterStop(int Type, int Level, const FString& CounterName)
{
    if (counterStack.Num() > 0)
    {
        FCycleCounter* counter = counterStack.Pop();
        FString functionName = counterFunction.Pop();
        counter->Stop();

        if (bOpenLog)
        {
            UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] counterStop pop CouterName %s. stop CouterName %s. Type is %d, Level is %d,Stack Num is %d"), *functionName, *CounterName, Type, Level, counterStack.Num());
            if (counterStack.Num() == 0)
            {
                UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] counterStop lastone CouterName %s"), *functionName);
            }
        }
        delete counter;
    }
    else
    {
        if (bOpenLog)
        {
            UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] stop CouterName %s. Type is %d, Level is %d"), *CounterName, Type, Level);
            UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] counterStop overflow "));
        }
    }
}

void FLuaCycleCounter::clearCounter()
{
    while (counterStack.Num()>0)
    {
        FLuaCycleCounter::counterStop(99);
    }

}
#else
void FLuaCycleCounter::counterStart(const FString& CouterName, int Type, int Level)
{

}

void FLuaCycleCounter::counterStop(int Type, int Level, const FString& CouterName)
{

}

void FLuaCycleCounter::clearCounter()
{

}

#endif