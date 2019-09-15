
// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "SluaUtil.h"
#include "LuaObject.h"
#include "LuaVar.h"
#include "LuaDelegate.h"
#include <chrono>

namespace NS_SLUA {
	FString getUObjName(UObject* obj) {
#if WITH_EDITOR
		if (auto ld = Cast<ULuaDelegate>(obj)) {
			return ld->getPropName();
		}
		else {
			return obj->GetFName().ToString();
		}
#else
		return obj->GetFName().ToString();
#endif
	}

	bool isUnrealStruct(const char* tn, UScriptStruct** out) {
		ensure(tn != nullptr && strlen(tn) > 0);
		// if prefix is the unreal prefix
		if (tn[0] == 'F') {
			// if can find it by name in package
			UScriptStruct* ustruct = FindObject<UScriptStruct>(ANY_PACKAGE, UTF8_TO_TCHAR(tn+1));
			if (ustruct) {
				if(out) *out = ustruct;
				return true;
			}
		}
		return false;
	}

	int64_t getTime() {
		return std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000;
	}
}