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
#include "SluaLib.h"

namespace slua {

    DefTypeName(LuaArray::Enumerator);
    

    void LuaArray::reg(lua_State* L) {
        SluaUtil::reg(L,"Array",__ctor);
    }

    LuaArray::LuaArray(UProperty* prop,FScriptArray* buf)
        :inner(prop) 
    {
        // why FScriptArray can't be copy constructed or MoveToEmpty?
        // just hack it, TODO deepcopy?
        if(buf) FMemory::Memcpy(&array,buf,sizeof(FScriptArray));
    }

    LuaArray::~LuaArray() {
        // should destroy inner property value
        clear();
    }

    void LuaArray::clear() {
        uint8 *Dest = getRawPtr(0);
        for (int32 i = 0 ; i < array.Num(); i++, Dest += inner->ElementSize)
        {
            inner->DestroyValue(Dest);
        }
        array.Empty(0, inner->ElementSize);
    }

    uint8* LuaArray::getRawPtr(int index) const {
        return (uint8*)array.GetData() + index * inner->ElementSize;
    }

    bool LuaArray::isValidIndex(int index) const {
        return index>=0 && index<num();
    }

    int LuaArray::num() const {
        return array.Num();
    }

    uint8* LuaArray::add() {
        const int index = array.Add(1, inner->ElementSize);
        constructItems(index, 1);
        return getRawPtr(index);
    }

    uint8* LuaArray::insert(int index) {
        array.Insert(index, 1, inner->ElementSize);
		constructItems(index, 1);
        return getRawPtr(index);
    }

    void LuaArray::remove(int index) {
        destructItems(index, 1);
		array.Remove(index, 1, inner->ElementSize);
    }

    void LuaArray::destructItems(int index,int count) {
        if (!(inner->PropertyFlags & (CPF_IsPlainOldData | CPF_NoDestructor)))
		{
			uint8 *Dest = getRawPtr(index);
			for (int32 i = 0 ; i < count; i++, Dest += inner->ElementSize)
			{
				inner->DestroyValue(Dest);
			}
		}
    }

    void LuaArray::constructItems(int index,int count) {
        uint8 *Dest = getRawPtr(index);
		if (inner->PropertyFlags & CPF_ZeroConstructor)
		{
			FMemory::Memzero(Dest, count * inner->ElementSize);
		}
		else
		{
			for (int32 i = 0 ; i < count; i++, Dest += inner->ElementSize)
			{
				inner->InitializeValue(Dest);
			}
		}
    }

    int LuaArray::push(lua_State* L,UProperty* inner,FScriptArray* data) {
        LuaArray* array = new LuaArray(inner,data);
        return LuaObject::pushType(L,array,"LuaArray",setupMT,gc);
    }

    template<typename T>
    int createArray(lua_State* L) {
        return LuaArray::push(L,Cast<UProperty>(T::StaticClass()->GetDefaultObject()),nullptr);
    }

    int LuaArray::__ctor(lua_State* L) {
		auto type = (UE4CodeGen_Private::EPropertyClass) LuaObject::checkValue<int>(L,1);
		auto array = FScriptArray();
		return push(L, LuaObject::getDefaultProperty(L, type), &array);
    }

    int LuaArray::Num(lua_State* L) {
        CheckUD(LuaArray,L,1);
        return LuaObject::push(L,UD->array.Num());
    }

    int LuaArray::Get(lua_State* L) {
        CheckUD(LuaArray,L,1);
        int i = LuaObject::checkValue<int>(L,2);
        UProperty* element = UD->inner;
        int32 es = element->ElementSize;
        return LuaObject::push(L,element,((uint8*)UD->array.GetData())+i*es);
    }

    int LuaArray::Add(lua_State* L) {
        CheckUD(LuaArray,L,1);
        // get element property
        UProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {
            checker(L,element,UD->add(),2);
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
        UProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {

            if(!UD->isValidIndex(index))
                luaL_error(L,"Array insert index %d out of range",index);

            checker(L,element,UD->insert(index),3);
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
        if(UD->isValidIndex(index))
            UD->remove(index);
        else
            luaL_error(L,"Array remove index %d out of range",index);
		return 0;
    }

    int LuaArray::Clear(lua_State* L) {
        CheckUD(LuaArray,L,1);
        UD->clear();
		return 0;
    }

	int LuaArray::Pairs(lua_State* L) {
		CheckUD(LuaArray, L, 1);
		auto iter = new LuaArray::Enumerator();
		iter->arr = UD;
		iter->index = 0;
		lua_pushcfunction(L, LuaArray::Enumerable);
		LuaObject::pushType(L, iter, "LuaArray::Enumerator", nullptr, LuaArray::Enumerator::gc);
		LuaObject::pushNil(L);
		return 3;
	}

	int LuaArray::Enumerable(lua_State* L) {
		CheckUD(LuaArray::Enumerator, L, 1);
		auto arr = UD->arr;
		if (arr->isValidIndex(UD->index)) {
			auto element = arr->inner;
			auto es = element->ElementSize;
			auto parms = ((uint8*)arr->array.GetData()) + UD->index * es;
			LuaObject::push(L, UD->index);
			LuaObject::push(L, element, parms);
			UD->index += 1;
			return 2;
		} 
		return 0;
	}

    int LuaArray::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

		RegMetaMethod(L,Pairs);
        RegMetaMethod(L,Num);
        RegMetaMethod(L,Get);
        RegMetaMethod(L,Add);
        RegMetaMethod(L,Insert);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);

		RegMetaMethodByName(L, "__pairs", Pairs);

        return 0;
    }

    int LuaArray::gc(lua_State* L) {
        CheckUD(LuaArray,L,1);
        delete UD;
        return 0;   
    }

	int LuaArray::Enumerator::gc(lua_State* L) {
		CheckUD(LuaArray::Enumerator, L, 1);
		delete UD;
		return 0;
	}

}