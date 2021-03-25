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
#include "LuaObject.h"
#include "SluaLib.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Blueprint/UserWidget.h"
#include "Misc/AssertionMacros.h"
#include "Misc/SecureHash.h"
#include "Log.h"
#include "lua/lua.hpp"
#include <map>
#include "LuaWrapper.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaSet.h"
#include "LuaSocketWrap.h"
#include "LuaMemoryProfile.h"
#include "HAL/RunnableThread.h"
#include "GameDelegates.h"
#include "LatentDelegate.h"
#include "LuaActor.h"
#include "LuaProfiler.h"
#include "Stats/Stats.h"

namespace NS_SLUA {

	const int MaxLuaExecTime = 5; // in second

    int import(lua_State *L) {
        const char* name = LuaObject::checkValue<const char*>(L,1);
        if(name) {
            UClass* uclass = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name));
            if(uclass) return LuaObject::pushClass(L,uclass);
            
			UScriptStruct* ustruct = FindObject<UScriptStruct>(ANY_PACKAGE, UTF8_TO_TCHAR(name));
            if(ustruct) return LuaObject::pushStruct(L,ustruct);

			UEnum* uenum = FindObject<UEnum>(ANY_PACKAGE, UTF8_TO_TCHAR(name));
			if (uenum) return LuaObject::pushEnum(L, uenum);
            
            luaL_error(L,"Can't find class named %s",name);
        }
        return 0;
    }
    
    int print(lua_State *L) {
        FString str;
        int top = lua_gettop(L);
        for(int n=1;n<=top;n++) {
            size_t len;
            const char* s = luaL_tolstring(L, n, &len);
            str+="\t";
            if(s) str+=UTF8_TO_TCHAR(s);
        }
        Log::Log("%s",TCHAR_TO_UTF8(*str));
        return 0;
    }

	int dofile(lua_State *L) {
		auto fn = luaL_checkstring(L, 1);
		auto ls = LuaState::get(L);
		ensure(ls);
		auto var = ls->doFile(fn);
		if (var.isValid()) {
			return var.push(L);
		}
		return 0;
	}

    int error(lua_State* L) {
        const char* err = lua_tostring(L,1);
        luaL_traceback(L,L,err,1);
        err = lua_tostring(L,2);
        lua_pop(L,1);
		auto ls = LuaState::get(L);
		ls->onError(err);
        return 0;
    }

	void LuaState::onError(const char* err) {
		if (errorDelegate) errorDelegate(err);
		else Log::Error("%s", err);
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

    LuaState* LuaState::mainState = nullptr;
    TMap<int,LuaState*> stateMapFromIndex;
    static int StateIndex = 0;

	LuaState::LuaState(const char* name, UGameInstance* gameInstance)
		: loadFileDelegate(nullptr)
		, errorDelegate(nullptr)
		, L(nullptr)
		, cacheObjRef(LUA_NOREF)
		, cacheFuncRef(LUA_NOREF)
		, stackCount(0)
		, si(0)
		, deadLoopCheck(nullptr)
		, latentDelegate(nullptr)
		, currentCallStack(0)
    {
        if(name) stateName=UTF8_TO_TCHAR(name);
		this->pGI = gameInstance;
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
			if (state->pGI && state->pGI == pGI)
				return state;
		}
		return nullptr;
	}

    // check lua top , this function can omit
    void LuaState::Tick(float dtime) {
		ensure(IsInGameThread());
		if (!L) return;

		int top = lua_gettop(L);
		if (top != stackCount) {
			stackCount = top;
			Log::Error("Error: lua stack count should be zero , now is %d, top is %s", top, luaL_typename(L,-1));
		}

#ifdef ENABLE_PROFILER
		LuaProfiler::tick(this);
#endif

		PROFILER_WATCHER(w1);
		if (stateTickFunc.isFunction())
		{
			PROFILER_WATCHER_X(w2,"TickFunc");
			stateTickFunc.call(dtime);
		}

		// try lua gc
		PROFILER_WATCHER_X(w3, "LuaGC");
		if (!enableMultiThreadGC) lua_gc(L, LUA_GCSTEP, 128);
    }

    void LuaState::close() {
        if(mainState==this) mainState = nullptr;

		latentDelegate = nullptr;

		freeDeferObject();

		releaseAllLink();

		cleanupThreads();
        
        if(L) {
 #ifdef ENABLE_PROFILER
 			LuaProfiler::clean(this);
 #endif
            lua_close(L);
			GUObjectArray.RemoveUObjectCreateListener(this);
			GUObjectArray.RemoveUObjectDeleteListener(this);
			FCoreUObjectDelegates::GetPostGarbageCollect().Remove(pgcHandler);
			FWorldDelegates::OnWorldCleanup.Remove(wcHandler);
            stateMapFromIndex.Remove(si);
            L=nullptr;
        }
		freeDeferObject();
		objRefs.Empty();
		SafeDelete(deadLoopCheck);

		LuaMemoryProfile::stop();
    }


    bool LuaState::init(bool gcFlag) {

        if(deadLoopCheck)
            return false;

        if(!mainState) 
            mainState = this;

		enableMultiThreadGC = gcFlag;
		pgcHandler = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(this, &LuaState::onEngineGC);
		wcHandler = FWorldDelegates::OnWorldCleanup.AddRaw(this, &LuaState::onWorldCleanup);
		GUObjectArray.AddUObjectDeleteListener(this);
		GUObjectArray.AddUObjectCreateListener(this);

		latentDelegate = NewObject<ULatentDelegate>((UObject*)GetTransientPackage(), ULatentDelegate::StaticClass());
		latentDelegate->bindLuaState(this);

        stackCount = 0;
        si = ++StateIndex;

		propLinks.Empty();
		classMap.clear();
		objRefs.Empty();

#if WITH_EDITOR
		// used for debug
		debugStringMap.Empty();
#endif

		deadLoopCheck = new FDeadLoopCheck();

        // use custom memory alloc func to profile memory footprint
        L = lua_newstate(LuaMemoryProfile::alloc,this);
        lua_atpanic(L,_atPanic);
        // bind this to L
        *((void**)lua_getextraspace(L)) = this;
        stateMapFromIndex.Add(si,this);

        // init obj cache table
        lua_newtable(L);
        lua_newtable(L);
        lua_pushstring(L,"kv");
        lua_setfield(L,-2,"__mode");
        lua_setmetatable(L,-2);
        // register it
        cacheObjRef = luaL_ref(L,LUA_REGISTRYINDEX);

		// init func cache table
		lua_newtable(L);
		lua_newtable(L);
		lua_pushstring(L, "kv");
		lua_setfield(L, -2, "__mode");
		lua_setmetatable(L, -2);
		// register it
		cacheFuncRef = luaL_ref(L, LUA_REGISTRYINDEX);

        ensure(lua_gettop(L)==0);
        
        luaL_openlibs(L);
        
        lua_pushcfunction(L,import);
        lua_setglobal(L, "import");
        
        lua_pushcfunction(L,print);
        lua_setglobal(L, "print");

		lua_pushcfunction(L, dofile);
		lua_setglobal(L, "dofile");

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
        
		LuaSocket::init(L);
        LuaObject::init(L);
        SluaUtil::openLib(L);
        LuaClass::reg(L);
        LuaArray::reg(L);
        LuaMap::reg(L);
        LuaSet::reg(L);
#ifdef ENABLE_PROFILER
		LuaProfiler::init(this);
#endif
		
		onInitEvent.Broadcast();

		// disable gc in main thread
		if (enableMultiThreadGC) lua_gc(L, LUA_GCSTOP, 0);

        lua_settop(L,0);

        return true;
    }

	void LuaState::attach(UGameInstance* GI) {
		this->pGI = GI;
	}

    int LuaState::_atPanic(lua_State* L) {
        const char* err = lua_tostring(L,-1);
        Log::Error("Fatal error: %s",err);
        return 0;
    }

	void LuaState::setLoadFileDelegate(LoadFileDelegate func) {
		loadFileDelegate = func;
	}

	void LuaState::setErrorDelegate(ErrorDelegate func) {
		errorDelegate = func;
	}

	static void* findParent(GenericUserData* parent) {
		auto pp = parent;
		while(true) {
			if (!pp->parent)
				break;
			pp = reinterpret_cast<GenericUserData*>(pp->parent);
		}
		return pp;
	}

	void LuaState::linkProp(void* parent, void* prop) {
		auto parentud = findParent(reinterpret_cast<GenericUserData*>(parent));
		auto propud = reinterpret_cast<GenericUserData*>(prop);
		propud->parent = parentud;
		auto& propList = propLinks.FindOrAdd(parentud);
		propList.Add(propud);
	}

	void LuaState::releaseLink(void* prop) {
		auto propud = reinterpret_cast<GenericUserData*>(prop);
		if (propud->flag & UD_AUTOGC) {
			auto propListPtr = propLinks.Find(propud);
			if (propListPtr) 
				for (auto& cprop : *propListPtr) 
					reinterpret_cast<GenericUserData*>(cprop)->flag |= UD_HADFREE;
		} else {
			propud->flag |= UD_HADFREE;
			auto propListPtr = propLinks.Find(propud->parent);
			if (propListPtr) 
				propListPtr->Remove(propud);
		}
	}

	void LuaState::releaseAllLink() {
		for (auto& pair : propLinks) 
			for (auto& prop : pair.Value) 
				reinterpret_cast<GenericUserData*>(prop)->flag |= UD_HADFREE;
		propLinks.Empty();
	}

	// engine will call this function on post gc
	void LuaState::onEngineGC()
	{
		PROFILER_WATCHER(w1);
		// find freed uclass
		for (ClassCache::CacheFuncMap::TIterator it(classMap.cacheFuncMap); it; ++it)
			if (!it.Key().IsValid())
				it.RemoveCurrent();
		
		for (ClassCache::CachePropMap::TIterator it(classMap.cachePropMap); it; ++it)
			if (!it.Key().IsValid())
				it.RemoveCurrent();		
		
		freeDeferObject();

		Log::Log("Unreal engine GC, lua used %d KB",lua_gc(L, LUA_GCCOUNT, 0));
	}

	void LuaState::onWorldCleanup(UWorld * World, bool bSessionEnded, bool bCleanupResources)
	{
		PROFILER_WATCHER(w1);
		unlinkUObject(World);
	}

	void LuaState::freeDeferObject()
	{
		// really delete FGCObject
		for (auto ptr : deferDelete)
			delete ptr;
		deferDelete.Empty();
	}

	LuaVar LuaState::doBuffer(const uint8* buf, uint32 len, const char* chunk, LuaVar* pEnv) {
        AutoStack g(L);
        int errfunc = pushErrorHandler(L);

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

	void LuaState::NotifyUObjectDeleted(const UObjectBase * Object, int32 Index)
	{
		PROFILER_WATCHER(w1);
		unlinkUObject((const UObject*)Object);
		LuaObject::removeFuncCache(L, (UFunction*)Object);

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
		objRefs.Remove(const_cast<UObject*>(Object));

		if (!ud || ud->flag & UD_HADFREE)
			return;

		// indicate ud had be free
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
		// do more gc step in collecting thread
		// lua_gc can be call async in bg thread in some isolate position
		// but this position equivalent to main thread
		// we just try and find some proper async position
		if (enableMultiThreadGC && L) lua_gc(L, LUA_GCSTEP, 128);
	}
#if (ENGINE_MINOR_VERSION>=23) && (ENGINE_MAJOR_VERSION>=4)
	void LuaState::OnUObjectArrayShutdown() {
		// nothing todo, we don't add any listener to FUObjectDeleteListener
	}
#endif

	int LuaState::pushErrorHandler(lua_State* L) {
        auto ls = get(L);
        ensure(ls!=nullptr);
        return ls->_pushErrorHandler(L);
    }
	
	TStatId LuaState::GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(LuaState, STATGROUP_Game);
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
				int status = lua_resume(thread, L, 0);
				if (status == LUA_OK || status == LUA_YIELD)
				{
					int nres = lua_gettop(thread);
					if (!lua_checkstack(L, nres + 1))
					{
						lua_pop(thread, nres);  /* remove results anyway */
						Log::Error("too many results to resume");
						threadIsDead = true;
					}
					else
					{
						lua_xmove(thread, L, nres);  /* move yielded values */

						if (status == LUA_OK)
						{
							threadIsDead = true;
						}
					}
				}
				else
				{
					lua_xmove(thread, L, 1);  /* move error message */
					const char* err = lua_tostring(L, -1);
					luaL_traceback(L, thread, err, 0);
					err = lua_tostring(L, -1);
					Log::Error("%s", err);
					lua_pop(L, 1);

					threadIsDead = true;
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
			lua_State *thread = It.Key();
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

	FDeadLoopCheck::FDeadLoopCheck()
		: timeoutEvent(nullptr)
		, timeoutCounter(0)
		, stopCounter(0)
		, frameCounter(0)
	{
		thread = FRunnableThread::Create(this, TEXT("FLuaDeadLoopCheck"), 0, TPri_BelowNormal);
	}

	FDeadLoopCheck::~FDeadLoopCheck()
	{
		Stop();
		if (thread != nullptr)
		{
			thread->WaitForCompletion();
		}
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
		ls->deadLoopCheck->scriptEnter(this);
	}

	LuaScriptCallGuard::~LuaScriptCallGuard()
	{
		auto ls = LuaState::get(L);
		ls->deadLoopCheck->scriptLeave();
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

	UFunction* LuaState::ClassCache::findFunc(UClass* uclass, const char* fname)
	{
		auto item = cacheFuncMap.Find(uclass);
		if (!item) return nullptr;
		auto func = item->Find(UTF8_TO_TCHAR(fname));
		if(func!=nullptr)
			return func->IsValid() ? func->Get() : nullptr;
		return nullptr;
	}

	FProperty* LuaState::ClassCache::findProp(UClass* uclass, const char* pname)
	{
		auto item = cachePropMap.Find(uclass);
		if (!item) return nullptr;
		auto prop = item->Find(UTF8_TO_TCHAR(pname));
		if (prop != nullptr)
			return prop->IsValid() ? prop->Get() : nullptr;
		return nullptr;
	}

	void LuaState::ClassCache::cacheFunc(UClass* uclass, const char* fname, UFunction* func)
	{
		auto& item = cacheFuncMap.FindOrAdd(uclass);
		item.Add(UTF8_TO_TCHAR(fname), func);
	}

	void LuaState::ClassCache::cacheProp(UClass* uclass, const char* pname, FProperty* prop)
	{
		auto& item = cachePropMap.FindOrAdd(uclass);
		item.Add(UTF8_TO_TCHAR(pname), prop);
	}

	NewObjectRecorder::NewObjectRecorder(lua_State* L_)
		: luaState(LuaState::get(G(L_)->mainthread))
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
}
