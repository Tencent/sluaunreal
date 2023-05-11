// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaDelegate.h"

#include "LuaFunctionAccelerator.h"
#include "LuaObject.h"
#include "LuaState.h"
#include "SluaUtil.h"

ULuaDelegate::ULuaDelegate(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    ,luafunction(nullptr)
    ,ufunction(nullptr)
{
}

ULuaDelegate::~ULuaDelegate() {
    SafeDelete(luafunction);
}

void ULuaDelegate::EventTrigger()
{
    ensure(false); // never run here
}

void ULuaDelegate::ProcessEvent( UFunction* f, void* Parms ) {
    if (luafunction == nullptr || ufunction == nullptr) {
#if WITH_EDITOR
        NS_SLUA::Log::Error("Can't remove lua delegate[%s] on trigger delegate!", TCHAR_TO_UTF8(*pName));
#else
        NS_SLUA::Log::Error("Can't remove lua delegate on trigger delegate!");
#endif
        return;
    }
    luafunction->callByUFunction(ufunction,reinterpret_cast<uint8*>(Parms));
}

void ULuaDelegate::bindFunction(NS_SLUA::lua_State* L,int p,UFunction* ufunc) {
    luaL_checktype(L,p,LUA_TFUNCTION);
    ensure(ufunc);
    luafunction = new NS_SLUA::LuaVar(L,p,NS_SLUA::LuaVar::LV_FUNCTION);
    ufunction = ufunc;
}

void ULuaDelegate::bindFunction(NS_SLUA::lua_State* L,int p) {
    luaL_checktype(L,p,LUA_TFUNCTION);
    luafunction = new NS_SLUA::LuaVar(L,p,NS_SLUA::LuaVar::LV_FUNCTION);
}

void ULuaDelegate::bindFunction(UFunction *ufunc) {
    ensure(ufunc);
    ufunction = ufunc;
}

void ULuaDelegate::dispose()
{
    SafeDelete(luafunction);
    ufunction = nullptr;
}

namespace NS_SLUA {

    struct LuaMultiDelegateWrap {
        FMulticastScriptDelegate* delegate;
        LuaFunctionAccelerator* funcAcc;
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        FMulticastSparseDelegateProperty* sparseProp = nullptr;
        FSparseDelegate* sparseDelegate = nullptr;
#endif
#if WITH_EDITOR
        FString pName;
#endif
    };

    DefTypeName(LuaMultiDelegateWrap);

    struct LuaDelegateWrap {
        FScriptDelegate* delegate;
        LuaFunctionAccelerator* funcAcc;
#if WITH_EDITOR
        FString pName;
#endif
    };

    DefTypeName(LuaDelegateWrap);

    int LuaMultiDelegate::Add(lua_State* L) {
        CheckUD(LuaMultiDelegateWrap,L,1);

        // bind luafucntion and signature function
        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(),ULuaDelegate::StaticClass());
#if WITH_EDITOR
        obj->setPropName(UD->pName);
#endif
        obj->bindFunction(L,2,UD->funcAcc->func);

        // add event listener
        FScriptDelegate Delegate;
        Delegate.BindUFunction(obj, TEXT("EventTrigger"));
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        if (UD->sparseProp)
        {
            UD->sparseProp->AddDelegate(Delegate, nullptr, UD->sparseDelegate);
        }
        else
#endif
        {
            UD->delegate->AddUnique(Delegate);
        }

        // add reference
        LuaObject::addRef(L,obj,nullptr,true);

        lua_pushlightuserdata(L,obj);
        return 1;
    }

    int LuaMultiDelegate::Remove(lua_State* L) {
        CheckUD(LuaMultiDelegateWrap,L,1);
        if(!lua_islightuserdata(L,2))
            luaL_error(L,"arg 2 expect ULuaDelegate");
        auto obj =  reinterpret_cast<ULuaDelegate*>(lua_touserdata(L,2));

        auto *luaState = LuaState::get(L);
        auto &map = luaState->cacheSet();
        
        if (!map.Contains(obj) || !obj->IsValidLowLevel())
        {
#if UE_BUILD_DEVELOPMENT
            luaL_error(L, "Invalid ULuaDelegate!");
#endif
            return 0;
        }

        FScriptDelegate Delegate;
        Delegate.BindUFunction(obj, TEXT("EventTrigger"));

        // remove delegate
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        if (UD->sparseProp)
        {
            UD->sparseProp->RemoveDelegate(Delegate, nullptr, UD->sparseDelegate);
        }
        else
#endif
        {
            UD->delegate->Remove(Delegate);
        }

        // remove reference
        LuaObject::removeRef(L,obj);
        obj->dispose();

        return 0;
    }

    int LuaMultiDelegate::Clear(lua_State* L) {
        CheckUD(LuaMultiDelegateWrap,L,1);

        auto clearLuaDelegate = [L](TArray<UObject*> array)
        {
            for (auto it : array) {
                ULuaDelegate* delegateObj = Cast<ULuaDelegate>(it);
                if (delegateObj)
                {
                    delegateObj->dispose();
                    LuaObject::removeRef(L, it);
                }
            }
        };
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        if (UD->sparseProp)
        {
            const FMulticastScriptDelegate* scriptDelegate = UD->sparseProp->GetMulticastDelegate(UD->sparseDelegate);
            if (scriptDelegate)
            {
                clearLuaDelegate(scriptDelegate->GetAllObjects());
                UD->sparseProp->ClearDelegate(nullptr, UD->sparseDelegate);
            }
        }
        else
#endif
        {
            clearLuaDelegate(UD->delegate->GetAllObjects());
            UD->delegate->Clear();
        }
        return 0;
    }

    int LuaMultiDelegate::BroadCast(lua_State* L) {
        CheckUD(LuaMultiDelegateWrap,L,1);

        auto callBroadcast = [UD, L](const FMulticastScriptDelegate* delegate)
        {
            if (!delegate)
            {
                return;
            }

            auto callback = [delegate](uint8* params, PTRINT* outParams, NewObjectRecorder *objectRecorder)
            {
                delegate->ProcessMulticastDelegate<UObject>(params);
            };
            bool isLatentFunction;
            UD->funcAcc->fillParam(L, 2, nullptr, callback, isLatentFunction);
        };

#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
        if (UD->sparseProp)
        {
            if (!UD->sparseDelegate->IsBound())
            {
                return 0;
            }
            callBroadcast(UD->sparseProp->GetMulticastDelegate(UD->sparseDelegate));
            return 0;
        }
        else
#endif
        {
            if (!UD->delegate->IsBound())
            {
                return 0;
            }
            callBroadcast(UD->delegate);
        }
        return 0;
    }

    int LuaMultiDelegate::gc(lua_State* L) { 
        CheckUD(LuaMultiDelegateWrap,L,1);
        delete UD;
        return 0;    
    }
   
    int LuaMultiDelegate::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,Add);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);
        RegMetaMethod(L,BroadCast);
        return 0;
    }

    int LuaMultiDelegate::push(lua_State* L,FMulticastScriptDelegate* delegate,UFunction* ufunc,const FString& pName) {
#if WITH_EDITOR
        LuaMultiDelegateWrap* wrapobj = new LuaMultiDelegateWrap{ delegate,LuaFunctionAccelerator::findOrAdd(ufunc) };
        wrapobj->pName = pName;
#else
        LuaMultiDelegateWrap* wrapobj = new LuaMultiDelegateWrap{ delegate,LuaFunctionAccelerator::findOrAdd(ufunc) };
#endif
        return LuaObject::pushType<LuaMultiDelegateWrap*>(L,wrapobj,"LuaMultiDelegateWrap",setupMT,gc);
    }

#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
    int LuaMultiDelegate::push(lua_State* L,FMulticastSparseDelegateProperty* prop,FSparseDelegate* sparseDelegate,UFunction* ufunc,const FString& pName)
    {
#if WITH_EDITOR
        LuaMultiDelegateWrap* wrapobj = new LuaMultiDelegateWrap{
            nullptr, LuaFunctionAccelerator::findOrAdd(ufunc), prop, sparseDelegate, pName
        };
#else
        LuaMultiDelegateWrap* wrapobj = new LuaMultiDelegateWrap{ nullptr, LuaFunctionAccelerator::findOrAdd(ufunc), prop, sparseDelegate };
#endif
        return LuaObject::pushType<LuaMultiDelegateWrap*>(L,wrapobj,"LuaMultiDelegateWrap",setupMT,gc);
    }
#endif

    void clear(lua_State* L, LuaDelegateWrap* ldw) {
        auto object = ldw->delegate->GetUObject();
        if (object)
        {
            ULuaDelegate* delegateObj = Cast<ULuaDelegate>(object);
            if (delegateObj)
            {
                LuaObject::removeRef(L, object);
                delegateObj->dispose();
            }
        }
        ldw->delegate->Clear();
    }

    int LuaDelegate::Bind(lua_State* L)
    {
        CheckUD(LuaDelegateWrap, L, 1);

        // clear old delegate object
        if(UD) clear(L,UD);

        // bind luafucntion and signature function
        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(), ULuaDelegate::StaticClass());
#if WITH_EDITOR 
        obj->setPropName(UD->pName);
#endif
        obj->bindFunction(L, 2, UD->funcAcc->func);

        UD->delegate->BindUFunction(obj, TEXT("EventTrigger"));

        // add reference
        LuaObject::addRef(L, obj, nullptr, true);

        lua_pushlightuserdata(L, obj);
        return 1;
    }

    int LuaDelegate::Clear(lua_State* L)
    {
        CheckUD(LuaDelegateWrap, L, 1);
        if(UD) clear(L,UD);
        return 0;
    }

    int LuaDelegate::Execute(lua_State* L)
    {
        CheckUD(LuaDelegateWrap, L, 1);
        if (!UD->delegate->IsBound())
        {
            return 0;
        }

        int outParamCount;
        auto funcAcc = UD->funcAcc;
        auto callback = [L, UD, funcAcc, &outParamCount](uint8* params, PTRINT* outParams, NewObjectRecorder* objectRecorder)
        {
            UD->delegate->ProcessDelegate<UObject>(params);
            
            outParamCount = funcAcc->returnValue(L, 2, params, outParams, objectRecorder);
        };
        
        bool isLatentFunction = false;
        funcAcc->fillParam(L, 2, nullptr, callback, isLatentFunction);
        return outParamCount;
    }

    int LuaDelegate::gc(lua_State* L)
    {
        CheckUD(LuaDelegateWrap, L, 1);
        delete UD;
        return 0;
    }

    int LuaDelegate::setupMT(lua_State* L)
    {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L, Bind);
        RegMetaMethod(L, Clear);
        RegMetaMethod(L, Execute);
        return 0;
    }

    int LuaDelegate::push(lua_State* L, FScriptDelegate* delegate, UFunction* ufunc, const FString& pName)
    {
#if WITH_EDITOR
        LuaDelegateWrap* wrapobj = new LuaDelegateWrap{delegate, LuaFunctionAccelerator::findOrAdd(ufunc), pName};
#else
        LuaDelegateWrap* wrapobj = new LuaDelegateWrap{ delegate, LuaFunctionAccelerator::findOrAdd(ufunc) };
#endif
        return LuaObject::pushType<LuaDelegateWrap*>(L, wrapobj, "LuaDelegateWrap", setupMT, gc);
    }

}