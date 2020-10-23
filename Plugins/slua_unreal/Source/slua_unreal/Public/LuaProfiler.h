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
#include "lua/lua.hpp"

namespace NS_SLUA {
    
	enum ProfilerHookEvent
	{
        PHE_MEMORY_TICK = -2,
		PHE_TICK = -1,
		PHE_CALL = 0,
		PHE_RETURN = 1,
		PHE_LINE = 2,
		PHE_TAILRET = 4,
        PHE_MEMORY_GC = 5,
		PHE_MEMORY_INCREACE = 6,
		PHE_ENTER_COROUTINE = 7,
		PHE_EXIT_COROUTINE = 8,
	};

	class SLUA_UNREAL_API LuaProfiler
	{
	public:
		LuaProfiler(const char* funcName);
		~LuaProfiler();
		
		static void init(class LuaState* LS);
		static void tick(class LuaState* LS);
		static void clean(class LuaState* LS);

		static const char* ChunkName;
		static lua_CFunction resumeFunc;
	};

#ifdef ENABLE_PROFILER
	// for native function
#define PROFILER_WATCHER(x)  NS_SLUA::LuaProfiler x(__FUNCTION__);
#define PROFILER_WATCHER_X(x,name)  NS_SLUA::LuaProfiler x(name);
#else
#define PROFILER_WATCHER(x) 
#define PROFILER_WATCHER_X(x,name)
#endif

}
