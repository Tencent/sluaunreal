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
#include "LuaUserWidget.h"
#include "LuaActor.h"

extern uint8 GRegisterNative(int32 NativeBytecodeIndex, const FNativeFuncPtr& Func);
#define Ex_LuaHook (EX_Max-1)

ULuaTableObjectInterface::ULuaTableObjectInterface(const class FObjectInitializer& OI)
	:Super(OI) {}

namespace NS_SLUA {

	NS_SLUA::LuaVar LuaBase::metaTable;

	bool LuaBase::luaImplemented(UFunction * func, void * params)
	{
		if (isOverride) return false;

		if (!func->HasAnyFunctionFlags(EFunctionFlags::FUNC_BlueprintEvent))
			return false;

		if (!luaSelfTable.isTable())
			return false;

		NS_SLUA::LuaVar lfunc = luaSelfTable.getFromTable<NS_SLUA::LuaVar>((const char*)TCHAR_TO_UTF8(*func->GetName()), true);
		if (!lfunc.isValid()) return false;

		return lfunc.callByUFunction(func, (uint8*)params, &luaSelfTable);
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

	int LuaBase::superCall(lua_State* L,UFunction* func)
	{
		UObject* obj = context.Get();
		if (!obj) return 0;

		FStructOnScope params(func);
		LuaObject::fillParam(L, 2, func, params.GetStructMemory());
		{
			// call function with params
			obj->ProcessEvent(func, params.GetStructMemory());
		}
		// return value to push lua stack
		return LuaObject::returnValue(L, func, params.GetStructMemory());
	}

	int LuaBase::__index(NS_SLUA::lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		if (!lua_isuserdata(L, -1))
			luaL_error(L, "expect LuaBase table at arg 1");
		// push key
		lua_pushvalue(L, 2);
		// get field from real actor
		lua_gettable(L, -2);
		return 1;
	}

	static int setParent(NS_SLUA::lua_State* L) {
		// set field to obj, may raise an error
		lua_settable(L, 1);
		return 0;
	}

	int LuaBase::__newindex(NS_SLUA::lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		if (!lua_isuserdata(L, -1))
			luaL_error(L, "expect LuaBase table at arg 1");

		lua_pushcfunction(L, setParent);
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

	void LuaBase::hookBpScript(UFunction* func, FNativeFuncPtr hookfunc) {
		static bool regExCode = false;
		if (!regExCode) {
			GRegisterNative(Ex_LuaHook, hookfunc);
			regExCode = true;
		}
		// if func had hooked
		if (func->Script.Num() > 5 && func->Script[5] == Ex_LuaHook)
			return;
		// goto 8(a uint32 value) to skip return
		uint8 code[] = { EX_JumpIfNot,8,0,0,0,Ex_LuaHook,EX_Return,EX_Nothing };
		func->Script.Insert(code, sizeof(code), 0);
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

	DEFINE_FUNCTION(LuaBase::luaOverrideFunc)
	{
		UFunction* func = Stack.Node;
		ensure(func);
		LuaBase* lb = checkBase(Stack.Object);

		ensure(lb);

		if (lb->isOverride && lb->currentFunction==func) {
			*(bool*)RESULT_PARAM = false;
			return;
		}

		void* params = Stack.Locals;

		LuaVar& luaSelfTable = lb->luaSelfTable;
		NS_SLUA::LuaVar lfunc = luaSelfTable.getFromTable<NS_SLUA::LuaVar>(func->GetName(), true);
		if (lfunc.isValid()) {
			lfunc.callByUFunction(func, (uint8*)params, &luaSelfTable, Stack.OutParms);
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
		for (TFieldIterator<UFunction> it(cls); it && (it->FunctionFlags&availableFlag); ++it) {
			if (luaSelfTable.getFromTable<LuaVar>(it->GetName(), true).isFunction()) {
				hookBpScript(*it, (FNativeFuncPtr)&luaOverrideFunc);
			}
		}
	}

	NS_SLUA::LuaSuper* LuaBase::newSuper(LuaBase* base)
	{
		return new LuaSuper{base};
	}

	int LuaBase::__superIndex(lua_State* L) {
		CheckUD(LuaSuper, L, 1);
		lua_getmetatable(L, 1);
		const char* name = LuaObject::checkValue<const char*>(L, 2);

		lua_getfield(L, -1, name);
		lua_remove(L, -2); // remove mt of ud
		if (!lua_isnil(L, -1)) {
			return 1;
		}
		
		UObject* obj = UD->base->context.Get();
		if (!obj) 
			luaL_error(L,"Context is invalid");
		UFunction* func = obj->GetClass()->FindFunctionByName(UTF8_TO_TCHAR(name));
		if (!func || (func->FunctionFlags&FUNC_BlueprintEvent) == 0)
			luaL_error(L, "Can't find function %s in super", name);

		lua_pushlightuserdata(L, func);
		lua_pushcclosure(L, __superCall, 1);
		return 1;
	}

	int LuaBase::__superTick(lua_State* L) {
		CheckUD(LuaSuper, L, 1);
		UD->base->isOverride = true;
		UD->base->superTick(L);
		UD->base->isOverride = false;
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
		lbase->isOverride = true;
		int ret = lbase->superCall(L, func);
		lbase->isOverride = false;
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

	int LuaBase::supergc(lua_State* L)
	{
		CheckUD(LuaSuper, L, 1);
		delete UD;
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
