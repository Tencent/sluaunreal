// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaBlueprintLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Blueprint/BlueprintSupport.h"
#include "LuaState.h"
#include "Internationalization/Internationalization.h"

namespace {
    const FName GetVarOutOfBoundsWarning = FName("GetVarOutOfBoundsWarning");    
    const FName GetVarTypeErrorWarning = FName("GetVarTypeErrorWarning");    
}

#define LOCTEXT_NAMESPACE "ULuaBlueprintLibrary"

ULuaBlueprintLibrary::ULuaBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    FBlueprintSupport::RegisterBlueprintWarning(
		FBlueprintWarningDeclaration (
			GetVarOutOfBoundsWarning,
			LOCTEXT("GetOutOfBoundsWarning", "BpVar read access out of bounds")
		)
	);
	FBlueprintSupport::RegisterBlueprintWarning(
		FBlueprintWarningDeclaration (
			GetVarTypeErrorWarning,
			LOCTEXT("GetVarTypeErrorWarning", "BpVar is not speicified type")
		)
	);
}

FLuaBPVar ULuaBlueprintLibrary::CallToLuaWithArgs(FString funcname,const TArray<FLuaBPVar>& args) {
    using namespace slua;
    // get main state
    auto ls = LuaState::get();
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

FLuaBPVar ULuaBlueprintLibrary::CallToLua(FString funcname) {
    using namespace slua;
    // get main state
    auto ls = LuaState::get();
    if(!ls) return FLuaBPVar();
    LuaVar f = ls->get(TCHAR_TO_UTF8(*funcname));
    if(f.isFunction()) {
        LuaVar r = f.callWithNArg(0);
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

namespace {
    using namespace slua;

    bool getValue(const LuaVar& lv,int index,int& value) {
        if(index==1 && lv.count()>=index && lv.isInt()) {
            value = lv.asInt();
            return true;
        }
        else if(lv.isTable() || lv.isTuple()) {
            LuaVar v = lv.getAt(index);
            return getValue(v,1,value);
        }
        else
            return false;
    }

    bool getValue(const LuaVar& lv,int index,bool& value) {
        if(index==1 && lv.count()>=index && lv.isBool()) {
            value = lv.asBool();
            return true;
        }
        else if(lv.isTable() || lv.isTuple()) {
            LuaVar v = lv.getAt(index);
            return getValue(v,1,value);
        }
        else
            return false;
    }

    bool getValue(const LuaVar& lv,int index,float& value) {
        if(index==1 && lv.count()>=index && lv.isNumber()) {
            value = lv.asFloat();
            return true;
        }
        else if(lv.isTable() || lv.isTuple()) {
            LuaVar v = lv.getAt(index);
            return getValue(v,1,value);
        }
        else
            return false;
    }

    bool getValue(const LuaVar& lv,int index,FString& value) {
        if(index==1 && lv.count()>=index && lv.isString()) {
            value = UTF8_TO_TCHAR(lv.asString());
            return true;
        }
        else if(lv.isTable() || lv.isTuple()) {
            LuaVar v = lv.getAt(index);
            return getValue(v,1,value);
        }
        else
            return false;
    }

    bool getValue(const LuaVar& lv,int index,UObject*& value) {
        if(index==1 && lv.count()>=index && lv.isUserdata("UObject")) {
            value = lv.asUserdata<UObject>("UObject");
            return true;
        }
        else if(lv.isTable() || lv.isTuple()) {
            LuaVar v = lv.getAt(index);
            return getValue(v,1,value);
        }
        else
            return false;
    }

    template<class T>
    T getValueFromVar(const FLuaBPVar& Value,int Index) {
        using namespace slua;
        const LuaVar& lv = Value.value;
        if(Index<=lv.count()) {
            T v;
            if(getValue(lv,Index,v))
                return v;
            else
                FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Attempted to index an item from an invalid type!")),
                    ELogVerbosity::Warning, GetVarTypeErrorWarning);
        }
        else {
            FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Attempted to index an item from an invalid index from BpVar [%d/%d]!"),
                 Index, lv.count()), ELogVerbosity::Warning, GetVarOutOfBoundsWarning);
        }
        return T();
    }
}



int ULuaBlueprintLibrary::GetIntFromVar(FLuaBPVar Value,int Index) {
    return getValueFromVar<int>(Value,Index);
}

float ULuaBlueprintLibrary::GetNumberFromVar(FLuaBPVar Value,int Index) {
    return getValueFromVar<float>(Value,Index);
}

bool ULuaBlueprintLibrary::GetBoolFromVar(FLuaBPVar Value,int Index) {
    return getValueFromVar<bool>(Value,Index);
}

FString ULuaBlueprintLibrary::GetStringFromVar(FLuaBPVar Value,int Index) {
    return getValueFromVar<FString>(Value,Index);
}

UObject* ULuaBlueprintLibrary::GetObjectFromVar(FLuaBPVar Value,int Index) {
    return getValueFromVar<UObject*>(Value,Index);
}