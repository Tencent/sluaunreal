// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "SluaLib.h"
#include "LuaObject.h"
#include "LuaState.h"
#include "UObject/UObjectGlobals.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Misc/AssertionMacros.h"
#include "LuaDelegate.h"

#if WITH_EDITOR
// Fix compile issue when using unity build
#ifdef G
#undef G
#endif
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif
#include "Serialization/ArrayWriter.h"
#include <chrono>

#include "LuaOverrider.h"
#include "Engine/GameEngine.h"

#if UE_BUILD_DEVELOPMENT
#include "GenericPlatform/GenericPlatformMisc.h"
#endif

namespace NS_SLUA {
    
    void SluaUtil::openLib(lua_State* L) {
        lua_newtable(L);
        RegMetaMethod(L, getGameInstance);
        RegMetaMethod(L, getWorld);
        RegMetaMethod(L, loadUI);
        RegMetaMethod(L, createDelegate);
        RegMetaMethod(L, loadClass);
        RegMetaMethod(L, loadObject);
        RegMetaMethod(L, setTickFunction);
        RegMetaMethod(L, getMicroseconds);
        RegMetaMethod(L, getMiliseconds);
        RegMetaMethod(L, getGStartTime);
        RegMetaMethod(L, setGCParam);
        RegMetaMethod(L, dumpUObjects);
        RegMetaMethod(L, getAllWidgetObjects);
        RegMetaMethod(L, isValid);
        RegMetaMethod(L, isStruct);
        RegMetaMethod(L, addRef);
        RegMetaMethod(L, removeRef);
        RegMetaMethod(L, removeDelegate);
#if UE_BUILD_DEVELOPMENT
        RegMetaMethod(L, getObjectTableMap);
        RegMetaMethod(L, getRefTraceback);
        RegMetaMethod(L, toggleRefTraceback);
#endif
        lua_setglobal(L,"slua");
    }

    void SluaUtil::reg(lua_State* L,const char* fn,lua_CFunction f) {
        lua_getglobal(L,"slua");
        lua_pushcclosure(L,f,0);
        lua_setfield(L,-2,fn);
        lua_pop(L,1);
    }

    int SluaUtil::getGameInstance(lua_State* L)
    {
        UGameInstance* GameInstance = LuaState::get(L)->getGameInstance();
        return LuaObject::push(L, GameInstance);
    }

    int SluaUtil::getWorld(lua_State* L)
    {
        UGameInstance* GameInstance = LuaState::get(L)->getGameInstance();
        if (GameInstance)
        {
            return LuaObject::push(L, GameInstance->GetWorld());
        }
        return 0;
    }

    template<typename T>
    UClass* loadClassT(const char* cls) {
        FString path(UTF8_TO_TCHAR(cls));
        int32 index;
        if (!path.FindChar(TCHAR('\''),index)) {
            // load blueprint widget from cpp, need add '_C' tail
            path = FString::Format(TEXT("Blueprint'{0}_C'"), { path });
        }
        else
        // auto add _C suffix
        {
            // remove last '
            path = path.Left(path.Len()-1);
            path += TEXT("_C'");
        }
        
        UClass* uclass = LoadClass<T>(NULL, *path);
        return uclass;
    }

    int SluaUtil::loadClass(lua_State* L) {
        const char* cls = luaL_checkstring(L,1);
        UClass* uclass = loadClassT<UObject>(cls);
        if(uclass==nullptr) luaL_error(L,"Can't find class named %s",cls);
        return LuaObject::pushClass(L,uclass);
    }

    int SluaUtil::loadObject(lua_State* L) {
        const char* objname = luaL_checkstring(L, 1);
        UObject* outter = LuaObject::checkValueOpt<UObject*>(L, 2, nullptr);
        return LuaObject::push(L, LoadObject<UObject>(outter, UTF8_TO_TCHAR(objname)));
    }
    
    int SluaUtil::loadUI(lua_State* L) {
        const char* cls = luaL_checkstring(L,1);

        lua_settop(L, 2); // make sure a 2nd argument
        UObject* obj = LuaObject::checkValueOpt<UObject*>(L, 2, nullptr);

        auto uclass = loadClassT<UUserWidget>(cls);
        if(uclass==nullptr) luaL_error(L,"Can't find class named %s",cls);

        UUserWidget* widget = nullptr;
        // obj can be 5 types
        if (obj) {
            if (obj->IsA<UWorld>())
                widget = CreateWidget<UUserWidget>(Cast<UWorld>(obj), uclass);
#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
            else if (obj->IsA<UWidget>())
                widget = CreateWidget<UUserWidget>(Cast<UWidget>(obj), uclass);
            else if (obj->IsA<UWidgetTree>())
                widget = CreateWidget<UUserWidget>(Cast<UWidgetTree>(obj), uclass);
#endif
            else if (obj->IsA<APlayerController>())
                widget = CreateWidget<UUserWidget>(Cast<APlayerController>(obj), uclass);
            else if (obj->IsA<UGameInstance>())
                widget = CreateWidget<UUserWidget>(Cast<UGameInstance>(obj), uclass);
            else
                luaL_error(L, "arg 2 expect UWorld or UWidget or UWidgetTree or APlayerController or UGameInstance, but got %s",
                    TCHAR_TO_UTF8(*obj->GetName()));
        }

        if(!widget) {
            // using GameInstance as default
            UGameInstance* GameInstance = LuaState::get(L)->getGameInstance();
            if (!GameInstance) {
#if WITH_EDITOR
                UUnrealEdEngine* engine = Cast<UUnrealEdEngine>(GEngine);
                if (engine && engine->PlayWorld) GameInstance = engine->PlayWorld->GetGameInstance();
#else
                UGameEngine* engine = Cast<UGameEngine>(GEngine);
                if (engine) GameInstance = engine->GameInstance;
#endif
            }
            
            if (!GameInstance) luaL_error(L, "gameinstance missing");
            widget = CreateWidget<UUserWidget>(GameInstance, uclass);
        }

        return LuaObject::push(L,widget,true);
    }

    int SluaUtil::createDelegate(lua_State* L) {
        luaL_checktype(L,1,LUA_TFUNCTION);
        UGameInstance* gameInstance = LuaState::get(L)->getGameInstance();

        if (!gameInstance)
        {
#if WITH_EDITOR
            UUnrealEdEngine* engine = Cast<UUnrealEdEngine>(GEngine);
            if (engine && engine->PlayWorld)
            {
                gameInstance = engine->PlayWorld->GetGameInstance();
            }
#else
            UEngine* engine = GEngine;
            UWorld* world = engine->GetCurrentPlayWorld();
            if (world)
            {
                gameInstance = world->GetGameInstance();
            }
#endif
        }

        if (!gameInstance)
        {
            luaL_error(L, "gameinstance missing");
        }

        auto obj = NewObject<ULuaDelegate>(gameInstance,ULuaDelegate::StaticClass());
        obj->bindFunction(L,1);
        return LuaObject::push(L,obj,true);
    }

    int SluaUtil::setTickFunction(lua_State* L)
    {
        LuaVar func(L, 1, LuaVar::LV_FUNCTION);

        LuaState* luaState = LuaState::get(L);
        luaState->setTickFunction(func);
        return 0;
    }

    int SluaUtil::getMicroseconds(lua_State* L)
    {
        int64_t nanoSeconds = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000;
        lua_pushnumber(L, nanoSeconds);
        return 1;
    }

    int SluaUtil::getMiliseconds(lua_State* L)
    {
        int64_t nanoSeconds = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000;
        lua_pushnumber(L, nanoSeconds);
        return 1;
    }

    int SluaUtil::getGStartTime(lua_State* L)
    {
        int64_t nanoSeconds = GStartTime;
        lua_pushnumber(L, nanoSeconds);
        return 1;
    }

    int SluaUtil::setGCParam(lua_State* L)
    {
        double limitedSeconds = lua_tonumber(L, 1);
        int limitedCount = lua_tointeger(L, 2);
        double interval = lua_tonumber(L, 3);
        LuaState* luaState = LuaState::get(L);
        luaState->setGCParam(limitedSeconds, limitedCount, interval);
        return 0;
    }

    int SluaUtil::dumpUObjects(lua_State * L)
    {
        auto state = LuaState::get(L);
        auto& map = state->cacheSet();
        lua_newtable(L);
        int index = 1;
        for (auto& it : map) {
            LuaObject::push(L, getUObjName(it.Key));
            lua_seti(L, -2, index++);
        }
        return 1;
    }

    int SluaUtil::getAllWidgetObjects(lua_State* L)
    {
        auto state = LuaState::get(L);
        auto& map = state->cacheSet();
        lua_newtable(L);
        int index = 1;
        UClass* WidgetClass = UUserWidget::StaticClass();
        for (auto& it : map) {
            GenericUserData* userData = it.Value;
			// Only stastics object with UD_REFERENCE flag
            if (userData && !(userData->flag & UD_REFERENCE))
            {
                continue;
            }

            UObject* obj = it.Key;
            UClass* cls = obj->GetClass();
            if (cls && cls->IsValidLowLevel() && (cls == WidgetClass || cls->IsChildOf(WidgetClass))) {
                LuaObject::push(L, obj);
                lua_seti(L, -2, index++);
            }
        }
        return 1;
    }
    
    int SluaUtil::isValid(lua_State * L)
    {
        if (lua_type(L, 1) != LUA_TUSERDATA) {
            return LuaObject::push(L, false);
        }

        const char* typeName = LuaObject::getType(L, 1);
#if UE_BUILD_DEVELOPMENT
        if (FPlatformString::Strcmp(typeName, "UObject") != 0 && FPlatformString::Strcmp(typeName, "UClass") != 0)
        {
            bool bSluaType = true;
            lua_pushglobaltable(L);
            lua_pushstring(L, typeName);
            if (lua_rawget(L, -2) == LUA_TNIL) // not lua wrapper type
            {
                bSluaType = false;

                static const char* LuaTypeName[] = {
                    "LuaStruct", "LuaArray", "LuaMap", "LuaSet", "LuaDelegateWrap", "LuaMultiDelegateWrap"
                };
                for (int i = 0; i < 6; ++i)
                {
                    if (FPlatformString::Strcmp(typeName, LuaTypeName[i]) == 0)
                    {
                        bSluaType = true;
                        break;
                    }
                }
            }

            lua_pop(L, 2);
            if (!bSluaType)
            {
                luaL_error(L, "arg 1 expect valid slua type, but got %s", typeName);
            }
        }
#endif

        GenericUserData *gud = (GenericUserData*)lua_touserdata(L, 1);
        bool bIsValid = !(gud->flag & UD_HADFREE);
        if(!bIsValid)
            return LuaObject::push(L, bIsValid);
        // if this ud is boxed UObject
        if (gud->flag & UD_UOBJECT) {
            UObject* obj = FPlatformString::Strcmp(typeName, "UObject") == 0
                               ? LuaObject::checkUD<UObject>(L, 1, false)
                               : obj = LuaObject::checkUD<UClass>(L, 1, false);
            bIsValid = LuaObject::isUObjectValid(obj);
        }
        else if (gud->flag&UD_WEAKUPTR) {
            UserData<WeakUObjectUD*>* wud = (UserData<WeakUObjectUD*>*)gud;
            bIsValid = wud->ud->isValid();
        }
        return LuaObject::push(L, bIsValid);
    }

    int SluaUtil::isStruct(lua_State* L)
    {
        if (lua_type(L, 1) != LUA_TUSERDATA) {
            return LuaObject::push(L, false);
        }
        const auto UD = LuaObject::checkUD<LuaStruct*>(L, 1, false);
        if (UD) {
            return LuaObject::push(L, true);
        }
        return LuaObject::push(L, false);
    }

    int SluaUtil::addRef(lua_State* L)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        GenericUserData* gud = (GenericUserData*)lua_touserdata(L, 1);
        if (gud->flag & UD_REFERENCE) {
            return LuaObject::push(L, false);
        }
        gud->flag |= UD_REFERENCE;
        return LuaObject::push(L, true);
    }

    int SluaUtil::removeRef(lua_State * L)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        GenericUserData *gud = (GenericUserData*)lua_touserdata(L, 1);
        if (gud->flag & UD_REFERENCE) {
            gud->flag -= UD_REFERENCE;
            return LuaObject::push(L, true);
        }
 
        return LuaObject::push(L, false);
    }

    int SluaUtil::removeDelegate(lua_State* L)
    {
        if (!lua_islightuserdata(L, 1))
            luaL_error(L, "arg 2 expect ULuaDelegate");
        auto obj = reinterpret_cast<ULuaDelegate*>(lua_touserdata(L, 1));
        auto state = LuaState::get(L);
        auto& map = state->cacheSet();
        if (!obj->IsValidLowLevel() || !LuaObject::isUObjectValid(obj) || !map.Contains(obj))
        {
#if UE_BUILD_DEVELOPMENT
            luaL_error(L, "Invalid ULuaDelegate!");
#else
            return 0;
#endif
        }

        obj->dispose();
        // remove reference
        LuaObject::removeRef(L, obj);

        return 0;
    }

#if UE_BUILD_DEVELOPMENT
    int SluaUtil::getObjectTableMap(lua_State* L)
    {
        lua_newtable(L);
        ULuaOverrider::ObjectTableMap* TableMap = ULuaOverrider::getObjectTableMap(L);
        if (TableMap)
        {
            for (auto it : *TableMap)
            {
                TWeakObjectPtr<UObject> obj = it.Key;
                NS_SLUA::LuaVar* LuaTable = &it.Value.table;
                if (obj.IsValid() && LuaTable)
                {
                    LuaObject::push(L, obj.Get());
                    LuaTable->push(L);
                    lua_settable(L, -3);
                }
            }
        }
        return 1;
    }
    
    int SluaUtil::getRefTraceback(lua_State* L)
    {
        auto state = LuaState::get(L);
        int ref = lua_tonumber(L, 1);
        FString traceback = state->getRefTraceback(ref);
        lua_pushstring(L, TCHAR_TO_UTF8(*traceback));

        return 1;
    }

    int SluaUtil::toggleRefTraceback(lua_State* L)
    {
        LuaState* state = LuaState::get(L);
        if (state)
        {
            state->setRefTraceEnable(!state->isRefTraceEnable());
        }
        return 0;
    }

    void toggleRefTraceEnable() {
        LuaState* state = LuaState::get();
        if (!state) return;
        state->setRefTraceEnable(!state->isRefTraceEnable());

        if (state->isRefTraceEnable()) {
            FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, TEXT("Lua registry ref leak trace enable!"), TEXT("Info"));
        }
        else {
            FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, TEXT("Lua registry ref leak trace disable!"), TEXT("Info"));
        }
    }

    static FAutoConsoleCommand CEnableRefTrace(
        TEXT("slua.EnableRefTrace"),
        TEXT("Enable [registry] tracer!"),
        FConsoleCommandDelegate::CreateStatic(toggleRefTraceEnable),
        ECVF_Cheat);
#endif

#if WITH_EDITOR
    void dumpUObjects() {
        auto state = LuaState::get();
        if (!state) return;
        auto& map = state->cacheSet();
        for (auto& it : map) {
            UE_LOG(Slua, Log, TEXT("Pushed UObject %s"), *getUObjName(it.Key));
        }
    }

    void garbageCollect() {
        auto state = LuaState::get();
        lua_gc(state->getLuaState(), LUA_GCCOLLECT, 0);
        UE_LOG(Slua, Log, TEXT("Performed full lua gc"));
    }

    void memUsed() {
        auto state = LuaState::get();
        int kb = lua_gc(state->getLuaState(), LUA_GCCOUNT, 0);
        UE_LOG(Slua, Log, TEXT("Lua use memory %d kb"), kb);
    }

    static FAutoConsoleCommand CVarDumpUObjects(
        TEXT("slua.DumpUObjects"),
        TEXT("Dump all uobject that referenced by lua in main state"),
        FConsoleCommandDelegate::CreateStatic(dumpUObjects),
        ECVF_Cheat);

    static FAutoConsoleCommand CVarGC(
        TEXT("slua.GC"),
        TEXT("Collect lua garbage"),
        FConsoleCommandDelegate::CreateStatic(garbageCollect),
        ECVF_Cheat);

    static FAutoConsoleCommand CVarMem(
        TEXT("slua.Mem"),
        TEXT("Print memory used"),
        FConsoleCommandDelegate::CreateStatic(memUsed),
        ECVF_Cheat);
#endif
}