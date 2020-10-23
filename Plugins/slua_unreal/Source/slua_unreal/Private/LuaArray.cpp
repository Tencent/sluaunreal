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
#include <string>
#include "SluaLib.h"
#include "LuaState.h"
#include "LuaReference.h"

namespace NS_SLUA {

    DefTypeName(LuaArray::Enumerator); 

    void LuaArray::reg(lua_State* L) {
        SluaUtil::reg(L,"Array",__ctor);
    }

    void LuaArray::clone(FScriptArray* destArray, FProperty* p, const FScriptArray* srcArray) {
        // blueprint stack will destroy the TArray
        // so deep-copy construct FScriptArray
        // it's very expensive
        if(!srcArray || srcArray->Num()==0)
            return;
            
        FScriptArrayHelper helper = FScriptArrayHelper::CreateHelperFormInnerProperty(p,destArray);
        helper.AddValues(srcArray->Num());
        uint8* dest = helper.GetRawPtr();
        uint8* src = (uint8*)srcArray->GetData();
        for(int n=0;n<srcArray->Num();n++) {
            p->CopySingleValue(dest,src);
            dest+=p->ElementSize;
            src+=p->ElementSize;
        }
    }

	LuaArray::LuaArray(FProperty* p, FScriptArray* buf)
		: inner(p)
		, prop(nullptr)
		, propObj(nullptr)
    {
		array = new FScriptArray();
		clone(array, p, buf);
		shouldFree = true;
    }

	LuaArray::LuaArray(FArrayProperty* p, UObject* obj)
		: inner(p->Inner)
		, prop(p)
		, propObj(obj)
	{
		array = prop->ContainerPtrToValuePtr<FScriptArray>(obj);
		shouldFree = false;
	}

    LuaArray::~LuaArray() {
		if (shouldFree)
		{
			// should destroy inner property value
			clear();
			ensure(array);
			SafeDelete(array);
		}
		
		propObj = nullptr;
    }

    void LuaArray::clear() {
        if(!inner) return;

		if (shouldFree) {
			uint8 *Dest = getRawPtr(0);
			for (int32 i = 0; i < array->Num(); i++, Dest += inner->ElementSize)
			{
				inner->DestroyValue(Dest);
			}
		}
        array->Empty(0, inner->ElementSize);
    }

    void LuaArray::AddReferencedObjects( FReferenceCollector& Collector )
    {
        if (inner) inner->AddReferencedObjects(Collector);
		if (prop) prop->AddReferencedObjects(Collector);
		if (propObj) Collector.AddReferencedObject(propObj);

        // if empty or owner object had been collected
		// AddReferencedObject will auto null propObj
        if((!shouldFree && !propObj) || num()==0) return;
		for (int n = num() - 1; n >= 0; n--) {
            void* ptr = getRawPtr(n);
			// if AddReferencedObject collect obj
			// we will auto remove it
			if (LuaReference::addRefByProperty(Collector, inner, ptr))
				remove(n);
        }
    }

    uint8* LuaArray::getRawPtr(int index) const {
        return (uint8*)array->GetData() + index * inner->ElementSize;
    }

    bool LuaArray::isValidIndex(int index) const {
        return index>=0 && index<num();
    }

    int LuaArray::num() const {
        return array->Num();
    }

    uint8* LuaArray::add() {
        const int index = array->Add(1, inner->ElementSize);
        constructItems(index, 1);
        return getRawPtr(index);
    }

    uint8* LuaArray::insert(int index) {
        array->Insert(index, 1, inner->ElementSize);
		constructItems(index, 1);
        return getRawPtr(index);
    }

    void LuaArray::remove(int index) {
        destructItems(index, 1);
		array->Remove(index, 1, inner->ElementSize);
    }

    void LuaArray::destructItems(int index,int count) {
        // if array is owned by uobject, don't destructItems
        if(!shouldFree) return;
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

    int LuaArray::push(lua_State* L,FProperty* inner,FScriptArray* data) {
        LuaArray* luaArrray = new LuaArray(inner,data);
		return LuaObject::pushType(L,luaArrray,"LuaArray",setupMT,gc);
    }

	int LuaArray::push(lua_State* L, FArrayProperty* prop, UObject* obj) {
		auto scriptArray = prop->ContainerPtrToValuePtr<FScriptArray>(obj);
		if (LuaObject::getObjCache(L, scriptArray, "LuaArray")) return 1;
		LuaArray* luaArray = new LuaArray(prop, obj);
		int r = LuaObject::pushType(L, luaArray, "LuaArray", setupMT, gc);
        if(r) LuaObject::cacheObj(L, luaArray->array);
        return 1;
	}

    int LuaArray::__ctor(lua_State* L) {
		auto type = (EPropertyClass) LuaObject::checkValue<int>(L,1);
		auto cls = LuaObject::checkValueOpt<UClass*>(L, 2, nullptr);
        if(type==EPropertyClass::Object && !cls)
            luaL_error(L,"Array of UObject should have second parameter is UClass");
		auto array = FScriptArray();
		return push(L, PropertyProto::createProperty({ type, cls }), &array);
    }

    int LuaArray::Num(lua_State* L) {
        CheckUD(LuaArray,L,1);
        return LuaObject::push(L,UD->num());
    }

    int LuaArray::Get(lua_State* L) {
        CheckUD(LuaArray,L,1);
        int i = LuaObject::checkValue<int>(L,2);
        FProperty* element = UD->inner;
		if (!UD->isValidIndex(i)) {
			luaL_error(L, "Array get index %d out of range", i);
			return 0;
		}
        return LuaObject::push(L,element,UD->getRawPtr(i));
    }


	int LuaArray::Set(lua_State* L)
	{
		CheckUD(LuaArray, L, 1);
		int index = LuaObject::checkValue<int>(L, 2);
		FProperty* element = UD->inner;
		auto checker = LuaObject::getChecker(element);
		if (checker) {
			if (!UD->isValidIndex(index))
				luaL_error(L, "Array set index %d out of range", index);
			checker(L, element, UD->getRawPtr(index), 3);
		}
		else {
			FString tn = element->GetClass()->GetName();
			luaL_error(L, "unsupport param type %s to set", TCHAR_TO_UTF8(*tn));
			return 0;
		}
		return 0;
	}

	int LuaArray::Add(lua_State* L) {
        CheckUD(LuaArray,L,1);
        // get element property
        FProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {
            checker(L,element,UD->add(),2);
            // return num of array
            return LuaObject::push(L,UD->array->Num());
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
        FProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {

            if(!UD->isValidIndex(index))
                luaL_error(L,"Array insert index %d out of range",index);

            checker(L,element,UD->insert(index),3);
            // return num of array
            return LuaObject::push(L,UD->array->Num());
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
		// hold LuaArray
		iter->holder = new LuaVar(L, 1);
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
			auto parms = ((uint8*)arr->array->GetData()) + UD->index * es;
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
		RegMetaMethod(L,Set);
        RegMetaMethod(L,Add);
        RegMetaMethod(L,Insert);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);

		RegMetaMethodByName(L, "__pairs", Pairs);

        return 0;
    }

    int LuaArray::gc(lua_State* L) {
        CheckUD(LuaArray,L,1);
		LuaObject::deleteFGCObject(L,UD);
        return 0;   
    }

	int LuaArray::Enumerator::gc(lua_State* L) {
		CheckUD(LuaArray::Enumerator, L, 1);
		delete UD;
		return 0;
	}

	LuaArray::Enumerator::~Enumerator()
	{
		SafeDelete(holder);
	}

}