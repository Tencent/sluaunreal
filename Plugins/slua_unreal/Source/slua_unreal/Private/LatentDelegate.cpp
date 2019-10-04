// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LatentDelegate.h"
#include "LuaState.h"

const FString ULatentDelegate::NAME_LatentCallback = TEXT("OnLatentCallback");

ULatentDelegate::ULatentDelegate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, luaState(nullptr)
{
}

void ULatentDelegate::OnLatentCallback(int32 threadRef)
{
	luaState->resumeThread(threadRef);
}

void ULatentDelegate::bindLuaState(NS_SLUA::LuaState *_luaState)
{
	luaState = _luaState;
}

int ULatentDelegate::getThreadRef(NS_SLUA::lua_State *L)
{
	ensure(L);

	int threadRef = luaState->findThread(L);
	if (threadRef == LUA_REFNIL)
	{
		threadRef = luaState->addThread(L);
	}
	return threadRef;
}