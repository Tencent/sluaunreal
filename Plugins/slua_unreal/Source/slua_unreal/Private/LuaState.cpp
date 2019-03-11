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
#include "LuaEnums.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaSocketWrap.h"
#include "LuaMemoryProfile.h"
#include "HAL/RunnableThread.h"
#include "GameDelegates.h"
#include "LuaActor.h"

namespace slua {

	const int MaxLuaExecTime = 5; // in second

    int import(lua_State *L) {
        const char* name = LuaObject::checkValue<const char*>(L,1);
        if(name) {
            UClass* uclass = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name));
            if(uclass) {
                LuaObject::pushClass(L,uclass);
                return 1;
            }
            UScriptStruct* ustruct = FindObject<UScriptStruct>(ANY_PACKAGE, UTF8_TO_TCHAR(name));
            if(ustruct) {
                LuaObject::pushStruct(L,ustruct);
                return 1;
            }
            
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

    int error(lua_State* L) {
        const char* err = lua_tostring(L,1);
        luaL_traceback(L,L,err,1);
        err = lua_tostring(L,2);
        Log::Error("%s",err);
        lua_pop(L,1);
        return 0;
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

    int LuaState::loader(lua_State* L) {
        LuaState* state = LuaState::get(L);
        const char* fn = lua_tostring(L,1);
        uint32 len;
        FString filepath;
        if(uint8* buf = state->loadFile(fn,len,filepath)) {
            AutoDeleteArray<uint8> defer(buf);

            char chunk[256];
            snprintf(chunk,256,"@%s",TCHAR_TO_UTF8(*filepath));
            if(luaL_loadbuffer(L,(const char*)buf,len,chunk)==0) {
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
    
    uint8* LuaState::loadFile(const char* fn,uint32& len,FString& filepath) {
        if(loadFileDelegate) return loadFileDelegate(fn,len,filepath);
        return nullptr;
    }

    LuaState* LuaState::mainState = nullptr;
    TMap<int,LuaState*> stateMapFromIndex;
    static int StateIndex = 0;

	LuaState::LuaState(const char* name)
		:loadFileDelegate(nullptr)
		, L(nullptr)
		, cacheObjRef(LUA_NOREF)
		, stackCount(0)
		, si(0)
		, deadLoopCheck(nullptr)
    {
        if(name) stateName=UTF8_TO_TCHAR(name);
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

    // check lua top , this function can omit
    void LuaState::tick(float dtime) {
        int top = lua_gettop(L);
        if(top!=stackCount) {
            stackCount = top;
            Log::Error("Error: lua stack count should be zero , now is %d",top);
        }
    }

    void LuaState::close() {
        if(mainState==this) mainState = nullptr;

		releaseAllLink();
        
        if(L) {
            lua_close(L);
			GUObjectArray.RemoveUObjectDeleteListener(this);
			FCoreUObjectDelegates::GetPostGarbageCollect().Remove(pgcHandler);
            stateMapFromIndex.Remove(si);
            L=nullptr;
        }

		objRefs.Empty();
		SafeDelete(deadLoopCheck);
    }


    bool LuaState::init() {

        if(deadLoopCheck)
            return false;

        if(!mainState) 
            mainState = this;

		pgcHandler = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(this, &LuaState::onEngineGC);
		GUObjectArray.AddUObjectDeleteListener(this);
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

        ensure(lua_gettop(L)==0);
        
        luaL_openlibs(L);
        
        lua_pushcfunction(L,import);
        lua_setglobal(L, "import");
        
        lua_pushcfunction(L,print);
        lua_setglobal(L, "print");

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

        lua_settop(L,0);

        return true;
    }

    int LuaState::_atPanic(lua_State* L) {
        const char* err = lua_tostring(L,-1);
        Log::Error("Fatal error: %s",err);
        return 0;
    }

	void LuaState::setLoadFileDelegate(LoadFileDelegate func) {
		loadFileDelegate = func;
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
		// find freed uclass
		for(ClassFunctionCache::CacheMap::TIterator it(classMap.cacheMap);it;++it)
			if (!it.Key().IsValid()) 
				classMap.cacheMap.Remove(it.Key());
	}

    LuaVar LuaState::doBuffer(const uint8* buf,uint32 len, const char* chunk, LuaVar* pEnv) {
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
        uint32 len;
        FString filepath;
        if(uint8* buf=loadFile(fn,len,filepath)) {
            char chunk[256];
            snprintf(chunk,256,"@%s",TCHAR_TO_UTF8(*filepath));

            LuaVar r = doBuffer( buf,len,chunk,pEnv );
            delete[] buf;
            return r;
        }
        return LuaVar();
    }

	void LuaState::NotifyUObjectDeleted(const UObjectBase * Object, int32 Index)
	{
		// pop ud to stack
		if (!LuaObject::getFromCache(L, const_cast<UObjectBase *>(Object), nullptr, false))
			return;

		GenericUserData* ud = (GenericUserData*)lua_touserdata(L, -1);
		// pop ud
		lua_pop(L, 1);
		// this cached ud is weak ref
		// maybe gc by lua, so check flag
		if (ud->flag & UD_HADFREE)
			return;

		// indicate ud had be free
		ud->flag |= UD_HADFREE;
		// remove ref, Object must be an UObject in slua
		removeRef((uint32)Index);
		// remove cache
		LuaObject::removeFromCache(L, ud);
	}

	void LuaState::AddReferencedObjects(FReferenceCollector & Collector)
	{
		Collector.AddReferencedObjects(objRefs);
	}

	int LuaState::pushErrorHandler(lua_State* L) {
        auto ls = get(L);
        ensure(ls!=nullptr);
        return ls->_pushErrorHandler(L);
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

	void LuaState::addRef(UObject* obj)
	{
		objRefs.Add(obj->GetUniqueID(), obj);
	}

	void LuaState::removeRef(UObject* obj)
	{
		objRefs.Remove(obj->GetUniqueID());
	}

	void LuaState::removeRef(uint32 id)
	{
		objRefs.Remove(id);
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

	void FDeadLoopCheck::scriptEnter(ScriptTimeoutEvent* pEvent)
	{
		if (frameCounter.Increment() == 1) {
			timeoutCounter.Set(0);
			timeoutEvent = pEvent;
		}
	}

	void FDeadLoopCheck::scriptLeave()
	{
		frameCounter.Decrement();
	}

	void FDeadLoopCheck::onScriptTimeout()
	{
		if (timeoutEvent) timeoutEvent->onTimeout();
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

	UFunction* LuaState::ClassFunctionCache::find(UClass* uclass, const char* fname)
	{
		auto item = cacheMap.Find(uclass);
		if (!item) return nullptr;
		auto func = item->Find(UTF8_TO_TCHAR(fname));
		if(func!=nullptr)
			return func->IsValid() ? func->Get() : nullptr;
		return nullptr;
	}

	void LuaState::ClassFunctionCache::cache(UClass* uclass, const char* fname, UFunction* func)
	{
		auto& item = cacheMap.FindOrAdd(uclass);
		item.Add(UTF8_TO_TCHAR(fname), func);
	}
}
