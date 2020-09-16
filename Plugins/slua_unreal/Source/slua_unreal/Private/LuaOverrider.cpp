#include "LuaOverrider.h"
#include <lstate.h>

#include "BlueprintSupport.h"
#include "CoreDelegates.h"
#include "Script.h"
#include "LuaVar.h"
#include "UObjectBaseUtility.h"
#include "LuaOverriderInterface.h"
#include "LuaOverriderSuper.h"

extern uint8 GRegisterNative(int32 NativeBytecodeIndex, const NS_SLUA::FNativeType& Func);
enum
{
	Ex_LuaOverride = EX_Max - 1,
};

TMap<NS_SLUA::lua_State*, ULuaOverrider::ObjectTableMap> ULuaOverrider::objectTableMap;
ULuaOverrider::ClassNativeMap ULuaOverrider::classSuperFuncs;

#if ((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
DEFINE_FUNCTION(ULuaOverrider::luaOverrideFunc)
#else
void ULuaOverrider::luaOverrideFunc(FFrame& Stack, RESULT_DECL)
#endif
{
	UFunction* func = Stack.Node;
	ensure(func);
	UObject* obj = Stack.Object;
	ensure(obj);

	if (Stack.CurrentNativeFunction)
	{
		if (func->GetNativeFunc() == (NS_SLUA::FNativeType)&ULuaOverrider::luaOverrideFunc)
	    {
	        Stack.SkipCode(1);      // skip LuaOverrideFunc only when called from native func
	    }
	}
	
	NS_SLUA::lua_State* L = getObjectLuaState(obj);

	auto& tableMap = objectTableMap.FindOrAdd(L);
	NS_SLUA::LuaVar* luaSelfTable = tableMap.Find(obj);
	
	if (!luaSelfTable || !luaSelfTable->isValid())
	{
		NS_SLUA::Log::Error("LuaOverrideFunc luaSelfTable not isValid %s %s", TCHAR_TO_UTF8(*(obj->GetName())), TCHAR_TO_UTF8(*(func->GetName())));
		return;
	}
	NS_SLUA::AutoStack as(luaSelfTable->getState());
	NS_SLUA::LuaVar luaFunc = luaSelfTable->getFromTable<NS_SLUA::LuaVar>(func->GetName());
	if (luaFunc.isValid())
	{
		luaFunc.callByUFunction(func, Stack.Locals, Stack.OutParms, RESULT_PARAM, luaSelfTable);
	}
}

NS_SLUA::lua_State* ULuaOverrider::getObjectLuaState(const UObject* obj)
{
	NS_SLUA::lua_State* L = nullptr;
#if WITH_EDITOR
	auto* outer = obj->GetOuter();
	auto* world = outer ? outer->GetWorld() : nullptr;
	auto* gameInstance = world ? world->GetGameInstance() : nullptr;
	if (gameInstance)
	{
		L = NS_SLUA::LuaState::get(gameInstance)->getLuaState();
	}
	else
	{
		for (TMap<NS_SLUA::lua_State*, ObjectTableMap>::TConstIterator iter(objectTableMap); iter; ++iter)
		{
			L = iter.Key();
			break;
		}
	}
#else
	for (TMap<lua_State*, ObjectTableMap>::TConstIterator iter(objectTableMap); iter; ++iter)
	{
		L = iter.Key();
		break;
	}
#endif
	return L;
}

void ULuaOverrider::onLuaStateClose(NS_SLUA::lua_State* L)
{
	if (objectTableMap.Contains(L))
	{
		objectTableMap.Remove(L);
	}
}

void ULuaOverrider::addObjectTable(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar& table)
{
	auto &tableMap = objectTableMap.FindOrAdd(L);
	tableMap.Add(obj, table);
}

void ULuaOverrider::removeObjectTable(UObject* obj)
{
	for (auto iter = objectTableMap.CreateIterator(); iter; ++iter)
	{
		auto& tableMap = iter.Value();
		
		NS_SLUA::LuaVar* Table = tableMap.Find(obj);
		if (Table && Table->isValid())
		{
			auto* L = Table->getState();
			Table->push(L);
			lua_pushstring(L, SLUA_CPPINST);
			lua_pushnil(L);
			lua_rawset(L, -3);
			lua_pop(L, 1);

			tableMap.Remove(obj);
		}
	}
	
}

NS_SLUA::LuaVar* ULuaOverrider::getObjectTable(const UObject* obj, NS_SLUA::lua_State* L)
{
	
	if (L)
	{
		L = G(L)->mainthread;
	}
	else
	{
		L = getObjectLuaState(obj);
	}

	auto* tableMap = objectTableMap.Find(L);
	if (tableMap)
		return tableMap->Find(obj);
	
	return nullptr;
}

NS_SLUA::FNativeType ULuaOverrider::getSuperNativeFunc(UFunction* func)
{
	if (!func)
	{
		return nullptr;
	}
	UClass* uclass = func->GetOuterUClass();
	auto* nativeMap = classSuperFuncs.Find(uclass);
	if (nativeMap)
	{
		auto *nativeFunc = nativeMap->Find(func->GetName());
		if (nativeFunc)
		{
			return *nativeFunc;
		}
	}

	return nullptr;
}

namespace NS_SLUA
{
	const uint8 LuaOverrider::Code[] = { (uint8)Ex_LuaOverride, EX_Return, EX_Nothing };
	LuaOverrider::FBlueprintFlushReinstancingQueue LuaOverrider::BlueprintFlushReinstancingQueue;
	
	LuaOverrider::LuaOverrider(NS_SLUA::LuaState* luaState)
		: sluaState(luaState)
	{
		GUObjectArray.AddUObjectDeleteListener(this);
		GUObjectArray.AddUObjectCreateListener(this);
		asyncLoadingFlushUpdateHandle = FCoreDelegates::OnAsyncLoadingFlushUpdate.AddRaw(this, &LuaOverrider::onAsyncLoadingFlushUpdate);
		gcHandler = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(this, &LuaOverrider::onEngineGC);
		if (!BlueprintFlushReinstancingQueue.IsBound())
		{
			FBlueprintSupport::SetFlushReinstancingQueueFPtr(OnBlueprintFlushReinstancingQueue);
		}
		BlueprintFlushDelegate = BlueprintFlushReinstancingQueue.AddRaw(this, &LuaOverrider::onAsyncLoadingFlushUpdate);
	}

	LuaOverrider::~LuaOverrider()
	{
		ULuaOverrider::onLuaStateClose(sluaState->getLuaState());
		sluaState = nullptr;

		BlueprintFlushReinstancingQueue.Remove(BlueprintFlushDelegate);
		if (!BlueprintFlushReinstancingQueue.IsBound())
		{
			FBlueprintSupport::SetFlushReinstancingQueueFPtr(nullptr);
		}
		
		FCoreUObjectDelegates::GetPostGarbageCollect().Remove(gcHandler);
		FCoreDelegates::OnAsyncLoadingFlushUpdate.Remove(asyncLoadingFlushUpdateHandle);
		GUObjectArray.RemoveUObjectCreateListener(this);
		GUObjectArray.RemoveUObjectDeleteListener(this);
	}

	void LuaOverrider::NotifyUObjectCreated(const UObjectBase* Object, int32 Index)
	{
		QUICK_SCOPE_CYCLE_COUNTER(LuaOverrider_NotifyUObjectCreated);
		UObjectBaseUtility* obj = (UObjectBaseUtility*)Object;
		//NS_SLUA::Log::Log("LuaOverrider::NotifyUObjectCreated log %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));

		if (!obj->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
		{
			tryHook(obj);
		}
	}

	void LuaOverrider::NotifyUObjectDeleted(const UObjectBase* Object, int32 Index)
	{
		UClass* cls = (UClass*)Object;
		if (overridedClasses.Contains(cls))
		{
			overridedClasses.Remove(cls);
		}

		UObject* obj = (UObject*)Object;
		ULuaOverrider::removeObjectTable(obj);
	}

#if (ENGINE_MINOR_VERSION>=23) && (ENGINE_MAJOR_VERSION>=4)
	void LuaOverrider::OnUObjectArrayShutdown() {
		// nothing todo
	}
#endif

	bool LuaOverrider::tryHook(const UObjectBaseUtility* obj, bool bIsPostLoad/* = false*/)
	{
		NS_SLUA::Log::Log("LuaOverrider::NotifyUObjectCreated %s, %p", TCHAR_TO_UTF8(*obj->GetFName().ToString()), obj);
		if (isHookable(obj))
		{
			if (IsInGameThread() && !bIsPostLoad)
			{
				//NS_SLUA::Log::Log("LuaOverrider::NotifyUObjectCreated %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));
				UClass* cls = obj->GetClass();
				bindOverrideFuncs(obj, cls);
			}
			else
			{
				FScopeLock lock(&asyncLoadedObjectCS);
				asyncLoadedObjects.Add((UObject*)obj);
			}

			return true;
		}

		return false;
	}

#if WITH_EDITOR
	void LuaOverrider::removeOverrides(UClass* cls)
	{
		EFunctionFlags availableFlag = FUNC_BlueprintEvent;
		for (TFieldIterator<UFunction> it(cls); it && (it->FunctionFlags&availableFlag); ++it)
		{
			auto func = *it;
			// if func had hooked
			if (func->Script.Num() > 0 && func->Script[0] == Ex_LuaOverride)
			{
				func->Script.RemoveAt(0, sizeof(Code), false);
			}
		}
	}
#endif

	void LuaOverrider::onAsyncLoadingFlushUpdate()
	{
		if (!IsInGameThread())
		{
			return;
		}
		
		//NS_SLUA::Log::Log("LuaOverrider::OnAsyncLoadingFlushUpdate");
		FScopeLock lock(&asyncLoadedObjectCS);
		
		for (int32 i = asyncLoadedObjects.Num() - 1; i >= 0; --i)
        {
            UObject *obj = asyncLoadedObjects[i];
			//NS_SLUA::Log::Log("LuaOverrider::OnAsyncLoadingFlushUpdate %d", obj->HasAnyFlags(RF_NeedPostLoad));
            if (obj && !obj->HasAnyFlags(RF_NeedPostLoad))
            {
            	//NS_SLUA::Log::Log("LuaOverrider::OnAsyncLoadingFlushUpdate %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));
				UClass* cls = obj->GetClass();
				bindOverrideFuncs(obj, cls);
            	
	            asyncLoadedObjects.RemoveAt(i, 1, false);
            }
		}
	}

	void LuaOverrider::onEngineGC()
	{
		// find freed uclass
		for (ULuaOverrider::ClassNativeMap::TIterator it(ULuaOverrider::classSuperFuncs); it; ++it)
			if (!it.Key().IsValid())
				it.RemoveCurrent();
	}

	void LuaOverrider::OnBlueprintFlushReinstancingQueue()
	{
		BlueprintFlushReinstancingQueue.Broadcast();
	}

	FString LuaOverrider::getLuaFilePath(UClass* cls)
	{
		UFunction* func = cls->FindFunctionByName(FName(*GET_LUA_FILE_FUNC_NAME));
		FString luaFilePath;
		if (func->GetNativeFunc())
		{
			UObject* defaultObject = cls->GetDefaultObject();
			defaultObject->ProcessEvent(func, &luaFilePath);
		}
		return MoveTemp(luaFilePath);
	}

	bool LuaOverrider::bindOverrideFuncs(const UObjectBase* obj, UClass* cls) {
		//NS_SLUA::Log::Log("LuaOverrider::BindOverrideFuncs %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));
		if (!sluaState) {
			return false;
		}

		FString luaFilePath = getLuaFilePath(cls);
		NS_SLUA::Log::Log("LuaOverrider::BindOverrideFuncs LuaFilePath[%s] of Object[%s]", 
			TCHAR_TO_UTF8(*luaFilePath), TCHAR_TO_UTF8(*(obj->GetFName().ToString())));
		if (luaFilePath.IsEmpty()) {
			return false;
		}
		NS_SLUA::LuaVar luaModule = sluaState->requireModule(TCHAR_TO_UTF8(*luaFilePath));
		if (!luaModule.isValid()) {
			NS_SLUA::Log::Error("LuaOverrider::BindOverrideFuncs can't find LuaFilePath[%s] of Object[%s]", 
				TCHAR_TO_UTF8(*luaFilePath), TCHAR_TO_UTF8(*(obj->GetFName().ToString())));
			return false;
		}

		if (!luaModule.isTable() && !luaModule.isFunction()) {
			NS_SLUA::Log::Error("LuaOverrider::BindOverrideFuncs Object[%s]'s LuaModule[%s] not a lua table or function!", 
				TCHAR_TO_UTF8(*(obj->GetFName().ToString())), TCHAR_TO_UTF8(*luaFilePath));
			return false;
		}

		NS_SLUA::LuaVar luaSelfTable;
		if (luaModule.isFunction()) {
			luaSelfTable = luaModule.call();
		}
		else if (luaModule.isTable()) {
			lua_State* L = sluaState->getLuaState();
			AutoStack as(L);
			
			luaModule.push(L);
			if (lua_getmetatable(L, -1)) {
				if (lua_getfield(L, -1, "__call") != LUA_TNIL) {
					int top = LuaState::pushErrorHandler(L) - 1;
					lua_insert(L, -2);
					
					lua_pushvalue(L, -2);
					if (lua_pcall(L, 1, 1, top))
						lua_pop(L, 1);

					lua_remove(L, top);

					int retCount = lua_gettop(L) - top + 1;
					if (retCount)
						luaSelfTable = LuaVar(L, -retCount);
				}
				else {
					lua_pop(L, 1);
				}

				lua_pop(L, 1);
			}
			lua_pop(L, 1);
		}

		if (!luaSelfTable.isTable()) {
			NS_SLUA::Log::Error("LuaOverrider::BindOverrideFuncs Object[%s]'s luaSelfTable[%s] not a lua table!",
				TCHAR_TO_UTF8(*(obj->GetFName().ToString())), TCHAR_TO_UTF8(*luaFilePath));
			return false;
		}
		
		auto* overridedCls = overridedClasses.Find(cls);
		if (!overridedCls || !overridedCls->IsValid()) {
			// NS_SLUA::Log::Log("LuaOverrider::BindOverrideFuncs OverridedCls %s", TCHAR_TO_UTF8(*luaFilePath));
			EFunctionFlags AvailableFlag = FUNC_BlueprintEvent;
			for (TFieldIterator<UFunction> it(cls, EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::ExcludeDeprecated); it; ++it) {
				if (it->FunctionFlags & AvailableFlag) {
					if (luaSelfTable.getFromTable<NS_SLUA::LuaVar>(it->GetName()).isFunction()) {
						hookBpScript(*it, cls, (NS_SLUA::FNativeType)&ULuaOverrider::luaOverrideFunc);
					}
				}
			}

			overridedClasses.Add(cls);
		}

		setmetatable(luaSelfTable, (void*)obj);
		
		ULuaOverrider::addObjectTable(sluaState->getLuaState(), (UObject*)obj, luaSelfTable);

		return true;
	}

	void LuaOverrider::setmetatable(const LuaVar& luaSelfTable, void* objPtr)
	{
		lua_State* L = sluaState->getLuaState();
		// setup __cppinst
		// we use rawpush to bind objptr and SLUA_CPPINST
		luaSelfTable.push(L);
		lua_pushstring(L, SLUA_CPPINST);
		lua_pushlightuserdata(L, objPtr);
		lua_rawset(L, -3);

		LuaObject::pushType(L, new LuaSuperOrRpc((UObject*)objPtr), "LuaSuperOrRpc", LuaSuperOrRpc::setupMetatable, LuaSuperOrRpc::genericGC<LuaSuperOrRpc>);
		lua_setfield(L, -2, "Super");

		if (lua_getmetatable(L, -1)) {
			if (lua_getfield(L, -1, "__index") != LUA_TNIL) {
				lua_pushcclosure(L, classIndex, 1);
				lua_setfield(L, -2, "__index");
			}
			else {
				lua_pop(L, 1);
			}

			if (lua_getfield(L, -1, "__newindex") != LUA_TNIL) {
				lua_pushcclosure(L, classNewindex, 1);
				lua_setfield(L, -2, "__newindex");
			}
			else {
				lua_pop(L, 1);
			}

			lua_pop(L, 1);
		}
		else {
			// setup metatable
			if (luaL_newmetatable(L, "LuaOverrider")) {
				lua_pushcfunction(L, __index);
				lua_setfield(L, -2, "__index");
				lua_pushcfunction(L, __newindex);
				lua_setfield(L, -2, "__newindex");
			}
			lua_setmetatable(L, -2);
		}

		// pop luaSelfTable
		lua_pop(L, 1);
	}

	bool LuaOverrider::isHookable(const UObjectBaseUtility* obj)
	{
		//NS_SLUA::Log::Log("LuaOverrider::isHookable log %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));
		check(!obj->IsPendingKill());
		UClass* cls = obj->GetClass();
		//NS_SLUA::Log::Log("LuaOverrider::isHookable GetClass %s, is Class: %d", TCHAR_TO_UTF8(*obj->GetFName().ToString()), cls->IsChildOf<UClass>());
		if (cls->IsChildOf<UPackage>() || cls->IsChildOf<UClass>())
		{
			return false;
		}
		//NS_SLUA::Log::Log("LuaOverrider::isHookable not UPackage %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));
		static UClass* interfaceClass = ULuaOverriderInterface::StaticClass();
		if (cls->ImplementsInterface(interfaceClass))
		{
			return true;
		}
		

		return false;
	}

	template <typename Tag, int Tag::* M>
	struct AccessPrivate {
		friend int UProperty::* OffsetPtr() { return M; }
	};

	int32 UProperty::* OffsetPtr();
	
	/// <summary>
	/// Hack: Access UProperty's private member "Offset_Internal"
	/// </summary>
	template struct AccessPrivate<UProperty, &UProperty::Offset_Internal>;
	
	UFunction* duplicateUFunction(UFunction* templateFunction, UClass* outerClass)
	{
		static FArchive Ar;
		static auto PropertyOffsetPtr = OffsetPtr();

		FName newFuncName = templateFunction->GetFName();
		if (templateFunction->HasAnyFunctionFlags(FUNC_Native))
		{
			// avoid "Failed to bind native function" warnings in UFunction::Bind while native UFunction duplicate.
			outerClass->AddNativeFunction(*newFuncName.ToString(), (NS_SLUA::FNativeType)&ULuaOverrider::luaOverrideFunc);
		}
		
		FObjectDuplicationParameters duplicationParams(templateFunction, outerClass);
		duplicationParams.DestName = newFuncName;
		duplicationParams.InternalFlagMask &= ~EInternalObjectFlags::Native;
		UFunction* newFunc = Cast<UFunction>(StaticDuplicateObjectEx(duplicationParams));
		newFunc->PropertyLink = Cast<UProperty>(newFunc->Children);
		newFunc->PropertiesSize = templateFunction->PropertiesSize;
		newFunc->MinAlignment = templateFunction->MinAlignment;
		for (TFieldIterator<UProperty> srcIter(templateFunction), dstIter(newFunc); srcIter && dstIter; ++srcIter, ++dstIter)
		{
			UProperty* srcProperty = *srcIter;
			UProperty* destProperty = *dstIter;

			destProperty->Link(Ar);
			destProperty->RepIndex = srcProperty->RepIndex;
			destProperty->*PropertyOffsetPtr = srcProperty->GetOffset_ForInternal();
		}
		
		outerClass->AddFunctionToFunctionMap(newFunc, newFuncName);
		
		newFunc->ClearInternalFlags(EInternalObjectFlags::Native);
		return newFunc;
	}

	void LuaOverrider::hookBpScript(UFunction* func, UClass* cls, NS_SLUA::FNativeType hookFunc)
	{
		static bool regExCode = false;
		if (!regExCode)
		{
			GRegisterNative(Ex_LuaOverride, hookFunc);
			regExCode = true;
		}

		// if func had hooked
		if (func->IsNative() && func->GetNativeFunc() == &ULuaOverrider::luaOverrideFunc)
			return;
		
		if (func->Script.Num() > 0 && func->Script[0] == Ex_LuaOverride)
			return;

		if (func->HasAnyFunctionFlags(FUNC_Native))
		{
			auto& funcMap = ULuaOverrider::classSuperFuncs.FindOrAdd(func->GetOuterUClass());

			FString funcName = func->GetName();
			auto nativeFunc = func->GetNativeFunc();
			funcMap.Add(funcName, nativeFunc);
		}
		
		UFunction* childFunc = cls->FindFunctionByName(func->GetFName(), EIncludeSuperFlag::ExcludeSuper);
		if (childFunc == func)
		{
			if (!func->HasAnyFunctionFlags(FUNC_Net) || func->HasAnyFunctionFlags(FUNC_Native))
			{
				func->SetNativeFunc(hookFunc);
			}

			func->Script.Insert(Code, sizeof(Code), 0);
		}
		else if (!childFunc)
		{
			auto *newFunc = duplicateUFunction(func, cls);
			if (!newFunc->HasAnyFunctionFlags(FUNC_Native))
			{
				static TArray<uint8> ShortCode(Code, sizeof(Code));
				newFunc->Script = ShortCode;
			}
		}
	}

	int LuaOverrider::__index(lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		void* ud = lua_touserdata(L, -1);
		if (!ud)
			luaL_error(L, "expect LuaBase table at arg 1");
		lua_pop(L, 1);
		UObject* obj = (UObject*)ud;
		if (!NS_SLUA::LuaObject::isUObjectValid(obj)) {
			return 0;
		}
		const char* name = LuaObject::checkValue<const char*>(L, 2);
		return LuaObject::objectIndex(L, obj, name);
	}

	int LuaOverrider::classIndex(lua_State *L)
	{
		int top = LuaState::pushErrorHandler(L);
		
		lua_pushvalue(L, lua_upvalueindex(1));
		lua_pushvalue(L, 1);
		lua_pushvalue(L, 2);

		if (lua_pcall(L, 2, 1, top))
			lua_pop(L, 1);

		lua_remove(L, top);
		
		int retCount = lua_gettop(L) - top +  1;
		if (retCount == 0)
		{
			retCount = __index(L);
		}
		// if first return value is nil
		else if (lua_isnil(L, -retCount)) 
		{
			// drop all return value
			lua_pop(L, retCount);
			retCount = __index(L);
		}
		return retCount;
	}

	int LuaOverrider::setParent(lua_State* L) {
		// set field to obj, may raise an error
		lua_settable(L, 1);
		return 0;
	}

	int LuaOverrider::__newindex(lua_State * L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		void* ud = lua_touserdata(L, -1);
		if (!ud)
			luaL_error(L, "expect LuaBase table at arg 1");
		lua_pop(L, 1);
		LuaObject::push(L, (UObject*)ud, false);

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

	int LuaOverrider::classNewindex(lua_State* L)
	{
		lua_pushstring(L, SLUA_CPPINST);
		lua_rawget(L, 1);
		void* ud = lua_touserdata(L, -1);
		if (!ud)
			luaL_error(L, "expect LuaBase table at arg 1");
		lua_pop(L, 1);
		LuaObject::push(L, (UObject*)ud, false);

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

			lua_pushvalue(L, lua_upvalueindex(1));
			lua_pushvalue(L, 1);
			// push key
			lua_pushvalue(L, 2);
			// push value
			lua_pushvalue(L, 3);
			lua_pcall(L, 3, 0, 0);
		}
		
		return 0;
	}
}
