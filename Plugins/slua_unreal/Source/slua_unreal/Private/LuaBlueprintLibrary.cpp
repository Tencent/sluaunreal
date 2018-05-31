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

#include "LuaBlueprintLibrary.h"
#include "LuaState.h"

ULuaBlueprintLibrary::ULuaBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FLuaBPVar ULuaBlueprintLibrary::CallToLua(FString funcname,const TArray<FLuaBPVar>& args) {
    using namespace slua;
    // get main state
    auto ls = LuaState::get((lua_State*)nullptr);
    if(!ls) return FLuaBPVar();
    LuaVar f = ls->get(TCHAR_TO_UTF8(*funcname));
    if(f.isFunction()) {
        for(auto arg:args) {
            arg.value.push(ls->getLuaState());
        }
        LuaVar r = f.callWithNArg(args.Num());
        return FLuaBPVar(r);
    }
    return FLuaBPVar();
}

FLuaBPVar ULuaBlueprintLibrary::CreateVarFromInt(int i) {
    FLuaBPVar v;
    v.value.set(i);
    return v;
}

FLuaBPVar ULuaBlueprintLibrary::CreateVarFromString(FString s) {
    FLuaBPVar v;
    v.value.set(TCHAR_TO_UTF8(*s));
    return v;
}

FLuaBPVar ULuaBlueprintLibrary::CreateVarFromNumber(float d) {
    FLuaBPVar v;
    v.value.set(d);
    return v;
}

FLuaBPVar ULuaBlueprintLibrary::CreateVarFromBool(bool b) {
    FLuaBPVar v;
    v.value.set(b);
    return v;
}

FLuaBPVar ULuaBlueprintLibrary::CreateVarFromObject(UObject* o) {
    using namespace slua;
    auto ls = LuaState::get();
    if(!ls) return FLuaBPVar();
    LuaObject::push(*ls,o);
    LuaVar ret(*ls,-1);
    lua_pop(*ls,1);
    return FLuaBPVar(ret);
}

