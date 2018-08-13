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

#define GET_HELPER() auto helper = FScriptMapHelper::CreateHelperFormInnerProperties(UD->keyProp, UD->valueProp, &UD->map)
#define GET_HELPER_INTERNAL() auto helper = FScriptMapHelper::CreateHelperFormInnerProperties(keyProp, valueProp, &map)

#define GET_CHECKER(tag) \
	auto tag##Checker = LuaObject::getChecker(UD->tag##Prop);\
	if (!tag##Checker) { \
		auto tn = UD->tag##Prop->GetClass()->GetName(); \
		luaL_error(L, "unsupport tag type %s to get", TCHAR_TO_UTF8(*tn)); \
		return 0; \
	}

namespace slua {

	void LuaMap::reg(lua_State* L) {
		SluaUtil::reg(L, "Map", __ctor);
	}

	int LuaMap::push(lua_State* L, UProperty* keyProp, UProperty* valueProp, FScriptMap* buf) {
		const auto map = new LuaMap(keyProp, valueProp, buf);
		return LuaObject::pushType(L, map, "LuaMap", setupMT, gc);
	}

	LuaMap::LuaMap(UProperty* keyProp, UProperty* valueProp, FScriptMap* buf) : keyProp(keyProp), valueProp(valueProp) {
		keyProp->PropertyFlags |= CPF_HasGetValueTypeHash;
		// just hack to clone FScriptMap construct by bp stack
		if(buf) FMemory::Memcpy(&map, buf, sizeof(FScriptMap));
	} 

	LuaMap::~LuaMap() {
		Clear();
	}

	uint8* LuaMap::getKeyPtr(uint8* pairPtr) {
		GET_HELPER_INTERNAL();
		return pairPtr + helper.MapLayout.KeyOffset;
	}

	uint8* LuaMap::getValuePtr(uint8* pairPtr) {
		GET_HELPER_INTERNAL();
		return pairPtr + helper.MapLayout.ValueOffset;
	}

	void LuaMap::Clear() {
		GET_HELPER_INTERNAL();
		helper.EmptyValues();
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
		GET_HELPER();
		return LuaObject::push(L, helper.Num());
	}

	int LuaMap::Get(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		GET_HELPER();
		GET_CHECKER(key);
		FDefaultConstructedPropertyElement tempKey(UD->keyProp);
		auto keyPtr = tempKey.GetObjAddress();
		keyChecker(L, UD->keyProp, (uint8*)keyPtr, 2);

		auto valuePtr = helper.FindValueFromHash(keyPtr);
		if (!valuePtr) {
			auto tn = UD->keyProp->GetClass()->GetName();
			luaL_error(L, "can not find key %s", TCHAR_TO_UTF8(*tn));
			return 0;
		}

		auto ret = LuaObject::push(L, UD->valueProp, valuePtr);
		return ret;
	}

	int LuaMap::Add(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		GET_HELPER();
		GET_CHECKER(key);
		GET_CHECKER(value);
		FDefaultConstructedPropertyElement tempKey(UD->keyProp);
		FDefaultConstructedPropertyElement tempValue(UD->valueProp);
		auto keyPtr = tempKey.GetObjAddress();
		auto valuePtr = tempValue.GetObjAddress();
		keyChecker(L, UD->keyProp, (uint8*)keyPtr, 2);
		valueChecker(L, UD->valueProp, (uint8*)valuePtr, 3);
		helper.AddPair(keyPtr, valuePtr);
		return 0;
	}

	int LuaMap::Remove(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		GET_HELPER();
		GET_CHECKER(key);
		FDefaultConstructedPropertyElement tempKey(UD->keyProp);
		auto keyPtr = tempKey.GetObjAddress();
		keyChecker(L, UD->keyProp, (uint8*)keyPtr, 2);
		return LuaObject::push(L, helper.RemovePair(keyPtr));
	}

	int LuaMap::Clear(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		UD->Clear();
		return 0;
	}

	int LuaMap::setupMT(lua_State* L) {
		LuaObject::setupMTSelfSearch(L);

		RegMetaMethod(L, Num);
		RegMetaMethod(L, Get);
		RegMetaMethod(L, Add);
		RegMetaMethod(L, Remove);
		RegMetaMethod(L, Clear);
		return 0;
	}

	int LuaMap::gc(lua_State* L) {
		CheckUD(LuaMap, L, 1);
		delete UD;
		return 0;
	}

}
