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
#include "LuaObject.h"
#include "Layout/Margin.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateBrush.h"
#include "Fonts/SlateFontInfo.h"
#include "Log.h"

#define LUA_WRAPPER_DEBUG

namespace NS_SLUA {

	struct LuaWrapper {

		static void init(lua_State* L);
		static int pushValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms);
		static int checkValue(lua_State* L, FStructProperty* p, UScriptStruct* uss, uint8* parms, int i);

	};

}

