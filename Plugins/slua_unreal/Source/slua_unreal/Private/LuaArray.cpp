// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaArray.h"
#include "LuaObject.h"
#include "LuaCppBinding.h"
#include <string>


namespace slua {

    void LuaArray::reg(lua_State* L) {

    }

    LuaArray::LuaArray(UArrayProperty* prop,FScriptArray* buf)
        :prop(prop) 
    {
        // why FScriptArray can't be copy constructed or MoveToEmpty?
        // just hack it, TODO
        // array.MoveToEmpty(*buf);
        FMemory::Memcpy(&array,buf,sizeof(FScriptArray));
        if(prop) prop->AddToRoot();
    }

    LuaArray::~LuaArray() {
        if(prop) prop->RemoveFromRoot();
    }

    int LuaArray::push(lua_State* L,UArrayProperty* prop,FScriptArray* data) {
        LuaArray* array = new LuaArray(prop,data);
        return LuaObject::pushType(L,array,"LuaArray",setupMT,gc);
    }

    int LuaArray::Num(lua_State* L) {
        CheckUD(LuaArray,L,1);
        return LuaObject::push(L,UD->array.Num());
    }

    int LuaArray::Get(lua_State* L) {
        CheckUD(LuaArray,L,1);
        int i = LuaObject::checkValue<int>(L,2);
        UProperty* element = UD->prop->Inner;
        int32 es = element->ElementSize;
        return LuaObject::push(L,element,((uint8*)UD->array.GetData())+i*es);
    }

    int LuaArray::Add(lua_State* L) {
        CheckUD(LuaArray,L,1);
        // get element property
        UProperty* element = UD->prop->Inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {
            FScriptArrayHelper ArrayHelper(UD->prop, &UD->array);
		    int NewIndex = ArrayHelper.AddValue();
            checker(L,element,ArrayHelper.GetRawPtr(NewIndex),2);
            // return num of array
            return LuaObject::push(L,UD->array.Num());
        }
        else {
            FString tn = element->GetClass()->GetName();
            luaL_error(L,"unsupport param type %s to add",TCHAR_TO_UTF8(*tn));
            return 0;
        }
    }

    int LuaArray::Insert(lua_State* L) {
        CheckUD(LuaArray,L,1);
        int index = LuaObject::checkValue<int>(L,2);
        
        // get element property
        UProperty* element = UD->prop->Inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {
            FScriptArrayHelper ArrayHelper(UD->prop, &UD->array);

            if(index<0 || index>ArrayHelper.Num())
                luaL_error(L,"Array insert index %d out of range",index);

            ArrayHelper.InsertValues(index);
            checker(L,element,ArrayHelper.GetRawPtr(index),3);
            // return num of array
            return LuaObject::push(L,UD->array.Num());
        }
        else {
            FString tn = element->GetClass()->GetName();
            luaL_error(L,"unsupport param type %s to add",TCHAR_TO_UTF8(*tn));
            return 0;
        }
    }

    int LuaArray::Remove(lua_State* L) {
        CheckUD(LuaArray,L,1);
        int index = LuaObject::checkValue<int>(L,2);
        FScriptArrayHelper ArrayHelper(UD->prop, &UD->array);
        if(index>=0 && index<ArrayHelper.Num())
            ArrayHelper.RemoveValues(index);
        else
            luaL_error(L,"Array remove index %d out of range",index);
		return 0;
    }

    int LuaArray::Clear(lua_State* L) {
        CheckUD(LuaArray,L,1);
        FScriptArrayHelper ArrayHelper(UD->prop, &UD->array);
        ArrayHelper.EmptyValues();
		return 0;
    }

    int LuaArray::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,Num);
        RegMetaMethod(L,Get);
        RegMetaMethod(L,Add);
        RegMetaMethod(L,Insert);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);
        return 0;
    }

    int LuaArray::gc(lua_State* L) {
        CheckUD(LuaArray,L,1);
        delete UD;
        return 0;   
    }
}