// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "LuaState.h"

#include <lgc.h>
#include <lstate.h>
#include "LuaObject.h"
#include "SluaLib.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Blueprint/UserWidget.h"
#include "Misc/AssertionMacros.h"
#include "Misc/SecureHash.h"
#include "Log.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaSet.h"
#include "LuaMemoryProfile.h"
#include "HAL/RunnableThread.h"
#include "LatentDelegate.h"
#include "LuaFunctionAccelerator.h"
#include "LuaOverrider.h"
#include "LuaOverriderInterface.h"
#include "LuaProfiler.h"
#include "LuaProtobufWrap.h"
#include "Stats/Stats.h"
#include "luasocket/luasocket.h"

namespace NS_SLUA {
    FLuaStateInitEvent LuaState::onInitEvent;
    
    const int MaxLuaExecTime = 60; // in second
    const int MaxLuaGCCount = 8192;

    static float GCStructTimeLimit = 0.001f;

    FAutoConsoleVariableRef CVarSluaGCStructTimeLimit(
        TEXT("slua.GCStructTimeLimit"),
        GCStructTimeLimit,
        TEXT("Defer gc struct time limit in one frame.\n"),
        ECVF_Default);
    
    int print(lua_State *L) {
        FString str;
        int top = lua_gettop(L);
        for(int n=1;n<=top;n++) {
            size_t len;
            const char* s = luaL_tolstring(L, n, &len);
            str+="\t";
            if(s) str+=UTF8_TO_TCHAR(s);
        }
        UE_LOG(Slua, Log, TEXT("%s"), *str);
        return 0;
    }

    int error(lua_State* L) {
        const char* err = lua_tostring(L,1);
        luaL_traceback(L,L,err,1);
        err = lua_tostring(L,2);
        auto ls = LuaState::get(L);
        ls->onError(err);
        lua_pop(L,1);
        return 0;
    }
    
    void LuaState::onError(const char* err) {
        if (errorDelegate.IsBound()) errorDelegate.Broadcast(err);
        else Log::Error("%s", err);
    }

    int newCacheTable(lua_State* L) {
        lua_newtable(L);
        lua_newtable(L);
        lua_pushstring(L, "kv");
        lua_setfield(L, -2, "__mode");
        lua_setmetatable(L, -2);
        // register it
        return luaL_ref(L, LUA_REGISTRYINDEX);
    }
    
     #if WITH_EDITOR
     // used for debug
    int LuaState::getStringFromMD5(lua_State* L) {
        const char* md5String = lua_tostring(L, 1);
        LuaState* state = LuaState::get(L);
        FString md5FString = UTF8_TO_TCHAR(md5String);
        bool hasValue = state->debugStringMap.Contains(md5FString);
        if (hasValue) {
            auto value = state->debugStringMap[md5FString];
            lua_pushstring(L, TCHAR_TO_UTF8(*value));
        }
        else {
            lua_pushstring(L, "");
        }
        return 1;
    }
    #endif

    int LuaState::increaseCallStack()
    {
        newObjectsInCallStack.Push(ObjectSet());
        return currentCallStack++;
    }

    void LuaState::decreaseCallStack()
    {
        currentCallStack--;
        newObjectsInCallStack.Pop(false);
    }

    bool LuaState::hasObjectInStack(const UObject* obj, int stackLayer)
    {
        return newObjectsInCallStack[stackLayer].Contains(const_cast<UObject*>(obj));
    }

    int LuaState::loader(lua_State* L) {
        LuaState* state = LuaState::get(L);
        const char* fn = lua_tostring(L,1);
        FString filepath;
        TArray<uint8> buf = state->loadFile(fn, filepath);
        if(buf.Num() > 0) {
            char chunk[256];
            snprintf(chunk,256,"@%s",TCHAR_TO_UTF8(*filepath));
            if(luaL_loadbuffer(L,(const char*)buf.GetData(),buf.Num(),chunk)==0) {
                return 1;
            }
            else {
                const char* err = lua_tostring(L,-1);
                Log::Error("%s",err);
                lua_pop(L,1);
            }
        }
        else
            Log::Error("Can't load file %s",fn);
        return 0;
    }
    
    TArray<uint8> LuaState::loadFile(const char* fn,FString& filepath) {
        if(loadFileDelegate) return loadFileDelegate(fn,filepath);
        return TArray<uint8>();
    }

    int LuaState::import(lua_State *L) {
        const char* name = LuaObject::checkValue<const char*>(L, 1);
        if (name) {
            LuaState* state = LuaState::get(L);
            ImportedObjectCache* cacheImportedItem = state->cacheImportedMap.Find(name);
            if (cacheImportedItem)
            {
                UObject* cacheObj = cacheImportedItem->cacheObjectPtr.Get();
                if (cacheObj) {
                    switch (cacheImportedItem->importedType) 
                    {
                    case ImportedClass:
                    {
                        UClass* uclass = Cast<UClass>(cacheObj);
                        if (uclass) {
                            LuaObject::pushClass(L, uclass);
                            return 1;
                        }
                        break;
                    }
                    case ImportedStruct:
                    {
                        UScriptStruct* ustruct = Cast<UScriptStruct>(cacheObj);
                        if (ustruct) {
                            LuaObject::pushStruct(L, ustruct);
                            return 1;
                        }
                        break;
                    }
                    case ImportedEnum:
                    {
                        UEnum* uenum = Cast<UEnum>(cacheObj);
                        if (uenum) {
                            LuaObject::pushEnum(L, uenum);
                            return 1;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
            }

#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION>0
            static UPackage* AnyPackage = (UPackage*)-1;
#else
            static UPackage* AnyPackage = ANY_PACKAGE;
#endif
            FString path = UTF8_TO_TCHAR(name);
            if (!FindObject<UObject>(AnyPackage, *path)) {
                // Try to load object if not found!
                LoadObject<UObject>(NULL, *path);
            }

            UClass* uclass = FindObject<UClass>(AnyPackage, *path);
            if (uclass) {
                LuaObject::pushClass(L, uclass);
                state->cacheImportedMap.Add(name, ImportedObjectCache {uclass, ImportedClass});
                return 1;
            }
            UScriptStruct* ustruct = FindObject<UScriptStruct>(AnyPackage, *path);
            if (ustruct) {
                LuaObject::pushStruct(L, ustruct);
                state->cacheImportedMap.Add(name, ImportedObjectCache {ustruct, ImportedStruct});
                return 1;
            }

            UEnum* uenum = FindObject<UEnum>(AnyPackage, *path);
            if (uenum) {
                LuaObject::pushEnum(L, uenum);
                state->cacheImportedMap.Add(name, ImportedObjectCache{ uenum, ImportedEnum });
                return 1;
            }

            luaL_error(L, "Can't find class named %s", name);
        }
        return 0;
    }

    LuaState* LuaState::mainState = nullptr;
    TMap<int,LuaState*> stateMapFromIndex;
    static int StateIndex = 0;

    LuaState::LuaState(const char* name, UGameInstance* gameInstance)
        : loadFileDelegate(nullptr)
        , L(nullptr)
        , cacheObjRef(LUA_NOREF)
        , cacheEnumRef(LUA_NOREF)
        , cacheClassPropRef(LUA_NOREF)
        , cacheClassFuncRef(LUA_NOREF)
        , si(0)
        , deadLoopCheck(nullptr)
        , overrider(nullptr)
        , stepGCTimeLimit(0.0)
        , stepGCCountLimit(0)
        , fullGCInterval(0.0)
        , lastFullGCSeconds(0.0)
        , latentDelegate(nullptr)
        , currentCallStack(0)
    {
        if(name) stateName=UTF8_TO_TCHAR(name);
        this->gameInstance = gameInstance;
#if UE_BUILD_DEVELOPMENT
        bRefTraceEnable = false;
#endif
    }

    LuaState::~LuaState()
    {
        close();
    }

    LuaState* LuaState::get(int index) {
        auto it = stateMapFromIndex.Find(index);
        if(it) return *it;
        return nullptr;
    }

    LuaState* LuaState::get(const FString& name) {
        for(auto& pair:stateMapFromIndex) {
            auto state = pair.Value;
            if(state->stateName==name)
                return state;
        }
        return nullptr;
    }

    LuaState* LuaState::get(UGameInstance* pGI) {
        for (auto& pair : stateMapFromIndex) {
            auto state = pair.Value;
            if (state->gameInstance.Get() == pGI)
                return state;
        }
        return nullptr;
    }

    UGameInstance* LuaState::getObjectGameInstance(const UObject* obj)
    {
        auto* outer = obj->GetOuter();
        auto* world = outer ? outer->GetWorld() : nullptr;
        if (!world)
        {
            world = GWorld;
        }
        return world ? world->GetGameInstance() : nullptr;
    }

    // check lua top , this function can omit
    void LuaState::Tick(float dtime) {
        ensure(IsInGameThread());
        if (!L) return;
        int top = lua_gettop(L);
        if(top != 0) {
            for (int i = -1; i >= -top; i--) {
                Log::Error("Error: lua stack count should be zero , now is %d, %d is %s", top, i, luaL_typename(L,i));
                switch (lua_type(L, i)) {
                case LUA_TNUMBER:
                    Log::Error("Error: lua stack %d value is %lf", i, lua_tonumber(L, i));
                    break;
                case LUA_TSTRING:
                    Log::Error("Error: lua stack %d value is %s", i, lua_tostring(L, i));
                    break;
                default:
                    break;
                }
            }
            lua_settop(L, 0);
        }

#ifdef ENABLE_PROFILER
#if !UE_BUILD_SHIPPING
        LuaProfiler::tick(this);
#endif
#endif

        if (stateTickFunc.isFunction()) {
            stateTickFunc.call(dtime);
        }
        tickGC(dtime);
        tickLuaActors(dtime);
    }

    TStatId LuaState::GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(LuaState, STATGROUP_Game);
    }

    void LuaState::tickGC(float dtime) {
        if (stepGCTimeLimit > 0.0) {
            QUICK_SCOPE_CYCLE_COUNTER(Lua_StepGC)
#if !UE_BUILD_SHIPPING
            PROFILER_WATCHER_X(stepGC, "StepGC");
#endif
            auto runStepGC = [&]()
            {
                // use step gc every frame
                int runtimes = 0;
                double stepCost = 0.0;
                int stepCount = 0;
                for (double start = FPlatformTime::Seconds(), now = start; stepCount < stepGCCountLimit &&
                    now - start + stepCost < stepGCTimeLimit; stepCount++)
                {
                    if (lua_gc(L, LUA_GCSTEP, 0)) {
                        lastFullGCSeconds = FPlatformTime::Seconds();
#if !UE_BUILD_SHIPPING
                        PROFILER_WATCHER_X(fullGC, "FullGC");
#endif
                        break;
                    }

                    double currentSeconds = FPlatformTime::Seconds();
                    stepCost = currentSeconds - now;
                    now = currentSeconds;
                    runtimes++;

#if LUA_VERSION_NUM <= 503
                    if (stepCost * 10.0 > stepGCTimeLimit && L->l_G->gcfinnum > 4)
                    {
                        L->l_G->gcfinnum = 4;
                    }
#endif
                }

                // Log::Log("Step GC runtimes: %d", runtimes);
            };

            if (fullGCInterval > 0.0f)
            {
                if (FPlatformTime::Seconds() - lastFullGCSeconds > fullGCInterval)
                {
                    runStepGC();
                }
                else if (L->l_G->gcstate != GCSpause)
                {
                    runStepGC();
                }
            }
            else
            {
                runStepGC();
            }
        }

        {
            QUICK_SCOPE_CYCLE_COUNTER(Lua_DeferGCStruct)
            double stepCost = 0.0;
            for (double start = FPlatformTime::Seconds(), now = start; now - start + stepCost < GCStructTimeLimit;)
            {
                if (deferGCStruct.Num() == 0)
                {
                    break;
                }

                auto luaStruct = deferGCStruct[0];
                deferGCStruct.RemoveAtSwap(0);
                delete luaStruct;

                double currentSeconds = FPlatformTime::Seconds();
                stepCost = currentSeconds - now;
                now = currentSeconds;
            }
        }
    }

    void LuaState::tickLuaActors(float dtime) {
        tickInternalTime += dtime;

        tickActors.RemoveAll([](LuaTickInfo& info)
        {
            return info.bRemoved;
        });
        
        for (int i = 0; i < tickActors.Num(); ++i)
        {
            LuaTickInfo& tickInfo = tickActors[i];
            if (tickInfo.bRemoved) {
                continue;
            }
            auto obj = tickInfo.obj.Get();
            check(obj);
            if (obj && (tickInternalTime > tickInfo.expire)) {
                callLuaTick(obj, tickInfo.tickFunc, tickInternalTime - tickInfo.preExecuteTime);
                tickInfo.preExecuteTime = tickInternalTime;
                tickInfo.expire = tickInternalTime + tickInfo.interval;
            }
        }
    }

    void LuaState::registLuaTick(UObject* obj, float tickInterval) {
        unRegistLuaTick(obj);
        tickActors.Add(LuaTickInfo(obj, tickInterval, tickInternalTime, tickInternalTime));
    }

    void LuaState::unRegistLuaTick(const UObject* obj) {
        for (int i = 0; i < tickActors.Num();i++) {
            LuaTickInfo& info = tickActors[i];
            if (info.obj == obj) {
                info.bRemoved = true;
                break;
            }
        }
    }
    
    void LuaState::callLuaTick(UObject* obj, LuaVar& tickFunc, float dtime) {
        ILuaOverriderInterface* overrideInterface = Cast<ILuaOverriderInterface>(obj);
        if (!overrideInterface) {
            Log::Error("callLuaTick cast fail: %s. if obj implement ILuaOverriderInterface in BP, change to c++ instead.", TCHAR_TO_UTF8(*obj->GetName()));
            return;
        }
        LuaVar self = overrideInterface->GetSelfTable();
        if (!tickFunc.isFunction()) {
            LuaVar tick = self.getFromTable<LuaVar>("LuaTick");
            if (tick.isFunction()) {
                tickFunc = tick;
            }
        }
        if (tickFunc.isFunction()) {
            tickFunc.call(self, dtime);
        }
    }

    void LuaState::close() {
        if(mainState==this) mainState = nullptr;

        latentDelegate = nullptr;

#if WITH_EDITOR
        if (!mainState && overrider)
            overrider->removeOverrides();
#endif
        SafeDelete(overrider);

        releaseAllLink();

        cleanupThreads();
        
        if(L) {
#ifdef ENABLE_PROFILER
#if !UE_BUILD_SHIPPING
             LuaProfiler::clean(this);
#endif
#endif
            lua_close(L);
            GUObjectArray.RemoveUObjectCreateListener(this);
            GUObjectArray.RemoveUObjectDeleteListener(this);
            FCoreUObjectDelegates::GetPostGarbageCollect().Remove(pgcHandler);
            FWorldDelegates::OnWorldCleanup.Remove(wcHandler);
            stateMapFromIndex.Remove(si);
            L=nullptr;
        }
        objRefs.Empty();
        SafeDelete(deadLoopCheck);

        LuaMemoryProfile::stop();

        if (!mainState)
        {
            LuaFunctionAccelerator::clear();
        }
    }


    bool LuaState::init() {

        if(deadLoopCheck)
            return false;

        if(!mainState) 
            mainState = this;

        pgcHandler = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(this, &LuaState::onEngineGC);
        wcHandler = FWorldDelegates::OnWorldCleanup.AddRaw(this, &LuaState::onWorldCleanup);
        GUObjectArray.AddUObjectDeleteListener(this);
        GUObjectArray.AddUObjectCreateListener(this);

        latentDelegate = NewObject<ULatentDelegate>((UObject*)GetTransientPackage(), ULatentDelegate::StaticClass());
        latentDelegate->bindLuaState(this);

        si = ++StateIndex;

        propLinks.Empty();
        classMap.clear();
        objRefs.Empty();

#if WITH_EDITOR
        // used for debug
        debugStringMap.Empty();

        if(!IsRunningCommandlet())
        {
            deadLoopCheck = new FDeadLoopCheck();
        }
#endif

        // use custom memory alloc func to profile memory footprint
#if ENABLE_PROFILER && !UE_BUILD_SHIPPING
        L = lua_newstate(LuaMemoryProfile::alloc,this);
#else
        L = luaL_newstate();
#endif
        
        lua_atpanic(L,_atPanic);
        // bind this to L
        *((void**)lua_getextraspace(L)) = this;
        stateMapFromIndex.Add(si,this);

        // init obj cache table
        cacheObjRef = newCacheTable(L);

        // init enum cache table
        lua_newtable(L);
        cacheEnumRef = luaL_ref(L, LUA_REGISTRYINDEX);

        // init cls prop cache metatable
        lua_newtable(L);
        cacheClassPropRef = luaL_ref(L, LUA_REGISTRYINDEX);

        // init cls function cache metatable
        lua_newtable(L);
        cacheClassFuncRef = luaL_ref(L, LUA_REGISTRYINDEX);

        ensure(lua_gettop(L)==0);
        
        luaL_openlibs(L);
        
        lua_pushcfunction(L,import);
        lua_setglobal(L, "import");
        
        lua_pushcfunction(L,print);
        lua_setglobal(L, "print");

        overrider = new LuaOverrider(this);

        #if WITH_EDITOR
        // used for debug
        lua_pushcfunction(L, getStringFromMD5);
        lua_setglobal(L, "getStringFromMD5");
        #endif
        
        lua_pushcfunction(L,loader);
        int loaderFunc = lua_gettop(L);

        lua_getglobal(L,"package");
        lua_getfield(L,-1,"searchers");

        int loaderTable = lua_gettop(L);

        for(int i=lua_rawlen(L,loaderTable)+1;i>2;i--) {
            lua_rawgeti(L,loaderTable,i-1);
            lua_rawseti(L,loaderTable,i);
        }
        lua_pushvalue(L,loaderFunc);
        lua_rawseti(L,loaderTable,2);
        lua_settop(L, 0);

        InitExtLib(L);

        LuaObject::init(L);
        LuaProtobuf::init(L);
        SluaUtil::openLib(L);
        LuaClass::reg(L);
        LuaArray::reg(L);
        LuaMap::reg(L);
        LuaSet::reg(L);
#ifdef ENABLE_PROFILER
#if !UE_BUILD_SHIPPING
        LuaProfiler::init(this);
#endif    
#endif

        lua_settop(L,0);

        onInitEvent.Broadcast(L);

        return true;
    }

    void LuaState::attach(UGameInstance* GI) {
        this->gameInstance = GI;
    }

    int LuaState::_atPanic(lua_State* L) {
        const char* err = lua_tostring(L,-1);
        Log::Error("Fatal error: %s",err);
        return 0;
    }

    void LuaState::setLoadFileDelegate(LoadFileDelegate func) {
        loadFileDelegate = func;
    }

    LuaState::ErrorDelegate* LuaState::getErrorDelegate()
    {
        return &errorDelegate;
    }

    void LuaState::addLink(void* address) {
        if (!propLinks.Contains(address))
            propLinks.Add(address);
    }

    void LuaState::releaseLink(void* address) {
        auto propLinksPtr = propLinks.Find(address); 
        if (!propLinksPtr) {
            return;
        }
        
        auto& propList = *propLinksPtr;
        for (auto& cprop : propList) {
            reinterpret_cast<GenericUserData*>(cprop)->flag |= UD_HADFREE;
        }
        propList.Empty();
        propLinks.Remove(address);
    }

    void LuaState::releaseAllLink() {
        for (auto& pair : propLinks) {
            for (auto& prop : pair.Value) {
                reinterpret_cast<GenericUserData*>(prop)->flag |= UD_HADFREE;
            }
        }
        propLinks.Empty();
    }

    void LuaState::linkProp(void* parentAddress, void* prop) {
        auto propud = reinterpret_cast<GenericUserData*>(prop);
        propud->parent = parentAddress;

        auto& propList = propLinks.FindChecked(parentAddress);
        propList.Add(propud);
    }

    void LuaState::unlinkProp(void* prop) {
        auto propud = reinterpret_cast<GenericUserData*>(prop);
        check(propud->parent);
        auto propLinksPtr = propLinks.Find(propud->parent);
        if (!propLinksPtr) {
            return;
        }

        auto& propList = *propLinksPtr;
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        propList.RemoveSwap(propud);
#else
        propList.RemoveSwap(propud, false);
#endif
    }

    // engine will call this function on post gc
    void LuaState::onEngineGC()
    {
        for (CacheImportedMap::TIterator it(cacheImportedMap); it; ++it)
            if (!it.Value().cacheObjectPtr.IsValid())
                it.RemoveCurrent();
    }
    
    void LuaState::onWorldCleanup(UWorld * World, bool bSessionEnded, bool bCleanupResources)
    {
        unlinkUObject(World);
    }

    LuaVar LuaState::doBuffer(const uint8* buf,uint32 len, const char* chunk, LuaVar* pEnv) {
        AutoStack g(L);
        pushErrorHandler(L);

        if(luaL_loadbuffer(L, (const char *)buf, len, chunk)) {
            const char* err = lua_tostring(L,-1);
            Log::Error("DoBuffer failed: %s",err);
            return LuaVar();
        }
        
        LuaVar f(L, -1);
        return f.call();
    }

    LuaVar LuaState::doString(const char* str, LuaVar* pEnv) {
        // fix #31 & #30 issue, 
        // vc compile optimize code cause cl.exe dead loop in release mode(no WITH_EDITOR)
        // if turn optimze flag on
        // so just write complex code to bypass link optimize
        // like this, WTF!
        uint32 len = strlen(str);
        #if WITH_EDITOR
        FString md5FString = FMD5::HashAnsiString(UTF8_TO_TCHAR(str));
        debugStringMap.Add(md5FString, UTF8_TO_TCHAR(str));
        return doBuffer((const uint8*)str,len,TCHAR_TO_UTF8(*md5FString),pEnv);
        #else
        return doBuffer((const uint8*)str,len,str,pEnv);
        #endif
    }

    LuaVar LuaState::doFile(const char* fn, LuaVar* pEnv) {
        FString filepath;
        TArray<uint8> buf = loadFile(fn, filepath);
        if (buf.Num() > 0) {
            char chunk[256];
            snprintf(chunk,256,"@%s",TCHAR_TO_UTF8(*filepath));

            LuaVar r = doBuffer(buf.GetData(),buf.Num(),chunk,pEnv );
            return r;
        }
        return LuaVar();
    }

    LuaVar LuaState::requireModule(const char* fn, LuaVar* pEnv) {
        int top = LuaState::pushErrorHandler(L);
        lua_getglobal(L, "require");
        lua_pushstring(L, fn);
        
        if (lua_pcall(L, 1, 1, top))
            lua_pop(L, 1);

        lua_remove(L, top);

        int retCount = lua_gettop(L) - top + 1;
        LuaVar luaModule(L, -retCount);
        lua_pop(L, retCount);
        return MoveTemp(luaModule);
    }

#if !((ENGINE_MINOR_VERSION<23) && (ENGINE_MAJOR_VERSION==4))
    void LuaState::OnUObjectArrayShutdown()
    {
        // remove listeners to avoid crash on pc when app exit
        GUObjectArray.RemoveUObjectCreateListener(this);
        GUObjectArray.RemoveUObjectDeleteListener(this);
    }
#endif

    void LuaState::NotifyUObjectDeleted(const UObjectBase * Object, int32 Index)
    {
        classMap.cachePropMap.Remove((UStruct*)Object);
        LuaObject::removeCache(L, Object, cacheEnumRef);
        LuaObject::removeCache(L, Object, cacheClassPropRef);
        LuaObject::removeCache(L, Object, cacheClassFuncRef);
        LuaFunctionAccelerator::remove((UFunction*)Object);

        // indicate ud and all child had be free
        releaseLink((void*)Object);
        
        unlinkUObject((const UObject*)Object);

        if (currentCallStack > 0)
        {
            ObjectSet& objSet = newObjectsInCallStack.Last();
            if (objSet.Contains(const_cast<UObjectBase*>(Object)))
            {
                objSet.Remove(const_cast<UObjectBase*>(Object));
            }
        }
    }

    void LuaState::NotifyUObjectCreated(const UObjectBase *Object, int32 Index)
    {
        if (!IsInGameThread())
        {
            return;
        }

        if (currentCallStack > 0)
        {
            ObjectSet& objSet = newObjectsInCallStack.Last();
            objSet.Add(const_cast<UObjectBase*>(Object));
        }
    }

    void LuaState::unlinkUObject(const UObject * Object,void* userdata/*=nullptr*/)
    {
        // find Object from objRefs, maybe nothing
        auto udptr = objRefs.Find(Object);
        // maybe Object not push to lua
        if (!udptr) {
            return;
        }

        GenericUserData* ud = *udptr;
        if (userdata && userdata != (void*)ud) {
            return;
        }

        // remove should put here avoid ud is invalid
        // remove ref, Object must be an UObject in slua
        objRefs.Remove(Object);

        if (!ud || ud->flag & UD_HADFREE)
            return;

        ud->flag |= UD_HADFREE;
        // remove cache
        ensure(ud->ud == Object);
        LuaObject::removeObjCache(L, (void*)Object);
    }

    void LuaState::AddReferencedObjects(FReferenceCollector & Collector)
    {
        if (latentDelegate)
        {
            Collector.AddReferencedObject(latentDelegate);
        }

        // erase all null reference
        // Collector.AddReferencedObjects will set inner item to nullptr
        // so check and remove it
        for (UObjectRefMap::TIterator it(objRefs); it; ++it)
        {
            UObject* item = it.Key();
            GenericUserData* userData = it.Value();
            if (userData && !(userData->flag & UD_REFERENCE))
            {
                continue;
            }
            Collector.AddReferencedObject(item);
        }
    }

    int LuaState::pushErrorHandler(lua_State* L) {
        auto ls = get(L);
        ensure(ls!=nullptr);
        return ls->_pushErrorHandler(L);
    }

    int LuaState::addThread(lua_State *thread)
    {
        int isMainThread = lua_pushthread(thread);
        if (isMainThread == 1)
        {
            lua_pop(thread, 1);

            luaL_error(thread, "Can't call latent action in main lua thread!");
            return LUA_REFNIL;
        }

        lua_xmove(thread, L, 1);
        lua_pop(thread, 1);

        ensure(lua_isthread(L, -1));

        int threadRef = luaL_ref(L, LUA_REGISTRYINDEX);
        threadToRef.Add(thread, threadRef);
        refToThread.Add(threadRef, thread);

        return threadRef;
    }

    void LuaState::resumeThread(int threadRef)
    {
        QUICK_SCOPE_CYCLE_COUNTER(Lua_LatentCallback);

        lua_State **threadPtr = refToThread.Find(threadRef);
        if (threadPtr)
        {
            lua_State *thread = *threadPtr;
            bool threadIsDead = false;

            if (lua_status(thread) == LUA_OK && lua_gettop(thread) == 0)
            {
                Log::Error("cannot resume dead coroutine");
                threadIsDead = true;
            }
            else
            {
#if LUA_VERSION_NUM > 503
                int nres = 0;
                int status = lua_resume(thread, L, 0, &nres);
#else
                int status = lua_resume(thread, L, 0);
#endif
                if (status == LUA_OK || status == LUA_YIELD)
                {
                    if (status == LUA_OK)
                    {
                        threadIsDead = true;
                    }
                }
            }

            if (threadIsDead)
            {
                threadToRef.Remove(thread);
                refToThread.Remove(threadRef);
                luaL_unref(L, LUA_REGISTRYINDEX, threadRef);
            }
        }
    }

    int LuaState::findThread(lua_State *thread)
    {
        int32 *threadRefPtr = threadToRef.Find(thread);
        return threadRefPtr ? *threadRefPtr : LUA_REFNIL;
    }

    void LuaState::cleanupThreads()
    {
        for (TMap<lua_State*, int32>::TIterator It(threadToRef); It; ++It)
        {
            int32 threadRef = It.Value();
            if (threadRef != LUA_REFNIL)
            {
                luaL_unref(L, LUA_REGISTRYINDEX, threadRef);
            }
        }
        threadToRef.Empty();
        refToThread.Empty();
    }

    ULatentDelegate* LuaState::getLatentDelegate() const
    {
        return latentDelegate;
    }

    bool LuaState::hookObject(LuaState* inState, const UObjectBaseUtility* obj, bool bHookImmediate/* = false*/, bool bPostLoad/* = false*/)
    {
        auto hook = [&](LuaState* state)
        {
            if (!state || !state->overrider)
            {
                return false;
            }
            return state->overrider->tryHook(obj, bHookImmediate, bPostLoad);
        };
        LuaState* state = inState;
        if (!state) {
            auto* gameInstance = getObjectGameInstance((UObject*)obj);
            state = gameInstance ? get(gameInstance) : nullptr;
            if (!state)
            {
                state = get();
            }
        }
        
        return hook(state);
    }

#if UE_BUILD_DEVELOPMENT
    void LuaState::addRefTraceback(int ref)
    {
        if (!bRefTraceEnable) {
            return;
        }

        luaL_traceback(L, L, nullptr, 0);
        const char* stacktrace = lua_tostring(L, -1);

        refTraceback.Add(ref, FString(UTF8_TO_TCHAR(stacktrace)));

        lua_pop(L, 1);
    }

    void LuaState::removeRefTraceback(int ref)
    {
        if (!bRefTraceEnable) {
            return;
        }
        if (refTraceback.Contains(ref)) {
            refTraceback.Remove(ref);
        }
    }

    FString LuaState::getRefTraceback(int ref)
    {
        FString *result = refTraceback.Find(ref);
        if (result)
        {
            return *result;
        }

        return FString();
    }

    bool LuaState::isRefTraceEnable() const
    {
        return bRefTraceEnable;
    }

    void LuaState::setRefTraceEnable(bool enable)
    {
        bRefTraceEnable = enable;
    }

#endif

    LuaVar LuaState::initInnerCode(const char * str)
    {
        uint32 len = strlen(str);
        return doBuffer((const uint8*)str, len, SLUA_LUACODE);
    }

    int LuaState::_pushErrorHandler(lua_State* state) {
        lua_pushcfunction(state,error);
        return lua_gettop(state);
    }

    LuaVar LuaState::get(const char* key) {
        // push global table
        lua_pushglobaltable(L);

        FString path(key);
        FString left,right;
        LuaVar rt;
        while(strSplit(path,".",&left,&right)) {
            if(lua_type(L,-1)!=LUA_TTABLE) break;
            lua_pushstring(L,TCHAR_TO_UTF8(*left));
            lua_gettable(L,-2);
            rt.set(L,-1);
            lua_remove(L,-2);
            if(rt.isNil()) break;
            path = right;
        }
        lua_pop(L,1);
        return rt;
    }

    bool LuaState::set(const char * key, LuaVar v)
    {
        // push global table
        AutoStack as(L);
        lua_pushglobaltable(L);

        FString path(key);
        FString left, right;
        LuaVar rt;
        while (strSplit(path, ".", &left, &right)) {
            if (lua_type(L, -1) != LUA_TTABLE) return false;
            lua_pushstring(L, TCHAR_TO_UTF8(*left));
            lua_gettable(L, -2);
            if (lua_isnil(L, -1))
            {
                // pop nil
                lua_pop(L, 1);
                if (right.IsEmpty()) {
                    lua_pushstring(L, TCHAR_TO_UTF8(*left));
                    v.push(L);
                    lua_rawset(L, -3);
                    return true;
                }
                else {
                    lua_newtable(L);
                    lua_pushstring(L, TCHAR_TO_UTF8(*left));
                    // push table again
                    lua_pushvalue(L, -2);
                    lua_rawset(L, -4);
                    // stack leave table for next get
                }
            }
            else
            {
                // if sub field isn't table, set failed
                if (!right.IsEmpty() && !lua_istable(L, -1))
                    return false;

                if (lua_istable(L, -1) && right.IsEmpty()) {
                    lua_pushstring(L, TCHAR_TO_UTF8(*left));
                    v.push(L);
                    lua_rawset(L, -3);
                    return true;
                }
            }
            path = right;
        }
        return false;
    }

    LuaVar LuaState::createTable() {
        lua_newtable(L);
        LuaVar ret(L,-1);
        lua_pop(L,1);
        return ret;
    }

    LuaVar LuaState::createTable(const char * key)
    {
        lua_newtable(L);
        LuaVar ret(L, -1);
        set(key, ret);
        lua_pop(L, 1);
        return ret;
    }

    void LuaState::setGCParam(double limitSeconds, int limitCount, double interval)
    {
        stepGCTimeLimit = limitSeconds;
        stepGCCountLimit = limitCount;
        fullGCInterval = interval;
    }

    void LuaState::setTickFunction(LuaVar func)
    {
        stateTickFunc = func;
    }

    void LuaState::addRef(UObject* obj, void* ud, bool ref)
    {
        auto* udptr = objRefs.Find(obj);
        // if any obj find in objRefs, it should be flag freed and removed
        if (udptr) {
            (*udptr)->flag |= UD_HADFREE;
            objRefs.Remove(obj);
        }

        GenericUserData* userData = (GenericUserData*)ud;
        if (ref && userData) {
            userData->flag |= UD_REFERENCE;
        }
        objRefs.Add(obj,userData);
    }

    int32 FDeadLoopCheck::NameCounter = 0;
    FDeadLoopCheck::FDeadLoopCheck()
        : timeoutEvent(nullptr)
        , timeoutCounter(0)
        , stopCounter(0)
        , frameCounter(0)
    {
        thread = FRunnableThread::Create(this, *FString::Printf(TEXT("FLuaDeadLoopCheck_%d"), NameCounter++), 0, TPri_BelowNormal);
    }

    FDeadLoopCheck::~FDeadLoopCheck()
    {
        Stop();
        thread->WaitForCompletion();
        SafeDelete(thread);
    }

    uint32 FDeadLoopCheck::Run()
    {
        while (stopCounter.GetValue() == 0) {
            FPlatformProcess::Sleep(1.0f);
            if (frameCounter.GetValue() != 0) {
                timeoutCounter.Increment();
                if(timeoutCounter.GetValue() >= MaxLuaExecTime)
                    onScriptTimeout();
            }
        }
        return 0;
    }

    void FDeadLoopCheck::Stop()
    {
        stopCounter.Increment();
    }

    int FDeadLoopCheck::scriptEnter(ScriptTimeoutEvent* pEvent)
    {
        int ret = frameCounter.Increment();
        if ( ret == 1) {
            timeoutCounter.Set(0);
            timeoutEvent.store(pEvent);
        }
        return ret;
    }

    int FDeadLoopCheck::scriptLeave()
    {
        return frameCounter.Decrement();
    }

    void FDeadLoopCheck::onScriptTimeout()
    {
        auto pEvent = timeoutEvent.load();
        if (pEvent) {
            timeoutEvent.store(nullptr);
            pEvent->onTimeout();
        }
    }

    LuaScriptCallGuard::LuaScriptCallGuard(lua_State * L_)
        :L(L_)
    {
        auto ls = LuaState::get(L);
        if (ls->deadLoopCheck)
        {
            ls->deadLoopCheck->scriptEnter(this);
        }
    }

    LuaScriptCallGuard::~LuaScriptCallGuard()
    {
        auto ls = LuaState::get(L);
        if(ls->deadLoopCheck)
        {
            ls->deadLoopCheck->scriptLeave();
        }
    }

    void LuaScriptCallGuard::onTimeout()
    {
        auto hook = lua_gethook(L);
        // if debugger isn't exists
        if (hook == nullptr) {
            // this function thread safe
            lua_sethook(L, scriptTimeout, LUA_MASKLINE, 0);
        }
    }

    void LuaScriptCallGuard::scriptTimeout(lua_State *L, lua_Debug *ar)
    {
        // only report once
        lua_sethook(L, nullptr, 0, 0);
        luaL_error(L, "script exec timeout");
    }

    FProperty* LuaState::ClassCache::findProp(UStruct* ustruct, const char* pname)
    {
        auto item = cachePropMap.Find(ustruct);
        if (!item) {
            // cache property's
            item = &cachePropMap.Add(ustruct);
            auto propertyLink = ustruct->PropertyLink;
            static const uint64 ScriptStructCastFlags = UScriptStruct::StaticClassCastFlags();
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            auto scriptStruct = ustruct->GetClass()->HasAnyCastFlag(ScriptStructCastFlags) ? Cast<UScriptStruct>(ustruct) : nullptr;
#else
            auto scriptStruct = ustruct->HasAnyCastFlags(ScriptStructCastFlags) ? Cast<UScriptStruct>(ustruct) : nullptr;
#endif
            if (scriptStruct && !scriptStruct->IsNative()) {
                for (FProperty* prop = propertyLink; prop != nullptr; prop = prop->PropertyLinkNext) {
                    item->Add(TCHAR_TO_UTF8(*getPropertyFriendlyName(prop)), prop);
                }
            }
            else {
                for (FProperty* prop = propertyLink; prop != nullptr; prop = prop->PropertyLinkNext) {
                    item->Add(TCHAR_TO_UTF8(*prop->GetName()), prop);
                }
            }
        }
        auto prop = item->Find(pname);
        if (prop != nullptr)
            return *prop;
        return nullptr;
    }

    NewObjectRecorder::NewObjectRecorder(lua_State* inL)
        : luaState(LuaState::get(inL->l_G->mainthread))
    {
        stackLayer = luaState->increaseCallStack();
    }

    NewObjectRecorder::~NewObjectRecorder()
    {
        luaState->decreaseCallStack();
    }

    bool NewObjectRecorder::hasObject(const UObject* obj) const
    {
        return luaState->hasObjectInStack(obj, stackLayer);
    }

    void LuaState::InitExtLib(lua_State* ls)
    {
        AutoStack as(ls);

        lua_getglobal(ls, "package");
        lua_getfield(ls, -1, "preload");

        static const luaL_Reg s_lib_preload[] = {
            { "socket.core", luaopen_socket_core },
            { NULL, NULL }
        };

        const luaL_Reg* lib;
        for (lib = s_lib_preload; lib->func; lib++) {
            lua_pushcfunction(ls, lib->func);
            lua_setfield(ls, -2, lib->name);
        }
        lua_pop(ls, 2);
    }
}
