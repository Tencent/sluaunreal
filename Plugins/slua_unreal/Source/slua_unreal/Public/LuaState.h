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
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LuaVar.h"
#include <string>
#include <memory>
#include <atomic>
#include "HAL/Runnable.h"
#include "Tickable.h"
#include "UObject/WeakFieldPtr.h"

#define SLUA_LUACODE "[sluacode]"
#define SLUA_CPPINST "__cppinst"

DECLARE_MULTICAST_DELEGATE(FLuaStateInitEvent);

class ULatentDelegate;

namespace NS_SLUA {

	struct ScriptTimeoutEvent {
		virtual void onTimeout() = 0;
	};

	class FDeadLoopCheck : public FRunnable
	{
	public:
		FDeadLoopCheck();
		~FDeadLoopCheck();

		int scriptEnter(ScriptTimeoutEvent* pEvent);
		int scriptLeave();

	protected:
		uint32 Run() override;
		void Stop() override;
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
         * if find fn to load, return file size to len and file full path fo filepath arguments
         * if find fn and load successful, return buf of file content, otherwise return nullptr
         * you must delete[] buf returned by function for free memory.
         */
        typedef TArray<uint8> (*LoadFileDelegate) (const char* fn, FString& filepath);
		typedef void (*ErrorDelegate) (const char* err);

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

        // return specified index is valid state index
        inline static bool isValid(int index)  {
            return get(index)!=nullptr;
        }
        
        // return state index
        int stateIndex() const { return si; }
        
        // init lua state
        virtual bool init(bool enableMultiThreadGC=false);
		// attach this luaState to UGameInstance
		// this function just store UGameInstance pointer for search future
		void attach(UGameInstance* pGI);
        
        // close lua state
        virtual void close();

        // execute lua string
        LuaVar doString(const char* str, LuaVar* pEnv = nullptr);
        // execute bytes buffer and named buffer to chunk
        LuaVar doBuffer(const uint8* buf,uint32 len, const char* chunk, LuaVar* pEnv = nullptr);
        // load file and execute it
        // file how to loading depend on load delegation
        // see setLoadFileDelegate function
        LuaVar doFile(const char* fn, LuaVar* pEnv = nullptr);

       
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
		// set error delegation function to handle error
		void setErrorDelegate(ErrorDelegate func);

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
        
		void setTickFunction(LuaVar func);

		// add obj to ref, tell Engine don't collect this obj
		void addRef(UObject* obj,void* ud,bool ref);
		// unlink UObject, flag Object had been free, and remove from cache and objRefs
		void unlinkUObject(const UObject * Object,void* userdata=nullptr);

		// if obj be deleted, call this function
		virtual void NotifyUObjectDeleted(const class UObjectBase *Object, int32 Index) override;

		// if obj created, call this function
		virtual void NotifyUObjectCreated(const class UObjectBase *Object, int32 Index) override;

		// tell Engine which objs should be referenced
		virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
        static int pushErrorHandler(lua_State* L);
#if (ENGINE_MINOR_VERSION>=23) && (ENGINE_MAJOR_VERSION>=4)
		virtual void OnUObjectArrayShutdown() override;
#endif

		// tickable object methods
		virtual void Tick(float DeltaTime) override;
		virtual TStatId GetStatId() const override;
#if !((ENGINE_MINOR_VERSION>18) && (ENGINE_MAJOR_VERSION>=4))
		virtual bool IsTickable() const override { return true; }
#endif

		int addThread(lua_State *thread);
		void resumeThread(int threadRef);
		int findThread(lua_State *thread);
		void cleanupThreads();
		ULatentDelegate* getLatentDelegate() const;

		// call this function on script error
		void onError(const char* err);
    protected:
		LoadFileDelegate loadFileDelegate;
		ErrorDelegate errorDelegate;
        TArray<uint8> loadFile(const char* fn,FString& filepath);
		static int loader(lua_State* L);
		static int getStringFromMD5(lua_State* L);

	public:
		FLuaStateInitEvent onInitEvent;
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
		int cacheFuncRef;
		// init enums lua code
        int _pushErrorHandler(lua_State* L);
        static int _atPanic(lua_State* L);
		void linkProp(void* parent, void* prop);
		void releaseLink(void* prop);
		void releaseAllLink();
		// unreal gc will call this funciton
		void onEngineGC();
		// on world cleanup
		void onWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
		void freeDeferObject();


		TMap<void*, TArray<void*>> propLinks;
        int stackCount;
        int si;
        FString stateName;

		// cache ufunction/uproperty ptr if index by lua
		struct ClassCache {
			typedef TMap<FString, TWeakObjectPtr<UFunction>> CacheFuncItem;
			typedef TMap<TWeakObjectPtr<UClass>, CacheFuncItem> CacheFuncMap;

			typedef TMap<FString, TWeakFieldPtr<FProperty>> CachePropItem;
			typedef TMap<TWeakObjectPtr<UClass>, CachePropItem> CachePropMap;
			
			UFunction* findFunc(UClass* uclass, const char* fname);
			FProperty* findProp(UClass* uclass, const char* pname);
			void cacheFunc(UClass* uclass, const char* fname, UFunction* func);
			void cacheProp(UClass* uclass, const char* pname, FProperty* prop);
			void clear() {
				cacheFuncMap.Empty();
				cachePropMap.Empty();
			}

			CacheFuncMap cacheFuncMap;
			CachePropMap cachePropMap;
		} classMap;

		FDeadLoopCheck* deadLoopCheck;

		// hold UObjects pushed to lua
		UObjectRefMap objRefs;
		// hold FGcObject to defer delete
		TArray<FGCObject*> deferDelete;
		// store UGameInstance ptr to search LuaState
		// we don't hold referrence
		UGameInstance* pGI;


		FDelegateHandle pgcHandler;
		FDelegateHandle wcHandler;

		bool enableMultiThreadGC;
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

    };
}
