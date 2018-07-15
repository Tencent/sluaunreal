// The MIT License (MIT)

// Copyright 2015 Siney/Pangweiwei siney@yeah.net
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "LuaDelegate.h"
#include "LuaObject.h"
#include "LuaVar.h"

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
    ensure(luafunction!=nullptr && ufunction!=nullptr);
    luafunction->callByUFunction(ufunction,reinterpret_cast<uint8*>(Parms));
}

void ULuaDelegate::bindFunction(slua::lua_State* L,int p,UFunction* ufunc) {
    luaL_checktype(L,p,LUA_TFUNCTION);
    ensure(ufunc);
    luafunction = new slua::LuaVar(L,p,slua::LuaVar::LV_FUNCTION);
    ufunction = ufunc;
}

void ULuaDelegate::bindFunction(slua::lua_State* L,int p) {
    luaL_checktype(L,p,LUA_TFUNCTION);
    luafunction = new slua::LuaVar(L,p,slua::LuaVar::LV_FUNCTION);
}

void ULuaDelegate::bindFunction(UFunction *ufunc) {
    ensure(ufunc);
    ufunction = ufunc;
}

namespace slua {

    struct LuaDelegateWrap {
        FMulticastScriptDelegate* delegate;
        UFunction* ufunc;
    };

    int LuaDelegate::Add(lua_State* L) {
        CheckUD(LuaDelegateWrap,L,1);

        // bind luafucntion and signature function
        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(),ULuaDelegate::StaticClass());
        obj->bindFunction(L,2,UD->ufunc);

        // add event listener
        FScriptDelegate Delegate;
        Delegate.BindUFunction(obj, TEXT("EventTrigger"));
        UD->delegate->AddUnique(Delegate);

        // add reference
        obj->AddToRoot();

        lua_pushlightuserdata(L,obj);
        return 1;
    }

    int LuaDelegate::Remove(lua_State* L) {
        CheckUD(LuaDelegateWrap,L,1);
        if(!lua_islightuserdata(L,2))
            luaL_error(L,"arg 2 expect ULuaDelegate");
        auto obj =  reinterpret_cast<ULuaDelegate*>(lua_touserdata(L,2));
        if(!obj->IsValidLowLevel()) return 0;

        FScriptDelegate Delegate;
        Delegate.BindUFunction(obj, TEXT("EventTrigger"));

        // remove delegate
        UD->delegate->Remove(Delegate);

        // remove reference
        obj->RemoveFromRoot();

        return 0;
    }

    int LuaDelegate::Clear(lua_State* L) {
        CheckUD(LuaDelegateWrap,L,1);
        auto array = UD->delegate->GetAllObjects();
        for(auto it:array) {
            it->RemoveFromRoot();
        }
        UD->delegate->Clear();
        return 0;
    }

    int LuaDelegate::gc(lua_State* L) { 
        CheckUD(LuaDelegateWrap,L,1);
        delete UD;
        return 0;    
    }
   

    int LuaDelegate::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,Add);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);
        return 0;
    }

    int LuaDelegate::push(lua_State* L,FMulticastScriptDelegate* delegate,UFunction* ufunc) {
        LuaDelegateWrap* wrapobj = new LuaDelegateWrap{delegate,ufunc};
        return LuaObject::pushType<LuaDelegateWrap*>(L,wrapobj,"LuaDelegateWrap",setupMT,gc);
    }



}