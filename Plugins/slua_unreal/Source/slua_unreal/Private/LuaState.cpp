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
#include "LuaCppBinding.h"
#include "LuaArray.h"

namespace slua {

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
            if(s)
                str+=s;
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

    TMap<lua_State*,LuaState*> stateMap;

    LuaState::LuaState()
        :loadFileDelegate(nullptr)
        ,L(nullptr)
        ,cacheObjRef(LUA_NOREF)
        ,root(nullptr)
        ,stackCount(0)
    {
        
    }

    LuaState::~LuaState()
    {
        close();
    }

    lua_State* LuaState::mainThread(lua_State* l) {
        // get main thread
        lua_geti(l,LUA_REGISTRYINDEX,LUA_RIDX_MAINTHREAD);
        lua_State* ml = lua_tothread(l,-1);
        lua_pop(l,1);
        return ml;
    }

    LuaState* LuaState::get(lua_State* L) {
        // if L is nullptr, return main state
        if(!L) return mainState;
        // get main thread
        lua_State* ml = mainThread(L);
        auto it = stateMap.Find(ml);
        if(it) return *it;
        return nullptr;
    }

    bool LuaState::isValid(lua_State* L) {
        if(!L) return false;
        auto it = stateMap.Find(L);
        return it!=nullptr;
    }

    void LuaState::tick(float dtime) {
        int top = lua_gettop(L);
        if(top!=stackCount) {
            stackCount = top;
            Log::Error("Error: lua stack count should be zero , now is %d",top);
        }
    }

    void LuaState::close() {
        if(mainState==this) mainState = nullptr;
        
        if(L) {
            lua_close(L);
            stateMap.Remove(L);
            L=nullptr;
        }

        sluaComponent=nullptr;
        if(root) {
            root->RemoveFromRoot();
            root = nullptr;
        }
    }


    bool LuaState::init(USceneComponent* comp) {

        if(!comp || root)
            return false;

        if(!mainState) 
            mainState = this;

        root = NewObject<ULuaObject>();
		root->AddToRoot();

        sluaComponent = comp;

        L = luaL_newstate();
        stateMap.Add(L,this);

        lua_atpanic(L,_atPanic);

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

        LuaObject::init(L);
        SluaUtil::openLib(L);
        LuaClass::reg(L);
        LuaArray::reg(L);

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

    LuaVar LuaState::doBuffer(const uint8* buf,uint32 len, const char* chunk) {
        AutoStack g(L);
        int errfunc = pushErrorHandler(L);

        if(luaL_loadbuffer(L, (const char *)buf, len, chunk)) {
            const char* err = lua_tostring(L,-1);
            Log::Error("DoBuffer failed: %s",err);
            return LuaVar();
        }
        
        if(!lua_pcall(L, 0, LUA_MULTRET, errfunc)) {
            int n = lua_gettop(L) - errfunc;
            return LuaVar::wrapReturn(L,n);
        }
        return LuaVar();
    }

    LuaVar LuaState::doString(const char* str) {
        #if WITH_EDITOR
        FMD5 md5;
        uint8 digest[17];
        md5.Update((const uint8*)str,strlen(str));
        md5.Final(digest);
        digest[16]=0;

        TArray<FStringFormatArg> Args;
		Args.Add(UTF8_TO_TCHAR(digest));
        FString chunk = FString::Format(TEXT("@codechunk_{0}"),Args);

        // addSourceToDebug(chunk,str);
        return doBuffer((const uint8*)str,strlen(str),TCHAR_TO_UTF8(*chunk));
        #else
        return doBuffer((const uint8*)str,strlen(str),str);
        #endif
    }

    LuaVar LuaState::doFile(const char* fn) {
        uint32 len;
        FString filepath;
        if(uint8* buf=loadFile(fn,len,filepath)) {
            char chunk[256];
            snprintf(chunk,256,"@%s",TCHAR_TO_UTF8(*filepath));

            LuaVar r = doBuffer( buf,len,chunk );
            delete[] buf;
            return r;
        }
        return LuaVar();
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

    // modified FString::Split function to return left if no InS to search
    static bool strSplit(const FString& S,const FString& InS, FString* LeftS, FString* RightS, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase,
		ESearchDir::Type SearchDir = ESearchDir::FromStart)
	{
        if(S.IsEmpty()) return false;

        
		int32 InPos = S.Find(InS, SearchCase, SearchDir);

		if (InPos < 0)	{ 
            *LeftS = S;
            *RightS = "";
            return true; 
        }

		if (LeftS)		{ *LeftS = S.Left(InPos); }
		if (RightS)	{ *RightS = S.Mid(InPos + InS.Len()); }

		return true;
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

}
