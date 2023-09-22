#pragma once
#include "SluaMicro.h"
#include "LuaNetSerialization.h"
#include "LuaVar.h"
#include "InputCoreTypes.h"
#include "UObject/Object.h"
#include "UObject/UObjectArray.h"
#include "LuaOverrider.generated.h"

UCLASS()
class SLUA_UNREAL_API ULuaOverrider : public UObject
{
    GENERATED_BODY()

public:
    DECLARE_FUNCTION(luaOverrideFunc);

    struct FObjectTable
    {
        NS_SLUA::LuaVar table;
        bool isInstance;
    };
    typedef TMap<TWeakObjectPtr<UObject>, FObjectTable, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UObject>, FObjectTable>> ObjectTableMap;

    static ObjectTableMap* getObjectTableMap(NS_SLUA::lua_State* L);
    static NS_SLUA::LuaVar* getObjectLuaTable(const UObject* obj, NS_SLUA::lua_State* L = nullptr);
    static FObjectTable* getObjectTable(const UObject* obj, NS_SLUA::lua_State* L = nullptr);
    static NS_SLUA::LuaVar getLuaFunction(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar* table, const FString& funcName);

	static bool isUFunctionHooked(UFunction* func);
    
protected:
    friend class NS_SLUA::LuaOverrider;

    static void addObjectTable(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar& table, bool isInstance);
    static void removeObjectTable(UObject* obj);

    static NS_SLUA::lua_State* editorGetObjLuaState(FFrame& Stack, const UObject* obj);
    static NS_SLUA::lua_State* getObjectLuaState(const UObject* obj);
    static void onLuaStateClose(NS_SLUA::lua_State* L);
    
    typedef TMap<FString, NS_SLUA::FNativeFuncPtr> NativeMap;
    typedef TMap<TWeakObjectPtr<UClass>, NativeMap, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UClass>, NativeMap>> ClassNativeMap;
    static ClassNativeMap classSuperFuncs;

    static TMap<NS_SLUA::lua_State*, ObjectTableMap> objectTableMap;

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void TriggerAnimNotify();

    UFUNCTION(BlueprintNativeEvent)
    void InputAction(FKey Key);

    UFUNCTION(BlueprintNativeEvent)
    void InputAxis(float AxisValue);

    UFUNCTION(BlueprintNativeEvent)
    void InputTouch(ETouchIndex::Type FingerIndex, const FVector &Location);

    UFUNCTION(BlueprintNativeEvent)
    void InputVectorAxis(const FVector &AxisValue);

    UFUNCTION(BlueprintNativeEvent)
    void InputGesture(float Value);
};

namespace NS_SLUA
{
    extern const FString SUPER_CALL_FUNC_NAME_PREFIX;

    struct AsyncLoadedObject
    {
        TWeakObjectPtr<UObject> obj;
    };
    
    class SLUA_UNREAL_API LuaOverrider
        : public FUObjectArray::FUObjectCreateListener
        , public FUObjectArray::FUObjectDeleteListener
    {
    public:
        static const char* UOBJECT_NAME;
        static const char* SUPER_NAME;
        static const char* CACHE_NAME;
        static const char* INSTANCE_CACHE_NAME;
        static const FName TRIGGER_ANIM_NOTIFY_FUNCTION_NAME;
        
        LuaOverrider(LuaState* luaState);
        ~LuaOverrider();

        void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index) override;
#if !((ENGINE_MINOR_VERSION<23) && (ENGINE_MAJOR_VERSION==4))
        void OnUObjectArrayShutdown() override;
#endif
        void NotifyUObjectDeleted(const UObjectBase* Object, int32 Index) override;

        static bool isHookable(const UObjectBaseUtility* obj);
        bool tryHook(const UObjectBaseUtility* obj, bool bHookImmediate = true, bool bPostLoad = false);
        static FString getLuaFilePath(UObject* obj, class UClass* cls, bool bCDOLua, bool& bHookInstancedObj);

#if WITH_EDITOR
        static ULuaOverrider::ClassNativeMap cacheNativeFuncs;
        static TMap<UClass*, TArray<TWeakObjectPtr<UFunction>>> classAddedFuncs;
        static TMap<UClass*, TArray<TWeakObjectPtr<UFunction>>> classHookedFuncs;

        void removeOverrides();
#endif
        void removeOneOverride(UClass* cls, bool bObjectDeleted);

    protected:
        friend class LuaObject;
        friend class LuaNet;

        static const EFunctionFlags OverrideFuncFlags = FUNC_BlueprintEvent | FUNC_Net;
        
        static const uint8 Code[];
        static const int32 CodeSize;

        void onAsyncLoadingFlushUpdate();
        void onEngineGC();

        bool bindOverrideFuncs(const UObjectBase* objBase, UClass* cls);
        void setmetatable(const LuaVar& luaSelfTable, void* objPtr, bool bNetReplicated);

        bool hookBpScript(UFunction* func, UClass* cls, FNativeFuncPtr hookFunc);

        static void CustomClassConstructor(const FObjectInitializer& ObjectInitializer);

        static FRWLock classHookMutex;
        static TMap<TWeakObjectPtr<UClass>, UClass::ClassConstructorType> classConstructors;
        static TMap<UObject*, TArray<LuaOverrider*>> objectOverriders;

        static int __index(lua_State* L);
        static int classIndex(lua_State* L);
        static int __newindex(lua_State* L);
        static int classNewindex(lua_State* L);

        LuaState* sluaState;
        class LuaNet* luaNet;
        
        typedef TMap<UClass*, TSet<FName>> ClassHookedFuncNames;
        static ClassHookedFuncNames classHookedFuncNames;
        typedef TSet<UClass*> OverridedClassMap;
        static OverridedClassMap overridedClasses;

        bool bOnAsyncLoadingFlushUpdate = false;
        FCriticalSection asyncLoadedObjectCS;
        TArray<AsyncLoadedObject> asyncLoadedObjects;

        FDelegateHandle asyncLoadingFlushUpdateHandle;
        FDelegateHandle gcHandler;

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        static void OnBlueprintFlushReinstancingQueue();
        
        DECLARE_MULTICAST_DELEGATE(FBlueprintFlushReinstancingQueue);
        static FBlueprintFlushReinstancingQueue blueprintFlushReinstancingQueue;

        FDelegateHandle blueprintFlushDelegate;
#endif
        
        UFunction* animNotifyTemplate;
        
    protected: // Input Overrides
        static const TCHAR* EInputEventNames[];
        
        void initInputs();
        void onWorldCleanup(UWorld * World, bool bSessionEnded, bool bCleanupResources);

#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION <= 23
        void onWorldTickStart(ELevelTick TickType, float DeltaTime);
#else
        void onWorldTickStart(UWorld *World, ELevelTick TickType, float DeltaTime);
#endif
        void overrideInputs(AActor *actor, UInputComponent *inputComponent);

        void overrideActionInputs(AActor *actor, UInputComponent *inputComponent, const TSet<FName> &luaFunctions);

        FDelegateHandle onWorldTickStartHandle;
        FDelegateHandle onWorldCleanupHandle;

        UFunction *inputActionFunc;
        UFunction *inputAxisFunc;
        UFunction *inputTouchFunc;
        UFunction *inputVectorAxisFunc;
        UFunction *inputGestureFunc;

        TSet<FName> defaultAxisNames;
        TSet<FName> defaultActionNames;
        TArray<FKey> allKeys;
        
        TArray<TWeakObjectPtr<UInputComponent>> inputComponents;
    };
}
