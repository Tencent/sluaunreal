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
#include "lua.h"
#include "LatentDelegate.generated.h"

namespace NS_SLUA {
	class LuaState;
}

UCLASS()
class SLUA_UNREAL_API ULatentDelegate : public UObject {
	GENERATED_UCLASS_BODY()
public:
	static const FString NAME_LatentCallback;

	UFUNCTION(BlueprintCallable, Category = "Lua|LatentDelegate")
	void OnLatentCallback(int32 threadRef);
	
	void bindLuaState(NS_SLUA::LuaState *_luaState);
	int getThreadRef(NS_SLUA::lua_State *L);

protected:
	NS_SLUA::LuaState* luaState;
};