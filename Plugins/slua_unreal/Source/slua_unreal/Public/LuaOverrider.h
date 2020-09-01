#pragma once
#include "CoreMinimal.h"
#include "LuaVar.h"
#include "LuaState.h"
#include "UObject.h"
#include "UObject/UObjectArray.h"
#include "LuaOverrider.generated.h"

namespace NS_SLUA
{
#if ((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
	typedef FNativeFuncPtr FNativeType;
#else
	typedef Native FNativeType;
#endif
}

UCLASS()
class ULuaOverrider : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_FUNCTION(luaOverrideFunc);

	static NS_SLUA::LuaVar* getObjectTable(const UObject* obj, NS_SLUA::lua_State* L = nullptr);

	static NS_SLUA::FNativeType getSuperNativeFunc(UFunction* func);
	
protected:
	friend class NS_SLUA::LuaOverrider;

	static void addObjectTable(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar& table);
	static void removeObjectTable(UObject* obj);

	static NS_SLUA::lua_State* getObjectLuaState(const UObject* obj);
	static void onLuaStateClose(NS_SLUA::lua_State* L);
	
	typedef TMap<FString, NS_SLUA::FNativeType> NativeMap;
	typedef TMap<TWeakObjectPtr<class UClass>, NativeMap> ClassNativeMap;
	static ClassNativeMap classSuperFuncs;

	typedef TMap<TWeakObjectPtr<class UObject>, NS_SLUA::LuaVar> ObjectTableMap;
	static TMap<NS_SLUA::lua_State*, ObjectTableMap> objectTableMap;
};

namespace NS_SLUA
{
	class SLUA_UNREAL_API LuaOverrider
		: public FUObjectArray::FUObjectCreateListener
		, public FUObjectArray::FUObjectDeleteListener
	{
	public:
		LuaOverrider(LuaState* luaState);
		~LuaOverrider();

		void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index) override;
		void NotifyUObjectDeleted(const UObjectBase* Object, int32 Index) override;

#if (ENGINE_MINOR_VERSION>=23) && (ENGINE_MAJOR_VERSION>=4)
		virtual void OnUObjectArrayShutdown() override;
#endif

		bool tryHook(const UObjectBaseUtility* obj, bool bIsPostLoad = false);

#if WITH_EDITOR
		static void removeOverrides(class UClass* cls);
#endif

	protected:
		NS_SLUA::LuaState* sluaState;
		friend class ULuaOverrider;
		const FString GET_LUA_FILE_FUNC_NAME = TEXT("GetLuaFilePath");
		static const uint8 Code[];

		void onAsyncLoadingFlushUpdate();
		void onEngineGC();
		
		FString getLuaFilePath(class UClass* cls);
		bool bindOverrideFuncs(const UObjectBase* obj, UClass* cls);
		void setmetatable(const LuaVar& luaSelfTable, void* objPtr);

		static bool isHookable(const UObjectBaseUtility* obj);

		static void hookBpScript(UFunction* func, UClass* cls, NS_SLUA::FNativeType hookFunc);

		static int setParent(lua_State* L);
		static int __index(lua_State* L);
		static int classIndex(lua_State* L);
		static int __newindex(lua_State* L);
		static int classNewindex(lua_State* L);

		TSet<TWeakObjectPtr<UClass>> overridedClasses;

		FCriticalSection asyncLoadedObjectCS;
		TArray<UObject*> asyncLoadedObjects;

		FDelegateHandle asyncLoadingFlushUpdateHandle;
		FDelegateHandle gcHandler;

		static void OnBlueprintFlushReinstancingQueue();
		
		DECLARE_MULTICAST_DELEGATE(FBlueprintFlushReinstancingQueue);
		static FBlueprintFlushReinstancingQueue BlueprintFlushReinstancingQueue;

		FDelegateHandle BlueprintFlushDelegate;
	};
}
