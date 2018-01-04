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

using namespace slua;


ULuaDelegate::ULuaDelegate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	luafunction = nullptr;
    ufunction = nullptr;
}

void ULuaDelegate::OnClicked()
{
    ensure(false); // never run here
}

void ULuaDelegate::ProcessEvent( UFunction* f, void* Parms ) {
    //UObject::ProcessEvent(Function,Parms);
    ensure(luafunction!=nullptr && ufunction!=nullptr);

	const bool bHasReturnParam = ufunction->ReturnValueOffset != MAX_uint16;
    if(ufunction->ParmsSize==0 && !bHasReturnParam)
        luafunction->call<void>();
    else {
        luafunction->callByUFunction(ufunction,reinterpret_cast<uint8*>(Parms));
    }
}

void ULuaDelegate::bindFunction(lua_State* L,int p,UFunction* ufunc) {
    luaL_checktype(L,p,LUA_TFUNCTION);
    luafunction = new LuaVar(L,p,LuaVar::LV_FUNCTION);
    ufunction = ufunc;
}

namespace slua {

    struct LuaDelegateWrap {
        FMulticastScriptDelegate* delegate;
        UFunction* ufunc;
    };

    int LuaDelegate::Add(lua_State* L) {
        CheckUD(LuaDelegateWrap,L,1);

        auto obj = NewObject<ULuaDelegate>((UObject*)GetTransientPackage(),ULuaDelegate::StaticClass());
        obj->bindFunction(L,2,UD->ufunc);
        obj->AddToRoot();

        FScriptDelegate* Delegate = new FScriptDelegate();
        Delegate->BindUFunction(obj, TEXT("OnClicked"));
        UD->delegate->AddUnique(*Delegate);

        return LuaObject::push(L,Delegate);
    }

    int LuaDelegate::Remove(lua_State* L) {
        CheckUD(LuaDelegateWrap,L,1);
        CheckUDEX(FScriptDelegate,d,L,2);
        
        FScriptDelegate* sd = d->ud;
        if(sd) {
            // remove delegate
            UD->delegate->Remove(*sd);
            UObject* obj = sd->GetUObject();
            // free uobject
            obj->RemoveFromRoot();
            obj->ConditionalBeginDestroy();
            delete sd;
            // set ud is null
            d->ud = nullptr;
        }
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
        return 0;
    }

    int LuaDelegate::push(lua_State* L,FMulticastScriptDelegate* delegate,UFunction* ufunc) {
        LuaDelegateWrap* wrapobj = new LuaDelegateWrap{delegate,ufunc};
        return LuaObject::pushType<LuaDelegateWrap*>(L,wrapobj,"LuaDelegateWrap",setupMT,gc);
    }



}