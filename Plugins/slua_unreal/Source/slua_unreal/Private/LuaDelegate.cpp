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

static TMap<int64, TWeakObjectPtr<UObject>> DelegateHandleToObjectMap;
static int64 DelegateHandle = 0;

ULuaDelegate::ULuaDelegate(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    ,luafunction(nullptr)
    ,ufunction(nullptr)
    ,handle(0)
{
}

ULuaDelegate::~ULuaDelegate() {
    if (luafunction)
    {
        delete luafunction;
        luafunction = nullptr;
    }
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
    if (luafunction)
    {
        delete luafunction;
        luafunction = nullptr;
    }
}

int ULuaDelegate::addLuaDelegate(NS_SLUA::lua_State* L, ULuaDelegate* obj)
{
    DelegateHandle++;
    obj->handle = DelegateHandle;
    DelegateHandleToObjectMap.Emplace(DelegateHandle, obj);

    // add reference
    NS_SLUA::LuaObject::addRef(L,obj,nullptr,true);

    lua_pushinteger(L, DelegateHandle);
    return 1;
}

int ULuaDelegate::removeLuaDelegate(NS_SLUA::lua_State* L, ULuaDelegate* obj)
{
    DelegateHandleToObjectMap.Remove(obj->handle);

    // remove reference
    NS_SLUA::LuaObject::removeRef(L,obj);
    obj->dispose();

    return 0;
}

int ULuaDelegate::removeLuaDelegateByHandle(NS_SLUA::lua_State* L, int64 handle)
{
    auto objPtr = DelegateHandleToObjectMap.Find(handle);
    if (!objPtr)
    {
        lua_pushboolean(L, 0);
        return 1;
    }
    auto obj = Cast<ULuaDelegate>(objPtr->Get());
    removeLuaDelegate(L, obj);

    lua_pushboolean(L, 1);
    return 1;
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

        int type = lua_type(L, 2);
        switch (type)
        {
        case LUA_TFUNCTION:
            {
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
                return ULuaDelegate::addLuaDelegate(L, obj);
            }
            break;
        case LUA_TUSERDATA:
        case LUA_TTABLE:
            {
                UObject* obj = LuaObject::checkUD<UObject>(L, 2);
                if (!obj)
                {
                    luaL_error(L, "Argument 2nd expect UObject but got %s!", lua_typename(L, 2));
                }

                FName funcName = UTF8_TO_TCHAR(lua_tostring(L, 3));
                auto cls = obj->GetClass();
                if (!cls->FindFunctionByName(funcName))
                {
                    luaL_error(L, "Can't find function %s to bind to delegate!", lua_tostring(L, 3));
                }
                // add event listener
                FScriptDelegate Delegate;
                Delegate.BindUFunction(obj, funcName);
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
            }
            break;
        default:
            break;
        }

        return 0;
    }

    int LuaMultiDelegate::Remove(lua_State* L) {
        CheckUD(LuaMultiDelegateWrap,L,1);

        int type = lua_type(L, 2);
        switch (type)
        {
        case LUA_TNUMBER:
            {
                int64 handle = lua_tointeger(L, 2);
                if (handle <= 0)
                    luaL_error(L,"arg 2 expect integer type of handle");
                auto objPtr = DelegateHandleToObjectMap.Find(handle);
                auto obj = objPtr ? objPtr->Get() : nullptr;
                if (!obj)
                {
                    return 0;
                }
                auto delegateObj = Cast<ULuaDelegate>(obj);

                FScriptDelegate Delegate;
                Delegate.BindUFunction(delegateObj, TEXT("EventTrigger"));

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

                ULuaDelegate::removeLuaDelegate(L, delegateObj);
            }
            break;
        case LUA_TUSERDATA:
        case LUA_TTABLE:
            {
                UObject* obj = LuaObject::checkUD<UObject>(L, 2);
                if (!obj)
                {
                    luaL_error(L, "Argument 2nd expect UObject but got %s!", lua_typename(L, 2));
                }

                FName funcName = UTF8_TO_TCHAR(lua_tostring(L, 3));
                auto cls = obj->GetClass();
                if (!cls->FindFunctionByName(funcName))
                {
                    luaL_error(L, "Can't find function %s to bind to delegate!", lua_tostring(L, 3));
                }
                // add event listener
                FScriptDelegate Delegate;
                Delegate.BindUFunction(obj, funcName);

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
            }
            break;
        default:
            break;
        }
        
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
                    ULuaDelegate::removeLuaDelegate(L, delegateObj);
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

    int LuaMultiDelegate::Broadcast(lua_State* L) {
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
        auto userdata = (UserData<LuaMultiDelegateWrap*>*)lua_touserdata(L, 1);
        auto self = userdata->ud;
        if (!userdata->parent && !(userdata->flag & UD_HADFREE))
            LuaObject::releaseLink(L, self->delegate);
        if (userdata->parent)
            LuaObject::unlinkProp(L, userdata);
        delete self;
        return 0;    
    }
   
    int LuaMultiDelegate::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,Add);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);
        RegMetaMethod(L,Broadcast);
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
                ULuaDelegate::removeLuaDelegate(L, delegateObj);
            }
        }
        ldw->delegate->Clear();
    }

    int LuaDelegate::Bind(lua_State* L)
    {
        CheckUD(LuaDelegateWrap, L, 1);

        // clear old delegate object
        if(UD) clear(L,UD);

        int type = lua_type(L, 2);
        switch (type)
        {
        case LUA_TFUNCTION:
            {
                // bind luafucntion and signature function
                auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(), ULuaDelegate::StaticClass());
#if WITH_EDITOR 
                obj->setPropName(UD->pName);
#endif
                obj->bindFunction(L, 2, UD->funcAcc->func);

                UD->delegate->BindUFunction(obj, TEXT("EventTrigger"));

                return ULuaDelegate::addLuaDelegate(L, obj);
            }
            break;
        case LUA_TUSERDATA:
        case LUA_TTABLE:
            {
                UObject* obj = LuaObject::checkUD<UObject>(L, 2);
                if (!obj)
                {
                    luaL_error(L, "Argument 2nd expect UObject but got %s!", lua_typename(L, 2));
                }

                FName funcName = UTF8_TO_TCHAR(lua_tostring(L, 3));
                auto cls = obj->GetClass();
                if (!cls->FindFunctionByName(funcName))
                {
                    luaL_error(L, "Can't find function %s to bind to delegate!", lua_tostring(L, 3));
                }

                UD->delegate->BindUFunction(obj, funcName);
            }
            break;
        default:
            break;
        }

        return 0;
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
        auto userdata = (UserData<LuaDelegateWrap*>*)lua_touserdata(L, 1);
        auto self = userdata->ud;
        if (!userdata->parent && !(userdata->flag & UD_HADFREE))
            LuaObject::releaseLink(L, self->delegate);
        if (userdata->parent)
            LuaObject::unlinkProp(L, userdata);
        delete self;
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
