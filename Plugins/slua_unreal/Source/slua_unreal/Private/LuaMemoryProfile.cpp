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
namespace NS_SLUA {

	// only calc memory alloc from lua script
	// not include alloc from lua vm
	size_t totalMemory;
	
    bool memTrack = false;
	MemoryDetail memoryRecord;

	int LuaMemInfo::push(lua_State * L) const
	{
		lua_newtable(L);
		lua_pushinteger(L, size);
		lua_setfield(L, -2, "size");
		lua_pushstring(L, TCHAR_TO_UTF8(*hint));
		lua_setfield(L, -2, "hint");
		lua_pushlightuserdata(L, ptr);
		lua_setfield(L, -2, "address");
		return 1;
	}

	bool getMemInfo(lua_State* L, void* ptr, size_t size, LuaMemInfo& info);

	inline void addRecord(LuaState* LS, void* ptr, size_t size) {
		if (!memTrack) return;
		// skip if lua_State is null, lua_State hadn't binded to LS
		lua_State* L = LS->getLuaState();
		if (!L) return;

		LuaMemInfo memInfo;
		if (getMemInfo(L, ptr, size, memInfo)) {
			// Log::Log("alloc memory %d from %s",size,TCHAR_TO_UTF8(*memInfo.hint));
			memoryRecord.Add(ptr, memInfo);
			totalMemory += size;
		}
	}

	inline void removeRecord(LuaState* LS, void* ptr, size_t osize) {
		if (!memTrack) return;
		// if ptr record 
		if (memoryRecord.Remove(ptr)) {
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
            ptr = FMemory::Realloc(ptr,nsize);
            addRecord(ls,ptr,nsize);
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
	}

	void LuaMemoryProfile::stop()
	{
		memTrack = false;
	}

	const MemoryDetail& LuaMemoryProfile::memDetail()
	{
		return memoryRecord;
	}

    bool getMemInfo(lua_State* L, void* ptr, size_t size, LuaMemInfo& info) {
        lua_Debug ar;
		for (int i = 0;;i++) {
			if (lua_getstack(L, i, &ar) && lua_getinfo(L, "nSl", &ar)) {
				CallInfo* ci = (CallInfo*)ar.i_ci;
                if (!isLua(ci))
					continue;
    
                if (strcmp(ar.source, SLUA_LUACODE) == 0)
                    continue;
                
				if (strcmp(ar.what, "Lua") == 0 || strcmp(ar.what, "main") == 0) {
					info.ptr = ptr;
					info.size = size;
					info.hint = FString::Printf(TEXT("%s:%d"), UTF8_TO_TCHAR(ar.source), ar.currentline);
					return true;
				}
			}
            else break;
		}
		return false;
    }

#if WITH_EDITOR
	void dumpMemoryDetail()
	{
		Log::Log("Total memory alloc %d bytes", totalMemory);
		for (auto& it : memoryRecord) {
			auto& memInfo = it.Value;
			Log::Log("Memory alloc %d from %s", memInfo.size, TCHAR_TO_UTF8(*memInfo.hint));
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
#endif

}
