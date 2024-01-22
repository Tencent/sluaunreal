#include "LuaOverrider.h"
#include <lstate.h>
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
#include "Blueprint/BlueprintSupport.h"
#endif
#include "Misc/CoreDelegates.h"
#include "LuaClass.inl"
#include "UObject/Script.h"
#include "LuaVar.h"
#include "LuaNet.h"
#include "UObject/UObjectBaseUtility.h"
#include "UObject/UObjectThreadContext.h"
#include "LuaOverriderInterface.h"
#include "LuaOverriderSuper.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/GameEngine.h"
#include "Engine/NetDriver.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerController.h"

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    typedef NS_SLUA::FProperty FProperty;
#endif

DECLARE_CYCLE_STAT(TEXT("LuaOverrider bindOverrideFuncs"), STAT_LuaOverrider_bindOverrideFuncs, STATGROUP_Game);
DECLARE_CYCLE_STAT(TEXT("LuaOverrider do bindOverrideFuncs"), STAT_LuaOverrider_do_bindOverrideFuncs, STATGROUP_Game);
DECLARE_CYCLE_STAT(TEXT("LuaOverrider hookBpScript"), STAT_LuaOverrider_hookBpScript, STATGROUP_Game);
DECLARE_CYCLE_STAT(TEXT("LuaOverrider bindOverrideFuncs selfCtor"), STAT_LuaOverrider_bindOverrideFuncs_selfCtor, STATGROUP_Game);
DECLARE_STATS_GROUP(TEXT("Lua"), STATGROUP_Lua, STATCAT_Advanced);

#if (ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4)
#define GET_INPUT_ACTION_NAME(IAB) IAB.ActionName
#define IS_INPUT_ACTION_PAIRED(IAB) IAB.bPaired
#else
#define GET_INPUT_ACTION_NAME(IAB) IAB.GetActionName()
#define IS_INPUT_ACTION_PAIRED(IAB) IAB.IsPaired()
#endif

extern uint8 GRegisterNative(int32 NativeBytecodeIndex, const NS_SLUA::FNativeFuncPtr& Func);
enum
{
    Ex_LuaOverride = EX_Max - 1,
};

namespace NS_SLUA
{
    const FString SUPER_CALL_FUNC_NAME_PREFIX("__overrider_");
    LuaOverrider::OverridedClassMap LuaOverrider::overridedClasses;
    LuaOverrider::ClassHookedFuncNames LuaOverrider::classHookedFuncNames;
}

TMap<NS_SLUA::lua_State*, ULuaOverrider::ObjectTableMap> ULuaOverrider::objectTableMap;
ULuaOverrider::ClassNativeMap ULuaOverrider::classSuperFuncs;

#if (ENGINE_MINOR_VERSION<19) && (ENGINE_MAJOR_VERSION==4)
void ULuaOverrider::luaOverrideFunc(FFrame& Stack, RESULT_DECL)
#else
void ULuaOverrider::luaOverrideFunc(UObject* Context, FFrame& Stack, RESULT_DECL)
#endif
{
    UFunction* func = Stack.Node;
    ensure(func);
#if (ENGINE_MINOR_VERSION<19) && (ENGINE_MAJOR_VERSION==4)
    UObject* obj = Stack.Object;
#else
    UObject* obj = Context;
#endif
    ensure(obj);
    uint8* locals = Stack.Locals;
    
    FProperty* returnProperty = func->GetReturnProperty();
    bool bReturnPropertyInitialized = false;

    bool bCallFromNative = false;
    bool bContextOp = false;
    
    TArray<FProperty*, TMemStackAllocator<>> propertyToDestructList;

    if (Stack.CurrentNativeFunction)
    {
        // if ProcessContextOpcode with native function Stack Node and Object should be fixed!
        if (Stack.CurrentNativeFunction != func)
        {
#if (ENGINE_MINOR_VERSION<19) && (ENGINE_MAJOR_VERSION==4)
            obj = this;
#endif
            bContextOp = true;
            func = Stack.CurrentNativeFunction;
            returnProperty = func->GetReturnProperty();

            if (Stack.Code)
            {
                locals = (uint8*)FMemory_Alloca(func->PropertiesSize);
                FMemory::Memzero(locals, func->PropertiesSize);

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                for (auto it = (FProperty*)func->Children; *Stack.Code != EX_EndFunctionParms; it = (FProperty*)it->Next)
#else
                for (auto it = CastField<FProperty>(func->ChildProperties); *Stack.Code != EX_EndFunctionParms; it = CastField<FProperty>(it->Next))
#endif
                {
                    it->InitializeValue_InContainer(locals);
                    Stack.Step(Stack.Object, it->ContainerPtrToValuePtr<uint8>(locals));

                    if (returnProperty && (it == returnProperty))
                    {
                        bReturnPropertyInitialized = true;
                    }
                    else
                    {
                        propertyToDestructList.Add(it);
                    }
                }
                Stack.SkipCode(1);
            }
        }
        else
        {
            if (func->GetNativeFunc() == (NS_SLUA::FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc)
            {
                Stack.SkipCode(1);      // skip LuaOverrideFunc only when called from native func
                bCallFromNative = true;
            }
        }
    }

#if STATS
    FString statName = TEXT("Lua") / obj->GetClass()->GetName() / func->GetName();
    const TStatId StatId = FDynamicStats::CreateStatId<STAT_GROUP_TO_FStatGroup(STATGROUP_Lua)>(statName);
    FScopeCycleCounter CycleCounter(StatId);
#endif

#if WITH_EDITOR
    NS_SLUA::lua_State* L = editorGetObjLuaState(Stack, obj);
#else
    NS_SLUA::lua_State* L = getObjectLuaState(obj);
#endif

    if (L == nullptr)
    {
        NS_SLUA::Log::Error("LuaOverrideFunc L = nullptr, %s %s", TCHAR_TO_UTF8(*(obj->GetName())), TCHAR_TO_UTF8(*(func->GetName())));
        return;
    }

    if (!bReturnPropertyInitialized && returnProperty && !returnProperty->HasAnyPropertyFlags(CPF_ZeroConstructor))
    {
        returnProperty->InitializeValue_InContainer(locals);
        bReturnPropertyInitialized = true;
    }
    
    // Avoid recursive function call
    FString functionName = func->GetName();
    auto cls = obj->GetClass();
    auto subFunction = cls->FindFunctionByName(func->GetFName());
    bool bCallSuper;
    if (subFunction != func && isUFunctionHooked(subFunction))
    {
        bCallSuper = true;
    }
    else
    {
        bCallSuper = true;
        auto& tableMap = objectTableMap.FindChecked(L);
        FObjectTable* objTable = tableMap.Find(obj);
        if (objTable)
        {
            NS_SLUA::LuaVar* luaSelfTable = &objTable->table;
        
            NS_SLUA::LuaVar luaFunc = getLuaFunction(L, obj, luaSelfTable, functionName);
            if (luaFunc.isValid())
            {
                NS_SLUA::AutoStack as(L);
                luaFunc.callByUFunction(func, locals, bContextOp ? nullptr : Stack.OutParms, luaSelfTable);
                bCallSuper = false;
            }
        }
    }

    if (bCallSuper)
    {
        // Can't use cls->FindFunctionByName! It will cause recursive call.
        auto superFunction = func->GetOuterUClass()->FindFunctionByName(FName(*(NS_SLUA::SUPER_CALL_FUNC_NAME_PREFIX + functionName)));
        if (superFunction)
        {
            uint8* savedCode = Stack.Code;
            auto savedNode = Stack.Node;
            auto savedPropertyChain = Stack.PropertyChainForCompiledIn;
            uint8* newCode = superFunction->Script.GetData();

            FOutParmRec* lastOut = Stack.OutParms;
            if (lastOut)
            {
                func = superFunction;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                for (FProperty* prop = (FProperty*)superFunction->Children; prop && (prop->PropertyFlags & (CPF_Parm)) == CPF_Parm; prop = (FProperty*)prop->Next)
#else
                for (FProperty* prop = CastField<FProperty>(superFunction->ChildProperties); prop && (prop->PropertyFlags & (CPF_Parm)) == CPF_Parm; prop = CastField<FProperty>(prop->Next))
#endif
                {
                    if (prop->HasAnyPropertyFlags(CPF_OutParm))
                    {
                        // Fixed OutParam Property in Script
                        lastOut->Property = prop;
                        lastOut = lastOut->NextOutParm;
                    }
                }
            }
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            Stack.PropertyChainForCompiledIn = superFunction->Children;
#else
            Stack.PropertyChainForCompiledIn = superFunction->ChildProperties;
#endif

#if (ENGINE_MINOR_VERSION>=3) && (ENGINE_MAJOR_VERSION==5)
            static auto ULuaOverrideClass = ULuaOverrider::StaticClass();
            static auto BlueprintFunc = ULuaOverrideClass->FindFunctionByName(NS_SLUA::LuaOverrider::TRIGGER_ANIM_NOTIFY_FUNCTION_NAME);
            static auto ProcessInternalNativeFunc = BlueprintFunc->GetNativeFunc();
            if (superFunction->GetNativeFunc() == ProcessInternalNativeFunc)
#else
            if (superFunction->GetNativeFunc() == (NS_SLUA::FNativeFuncPtr)&UObject::ProcessInternal)
#endif
            {
                if (newCode)
                {
                    Stack.Code = newCode;
                    Stack.Node = superFunction;
                    superFunction->Invoke(obj, Stack, RESULT_PARAM);
                }
            }
            else
            {
                Stack.Code = newCode;
                Stack.Node = superFunction;
                superFunction->Invoke(obj, Stack, RESULT_PARAM);
            }

            Stack.PropertyChainForCompiledIn = savedPropertyChain;
            Stack.Node = savedNode;
            Stack.Code = savedCode;
        }
        else
        {
            NS_SLUA::Log::Error("LuaOverrideFunc luaFunc not isValid %s %s", TCHAR_TO_UTF8(*(obj->GetName())), TCHAR_TO_UTF8(*(func->GetName())));
        }
    }

    if (bCallFromNative || !Stack.OutParms || bContextOp)
    {
        if (RESULT_PARAM && func->ReturnValueOffset != MAX_uint16)
        {
            auto prop = func->GetReturnProperty();
            FOutParmRec* out = bContextOp ? nullptr : Stack.OutParms;
            while (out && out->Property != prop)
            {
                out = out->NextOutParm;
            }
            uint8* outParam = out ? out->PropAddr : locals + prop->GetOffset_ForInternal();
            if (RESULT_PARAM != outParam)
            {
                prop->CopyCompleteValueToScriptVM(RESULT_PARAM, outParam);
            }
        }
    }
    else if (func->ReturnValueOffset != MAX_uint16)
    {
        // Copy return value to previous frame's RESULT_PARAM, see UObject::ProcessInternal
        // if (*Stack.Code != EX_Nothing)
        // {
        //        Stack.Step(Stack.Object, RESULT_PARAM);
        // }
        static uint8 LocalOutCode[] = { EX_Return, EX_LocalOutVariable, 0, 0, 0, 0, 0, 0, 0, 0 };
        static ScriptPointerType *PropertyCode = reinterpret_cast<ScriptPointerType*>(LocalOutCode + 2);
        ScriptPointerType TempCode = (ScriptPointerType)(func->GetReturnProperty());
#ifdef REQUIRES_ALIGNED_INT_ACCESS
        FMemory::Memcpy(PropertyCode, &TempCode, sizeof(ScriptPointerType));
#else
        *PropertyCode = TempCode;
#endif
        Stack.Code = LocalOutCode;
    }

    for (auto& iter : propertyToDestructList)
    {
        iter->DestroyValue_InContainer(locals);
    }

    if (bReturnPropertyInitialized && returnProperty)
    {
        returnProperty->DestroyValue_InContainer(locals);
    }
}

NS_SLUA::lua_State* ULuaOverrider::editorGetObjLuaState(FFrame& Stack, const UObject* obj)
{
    const UObject* nowObj = obj;
    if (Cast<UBlueprintFunctionLibrary>(obj))
    {
        FFrame* nowStack = Stack.PreviousFrame;
        while (nowStack)
        {
            nowObj = nowStack->Object;
            if (!Cast<UBlueprintFunctionLibrary>(nowObj))
            {
                UGameInstance* gameInst = NS_SLUA::LuaState::getObjectGameInstance(nowObj);
                if (!gameInst)
                {
                    nowStack = nowStack->PreviousFrame;
                    continue;
                }
                break;
            }
            nowStack = nowStack->PreviousFrame;
        }
    }

    NS_SLUA::lua_State* L = getObjectLuaState(nowObj);
    return L;
}

NS_SLUA::lua_State* ULuaOverrider::getObjectLuaState(const UObject* obj)
{
    NS_SLUA::lua_State* L = nullptr;
    UGameInstance* gameInst = NS_SLUA::LuaState::getObjectGameInstance(obj);
    auto* luaState = gameInst ? NS_SLUA::LuaState::get(gameInst) : nullptr;
    if (luaState)
    {
        L = luaState->getLuaState();
    }
    else
    {
        for (TMap<NS_SLUA::lua_State*, ObjectTableMap>::TConstIterator iter(objectTableMap); iter;)
        {
            L = iter.Key();
            break;
        }
    }
    return L;
}

void ULuaOverrider::onLuaStateClose(NS_SLUA::lua_State* L)
{
    if (objectTableMap.Contains(L))
    {
#if WITH_EDITOR
        auto tableMap = objectTableMap.Find(L);
        for (auto iter : *tableMap)
        {
            UObject* obj = iter.Key.Get();
            if (!obj) continue;
            ILuaOverriderInterface* overrideInterface = Cast<ILuaOverriderInterface>(obj);
            if (!overrideInterface) continue;
            overrideInterface->FuncMap.Empty();
        }
#endif
        objectTableMap.Remove(L);
    }
}

void ULuaOverrider::InputAction_Implementation(FKey Key)
{
}

void ULuaOverrider::InputAxis_Implementation(float AxisValue)
{
}

void ULuaOverrider::InputTouch_Implementation(ETouchIndex::Type FingerIndex, const FVector& Location)
{
}

void ULuaOverrider::InputVectorAxis_Implementation(const FVector& AxisValue)
{
}

void ULuaOverrider::InputGesture_Implementation(float Value)
{
}

NS_SLUA::LuaVar ULuaOverrider::getLuaFunction(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar* table, const FString& funcName)
{
    if (!obj || !table)
    {
        return NS_SLUA::LuaVar();
    }
    NS_SLUA::AutoStack as(L);

    // implement ILuaOverriderInterface in BP will cause Cast fail. getLuaFunction each time for this case
    ILuaOverriderInterface* overrideInterface = Cast<ILuaOverriderInterface>(obj);
    if (overrideInterface)
    {
        return overrideInterface->GetCachedLuaFunc(L, *table, funcName);
    }
    return ILuaOverriderInterface::getFromTableIndex<NS_SLUA::LuaVar>(L, *table, funcName);
}

bool ULuaOverrider::isUFunctionHooked(UFunction* func)
{
    ensure(func);
    if (func->HasAnyFunctionFlags(FUNC_Native) && func->GetNativeFunc() == (NS_SLUA::FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc)
    {
        return true;
    }
    if (func->Script.Num() > 0 && func->Script[0] == Ex_LuaOverride)
    {
        return true;
    }
    return false;
}

void ULuaOverrider::addObjectTable(NS_SLUA::lua_State* L, UObject* obj, const NS_SLUA::LuaVar& table, bool isInstance)
{
    auto &tableMap = objectTableMap.FindOrAdd(L);
    tableMap.Add(obj, {table, isInstance});
    
    NS_SLUA::LuaObject::addLink(L, obj);
    //NS_SLUA::Log::Log("ULuaOverrider::addObjectTable L[%p], obj[%p]", L, obj);
}

void ULuaOverrider::removeObjectTable(UObject* obj)
{
    for (auto iter = objectTableMap.CreateIterator(); iter; ++iter)
    {
        auto& tableMap = iter.Value();
        
        auto objTable = tableMap.Find(obj);
        if (objTable)
        {
            NS_SLUA::LuaVar* table = objTable ? &objTable->table : nullptr;
            if (table->isValid())
            {
                auto* L = table->getState();
                table->push(L);
                lua_pushstring(L, SLUA_CPPINST);
                lua_pushnil(L);
                lua_rawset(L, -3);
                lua_pop(L, 1);
            }

            tableMap.Remove(obj);
        }
    }

    NS_SLUA::LuaNet::removeObjectTable(obj);
}

NS_SLUA::LuaVar* ULuaOverrider::getObjectLuaTable(const UObject* obj, NS_SLUA::lua_State* L)
{
    if (L)
    {
        L = L->l_G->mainthread;
    }
    else
    {
        L = getObjectLuaState(obj);
    }

    auto* tableMap = objectTableMap.Find(L);
    if (tableMap)
    {
        auto objTable = tableMap->Find(const_cast<UObject*>(obj));
        if (objTable)
        {
            return &objTable->table;
        }
    }
    
    return nullptr;
}

ULuaOverrider::FObjectTable* ULuaOverrider::getObjectTable(const UObject* obj, slua::lua_State* L)
{
    if (L)
    {
        L = L->l_G->mainthread;
    }
    else
    {
        L = getObjectLuaState(obj);
    }

    auto* tableMap = objectTableMap.Find(L);
    if (tableMap)
    {
        return tableMap->Find(const_cast<UObject*>(obj));
    }
    
    return nullptr;
}


ULuaOverrider::ObjectTableMap* ULuaOverrider::getObjectTableMap(NS_SLUA::lua_State* L)
{
    auto* tableMap = objectTableMap.Find(L);
    if (tableMap) return tableMap;
    return nullptr;
}

namespace NS_SLUA
{
    const char* LuaOverrider::UOBJECT_NAME = "Object";
    const char* LuaOverrider::SUPER_NAME = "Super";
    const char* LuaOverrider::CACHE_NAME = "__cache";
    const char* LuaOverrider::INSTANCE_CACHE_NAME = "__instance_cache";
    const FName LuaOverrider::TRIGGER_ANIM_NOTIFY_FUNCTION_NAME = TEXT("TriggerAnimNotify");
#if WITH_EDITOR
    ULuaOverrider::ClassNativeMap LuaOverrider::cacheNativeFuncs;
    TMap<UClass*, TArray<TWeakObjectPtr<UFunction>>> LuaOverrider::classAddedFuncs;
    TMap<UClass*, TArray<TWeakObjectPtr<UFunction>>> LuaOverrider::classHookedFuncs;
#endif

    const uint8 LuaOverrider::Code[] = { (uint8)Ex_LuaOverride, EX_Return, EX_Nothing };
    const int32 LuaOverrider::CodeSize = sizeof(Code);
    FRWLock LuaOverrider::classHookMutex;
    TMap<TWeakObjectPtr<UClass>, UClass::ClassConstructorType> LuaOverrider::classConstructors;
    TMap<UObject*, TArray<LuaOverrider*>> LuaOverrider::objectOverriders;

    const TCHAR* LuaOverrider::EInputEventNames[] = { TEXT("Pressed"), TEXT("Released"), TEXT("Repeat"), TEXT("DoubleClick"), TEXT("Axis"), TEXT("Max") };
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    LuaOverrider::FBlueprintFlushReinstancingQueue LuaOverrider::blueprintFlushReinstancingQueue;
#endif

    #define ACCESS_PRIVATE_FIELD(Class, Type, Member) \
        template <typename Class, Type Class::* M> \
        struct AccessPrivate##Class##Member { \
            friend Type Class::* Private##Class##Member() { return M; } \
        };\
        Type Class::* Private##Class##Member(); \
        template struct AccessPrivate##Class##Member<Class, &Class::Member>
    
    LuaOverrider::LuaOverrider(NS_SLUA::LuaState* luaState)
        : sluaState(luaState)
    {
        sluaState->doBuffer((const uint8*)LuaClassSource,strlen(LuaClassSource), SLUA_LUACODE);
        luaNet = new LuaNet();
        
        GUObjectArray.AddUObjectDeleteListener(this);
        GUObjectArray.AddUObjectCreateListener(this);
        asyncLoadingFlushUpdateHandle = FCoreDelegates::OnAsyncLoadingFlushUpdate.AddRaw(this, &LuaOverrider::onAsyncLoadingFlushUpdate);
        gcHandler = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(this, &LuaOverrider::onEngineGC);
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        if (!blueprintFlushReinstancingQueue.IsBound())
        {
            FBlueprintSupport::SetFlushReinstancingQueueFPtr(OnBlueprintFlushReinstancingQueue);
        }
        blueprintFlushDelegate = blueprintFlushReinstancingQueue.AddRaw(this, &LuaOverrider::onAsyncLoadingFlushUpdate);
#endif
        auto ULuaOverrideClass = ULuaOverrider::StaticClass();
        animNotifyTemplate = ULuaOverrideClass->FindFunctionByName(TRIGGER_ANIM_NOTIFY_FUNCTION_NAME);

        initInputs();
    }

    LuaOverrider::~LuaOverrider()
    {
        delete luaNet;
        luaNet = nullptr;
        ULuaOverrider::onLuaStateClose(sluaState->getLuaState());
        sluaState = nullptr;

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        blueprintFlushReinstancingQueue.Remove(blueprintFlushDelegate);
        if (!blueprintFlushReinstancingQueue.IsBound())
        {
            FBlueprintSupport::SetFlushReinstancingQueueFPtr(nullptr);
        }
#endif

        FWorldDelegates::OnWorldCleanup.Remove(onWorldCleanupHandle);
        if (onWorldTickStartHandle.IsValid())
        {
            FWorldDelegates::OnWorldTickStart.Remove(onWorldTickStartHandle);
            onWorldTickStartHandle.Reset();
        }
        FCoreUObjectDelegates::GetPostGarbageCollect().Remove(gcHandler);
        FCoreDelegates::OnAsyncLoadingFlushUpdate.Remove(asyncLoadingFlushUpdateHandle);
        GUObjectArray.RemoveUObjectCreateListener(this);
        GUObjectArray.RemoveUObjectDeleteListener(this);

        FRWScopeLock lock(classHookMutex, SLT_Write);
        objectOverriders.Empty();
        for (auto iter : classConstructors)
        {
            auto cls = iter.Key.Get();
            if (cls)
            {
                cls->ClassConstructor = iter.Value;
            }
        }
        classConstructors.Empty();
    }

    void LuaOverrider::NotifyUObjectCreated(const UObjectBase* Object, int32 Index)
    {
        QUICK_SCOPE_CYCLE_COUNTER(LuaOverrider_NotifyUObjectCreated);
        UObjectBaseUtility* obj = (UObjectBaseUtility*)Object;
        //NS_SLUA::Log::Log("LuaOverrider::NotifyUObjectCreated log %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));

        if (!obj->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
        {
            tryHook(obj, false);
        }

        // Process UInputComponent
        if (!obj->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject) && obj->IsA(UInputComponent::StaticClass()))
        {
            auto inputComponent = Cast<UInputComponent>((UObject*)obj);
            if (inputComponent)
            {
                AActor* actor = Cast<APlayerController>(Object->GetOuter());
                if (!actor)
                {
                    actor = Cast<APawn>(Object->GetOuter());
                }
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
                if (actor && actor->Role >= ROLE_AutonomousProxy)
#else
                if (actor && actor->GetLocalRole() >= ROLE_AutonomousProxy)
#endif
                {
                    inputComponents.AddUnique(inputComponent);

                    if (onWorldTickStartHandle.IsValid())
                    {
                        FWorldDelegates::OnWorldTickStart.Remove(onWorldTickStartHandle);
                    }
                    onWorldTickStartHandle = FWorldDelegates::OnWorldTickStart.AddRaw(this, &LuaOverrider::onWorldTickStart);
                }
            }
        }
    }

#if !((ENGINE_MINOR_VERSION<23) && (ENGINE_MAJOR_VERSION==4))
    void LuaOverrider::OnUObjectArrayShutdown()
    {
        GUObjectArray.RemoveUObjectCreateListener(this);
        GUObjectArray.RemoveUObjectDeleteListener(this);
    }
#endif

    void LuaOverrider::NotifyUObjectDeleted(const UObjectBase* Object, int32 Index)
    {
        UObject* obj = (UObject*)Object;
        ULuaOverrider::removeObjectTable(obj);
        
        UClass* cls = (UClass*)Object;;
        if (cls )
        {
            if (overridedClasses.Contains(cls))
            {
                removeOneOverride(cls, true);
                overridedClasses.Remove(cls);
            }

            LuaNet::onObjectDeleted(cls);

            FRWScopeLock lock(classHookMutex, SLT_Write);
            classConstructors.Remove(cls);
        }
    }

    bool LuaOverrider::tryHook(const UObjectBaseUtility* obj, bool bHookImmediate/* = false*/, bool bPostLoad/* = false*/)
    {
        if (isHookable(obj))
        {
            if (IsInGameThread() && !bPostLoad)
            {
                if (!obj->HasAnyFlags(RF_NeedPostLoad) || bHookImmediate)
                {
                    //NS_SLUA::Log::Log("LuaOverrider::NotifyUObjectCreated %s", TCHAR_TO_UTF8(*obj->GetFName().ToString()));
                    UGameInstance* gameInstance = LuaState::getObjectGameInstance((UObject*)obj);
                    if (gameInstance && gameInstance != sluaState->getGameInstance())
                    {
                        return false;
                    }

                    UClass* cls = obj->GetClass();
                    if (bHookImmediate)
                    {
                        bindOverrideFuncs(obj, cls);
                        return true;
                    }

#if USE_CIRCULAR_DEPENDENCY_LOAD_DEFERRING
                    FRWScopeLock lock(classHookMutex, SLT_Write);
                    if (cls->ClassConstructor != CustomClassConstructor)
                    {
                        classConstructors.Add(cls, cls->ClassConstructor);
                        cls->ClassConstructor = CustomClassConstructor;
                    }
                    auto &overriderList = objectOverriders.FindOrAdd((UObject*)obj);
                    overriderList.Add(this);
                    return true;
#else
                    bindOverrideFuncs(obj, cls);
                    return true;
#endif
                }
            }

            FScopeLock lock(&asyncLoadedObjectCS);
            asyncLoadedObjects.Add(AsyncLoadedObject{ (UObject*)obj });
        }

        return false;
    }

#if USE_CIRCULAR_DEPENDENCY_LOAD_DEFERRING
#if ENGINE_MAJOR_VERSION==4
    ACCESS_PRIVATE_FIELD(FObjectInitializer, UObject*, LastConstructedObject);
#else
    ACCESS_PRIVATE_FIELD(FObjectInitializer, bool, bIsDeferredInitializer);
#endif
#endif

    void LuaOverrider::CustomClassConstructor(const FObjectInitializer& ObjectInitializer)
    {
        auto obj = ObjectInitializer.GetObj();
        auto cls = obj->GetClass();

        UClass::ClassConstructorType clsConstructor;
        
        {
            FRWScopeLock lock(classHookMutex, SLT_Write);
            UClass::ClassConstructorType *classConstructorFuncPtr = nullptr;
            TArray<UClass*, TMemStackAllocator<>> handleClasses;
            auto superCls = cls;
            while (classConstructorFuncPtr == nullptr && superCls)
            {
                classConstructorFuncPtr = classConstructors.Find(superCls);
                if (!classConstructorFuncPtr)
                {
                    handleClasses.Add(superCls);
                }
                superCls = superCls->GetSuperClass();
            }
            check(classConstructorFuncPtr != nullptr);
            clsConstructor = *classConstructorFuncPtr;
            for (auto iter = handleClasses.CreateConstIterator(); iter; ++iter)
            {
                classConstructors.Emplace(*iter, clsConstructor);
            }
        }
        
        check(clsConstructor != CustomClassConstructor);
        
        {
            clsConstructor(ObjectInitializer);
            if (!IsInGameThread())
            {
                return;
            }
            ObjectInitializer.~FObjectInitializer();

            auto &ObjectInitializerProxy = *const_cast<FObjectInitializer*>(&ObjectInitializer);

            FUObjectThreadContext& ThreadContext = FUObjectThreadContext::Get();
            auto lastConstructedObject = ThreadContext.ConstructedObject;
            // set InstanceGraph(in UE4)/SubobjectOverrides(in UE5) and ComponentInits to initialize to avoid destructor twice
            new (&ObjectInitializerProxy) FObjectInitializer();

            ThreadContext.PopInitializer();

            // Let the FObjectFinders know we left the constructor.
            ThreadContext.IsInConstructor--;
            check(ThreadContext.IsInConstructor >= 0);
            ThreadContext.ConstructedObject = lastConstructedObject;
            
#if USE_CIRCULAR_DEPENDENCY_LOAD_DEFERRING
#if ENGINE_MAJOR_VERSION==4
            static auto LastConstructedObjectPtr = PrivateFObjectInitializerLastConstructedObject();

            struct FObjectProxyStruct
            {
                UObject* LastConstructedObject;
                bool bIsDeferredInitializer : 1;
            };

            FObjectProxyStruct* objProxy = reinterpret_cast<FObjectProxyStruct*>(&(ObjectInitializerProxy.*LastConstructedObjectPtr));
#else
            static auto bIsDeferredInitializerPtr = PrivateFObjectInitializerbIsDeferredInitializer();
            bool &bIsDeferredInitializer = ObjectInitializerProxy.*bIsDeferredInitializerPtr;
#endif
            if (!ObjectInitializer.GetObj())
            {
                // avoid ObjectInitializer destruct twice.
#if ENGINE_MAJOR_VERSION==4
                objProxy->bIsDeferredInitializer = true;
#else
                bIsDeferredInitializer = true;
#endif
            }
#endif
        }

        auto actorComponent = Cast<UActorComponent>(obj);
        auto luaInterface = Cast<ILuaOverriderInterface>(obj);
        if (actorComponent)
        {
            actorComponent->bWantsInitializeComponent = true;
        }

        if (!actorComponent || !luaInterface)
        {
            TArray<LuaOverrider*> overriderList;
            {
                FRWScopeLock lock(classHookMutex, SLT_ReadOnly);
                auto overriderListPtr = objectOverriders.Find(obj);
                if (overriderListPtr)
                {
                    overriderList = *overriderListPtr; // copy overrider list, don't use '&' reference
                }
            }

            for (auto overrider : overriderList)
            {
                overrider->bindOverrideFuncs(obj, cls);
            }
        }

        FRWScopeLock lock(classHookMutex, SLT_Write);
        objectOverriders.Remove(obj);
    }

    void LuaOverrider::removeOneOverride(UClass* cls, bool bObjectDeleted)
    {
#if WITH_EDITOR
        if (!bObjectDeleted)
        {
            auto hookedFuncsPtr = classHookedFuncs.Find(cls);
            if (hookedFuncsPtr)
            {
                // Revert hooked functions
                for (auto weakFunc : *hookedFuncsPtr)
                {
                    auto func = weakFunc.Get();
                    if (!func)
                    {
                        continue;
                    }

                    auto& script = func->Script;
                    int scriptNum = script.Num();

                    // func hooked by insert code
                    if (scriptNum >= CodeSize && script[0] == Ex_LuaOverride)
                    {
                        script.RemoveAt(0, CodeSize, false);
                        if (script.Num() == 0)
                        {
                            // Fixed crash: avoid FFrame Construct initialize with "Code(InNode->Script.GetData())" error assign with not null data while play twice in editor!
                            script.~TArray();
                            new (&script) TArray<uint8>();
                        }
                    }
                    
                    // func hooked by SetNativeFunc
                    if (func->GetNativeFunc() == (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc)
                    {
                        auto nativeMap = cacheNativeFuncs.Find(cls);
                        if (!nativeMap) return;
                        auto nativeFunc = nativeMap->Find(func->GetName());
                        if (!nativeFunc) return;
                        func->SetNativeFunc(*nativeFunc);
                    }
                }
            }

            auto addedFuncsPtr = classAddedFuncs.Find(cls);
            if (addedFuncsPtr)
            {
                // Remove functions added to class
                for (auto weakFunc : *addedFuncsPtr)
                {
                    auto func = weakFunc.Get();
                    if (!func)
                    {
                        continue;
                    }

                    if (LuaNet::luaRPCFuncs.Contains(func))
                    {
#if (ENGINE_MINOR_VERSION>=3) && (ENGINE_MAJOR_VERSION==5)
                        auto field = cls->Children.Get();
                        if (field == func)
                        {
                            cls->Children = func->Next;
                            func->Next = nullptr;
                        }
                        else
                        {
                            for (auto fieldAddress = &field->Next; (fieldAddress && *fieldAddress); fieldAddress = &((*fieldAddress)->Next))
                            {
                                if (*fieldAddress == func)
                                {
                                    *fieldAddress = func->Next;
                                    func->Next = nullptr;
                                    break;
                                }
                            }
                        }
#else
                        for (auto fieldAddress = &cls->Children; (fieldAddress && *fieldAddress); fieldAddress = &((*fieldAddress)->Next))
                        {
                            if (*fieldAddress == func)
                            {
                                *fieldAddress = func->Next;
                                func->Next = nullptr;
                                break;
                            }
                        }
#endif

                        cls->NetFields.Remove(func);
                        LuaNet::luaRPCFuncs.Remove(func);
                    }

                    cls->RemoveFunctionFromFunctionMap(func);
                    func->RemoveFromRoot();
                    func->ConditionalBeginDestroy();
                }
            }
        }

        classHookedFuncs.Remove(cls);
        classAddedFuncs.Remove(cls);
        cacheNativeFuncs.Remove(cls);
#endif
        classHookedFuncNames.Remove(cls);

        if (NS_SLUA::LuaNet::classLuaReplicatedMap.Contains(cls))
        {    
            auto &classLuaReplicated = NS_SLUA::LuaNet::classLuaReplicatedMap.FindChecked(cls);
            if (classLuaReplicated->ustruct.IsValid())
            {
                classLuaReplicated->ustruct->RemoveFromRoot();
            }
            
            delete classLuaReplicated;
            NS_SLUA::LuaNet::classLuaReplicatedMap.Remove(cls);
        }
    }

#if WITH_EDITOR
    void clearSuperFuncCache(UClass* cls)
    {
        if (!IsValid(cls))
        {
            return;
        }
        cls->ClearFunctionMapsCaches();
        clearSuperFuncCache(cls->GetSuperClass());
    }
    
    void LuaOverrider::removeOverrides()
    {
        TArray<UClass*> classArray;
        classHookedFuncs.GetKeys(classArray);
        for (auto cls : classArray)
        {
            removeOneOverride(cls, false);
            clearSuperFuncCache(cls);
        }

        classAddedFuncs.GetKeys(classArray);
        for (auto cls : classArray)
        {
            removeOneOverride(cls, false);
            clearSuperFuncCache(cls);
        }

        for (auto cls : overridedClasses)
        {
            removeOneOverride(cls, false);
            clearSuperFuncCache(cls);
        }
        overridedClasses.Empty();
        LuaNet::addedRPCClasses.Empty();
    }
#endif

    void LuaOverrider::onAsyncLoadingFlushUpdate()
    {
        if (!IsInGameThread() || bOnAsyncLoadingFlushUpdate)
        {
            return;
        }
        
        // NS_SLUA::Log::Log("LuaOverrider::OnAsyncLoadingFlushUpdate");
        bOnAsyncLoadingFlushUpdate = true;
        FScopeLock lock(&asyncLoadedObjectCS);

        uint32 curIndex = 0;
        uint32 newIndex = 0;
        while (asyncLoadedObjects.IsValidIndex(curIndex))
        {
            AsyncLoadedObject& objInfo = asyncLoadedObjects[curIndex];
            auto obj = objInfo.obj.Get();
            if (obj && !obj->HasAnyFlags(RF_NeedPostLoad) && !obj->HasAnyFlags(RF_NeedInitialization))
            {
                // NS_SLUA::Log::Log("LuaOverrider::OnAsyncLoadingFlushUpdate %s", TCHAR_TO_UTF8(*actorInfo.obj->GetFName().ToString()));
                UGameInstance* gameInstance = LuaState::getObjectGameInstance(obj);
                if (!gameInstance || gameInstance == sluaState->getGameInstance())
                {
                    UClass* cls = obj->GetClass();
                    bindOverrideFuncs(obj, cls);
                }
            }
            else if (obj)
            {
                // need to handle next time
                asyncLoadedObjects[newIndex] = objInfo;
                newIndex++;
            }
            curIndex++;
        }
        asyncLoadedObjects.RemoveAt(newIndex, asyncLoadedObjects.Num() - newIndex, false);

        bOnAsyncLoadingFlushUpdate = false;
    }

    void LuaOverrider::onEngineGC()
    {
    }

#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    void LuaOverrider::OnBlueprintFlushReinstancingQueue()
    {
        blueprintFlushReinstancingQueue.Broadcast();
    }
#endif

    FString LuaOverrider::getLuaFilePath(UObject* obj, UClass* cls, bool bCDOLua, bool& bHookInstancedObj)
    {
        bHookInstancedObj = false;
        const FString GET_LUA_FILE_FUNC_NAME = TEXT("GetLuaFilePath");
        UFunction* func = cls->FindFunctionByName(FName(*GET_LUA_FILE_FUNC_NAME));
        FString luaFilePath;
        if (func->GetNativeFunc())
        {
            UObject* defaultObject = cls->GetDefaultObject();
            defaultObject->ProcessEvent(func, &luaFilePath);

            if (!bCDOLua)
            {
                FString instanceFilePath;
                obj->UObject::ProcessEvent(func, &instanceFilePath);
                if (!instanceFilePath.IsEmpty() && instanceFilePath != luaFilePath)
                {
                    bHookInstancedObj = true;
                    luaFilePath = MoveTemp(instanceFilePath);
                }
            }
        }
        return MoveTemp(luaFilePath);
    }

    void iterateTable(lua_State* L, TSet<FName>& funcNames)
    {
        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            if (lua_type(L, -1) == LUA_TFUNCTION)
            {
                funcNames.Add(FName(lua_tostring(L, -2)));
            }
            lua_pop(L, 1);
        }
    }

    void getLuaFunctionsRecursive(lua_State* L, TSet<FName>& funcNames)
    {
        if (lua_type(L, -1) == LUA_TNIL)
        {
            NS_SLUA::Log::Error("LuaOverride getLuaFunctionsRecursive ValueType nil");
            return;
        }

        // Find subclass function names.
        int subType = lua_getfield(L, -1, "__inner_impl");
        if (subType != LUA_TTABLE)
        {
            lua_pop(L, 1); // pop __inner_impl
            return;
        }
        iterateTable(L, funcNames);

        // Find parent class function names.
        int baseType = lua_getfield(L, -1, "__super");
        if (baseType != LUA_TNIL)
        {
            getLuaFunctionsRecursive(L, funcNames);
        }
        lua_pop(L, 1); // pop __super

        lua_pop(L, 1); // pop __inner_impl
    }

    void getLuaFunctions(lua_State* L, TSet<FName>& funcNames, const NS_SLUA::LuaVar& luaModule)
    {
        NS_SLUA::AutoStack as(L);
        luaModule.push(L);
        if (lua_getmetatable(L, -1))
        {
            lua_pop(L, 1);
            getLuaFunctionsRecursive(L, funcNames);
        }
        else
        {
            iterateTable(L, funcNames);
        }
    }

    ACCESS_PRIVATE_FIELD(FProperty, int, Offset_Internal);

    UFunction* duplicateUFunction(UFunction* templateFunction, UClass* outerClass, FName newFuncName, FNativeFuncPtr nativeFunc)
    {
        static FArchive Ar;
        static auto PropertyOffsetPtr = PrivateFPropertyOffset_Internal();

        if (templateFunction->HasAnyFunctionFlags(FUNC_Native))
        {
            // avoid "Failed to bind native function" warnings in UFunction::Bind while native UFunction duplicate.
            outerClass->AddNativeFunction(*newFuncName.ToString(), nativeFunc);
        }

        FObjectDuplicationParameters duplicationParams(templateFunction, outerClass);
        duplicationParams.DestName = newFuncName;
        duplicationParams.InternalFlagMask &= ~EInternalObjectFlags::Native;

        UFunction* newFunc = Cast<UFunction>(StaticDuplicateObjectEx(duplicationParams));
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        newFunc->PropertyLink = Cast<FProperty>(newFunc->Children);
#else
        newFunc->PropertyLink = CastField<FProperty>(newFunc->ChildProperties);
#endif

        newFunc->PropertiesSize = templateFunction->PropertiesSize;
        newFunc->MinAlignment = templateFunction->MinAlignment;
        for (TFieldIterator<FProperty> srcIter(templateFunction), dstIter(newFunc); srcIter && dstIter; ++srcIter, ++dstIter)
        {
            FProperty* srcProperty = *srcIter;
            FProperty* destProperty = *dstIter;

            destProperty->Link(Ar);
            destProperty->RepIndex = srcProperty->RepIndex;
            destProperty->*PropertyOffsetPtr = srcProperty->GetOffset_ForInternal();
            destProperty->PropertyLinkNext = CastField<FProperty>(destProperty->Next);
        }

        outerClass->AddFunctionToFunctionMap(newFunc, newFuncName);
#if WITH_EDITOR
        auto &funcs = LuaOverrider::classAddedFuncs.FindOrAdd(outerClass);
        funcs.Add(newFunc);
#endif
        
        if (newFunc->HasAnyFunctionFlags(FUNC_NetMulticast))
        {
            outerClass->NetFields.Add(newFunc);
        }
        else
        {
            newFunc->SetSuperStruct(templateFunction);
        }
        
        newFunc->ClearInternalFlags(EInternalObjectFlags::Native);

        if (GUObjectArray.IsDisregardForGC(outerClass) && !GUObjectArray.IsOpenForDisregardForGC())
        {
            newFunc->AddToRoot();
        }
        else
        {
            newFunc->AddToCluster(outerClass);
        }
        
        return newFunc;
    }

    bool LuaOverrider::bindOverrideFuncs(const UObjectBase* objBase, UClass* cls) {
        SCOPE_CYCLE_COUNTER(STAT_LuaOverrider_bindOverrideFuncs);

        //UE_LOG(Slua, Log, TEXT("LuaOverrider::BindOverrideFuncs %s"), *objBase->GetFName().ToString());
        if (!sluaState || !objBase || !cls) {
            return false;
        }
        lua_State* L = sluaState->getLuaState();
        auto obj = (UObject*)objBase;
        NS_SLUA::LuaVar* selfTable = ULuaOverrider::getObjectLuaTable(obj, L);
        if (selfTable) {
            return true;
        }

        bool bHookInstancedObj;
        FString luaFilePath = getLuaFilePath(obj, cls, false, bHookInstancedObj);
        if (luaFilePath.IsEmpty()) {
            //NS_SLUA::Log::Log("LuaOverrider::BindOverrideFuncs LuaFilePath empty of Object[%s]", TCHAR_TO_UTF8(*(obj->GetFName().ToString())));
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
        //NS_SLUA::Log::Log("LuaOverrider::BindOverrideFuncs LuaFilePath[%s] of Object[%s]", TCHAR_TO_UTF8(*luaFilePath), TCHAR_TO_UTF8(*(obj->GetFName().ToString())));

        NS_SLUA::LuaVar luaSelfTable;
        if (luaModule.isFunction()) {
            luaModule = luaModule.call();
        }

        if (luaModule.isTable()) {
            SCOPE_CYCLE_COUNTER(STAT_LuaOverrider_bindOverrideFuncs_selfCtor);
            
            AutoStack as(L);
            luaModule.push(L);
            if (lua_getmetatable(L, -1)) {
                if (lua_getfield(L, -1, "__call") != LUA_TNIL) {
                    int top = LuaState::pushErrorHandler(L) - 1;
                    lua_insert(L, -2);
                    
                    lua_pushvalue(L, -4);
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
#if UE_BUILD_DEVELOPMENT
        luaSelfTable.push(L);
        lua_pushstring(L, UOBJECT_NAME);
        if (lua_rawget(L, -2) != LUA_TNIL) {
            NS_SLUA::Log::Error("LuaOverrider::BindOverrideFuncs Object[%s]'s luaSelfTable[%s] not allow to define \"Object\" variable!",
                TCHAR_TO_UTF8(*(obj->GetFName().ToString())), TCHAR_TO_UTF8(*luaFilePath));
        }
        lua_pop(L, 2);
#endif
        
        if (!overridedClasses.Contains(cls)) {
            SCOPE_CYCLE_COUNTER(STAT_LuaOverrider_do_bindOverrideFuncs);

            overridedClasses.Add(cls);

            TSet<FName> funcNames;
            getLuaFunctions(L, funcNames, luaModule);

            int hookCounter = 0;
            for (auto& funcName : funcNames) {
                UFunction* func = cls->FindFunctionByName(funcName, EIncludeSuperFlag::IncludeSuper);
                if (!func && (funcName.ToString()).StartsWith(TEXT("AnimNotify_"))) {
                    func = duplicateUFunction(animNotifyTemplate, cls, funcName, (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc);
                }
                if (func && (func->FunctionFlags & OverrideFuncFlags)) {
                    if (hookBpScript(func, cls, (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc)) {
                        hookCounter++;
                    }
                }
            }

            luaNet->addClassRPC(L, cls, luaFilePath);
            //NS_SLUA::Log::Log("LuaOverrider::bindOverrideFuncs luafile:%s totalFuncs:%d, cost:%.5fs", TCHAR_TO_UTF8(*luaFilePath), hookCounter, FPlatformTime::Seconds() - CurTime);
            classHookedFuncNames.Add(cls, funcNames);
        }

        bool bNetReplicated = false;
        if (auto classReplicated = LuaNet::addClassReplicatedProps(L, obj, luaModule))
        {
            LuaNet::initLuaReplicatedProps(L, obj, *classReplicated, luaSelfTable);
            bNetReplicated = true;
        }

        setmetatable(luaSelfTable, (void*)obj, bNetReplicated);
        ULuaOverrider::addObjectTable(L, obj, luaSelfTable, bHookInstancedObj);

        if (auto luaInterface = Cast<ILuaOverriderInterface>(obj))
        {
            luaInterface->PostLuaHook();
        }

        return true;
    }

    void LuaOverrider::setmetatable(const LuaVar& luaSelfTable, void* objPtr, bool bNetReplicated)
    {
        lua_State* L = sluaState->getLuaState();
        // setup __cppinst
        // we use rawpush to bind objptr and SLUA_CPPINST
        luaSelfTable.push(L);
        lua_pushstring(L, SLUA_CPPINST);
        lua_pushlightuserdata(L, objPtr);
        lua_rawset(L, -3);

        if (bNetReplicated)
        {
            LuaNet::setupFunctions(L);
        }

        lua_pushstring(L, SUPER_NAME);
        LuaObject::pushType(L, new LuaSuperCall((UObject*)objPtr), "LuaSuperCall", LuaSuperCall::setupMetatable, LuaSuperCall::genericGC);
        lua_rawset(L, -3);

        if (lua_getmetatable(L, -1)) {
            lua_newtable(L);
            lua_getfield(L, -2, "__index");
            lua_pushcclosure(L, classIndex, 1);
            lua_setfield(L, -2, "__index");

            lua_pushcfunction(L, classNewindex);
            lua_setfield(L, -2, "__newindex");

            lua_setmetatable(L, -3);

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
#if ENGINE_MAJOR_VERSION==4
        check(!obj->IsPendingKill());
#endif
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

    bool LuaOverrider::hookBpScript(UFunction* func, UClass* cls, FNativeFuncPtr hookFunc)
    {
        SCOPE_CYCLE_COUNTER(STAT_LuaOverrider_hookBpScript);

        static bool regExCode = false;
        if (!regExCode)
        {
            GRegisterNative(Ex_LuaOverride, hookFunc);
            regExCode = true;
        }

        // if func had hooked
        if (ULuaOverrider::isUFunctionHooked(func))
        {
            return false;
        }

        // duplicate UFunction for super call
        auto supercallFunc = duplicateUFunction(func, cls, FName(*(SUPER_CALL_FUNC_NAME_PREFIX + func->GetName())), func->GetNativeFunc());
#if WITH_EDITOR
        if (func->HasAnyFunctionFlags(FUNC_NetMulticast))
        {
            LuaNet::luaRPCFuncs.Add(supercallFunc);
        }
#endif

        bool hooked = false;
        UFunction* overrideFunc = cls->FindFunctionByName(func->GetFName(), EIncludeSuperFlag::ExcludeSuper);
        if (overrideFunc == func)
        {
            if (overrideFunc->HasAnyFunctionFlags(FUNC_Net) || overrideFunc->HasAnyFunctionFlags(FUNC_Native))
            {
#if WITH_EDITOR
                auto& funcMap = cacheNativeFuncs.FindOrAdd(cls);
                funcMap.Add(overrideFunc->GetName(), overrideFunc->GetNativeFunc());
#endif
                overrideFunc->SetNativeFunc(hookFunc);
            }
            overrideFunc->Script.Insert(Code, CodeSize, 0);
            hooked = true;

#if WITH_EDITOR
            auto &hookedFuncs = classHookedFuncs.FindOrAdd(cls);
            hookedFuncs.Add(func);
#endif
        }
        else if (!overrideFunc)
        {
            overrideFunc = duplicateUFunction(func, cls, func->GetFName(), (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc);
#if WITH_EDITOR
            if (func->HasAnyFunctionFlags(FUNC_NetMulticast))
            {
                LuaNet::luaRPCFuncs.Add(overrideFunc);
            }
#endif
            if (!overrideFunc->HasAnyFunctionFlags(FUNC_Native))
            {
                static TArray<uint8> ShortCode(Code, CodeSize);
                overrideFunc->Script = ShortCode;
            }
            hooked = true;
        }

        // BlueprintImplementableEvent type of UFunction can't return correct value with c++ call
        if (overrideFunc->ReturnValueOffset != MAX_uint16 && !overrideFunc->HasAnyFunctionFlags(FUNC_HasOutParms | FUNC_Native))
        {
            overrideFunc->FunctionFlags |= FUNC_HasOutParms;
        }
        return hooked;
    }

    int LuaOverrider::__index(lua_State * L)
    {
        lua_pushstring(L, SLUA_CPPINST);
        lua_rawget(L, 1);
        void* ud = lua_touserdata(L, -1);
        lua_pop(L, 1);
        UObject* obj = (UObject*)ud;
        if (!NS_SLUA::LuaObject::isUObjectValid(obj)) {
            return 0;
        }

        if (int res = LuaObject::fastIndex(L, (uint8*)obj, obj->GetClass()))
        {
            return res;
        }

        const char* keyName = lua_tostring(L, 2);
        if (keyName == nullptr) {
            return 0;
        }
        if (strcmp(keyName, UOBJECT_NAME) == 0) {
            return LuaObject::push(L, obj);
        }

        int netProp = LuaNet::__index(L, obj, keyName);
        if (netProp)
        {
            return netProp;
        }
        
        return LuaObject::objectIndex(L, obj, keyName, true);
    }

    int LuaOverrider::classIndex(lua_State *L)
    {
        lua_settop(L, 3);
        bool bLuaFirst = !!lua_toboolean(L, 3);
        
        if (!bLuaFirst) {
            int retCount = __index(L);
            if (retCount != 0)
            {
                return retCount;
            }
        }
        
        int top = lua_gettop(L);
        
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_pushvalue(L, 1);
        lua_pushvalue(L, 2);
        lua_pushboolean(L, !bLuaFirst);
        lua_call(L, 3, 1);

        int retCount = lua_gettop(L) - top;
        return retCount;
    }

    int LuaOverrider::__newindex(lua_State * L)
    {
        lua_pushstring(L, SLUA_CPPINST);
        lua_rawget(L, 1);
        void* ud = lua_touserdata(L, -1);
        if (!ud)
            luaL_error(L, "expect LuaBase table at arg 1");
        lua_pop(L, 1);

        const char* keyName = lua_tostring(L, 2);
        if (keyName == nullptr) {
            return 0;
        }
#if UE_BUILD_DEVELOPMENT
        if (strcmp(keyName, UOBJECT_NAME) == 0) {
            luaL_error(L, "Not allow assignment to \"Object\"!");
        }
#endif
        
        if (!LuaObject::objectNewIndex(L, (UObject*)ud, keyName, 3, false)) {
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
        lua_pop(L, 1);

        auto obj = (UObject*)ud;

        if (!NS_SLUA::LuaObject::isUObjectValid(obj))
        {
            return 0;
        }

        if (LuaObject::fastNewIndex(L, (uint8*)obj))
        {
            return 0;
        }
        
        const char* keyName = lua_tostring(L, 2);
        if (keyName == nullptr) {
            return 0;
        }
#if UE_BUILD_DEVELOPMENT
        if (strcmp(keyName, UOBJECT_NAME) == 0) {
            luaL_error(L, "Not allow assignment to \"Object\"!");
        }
#endif

        if (LuaNet::__newindex(L, obj, keyName))
        {
            return 0;
        }

        if (!LuaObject::objectNewIndex(L, obj, keyName, 3, false)) {
            lua_rawset(L, 1);
        }

        return 0;
    }

    void LuaOverrider::initInputs()
    {
        auto ULuaOverrideClass = ULuaOverrider::StaticClass();
        
        // Input Overrides Init
        inputActionFunc = ULuaOverrideClass->FindFunctionByName(FName("InputAction"));
        inputAxisFunc = ULuaOverrideClass->FindFunctionByName(FName("InputAxis"));
        inputTouchFunc = ULuaOverrideClass->FindFunctionByName(FName("InputTouch"));
        inputVectorAxisFunc = ULuaOverrideClass->FindFunctionByName(FName("InputVectorAxis"));
        inputGestureFunc = ULuaOverrideClass->FindFunctionByName(FName("InputGesture"));

        UInputSettings *defaultIS = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
        TArray<FName> axisNames, actionNames;
        defaultIS->GetAxisNames(axisNames);
        defaultIS->GetActionNames(actionNames);
        defaultAxisNames.Append(axisNames);
        defaultActionNames.Append(actionNames);

        EKeys::GetAllKeys(allKeys);

        onWorldCleanupHandle = FWorldDelegates::OnWorldCleanup.AddRaw(this, &LuaOverrider::onWorldCleanup);
    }

    void LuaOverrider::onWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
    {
        if (onWorldTickStartHandle.IsValid())
        {
            FWorldDelegates::OnWorldTickStart.Remove(onWorldTickStartHandle);
            onWorldTickStartHandle.Reset();
        }
    }

#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION <= 23
    void LuaOverrider::onWorldTickStart(ELevelTick TickType, float DeltaTime)
#else
    void LuaOverrider::onWorldTickStart(UWorld *World, ELevelTick TickType, float DeltaTime)
#endif
    {
        for (auto iter : inputComponents)
        {
            auto inputComponent = iter.Get();
            if (!inputComponent)
            {
                continue;
            }

            AActor* actor = Cast<AActor>(inputComponent->GetOuter());
            // Try to override input events
            overrideInputs(actor, inputComponent);
        }

        inputComponents.Empty();
        FWorldDelegates::OnWorldTickStart.Remove(onWorldTickStartHandle);
        onWorldTickStartHandle.Reset();
    }

    void LuaOverrider::overrideInputs(AActor* actor, UInputComponent* inputComponent)
    {
        UClass *actorClass = actor->GetClass();
        auto funcNames = classHookedFuncNames.Find(actorClass);
        if (!funcNames)
        {
            return;
        }

        overrideActionInputs(actor, inputComponent, *funcNames);
    }

    void LuaOverrider::overrideActionInputs(AActor* actor, UInputComponent* inputComponent, const TSet<FName>& luaFunctions)
    {
        UClass *actorClass = actor->GetClass();

        TSet<FName> actionNames;
        int32 numActionBindings = inputComponent->GetNumActionBindings();
        for (int32 i = 0; i < numActionBindings; ++i)
        {
            FInputActionBinding &inputActionBinding = inputComponent->GetActionBinding(i);
            FName name = GET_INPUT_ACTION_NAME(inputActionBinding);
            FString actionName = name.ToString();
            actionNames.Add(name);

            FName funcName = FName(*FString::Printf(TEXT("%s_%s"), *actionName, EInputEventNames[inputActionBinding.KeyEvent]));
            if (luaFunctions.Find(funcName))
            {
                auto inputFunc = duplicateUFunction(inputActionFunc, actorClass, funcName, (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc);
                inputActionBinding.ActionDelegate.BindDelegate(actor, funcName);
            }

            if (IS_INPUT_ACTION_PAIRED(inputActionBinding))
            {
                EInputEvent inputEvent = inputActionBinding.KeyEvent == IE_Pressed ? IE_Released : IE_Pressed;
                funcName = FName(*FString::Printf(TEXT("%s_%s"), *actionName, EInputEventNames[inputEvent]));
                if (luaFunctions.Find(funcName))
                {
                    auto inputFunc = duplicateUFunction(inputActionFunc, actorClass, funcName, (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc);
                    FInputActionBinding AB(name, inputEvent);
                    AB.ActionDelegate.BindDelegate(actor, funcName);
                    inputComponent->AddActionBinding(AB);
                }
            }
        }

        const EInputEvent InputEvents[] = { IE_Pressed, IE_Released };
        TSet<FName> diffActionNames = defaultActionNames.Difference(actionNames);
        for (TSet<FName>::TConstIterator it(diffActionNames); it; ++it)
        {
            FName actionName = *it;
            for (int32 i = 0; i < 2; ++i)
            {
                FName funcName = FName(*FString::Printf(TEXT("%s_%s"), *actionName.ToString(), EInputEventNames[InputEvents[i]]));
                if (luaFunctions.Find(funcName))
                {
                    auto inputFunc = duplicateUFunction(inputActionFunc, actorClass, funcName, (FNativeFuncPtr)&ULuaOverrider::luaOverrideFunc);
                    FInputActionBinding inputActionBinding(actionName, InputEvents[i]);
                    inputActionBinding.ActionDelegate.BindDelegate(actor, funcName);
                    inputComponent->AddActionBinding(inputActionBinding);
                }
            }
        }
    }
}
