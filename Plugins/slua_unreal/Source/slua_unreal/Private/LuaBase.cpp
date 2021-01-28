// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "LuaBase.h"
#include "UObject/Script.h"
#include "LuaState.h"
#include "UObject/StructOnScope.h"
#include "LuaUserWidget.h"
#include "LuaActor.h"

#if ((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
extern uint8 GRegisterNative(int32 NativeBytecodeIndex, const FNativeFuncPtr& Func);
#else
extern uint8 GRegisterNative(int32 NativeBytecodeIndex, const Native& Func);
#endif
#define Ex_LuaHook (EX_Max-1)

ULuaTableObjectInterface::ULuaTableObjectInterface(const class FObjectInitializer& OI)
	:Super(OI) {}

namespace NS_SLUA {

	bool LuaBase::luaImplemented(UFunction * func, void * params)
	{
		if (indexFlag!=IF_NONE && (func==currentFunction || currentFunction==nullptr)) return false;

		if (!func->HasAnyFunctionFlags(EFunctionFlags::FUNC_BlueprintEvent))
			return false;

		if (!luaSelfTable.isTable())
			return false;

		NS_SLUA::LuaVar lfunc = luaSelfTable.getFromTable<NS_SLUA::LuaVar>((const char*)TCHAR_TO_UTF8(*func->GetName()), true);
		if (!lfunc.isValid()) return false;

		return lfunc.callByUFunction(func, (uint8*)params, nullptr, nullptr, &luaSelfTable);
	}

	// Called every frame
	void LuaBase::tick(float DeltaTime)
	{
		deltaTime = DeltaTime;
		if (!tickFunction.isValid()) {
			superTick();
			return;
		}
		tickFunction.call(luaSelfTable, DeltaTime);
	}

	void LuaBase::superTick(lua_State* L)
	{
		deltaTime = luaL_checknumber(L, 2);
		superTick();
	}

	int LuaBase::superOrRpcCall(lua_State* L,UFunction* func)
	{
		UObject* obj = context.Get();
		if (!obj) return 0;

		NewObjectRecorder objectRecorder(L);

		uint8* params = (uint8*)FMemory_Alloca(func->ParmsSize);
		FMemory::Memzero(params, func->ParmsSize);
		for (TFieldIterator<FProperty> it(func); it && it->HasAnyPropertyFlags(CPF_Parm); ++it)
		{
			FProperty* localProp = *it;
			checkSlow(localProp);
			if (!localProp->HasAnyPropertyFlags(CPF_ZeroConstructor))
			{
				localProp->InitializeValue_InContainer(params);
			}
		}

		LuaObject::fillParam(L, 2, func, params);
		{
			// call function with params
			LuaObject::callUFunction(L, obj, func, params);
		}
		// return value to push lua stack
		int outParamCount = LuaObject::returnValue(L, func, params, &objectRecorder);

		for (TFieldIterator<FProperty> it(func); it && (it->HasAnyPropertyFlags(CPF_Parm)); ++it)
		{
			it->DestroyValue_InContainer(params);
		}

		return outParamCount;
	}

	void LuaBase::dispose()
	{
		if (!luaSelfTable.isValid())
		{
			return;
		}
		auto* L = luaSelfTable.getState();

		luaSelfTable.push(L);
		lua_pushnil(L);
		lua_setfield(L, -2, SLUA_CPPINST);
		lua_pop(L, 1);

		luaSelfTable.free();
	}

	int LuaBase::__index(NS_SLUA::lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		void* ud = lua_touserdata(L, -1);
		if (!ud)
			luaL_error(L, "expect LuaBase table at arg 1");
		lua_pop(L, 1);
		UObject* obj = (UObject*)ud;
		if (!NS_SLUA::LuaObject::isUObjectValid(obj))
		{
			return 0;
		}
		LuaObject::push(L, obj, true);

		// push key
		lua_pushvalue(L, 2);
		// get field from real actor
		lua_gettable(L, -2);
		return 1;
	}

	static int setParent(NS_SLUA::lua_State* L) {
		// set field to obj, may raise an error
		ensure(lua_type(L, 1) == LUA_TUSERDATA);
		lua_settable(L, 1);
		return 0;
	}

	int LuaBase::__newindex(NS_SLUA::lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		void* ud = lua_touserdata(L, -1);
		if (!ud)
			luaL_error(L, "expect LuaBase table at arg 1");
		lua_pop(L, 1);
		LuaObject::push(L, (UObject*)ud, true);

		lua_pushcfunction(L, setParent);
		ensure(lua_type(L, -2) == LUA_TUSERDATA);
		// push cpp inst
		lua_pushvalue(L, -2);
		// push key
		lua_pushvalue(L, 2);
		// push value
		lua_pushvalue(L, 3);
		// set ok?
		if (lua_pcall(L, 3, 0, 0)) {
			lua_pop(L, 1);
			// push key
			lua_pushvalue(L, 2);
			// push value
			lua_pushvalue(L, 3);
			// rawset to table
			lua_rawset(L, 1);
		}
		return 0;
	}

#if ((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
	void LuaBase::hookBpScript(UFunction* func, FNativeFuncPtr hookfunc) {
#else
	void LuaBase::hookBpScript(UFunction* func, Native hookfunc) {
#endif
		static bool regExCode = false;
		if (!regExCode) {
			GRegisterNative(Ex_LuaHook, hookfunc);
			regExCode = true;
		}
		// if func had hooked
		if (func->Script.Num() > 5 && func->Script[5] == Ex_LuaHook)
			return;
		// if script isn't empty
		if (func->Script.Num() > 0) {
			// goto 8(a uint32 value) to skip return
			uint8 code[] = { EX_JumpIfNot,8,0,0,0,Ex_LuaHook,EX_Return,EX_Nothing };
			func->Script.Insert(code, sizeof(code), 0);
		}
	}

	LuaBase* checkBase(UObject* obj) {
		if (auto uit = Cast<ULuaUserWidget>(obj))
			return uit;
		else if (auto ait = Cast<ALuaActor>(obj))
			return ait;
		else if (auto pit = Cast<ALuaPawn>(obj))
			return pit;
		else if (auto cit = Cast<ALuaCharacter>(obj))
			return cit;
		else if (auto coit = Cast<ALuaController>(obj))
			return coit;
		else if (auto pcit = Cast<ALuaPlayerController>(obj))
			return pcit;
		else if (auto acit = Cast<ULuaActorComponent>(obj))
			return acit;
		else if (auto gmit = Cast<ALuaGameModeBase>(obj))
			return gmit;
		else if (auto hit = Cast<ALuaHUD>(obj))
			return hit;
		else
			return nullptr;
	}

#if ((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
	DEFINE_FUNCTION(LuaBase::luaOverrideFunc)
#else
	void LuaBase::luaOverrideFunc(FFrame& Stack, RESULT_DECL)
#endif
	{
		UFunction* func = Stack.Node;
		ensure(func);
		LuaBase* lb = checkBase(Stack.Object);

		// maybe lb is nullptr, some member function with same name in different class
		// we don't care about it
		if (!lb) {
			*(bool*)RESULT_PARAM = false;
			return;
		}

		ensure(lb);

		if (lb->indexFlag==IF_SUPER && lb->currentFunction==func) {
			*(bool*)RESULT_PARAM = false;
			return;
		}

		void* params = Stack.Locals;

		LuaVar& luaSelfTable = lb->luaSelfTable;
		NS_SLUA::LuaVar lfunc = luaSelfTable.getFromTable<NS_SLUA::LuaVar>(func->GetName(), true);
		if (lfunc.isValid()) {
			lfunc.callByUFunction(func, (uint8*)params, Stack.OutParms, nullptr, &luaSelfTable);
			*(bool*)RESULT_PARAM = true;
		}
		else {
			// if RESULT_PARAM is true, don't execute code behind this hook
			// otherwise execute code continue
			// don't have lua override function, continue execute bp code
			*(bool*)RESULT_PARAM = false;
		}

		
	}

	void LuaBase::bindOverrideFunc(UObject* obj)
	{
		ensure(obj && luaSelfTable.isValid());
		UClass* cls = obj->GetClass();
		ensure(cls);

		EFunctionFlags availableFlag = FUNC_BlueprintEvent;
		for (TFieldIterator<UFunction> it(cls); it; ++it) {
			if (!(it->FunctionFlags&availableFlag))
				continue;
			if (luaSelfTable.getFromTable<LuaVar>(it->GetName(), true).isFunction()) {
#if ((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
				hookBpScript(*it, (FNativeFuncPtr)&luaOverrideFunc);
#else
				hookBpScript(*it, (Native)&LuaBase::luaOverrideFunc);
#endif
			}
		}
	}

	template<typename T>
	UFunction* getSuperOrRpcFunction(lua_State* L) {
		CheckUD(T, L, 1);
		lua_getmetatable(L, 1);
		const char* name = LuaObject::checkValue<const char*>(L, 2);

		lua_getfield(L, -1, name);
		lua_remove(L, -2); // remove mt of ud
		if (!lua_isnil(L, -1)) {
			return nullptr;
		}

		UObject* obj = UD->base->getContext().Get();
		if (!obj)
			luaL_error(L, "Context is invalid");
		if (UD->base->getIndexFlag() == LuaBase::IF_RPC)
			luaL_error(L, "Can't call super in RPC function");

		UFunction* func = obj->GetClass()->FindFunctionByName(UTF8_TO_TCHAR(name));
		if (!func || (func->FunctionFlags&FUNC_BlueprintEvent) == 0)
			luaL_error(L, "Can't find function %s in super", name);

		return func;
	}

	int LuaBase::__superIndex(lua_State* L) {
		
		UFunction* func = getSuperOrRpcFunction<LuaSuper>(L);
		if (!func) return 1;

		lua_pushlightuserdata(L, func);
		lua_pushcclosure(L, __superCall, 1);
		return 1;
	}

	int LuaBase::__rpcIndex(lua_State* L) {

		UFunction* func = getSuperOrRpcFunction<LuaRpc>(L);
		if (!func) return 1;

		lua_pushlightuserdata(L, func);
		lua_pushcclosure(L, __rpcCall, 1);
		return 1;
	}

	int LuaBase::__superTick(lua_State* L) {
		CheckUD(LuaSuper, L, 1);
		UD->base->indexFlag = IF_SUPER;
		UD->base->superTick(L);
		UD->base->indexFlag = IF_NONE;
		return 0;
	}

	int LuaBase::__superCall(lua_State* L)
	{
		CheckUD(LuaSuper, L, 1);
		lua_pushvalue(L, lua_upvalueindex(1));
		UFunction* func = (UFunction*) lua_touserdata(L, -1);
		if (!func || !func->IsValidLowLevel())
			luaL_error(L, "Super function is isvalid");
		lua_pop(L, 1);
		auto lbase = UD->base;
		ensure(lbase);
		lbase->currentFunction = func;
		lbase->indexFlag = IF_SUPER;
		int ret = lbase->superOrRpcCall(L, func);
		lbase->indexFlag = IF_NONE;
		lbase->currentFunction = nullptr;
		return ret;
	}

	int LuaBase::__rpcCall(lua_State* L)
	{
		CheckUD(LuaRpc, L, 1);
		lua_pushvalue(L, lua_upvalueindex(1));
		UFunction* func = (UFunction*)lua_touserdata(L, -1);
		if (!func || !func->IsValidLowLevel())
			luaL_error(L, "Super function is isvalid");
		lua_pop(L, 1);
		auto lbase = UD->base;
		ensure(lbase);
		lbase->currentFunction = func;
		lbase->indexFlag = IF_RPC;
		int ret = lbase->superOrRpcCall(L, func);
		lbase->indexFlag = IF_NONE;
		lbase->currentFunction = nullptr;
		return ret;
	}

	int LuaBase::supermt(lua_State* L)
	{
		LuaObject::setupMTSelfSearch(L);
		RegMetaMethodByName(L, "Tick", __superTick);
		RegMetaMethodByName(L, "__index", __superIndex);
		return 0;
	}

	int LuaBase::rpcmt(lua_State* L)
	{
		LuaObject::setupMTSelfSearch(L);
		RegMetaMethodByName(L, "__index", __rpcIndex);
		return 0;
	}

	LuaVar LuaBase::callMember(FString func, const TArray<FLuaBPVar>& args)
	{
		NS_SLUA::LuaVar lfunc = luaSelfTable.getFromTable<NS_SLUA::LuaVar>((const char*)TCHAR_TO_UTF8(*func), true);
		if (!lfunc.isFunction()) {
			Log::Error("Can't find lua member function named %s to call", TCHAR_TO_UTF8(*func));
			return false;
		}
		
		auto L = luaSelfTable.getState();
		// push self
		luaSelfTable.push(L);
		// push arg to lua
		for (auto& arg : args) {
			arg.value.push(L);
		}
		return lfunc.callWithNArg(args.Num()+1);
	}

	bool LuaBase::postInit(const char* tickFlag,bool rawget)
	{
		if (!luaSelfTable.isTable())
			return false;

		if (luaSelfTable.isTable()) {
			tickFunction = luaSelfTable.getFromTable<NS_SLUA::LuaVar>("Tick", true);
		}

		return luaSelfTable.getFromTable<bool>(tickFlag, rawget);
	}
}

bool ILuaTableObjectInterface::isValid(ILuaTableObjectInterface * luaTableObj)
{
	return luaTableObj && luaTableObj->getSelfTable().isTable();
}

int ILuaTableObjectInterface::push(NS_SLUA::lua_State * L, ILuaTableObjectInterface * luaTableObj)
{
	if (!isValid(luaTableObj)) {
		NS_SLUA::Log::Error("Can't get a valid lua self table, push nil instead.");
		return NS_SLUA::LuaObject::pushNil(L);
	}
	auto self = luaTableObj->getSelfTable();
	return self.push(L);
}
