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
#include "LuaNetSerialization.h"

namespace NS_SLUA {

    DefTypeName(LuaArray::Enumerator); 

    void LuaArray::reg(lua_State* L) {
        SluaUtil::reg(L,"Array",__ctor);
    }

    void LuaArray::clone(FScriptArray* destArray, FArrayProperty* arrayP, const FScriptArray* srcArray) {
        // blueprint stack will destroy the TArray
        // so deep-copy construct FScriptArray
        // it's very expensive
        if(!srcArray)
            return;

        arrayP->CopyCompleteValue(destArray, srcArray);
    }

    void LuaArray::clone(FScriptArray* destArray, FProperty* p, const FScriptArray* srcArray) {
        // blueprint stack will destroy the TArray
        // so deep-copy construct FScriptArray
        // it's very expensive
        if(!srcArray)
            return;
            
        FScriptArrayHelper helper = FScriptArrayHelper::CreateHelperFormInnerProperty(p, destArray);
        if (srcArray->Num() == 0) {
            helper.EmptyValues();
            return;
        }
        helper.Resize(srcArray->Num());
        uint8* dest = helper.GetRawPtr();
        uint8* src = (uint8*)srcArray->GetData();
        for(int n=0;n<srcArray->Num();n++) {
            p->CopySingleValue(dest,src);
            dest+=p->ElementSize;
            src+=p->ElementSize;
        }
    }

    LuaArray::LuaArray(FProperty* p, FScriptArray* buf, bool bIsRef, bool bIsNewInner)
        : inner(p)
        , isRef(bIsRef)
        , isNewInner(bIsNewInner)
        , proxy(nullptr)
        , luaReplicatedIndex(InvalidReplicatedIndex)
    {
        if (isRef)
        {
            array = buf;
        }
        else
        {
            array = new FScriptArray();
            clone(array, p, buf);
        }
    }

    LuaArray::LuaArray(FArrayProperty* arrayProp, FScriptArray* buf, bool bIsRef, FLuaNetSerializationProxy* netProxy, uint16 replicatedIndex)
        : inner(arrayProp->Inner)
        , array(buf)
        , isRef(bIsRef)
        , isNewInner(false)
        , proxy(netProxy)
        , luaReplicatedIndex(replicatedIndex)
    {
        if (isRef)
        {
            array = buf;
        }
        else
        {
            array = new FScriptArray();
            clone(array, arrayProp, buf);
        }
    }

    LuaArray::~LuaArray() {
        if (!isRef)
        {
            // should destroy inner property value
            clear();
            ensure(array);
            SafeDelete(array);
        }

        if (isNewInner)
        {
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
            delete inner;
#endif
        }

        inner = nullptr;
    }

    bool LuaArray::markDirty(LuaArray* luaArray)
    {
        auto proxy = luaArray->proxy;
        if (proxy)
        {
            proxy->dirtyMark.Add(luaArray->luaReplicatedIndex);
            proxy->assignTimes++;
            return true;
        }

        return false;
    }

    void LuaArray::clear() {
        if(!inner) return;

        if (!isRef) {
            uint8 *Dest = getRawPtr(0);
            for (int32 i = 0; i < array->Num(); i++, Dest += inner->ElementSize)
            {
                inner->DestroyValue(Dest);
            }
        }
#if ENGINE_MAJOR_VERSION==5
        array->Empty(0, inner->ElementSize, GetPropertyAlignment(inner));
#else
        array->Empty(0, inner->ElementSize);
#endif
    }

    void LuaArray::AddReferencedObjects( FReferenceCollector& Collector )
    {
        if (inner) {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            Collector.AddReferencedObject(inner);
#else
            inner->AddReferencedObjects(Collector);
#endif
        }

        // if empty or owner object had been collected
        // AddReferencedObject will auto null propObj
        if ((isRef) || num() == 0 || !inner) return;

        if (!LuaReference::isRefProperty(inner)) {
            return;
        }

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
#if ENGINE_MAJOR_VERSION==5
        const int index = array->Add(1, inner->ElementSize, GetPropertyAlignment(inner));
#else
        const int index = array->Add(1, inner->ElementSize);
#endif
        
        constructItems(index, 1);
        return getRawPtr(index);
    }

    uint8* LuaArray::insert(int index) {
#if ENGINE_MAJOR_VERSION==5
        array->Insert(index, 1, inner->ElementSize, GetPropertyAlignment(inner));
#else
        array->Insert(index, 1, inner->ElementSize);
#endif
        
        constructItems(index, 1);
        return getRawPtr(index);
    }

    void LuaArray::remove(int index) {
        destructItems(index, 1);
#if ENGINE_MAJOR_VERSION==5
        array->Remove(index, 1, inner->ElementSize, GetPropertyAlignment(inner));
#else
        array->Remove(index, 1, inner->ElementSize);
#endif  
    }

    void LuaArray::destructItems(int index,int count) {
        // if array is owned by uobject, don't destructItems
        if(isRef) return;
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

    int LuaArray::push(lua_State* L,FProperty* inner,FScriptArray* data, bool bIsNewInner) {
        if (inner->GetClass() == FByteProperty::StaticClass())
        {
            char* dest = (char*)data->GetData();
            int32 len = data->Num();
            lua_pushlstring(L, dest, (size_t)len);
            return 1;
        }

        LuaArray* luaArrray = new LuaArray(inner, data, false, bIsNewInner);
        LuaObject::addLink(L, luaArrray->get());
        return LuaObject::pushType(L,luaArrray,"LuaArray",setupMT,gc);
    }

    int LuaArray::push(lua_State* L, FArrayProperty* prop, FScriptArray* data) {
        if (prop->Inner->GetClass() == FByteProperty::StaticClass())
        {
            char* dest = (char*)data->GetData();
            int32 len = data->Num();
            lua_pushlstring(L, dest, (size_t)len);
            return 1;
        }

        LuaArray* luaArrray = new LuaArray(prop, data, false, nullptr, 0);
        LuaObject::addLink(L, luaArrray->get());
        return LuaObject::pushType(L,luaArrray,"LuaArray",setupMT,gc);
    }

    int LuaArray::push(lua_State* L, LuaArray* luaArray)
    {
        return LuaObject::pushType(L,luaArray,"LuaArray",setupMT,gc);
    }

    int LuaArray::__ctor(lua_State* L) {
        auto type = (EPropertyClass) LuaObject::checkValue<int>(L,1);
        auto array = FScriptArray();
        if (type == EPropertyClass::Object)
        {
            auto cls = LuaObject::checkValueOpt<UClass*>(L, 2, nullptr);
            if (!cls)
                luaL_error(L, "Array of UObject should have second parameter is UClass");
            return push(L, PropertyProto::createProperty(PropertyProto(type, cls)), &array, true);
        }
        else if (type == EPropertyClass::Struct)
        {
            auto scriptStruct = LuaObject::checkValueOpt<UScriptStruct*>(L, 2, nullptr);
            if (!scriptStruct)
                luaL_error(L, "Array of UStruct should have second parameter is UStruct");
            return push(L, PropertyProto::createProperty(PropertyProto(type, scriptStruct)), &array, true);
        }
        return push(L, PropertyProto::createProperty(PropertyProto(type)), &array, true);
    }

    int LuaArray::Num(lua_State* L) {
        CheckUD(LuaArray, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        return LuaObject::push(L,UD->num());
    }

    int LuaArray::Get(lua_State* L) {
        CheckUD(LuaArray, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
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
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        int index = LuaObject::checkValue<int>(L, 2);
        FProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if (checker) {
            if (!UD->isValidIndex(index))
                luaL_error(L, "Array set index %d out of range", index);
            checker(L, element, UD->getRawPtr(index), 3, true);
        }
        else {
            FString tn = element->GetClass()->GetName();
            luaL_error(L, "unsupport param type %s to set", TCHAR_TO_UTF8(*tn));
            return 0;
        }

        markDirty(UD);
        return 0;
    }

    int LuaArray::Add(lua_State* L) {
        CheckUD(LuaArray,L,1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        // get element property
        FProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {
            checker(L,element,UD->add(),2,true);

            markDirty(UD);

            // return num of array
            return LuaObject::push(L,UD->array->Num());
        }
        else {
            FString tn = element->GetClass()->GetName();
            luaL_error(L,"unsupport param type %s to add",TCHAR_TO_UTF8(*tn));
            return 0;
        }
    }

    int LuaArray::AddUnique(lua_State* L) {
        CheckUD(LuaArray,L,1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        // get element property
        FProperty* element = UD->inner;
        uint8* newElement = UD->add();
        auto checker = LuaObject::getChecker(element);
        if(checker) {
	        checker(L,element,newElement,2,true);

            markDirty(UD);

            int32 num = UD->array->Num();
            for (int i = 0; i < num - 1; ++i) {
                if (element->Identical(newElement, UD->getRawPtr(i))) {
                    UD->remove(num - 1);
                    return LuaObject::push(L, i);
                }
            }
            return LuaObject::push(L, num);
        }
        else {
            FString tn = element->GetClass()->GetName();
            luaL_error(L,"unsupport param type %s to add unique",TCHAR_TO_UTF8(*tn));
            return 0;
        }
    }

    int LuaArray::Insert(lua_State* L) {
        CheckUD(LuaArray,L,1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        int index = LuaObject::checkValue<int>(L,2);
        
        // get element property
        FProperty* element = UD->inner;
        auto checker = LuaObject::getChecker(element);
        if(checker) {

            if(!UD->isValidIndex(index))
                luaL_error(L,"Array insert index %d out of range",index);

            checker(L,element,UD->insert(index),3,true);

            markDirty(UD);

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
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        int index = LuaObject::checkValue<int>(L,2);
        if(UD->isValidIndex(index))
        {
            UD->remove(index);
            markDirty(UD);
        }
        else
            luaL_error(L,"Array remove index %d out of range",index);
        return 0;
    }

    int LuaArray::Clear(lua_State* L) {
        CheckUD(LuaArray,L,1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        UD->clear();

        markDirty(UD);
        return 0;
    }

    int LuaArray::Pairs(lua_State* L) {
        CheckUD(LuaArray, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        auto iter = new LuaArray::Enumerator();
        
        iter->arr = UD;
        iter->index = 0;
        lua_pushcfunction(L, LuaArray::Enumerable);
        LuaObject::pushType(L, iter, "LuaArray::Enumerator", nullptr, LuaArray::Enumerator::gc, 1);
        // hold referrence of LuaArray, avoid gc
        lua_pushvalue(L, 1);
        lua_setuservalue(L,3);
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

    int LuaArray::CreateValueTypeObject(lua_State* L) {
        CheckUD(LuaArray, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaArray, but got nil!");
        }
        FFieldClass* uclass = UD->inner->GetClass();
        if (uclass) {
            FDefaultConstructedPropertyElement tempValue(UD->inner);
            auto valuePtr = tempValue.GetObjAddress();
            if (valuePtr) {
                return LuaObject::push(L, UD->inner, (uint8*)valuePtr);
            }
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
        RegMetaMethod(L,AddUnique);
        RegMetaMethod(L,Insert);
        RegMetaMethod(L,Remove);
        RegMetaMethod(L,Clear);
        RegMetaMethod(L,CreateValueTypeObject);

        RegMetaMethodByName(L, "__pairs", Pairs);

        return 0;
    }

    int LuaArray::gc(lua_State* L) {
        auto userdata = (UserData<LuaArray*>*)luaL_testudata(L, 1, "LuaArray");
        auto self = userdata->ud;
        if (!userdata->parent && !(userdata->flag & UD_HADFREE)) {
            LuaObject::releaseLink(L, self->get());
        }
        if (self->isRef) {
            LuaObject::unlinkProp(L, userdata);
        }
        
        delete userdata->ud;
        return 0;
    }

    int LuaArray::Enumerator::gc(lua_State* L) {
        CheckUD(LuaArray::Enumerator, L, 1);
        delete UD;
        return 0;
    }
}