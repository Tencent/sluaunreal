// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#pragma once
#define LUA_LIB
#include "SluaMicro.h"
#include "LuaVar.h"
#include <string>
#include <memory>
#include <atomic>

#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
#include "UObject/WeakFieldPtr.h"
#endif
#include "HAL/Runnable.h"
#include "Tickable.h"

#define SLUA_LUACODE "[sluacode]"
#define SLUA_CPPINST "__cppinst"

class ULatentDelegate;

namespace NS_SLUA {
    DECLARE_MULTICAST_DELEGATE_OneParam(FLuaStateInitEvent, lua_State*);

    struct ScriptTimeoutEvent {
        virtual void onTimeout() = 0;
    };

    class FDeadLoopCheck : public FRunnable
    {
    public:
        FDeadLoopCheck();
        ~FDeadLoopCheck();

        static int32 NameCounter;

        int scriptEnter(ScriptTimeoutEvent* pEvent);
        int scriptLeave();

    protected:
        uint32 Run() override;
        void Stop() final;
        void onScriptTimeout();
    private:
        std::atomic<ScriptTimeoutEvent*> timeoutEvent;
        FThreadSafeCounter timeoutCounter;
        FThreadSafeCounter stopCounter;
        FThreadSafeCounter frameCounter;
        FRunnableThread* thread;
    };

    // check lua script dead loop
    class LuaScriptCallGuard : public ScriptTimeoutEvent {
    public:
        LuaScriptCallGuard(lua_State* L);
        virtual ~LuaScriptCallGuard();
        void onTimeout() override;
    private:
        lua_State* L;
        static void scriptTimeout(lua_State *L, lua_Debug *ar);
    };

    typedef TSet<UObjectBase*> ObjectSet;

    class NewObjectRecorder {
    public:
        NewObjectRecorder(lua_State* L);

        ~NewObjectRecorder();

        bool hasObject(const UObject* obj) const;

    protected:
        class LuaState* luaState;

        int stackLayer;
    };

    typedef TMap<UObject*, GenericUserData*> UObjectRefMap;

    class SLUA_UNREAL_API LuaState 
        : public FUObjectArray::FUObjectDeleteListener
        , public FUObjectArray::FUObjectCreateListener
        , public FGCObject
        , public FTickableGameObject
    {
    public:
        LuaState(const char* name=nullptr,UGameInstance* pGI=nullptr);
        virtual ~LuaState();

        /*
         * fn, lua file to load, fn may be a short filename
         * if find fn to load, return file size to len and file full path fo filepath arguments.
         */
        typedef TArray<uint8> (*LoadFileDelegate) (const char* fn, FString& filepath);
        DECLARE_MULTICAST_DELEGATE_OneParam(ErrorDelegate, const char*);

        inline static LuaState* get(lua_State* l=nullptr) {
            // if L is nullptr, return main state
            if(!l) return mainState;
            return (LuaState*)*((void**)lua_getextraspace(l));
        }
        // get LuaState from state index
        static LuaState* get(int index);
        // get LuaState from UGameInstance, you should create LuaState with an UGameInstance pointer at first
        // if multi LuaState have same UGameInstance, we will return first one
        static LuaState* get(UGameInstance* pGI);

        // get LuaState from name
        static LuaState* get(const FString& name);

        static UGameInstance* getObjectGameInstance(const UObject* obj);

        UGameInstance* getGameInstance() const {
            return gameInstance.Get();
        }

        // return specified index is valid state index
        inline static bool isValid(int index)  {
            return get(index)!=nullptr;
        }
        
        // return state index
        int stateIndex() const { return si; }
        
        // init lua state
        virtual bool init();

        // attach this luaState to UGameInstance
        // this function just store UGameInstance pointer for search future
        void attach(UGameInstance* pGI);

        void registLuaTick(UObject* obj, float tickInterval);
        void unRegistLuaTick(const UObject* obj);
        FORCEINLINE void callLuaTick(UObject* obj, NS_SLUA::LuaVar& tickFunc, float dtime);
        // tick function
        virtual void Tick(float dtime);
        virtual TStatId GetStatId() const;
#if (ENGINE_MINOR_VERSION<=18) && (ENGINE_MAJOR_VERSION==4)
		virtual bool IsTickable() const override { return true; }
#endif
        void tickGC(float dtime);
        void tickLuaActors(float dtime);

        // close lua state
        void close();

        // execute lua string
        LuaVar doString(const char* str, LuaVar* pEnv = nullptr);
        // execute bytes buffer and named buffer to chunk
        LuaVar doBuffer(const uint8* buf,uint32 len, const char* chunk, LuaVar* pEnv = nullptr);
        // load file and execute it
        // file how to loading depend on load delegation
        // see setLoadFileDelegate function
        LuaVar doFile(const char* fn, LuaVar* pEnv = nullptr);
        // require a module
        LuaVar requireModule(const char* fn, LuaVar* pEnv = nullptr);

       
        // call function that specified by key
        // any supported c++ value can be passed as argument to lua 
        template<typename ...ARGS>
        LuaVar call(const char* key,ARGS&& ...args) {
            LuaVar f = get(key);
            return f.call(std::forward<ARGS>(args)...);
        }

        // get field from _G, support "x.x.x.x" to search children field
        LuaVar get(const char* key);
        // set field to _G, support "x.x.x.x" to create sub table recursive
        bool set(const char* key, LuaVar v);

        // set load delegation function to load lua code
        void setLoadFileDelegate(LoadFileDelegate func);
        // get error delegation function to handle error
        ErrorDelegate* getErrorDelegate();

        lua_State* getLuaState() const
        {
            return L;
        }
        operator lua_State*() const
        {
            return L;
        }

        // create a empty table
        LuaVar createTable();
        // create named table, support "x.x.x.x", put table to _G
        LuaVar createTable(const char* key);

        const UObjectRefMap& cacheSet() const {
            return objRefs;
        }

        void setGCParam(double limitSeconds, int limitCount, double interval);
        void setTickFunction(LuaVar func);

        // add obj to ref, tell Engine don't collect this obj
        void addRef(UObject* obj,void* ud,bool ref);
        // unlink UObject, flag Object had been free, and remove from cache and objRefs
        void unlinkUObject(const UObject * Object,void* userdata=nullptr);

#if !((ENGINE_MINOR_VERSION<23) && (ENGINE_MAJOR_VERSION==4))
        void OnUObjectArrayShutdown() override;
#endif

        // if obj be deleted, call this function
        virtual void NotifyUObjectDeleted(const class UObjectBase *Object, int32 Index) override;

        // if obj created, call this function
        virtual void NotifyUObjectCreated(const class UObjectBase *Object, int32 Index) override;

        // tell Engine which objs should be referenced
        virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
        virtual FString GetReferencerName() const override
        {
            return "LuaState";
        }
#endif

        static int pushErrorHandler(lua_State* L);

        int addThread(lua_State *thread);
        void resumeThread(int threadRef);
        int findThread(lua_State *thread);
        void cleanupThreads();
        ULatentDelegate* getLatentDelegate() const;

        // call this function on script error
        void onError(const char* err);
        
        static bool hookObject(LuaState* inState, const class UObjectBaseUtility* obj, bool bHookImmediate = true, bool bPostHook = false);

#if UE_BUILD_DEVELOPMENT
        void addRefTraceback(int ref);

        void removeRefTraceback(int ref);

        FString getRefTraceback(int ref);

        bool isRefTraceEnable() const;
        void setRefTraceEnable(bool enable);
#endif

    protected:
        LoadFileDelegate loadFileDelegate;
        ErrorDelegate errorDelegate;
        TArray<uint8> loadFile(const char* fn,FString& filepath);
        static int loader(lua_State* L);
        static int import(lua_State *L);
        static int getStringFromMD5(lua_State* L);

    public:
        static FLuaStateInitEvent onInitEvent;
    protected:
        friend class NewObjectRecorder;

        int increaseCallStack();
        void decreaseCallStack();
        bool hasObjectInStack(const UObject* obj, int stackLayer);

    private:
        friend class LuaObject;
        friend class SluaUtil;
        friend struct LuaEnums;
        friend class LuaScriptCallGuard;
        lua_State* L;
        int cacheObjRef;
        int cacheEnumRef;
        int cacheClassPropRef;
        int cacheClassFuncRef;
        // init enums lua code
        LuaVar initInnerCode(const char* s);
        int _pushErrorHandler(lua_State* L);
        static int _atPanic(lua_State* L);
        void addLink(void* address);
        void releaseLink(void* address);
        void releaseAllLink();
        void linkProp(void* parentAddress, void* prop);
        void unlinkProp(void* prop);
        // unreal gc will call this funciton
        void onEngineGC();
        // on world cleanup
        void onWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);

        TMap<void*, TArray<void*>> propLinks;
        int si;
        FString stateName;

        // cache ufunction/uproperty ptr if index by lua
        struct ClassCache {
            typedef TMap<SimpleString, FProperty*> CachePropItem;
            typedef TMap<UStruct*, CachePropItem> CachePropMap;
            
            FProperty* findProp(UStruct* ustruct, const char* pname);
            void clear() {
                cachePropMap.Empty();
            }

            CachePropMap cachePropMap;
        } classMap;

        enum ImportedType {
            ImportedClass,
            ImportedStruct,
            ImportedEnum,
        };
        struct ImportedObjectCache {
            TWeakObjectPtr<UObject> cacheObjectPtr;
            ImportedType importedType;
        };

        typedef TMap<FString, ImportedObjectCache> CacheImportedMap;
        CacheImportedMap cacheImportedMap;

        FDeadLoopCheck* deadLoopCheck;

        // hold UObjects pushed to lua
        UObjectRefMap objRefs;
        
        // store UGameInstance ptr to search LuaState
        // we don't hold referrence
        TWeakObjectPtr<UGameInstance> gameInstance;

        FDelegateHandle pgcHandler;
        FDelegateHandle wcHandler;
        class LuaOverrider* overrider;

        double stepGCTimeLimit;
        int stepGCCountLimit;
        double fullGCInterval;
        double lastFullGCSeconds;
        
        LuaVar stateTickFunc;

        static LuaState* mainState;

#if WITH_EDITOR
        // used for debug
        TMap<FString, FString> debugStringMap;
#endif

        TMap<lua_State*, int> threadToRef;                                // coroutine -> ref
        TMap<int, lua_State*> refToThread;                                // coroutine -> ref
        ULatentDelegate* latentDelegate;
        
        int currentCallStack;
        TArray<ObjectSet> newObjectsInCallStack;

        TArray<struct LuaStruct*> deferGCStruct;

#if UE_BUILD_DEVELOPMENT
        bool bRefTraceEnable;
        TMap<int, FString> refTraceback;
#endif

        void InitExtLib(lua_State* ls);

        struct LuaTickInfo {
            TWeakObjectPtr<UObject> obj;
            double interval;
            double expire;
            double preExecuteTime;
            NS_SLUA::LuaVar tickFunc;
            bool bRemoved;
            LuaTickInfo(UObject* object, float tickInterval, double expireTime, double preExeTime)
                :obj(object), interval(tickInterval), expire(expireTime), preExecuteTime(preExeTime), bRemoved(false) {}
        };
        double tickInternalTime = 0;
        TArray<LuaTickInfo> tickActors;
    };
}