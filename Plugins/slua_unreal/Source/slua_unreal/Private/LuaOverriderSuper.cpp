#include "LuaOverriderSuper.h"

#include "LuaObject.h"
#include "LuaOverrider.h"

namespace NS_SLUA
{
	template<typename T>
	UFunction* getSuperOrRpcFunction(lua_State* L)
	{
		CheckUD(T, L, 1);
		lua_getmetatable(L, 1);
		const char* name = LuaObject::checkValue<const char*>(L, 2);

		lua_getfield(L, -1, name);
		lua_remove(L, -2); // remove mt of ud
		if (!lua_isnil(L, -1)) 
		{
			return nullptr;
		}

		UObject* obj = UD->base.Get();
		if (!obj)
			luaL_error(L, "Context is invalid");

		UClass* cls = obj->GetClass();
		FName funcName = UTF8_TO_TCHAR(name);
		UFunction* func = cls->FindFunctionByName(funcName);
		
		while (func && cls && !ULuaOverrider::getSuperNativeFunc(func))
		{
			cls = cls->GetSuperClass();
			if (cls)
				func = cls->FindFunctionByName(funcName);
		}
		
		if (!func)
			luaL_error(L, "Can't find function %s in super", name);

		if ((func->FunctionFlags & FUNC_Native) == 0)
			luaL_error(L, "Super only support with native UFunction[%s]!", name);

		return func;
	}

	class GuardNativeFunc
	{
	public:
		GuardNativeFunc(UFunction* func, NS_SLUA::FNativeType newNativeFunc)
		{
			ufunc = func;
			oldNative = func->GetNativeFunc();
			func->SetNativeFunc(newNativeFunc);

			auto flags = func->FunctionFlags;
			hasNativeFlag = (flags & FUNC_Native) != 0;
			if (!hasNativeFlag)
			{
				func->FunctionFlags = flags | FUNC_Native;
			}
		}

		~GuardNativeFunc()
		{
			ufunc->SetNativeFunc(oldNative);
			if (!hasNativeFlag)
			{
				ufunc->FunctionFlags &= ~FUNC_Native;
			}
		}

	protected:
		UFunction* ufunc;
		NS_SLUA::FNativeType oldNative;
		bool hasNativeFlag;
	};
	
	int LuaSuperOrRpc::setupMetatable(lua_State* L)
	{
		LuaObject::setupMTSelfSearch(L);
		RegMetaMethodByName(L, "__index", __superIndex);
		return 0;
	}

	int LuaSuperOrRpc::__superIndex(lua_State* L) {

		UFunction* func = getSuperOrRpcFunction<LuaSuperOrRpc>(L);
		if (!func) return 1;

		lua_pushlightuserdata(L, func);
		lua_pushcclosure(L, __superCall, 1);
		return 1;
	}

	int LuaSuperOrRpc::__superCall(lua_State* L)
	{
		CheckUD(LuaSuperOrRpc, L, 1);
		auto base = UD->base;
		UObject* obj = base.Get();
		if (!obj)
			luaL_error(L, "Context is invalid");
		
		lua_pushvalue(L, lua_upvalueindex(1));
		UFunction* func = (UFunction*)lua_touserdata(L, -1);
		if (!func || !func->IsValidLowLevel())
			luaL_error(L, "Super function is isvalid");
		lua_pop(L, 1);
		
		return UD->superOrRpcCall(L, func);
	}

	int LuaSuperOrRpc::superOrRpcCall(lua_State* L, UFunction* func)
	{
		UObject* obj = base.Get();
		if (!obj)
		{
			return 0;
		}

		NS_SLUA::FNativeType superNative = ULuaOverrider::getSuperNativeFunc(func);
		if (!superNative)
		{
			NS_SLUA::Log::Error("LuaOverrider SuperOrRpcCall not isValid UObject[%s] of FunctionName[%s]", TCHAR_TO_UTF8(*(obj->GetName())), TCHAR_TO_UTF8(*(func->GetName())));
			return 0;
		}

		bool isLatentFunction = false;
		int outParamCount = 0;

		// Avoid longjump break objectRecorder's destruction at iOS.
		{
			NewObjectRecorder objectRecorder(L);

			uint8* params = (uint8*)FMemory_Alloca(func->ParmsSize);
			FMemory::Memzero(params, func->ParmsSize);
			for (TFieldIterator<UProperty> it(func); it && it->HasAnyPropertyFlags(CPF_Parm); ++it)
			{
				UProperty* localProp = *it;
				checkSlow(localProp);
				if (!localProp->HasAnyPropertyFlags(CPF_ZeroConstructor))
				{
					localProp->InitializeValue_InContainer(params);
				}
			}

			LuaObject::fillParam(L, 2, func, params);
			{
				GuardNativeFunc nativeFuncGuard(func, superNative);
				// call function with params
				LuaObject::callUFunction(L, obj, func, params);
			}
			// return value to push lua stack
			outParamCount = LuaObject::returnValue(L, func, params, &objectRecorder, isLatentFunction);

			for (TFieldIterator<UProperty> it(func); it && (it->HasAnyPropertyFlags(CPF_Parm)); ++it)
			{
				it->DestroyValue_InContainer(params);
			}
		}

		if (isLatentFunction)
			return lua_yield(L, outParamCount);
		return outParamCount;
	}
}

