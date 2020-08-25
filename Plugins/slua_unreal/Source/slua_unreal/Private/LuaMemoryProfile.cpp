// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "LuaMemoryProfile.h"
#include "LuaState.h"
#include "Log.h"
#include "lua/lstate.h"
#include "LuaProfiler.h"
namespace NS_SLUA {

	// only calc memory alloc from lua script
	// not include alloc from lua vm
	size_t totalMemory;
	
    bool memTrack = false;
	TMap<LuaState*, MemoryDetail> memoryRecord;
	TMap<LuaState*, TArray<LuaMemInfo>> memoryIncreaseThisFrame;

	bool getMemInfo(LuaState* ls, size_t size, LuaMemInfo& info);

	MemoryDetail* TryGetMemoryRecord(LuaState* LS)
	{
		auto* memoryRecordDetail = memoryRecord.Find(LS);
		if (!memoryRecordDetail)
		{
			memoryRecordDetail = &memoryRecord.Add(LS);
		}
		return memoryRecordDetail;
	}

	TArray<LuaMemInfo>* TryGetMemoryIncrease(LuaState* LS)
	{
		auto* memoryIncrease = memoryIncreaseThisFrame.Find(LS);
		if (!memoryIncrease)
		{
			memoryIncrease = &memoryIncreaseThisFrame.Add(LS);
		}
		return memoryIncrease;
	}

	inline void addRecord(LuaState* LS, void* ptr, size_t size, LuaMemInfo &memInfo) {
		if (!memTrack) return;
		// skip if lua_State is null, lua_State hadn't binded to LS
		lua_State* L = LS->getLuaState();
		if (!L) return;

		// Log::Log("alloc memory %d from %s",size,TCHAR_TO_UTF8(*memInfo.hint));
		memInfo.ptr = (int64)ptr;
		memInfo.bAlloc = true;

		auto* memoryRecordDetail = TryGetMemoryRecord(LS);
		memoryRecordDetail->Add(ptr, memInfo);

		auto* memoryIncrease = TryGetMemoryIncrease(LS);
		memoryIncrease->Add(memInfo);
		totalMemory += size;
	}

	inline void removeRecord(LuaState* LS, void* ptr, size_t osize) {
		if (!memTrack) return;
		// if ptr record

		auto* memoryRecordDetail = TryGetMemoryRecord(LS);
		
		auto memInfoPtr = memoryRecordDetail->Find(ptr);
		if (memInfoPtr) {
			memInfoPtr->bAlloc = false;
			TryGetMemoryIncrease(LS)->Add(*memInfoPtr);
			memoryRecordDetail->Remove(ptr);
			// Log::Log("free memory %p size %d", ptr, osize);
			
			totalMemory -= osize;
		}
	}

    void* LuaMemoryProfile::alloc (void *ud, void *ptr, size_t osize, size_t nsize) {
        LuaState* ls = (LuaState*)ud;
        if (nsize == 0) {
            removeRecord(ls, ptr, osize);
            FMemory::Free(ptr);
            return NULL;
        }
        else {
			if(ptr) removeRecord(ls, ptr, osize);
			
			LuaMemInfo memInfo;
        	// get stack before realloc to avoid luaD_reallocstack crash!
			bool bHasStack = getMemInfo(ls, nsize, memInfo);
            ptr = FMemory::Realloc(ptr,nsize);
        	if (bHasStack)
				addRecord(ls,ptr,nsize,memInfo);
            return ptr;
        }
    }

	size_t LuaMemoryProfile::total()
	{
		return totalMemory;
	}

	void LuaMemoryProfile::start()
	{
        memTrack = true;
		onStart();
	}

	void LuaMemoryProfile::onStart() 
	{
		memoryRecord.Empty();
		memoryIncreaseThisFrame.Empty();
	}

	void LuaMemoryProfile::stop()
	{
		memTrack = false;
	}

	void LuaMemoryProfile::tick(LuaState* LS)
	{
		auto *memoryIncrease = TryGetMemoryIncrease(LS);
		memoryIncrease->Empty();
	}

	const MemoryDetail& LuaMemoryProfile::memDetail(LuaState* LS)
	{
		auto *memoryRecordDetail = TryGetMemoryRecord(LS);
		return *memoryRecordDetail;
	}

	TArray<LuaMemInfo>& LuaMemoryProfile::memIncreaceThisFrame(LuaState* LS)
	{
		auto *memoryIncrease = TryGetMemoryIncrease(LS);
		return *memoryIncrease;
	}

	bool isCoroutineAlive(lua_State* co)
	{
		switch (lua_status(co)) {
		case LUA_YIELD:
			return false;
			break;
		case LUA_OK: {
			lua_Debug ar;
			if (lua_getstack(co, 0, &ar) > 0)
				return true;
			break;
		}
		default:
			break;
		}
		
		return false;
	}

    bool getMemInfo(LuaState* ls, size_t size, LuaMemInfo& info) {
		if (!memTrack) return false;
		// skip if lua_State is null, lua_State hadn't binded to LS
		lua_State* L = ls->getLuaState();
		if (!L) return false;

		info.ptr = 0;
		
		FString firstCName = TEXT("C");
		
		for (int i = 0;;i++) {
			lua_Debug ar;
			AutoStack as(L);
			if (lua_getstack(L, i, &ar) && lua_getinfo(L, "nSlf", &ar)) {
				if (strcmp(ar.what, "C") == 0) {
					if (ar.name) {
						firstCName += UTF8_TO_TCHAR(ar.name);
						lua_CFunction cfunc = lua_tocfunction(L, -1);
						if (cfunc == LuaProfiler::resumeFunc) {
							if (lua_isthread(L, 1)) {
								lua_State* L1 = lua_tothread(L, 1);
								if (isCoroutineAlive(L1)) {
									L = L1;
									i = -1;
									continue;
								}
							}
						}
					}
				}
    
                if (strcmp(ar.source, SLUA_LUACODE) == 0)
                    continue;

				if (strcmp(ar.source, LuaProfiler::ChunkName) == 0)
					return false;
                
				if (strcmp(ar.what, "Lua") == 0 || strcmp(ar.what, "main") == 0) {
					info.size = size;
					info.hint = UTF8_TO_TCHAR(ar.source);
					info.lineNumber = ar.currentline;
					return true;
				}
			}
            else break;
		}

		info.size = size;
		info.hint = FString::Printf(TEXT("%s"), *firstCName);
		info.lineNumber = 0;
		return true;
    }

	void dumpMemoryDetail()
	{
		Log::Log("Total memory alloc %d bytes", totalMemory);
		for (auto& it : memoryRecord) {
			for (auto& itMemInfo : it.Value) {
				auto& memInfo = itMemInfo.Value;
				Log::Log("Memory alloc %d from %s:%d", memInfo.size, TCHAR_TO_UTF8(*memInfo.hint), memInfo.lineNumber);
			}
		}
	}

	static FAutoConsoleCommand CVarDumpMemoryDetail(
		TEXT("slua.DumpMemoryDetail"),
		TEXT("Dump memory datail information"),
		FConsoleCommandDelegate::CreateStatic(dumpMemoryDetail),
		ECVF_Cheat);

	static FAutoConsoleCommand CVarStopMemTrack(
		TEXT("slua.StopMemoryTrack"),
		TEXT("Stop track memory info"),
		FConsoleCommandDelegate::CreateStatic(LuaMemoryProfile::stop),
		ECVF_Cheat);

	static FAutoConsoleCommand CVarStartMemTrack(
		TEXT("slua.StartMemoryTrack"),
		TEXT("Start track memory info"),
		FConsoleCommandDelegate::CreateStatic(LuaMemoryProfile::start),
		ECVF_Cheat);
}
