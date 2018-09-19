// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaMap.h"
#include "SluaLib.h"
#include "LuaObject.h"
#include "Log.h"
#include <algorithm>

#define GET_CHECKER(tag) \
	auto tag##Checker = LuaObject::getChecker(UD->tag##Prop);\
	if (!tag##Checker) { \
		auto tn = UD->tag##Prop->GetClass()->GetName(); \
		luaL_error(L, "unsupport tag type %s to get", TCHAR_TO_UTF8(*tn)); \
		return 0; \
	}

namespace slua {

	DefTypeName(LuaMap::Enumerator);

	void LuaMap::reg(lua_State* L) {
		SluaUtil::reg(L, "Map", __ctor);
	}

	int LuaMap::push(lua_State* L, UProperty* keyProp, UProperty* valueProp, FScriptMap* buf) {
		const auto map = new LuaMap(keyProp, valueProp, buf);
		return LuaObject::pushType(L, map, "LuaMap", setupMT, gc);
	}

	LuaMap::LuaMap(UProperty* kp, UProperty* vp, FScriptMap* buf) : 
		keyProp(kp), 
		valueProp(vp) ,
		helper(FScriptMapHelper::CreateHelperFormInnerProperties(keyProp, valueProp, &map)) {
		keyProp->PropertyFlags |= CPF_HasGetValueTypeHash;
		if (buf) {
			// just hack to clone FScriptMap construct by bp stack
			FMemory::Memcpy(&map, buf, sizeof(FScriptMap));
			createdByBp = true;
		} else {
			createdByBp = false;
		}
		
	} 

	LuaMap::~LuaMap() {
		Clear();
	}

	uint8* LuaMap::getKeyPtr(uint8* pairPtr) {
		return pairPtr + helper.MapLayout.KeyOffset;
	}

	uint8* LuaMap::getValuePtr(uint8* pairPtr) {
		return pairPtr + helper.MapLayout.ValueOffset;
	}

	void LuaMap::Clear() {
		EmptyValues();
	}

	// modified FScriptMapHelper::EmptyValues function to add value property offset on value ptr 
	void LuaMap::EmptyValues(int32 Slack) {
		checkSlow(Slack >= 0);

		int32 OldNum = Num();
		if (OldNum) {
			DestructItems(0, OldNum);
		}
		if (OldNum || Slack) {
			map.Empty(Slack, helper.MapLayout);
		}
	}

	// modified FScriptMapHelper::DestructItems function to add value property offset on value ptr 
	void LuaMap::DestructItems(uint8* PairPtr, uint32 Stride, int32 Index, int32 Count, bool bDestroyKeys, bool bDestroyValues) {
		auto valueOffset = createdByBp ? 0 : helper.MapLayout.ValueOffset;
		for (; Count; ++Index) {
			if (helper.IsValidIndex(Index)) {
				if (bDestroyKeys) {
					keyProp->DestroyValue_InContainer(PairPtr);
				}
				if (bDestroyValues) {
					valueProp->DestroyValue_InContainer(PairPtr + valueOffset);
				}
				--Count;
			}
			PairPtr += Stride;
		}
	}

	// modified FScriptMapHelper::DestructItems function to add value property offset on value ptr 
	void LuaMap::DestructItems(int32 Index, int32 Count) {
		check(Index >= 0);
		check(Count >= 0);

		if (Count == 0) {
			return;
		}

		bool bDestroyKeys = !(keyProp->PropertyFlags & (CPF_IsPlainOldData | CPF_NoDestructor));
		bool bDestroyValues = !(valueProp->PropertyFlags & (CPF_IsPlainOldData | CPF_NoDestructor));

		if (bDestroyKeys || bDestroyValues) {
			uint32 Stride = helper.MapLayout.SetLayout.Size;
			uint8* PairPtr = (uint8*)map.GetData(Index, helper.MapLayout);
			DestructItems(PairPtr, Stride, Index, Count, bDestroyKeys, bDestroyValues);
		}
	}

	// modified FScriptMapHelper::RemovePair function to call LuaMap::RemoveAt
	bool LuaMap::RemovePair(const void* KeyPtr) {
		UProperty* LocalKeyPropForCapture = keyProp;
		if (uint8* Entry = map.FindValue(KeyPtr, helper.MapLayout,
			[LocalKeyPropForCapture](const void* ElementKey) { return LocalKeyPropForCapture->GetValueTypeHash(ElementKey); },
			[LocalKeyPropForCapture](const void* A, const void* B) { return LocalKeyPropForCapture->Identical(A, B); }
		)) {
			int32 Idx = (Entry - (uint8*)map.GetData(0, helper.MapLayout)) / helper.MapLayout.SetLayout.Size;
			RemoveAt(Idx);
			return true;
		} else {
			return false;
		}
	}

	// modified FScriptMapHelper::RemoveAt function to call LuaMap::DestructItems
	void LuaMap::RemoveAt(int32 Index, int32 Count) {
		check(helper.IsValidIndex(Index));
		DestructItems(Index, Count);
		for (; Count; ++Index) {
			if (helper.IsValidIndex(Index)) {
				map.RemoveAt(Index, helper.MapLayout);
				--Count;
			}
		}
	}

	int32 LuaMap::Num() const {
		return helper.Num();
	}

	int LuaMap::__ctor(lua_State* L) {
		auto keyType = (UE4CodeGen_Private::EPropertyClass)LuaObject::checkValue<int>(L, 1);
		auto valueType = (UE4CodeGen_Private::EPropertyClass)LuaObject::checkValue<int>(L, 2);
		auto keyProp = LuaObject::getDefaultProperty(L, keyType);
		auto valueProp = LuaObject::getDefaultProperty(L, valueType);
		return push(L, keyProp, valueProp, nullptr);
	}

	int LuaMap::Num(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		return LuaObject::push(L, UD->Num());
	}

	int LuaMap::Get(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		GET_CHECKER(key);
		FDefaultConstructedPropertyElement tempKey(UD->keyProp);
		auto keyPtr = tempKey.GetObjAddress();
		keyChecker(L, UD->keyProp, (uint8*)keyPtr, 2);

		auto valuePtr = UD->helper.FindValueFromHash(keyPtr);
		if (valuePtr) {
			LuaObject::push(L, UD->valueProp, valuePtr);
			LuaObject::push(L, true);
		} else {
			LuaObject::pushNil(L);
			LuaObject::push(L, false);
		}
		return 2;
	}

	int LuaMap::Add(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		GET_CHECKER(key);
		GET_CHECKER(value);
		FDefaultConstructedPropertyElement tempKey(UD->keyProp);
		FDefaultConstructedPropertyElement tempValue(UD->valueProp);
		auto keyPtr = tempKey.GetObjAddress();
		auto valuePtr = tempValue.GetObjAddress();
		keyChecker(L, UD->keyProp, (uint8*)keyPtr, 2);
		valueChecker(L, UD->valueProp, (uint8*)valuePtr, 3);
		UD->helper.AddPair(keyPtr, valuePtr);
		return 0;
	}

	int LuaMap::Remove(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		GET_CHECKER(key);
		FDefaultConstructedPropertyElement tempKey(UD->keyProp);
		auto keyPtr = tempKey.GetObjAddress();
		keyChecker(L, UD->keyProp, (uint8*)keyPtr, 2);
		return LuaObject::push(L, UD->RemovePair(keyPtr));
	}

	int LuaMap::Clear(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		UD->Clear();
		return 0;
	}

	int LuaMap::Pairs(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		auto iter = new LuaMap::Enumerator();
		iter->map = UD;
		iter->index = 0;
		iter->num = UD->helper.Num();
		lua_pushcfunction(L, LuaMap::Enumerable);
		LuaObject::pushType(L, iter, "LuaMap::Enumerator", nullptr, LuaMap::Enumerator::gc);
		LuaObject::pushNil(L);
		return 3;
	}

	int LuaMap::Enumerable(lua_State* L) {
		CheckUD(LuaMap::Enumerator, L, 1);
		auto map = UD->map;
		auto& helper = map->helper;
		do {
			if (UD->num <= 0) {
				return 0;
			} else if (helper.IsValidIndex(UD->index)) {
				auto pairPtr = helper.GetPairPtr(UD->index);
				auto keyPtr = pairPtr + helper.MapLayout.KeyOffset;
				auto valuePtr = pairPtr + helper.MapLayout.ValueOffset;
				LuaObject::push(L, map->keyProp, keyPtr);
				LuaObject::push(L, map->valueProp, valuePtr);
				UD->index += 1;
				UD->num -= 1;
				return 2;
			} else {
				UD->index += 1;
			}
		} while (true);
	}

	int LuaMap::Enumerator::gc(lua_State* L) {
		CheckUD(LuaMap::Enumerator, L, 1);
		delete UD;
		return 0;
	}

	int LuaMap::gc(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		delete UD;
		return 0;
	}

	int LuaMap::setupMT(lua_State* L) {
		LuaObject::setupMTSelfSearch(L);

		RegMetaMethod(L, Pairs);
		RegMetaMethod(L, Num);
		RegMetaMethod(L, Get);
		RegMetaMethod(L, Add);
		RegMetaMethod(L, Remove);
		RegMetaMethod(L, Clear);

		RegMetaMethodByName(L, "__pairs", Pairs);

		return 0;
	}

}
