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

	class SLUA_UNREAL_API LuaProfiler
	{
	public:
		LuaProfiler(const char* funcName);
		~LuaProfiler();
		
		static void init(lua_State* L);
		static void tick();
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