// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaReference.h"
#include "UObject/UnrealType.h"

namespace NS_SLUA {
    namespace LuaReference {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        const uint64 StructPropertyFlag = FStructProperty::StaticClassCastFlags();
        const uint64 RefPropertyFlag = FObjectProperty::StaticClassCastFlags()
                                        | FArrayProperty::StaticClassCastFlags()
                                        | FStructProperty::StaticClassCastFlags()
                                        | FMapProperty::StaticClassCastFlags()
                                        | FSetProperty::StaticClassCastFlags();
#else
        const uint64 StructPropertyFlag = FStructProperty::StaticClassCastFlagsPrivate();
        const uint64 RefPropertyFlag = FObjectProperty::StaticClassCastFlagsPrivate()
                                        | FArrayProperty::StaticClassCastFlagsPrivate()
                                        | FStructProperty::StaticClassCastFlagsPrivate()
                                        | FMapProperty::StaticClassCastFlagsPrivate()
                                        | FSetProperty::StaticClassCastFlagsPrivate();
#endif
        bool isRefProperty(const FProperty* prop) {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            auto castFlags = prop->GetClass()->ClassCastFlags;
#else
            auto castFlags = prop->GetCastFlags();
#endif
            if (!!(castFlags & StructPropertyFlag)) {
                if (auto structProp = CastField<FStructProperty>(prop)) {
                    auto scriptStruct = structProp->Struct;
                    if (scriptStruct && (scriptStruct->StructFlags & STRUCT_IsPlainOldData))
                        return false;
                }
            }
            return !!(castFlags & RefPropertyFlag);
        }

        void addRefByStruct(FReferenceCollector& collector, UStruct* us, void* base) {
            for (TFieldIterator<const FProperty> it(us); it; ++it)
            {
                auto prop = *it;
                if (isRefProperty(prop))
                {
                    addRefByProperty(collector, *it, prop->ContainerPtrToValuePtr<void>(base));
                }
            }
        }

        bool addRef(const FSetProperty* p, void* base, FReferenceCollector& collector)
        {
            if (!isRefProperty(p->ElementProp))
                return false;
            
            bool ret = false;
            for (int32 n = 0; n < p->ArrayDim; ++n)
            {
                bool valuesChanged = false;
                FScriptSetHelper helper(p, (uint8*)base + n * p->ElementSize);

                for (int32 index = 0; index < helper.GetMaxIndex(); ++index)
                {
                    if (helper.IsValidIndex(index))
                    {
                        valuesChanged |= addRefByProperty(collector,
                            helper.GetElementProperty(), helper.GetElementPtr(index));
                    }
                }

                if (valuesChanged)
                {
                    ret = true;
                    helper.Rehash();
                }
            }
            return ret;
        }

        bool addRef(const FMapProperty* p, void* base, FReferenceCollector& collector)
        {
            if (!isRefProperty(p->KeyProp) && !isRefProperty(p->ValueProp))
                return false;
            
            bool ret = false;
            for (int n = 0; n < p->ArrayDim; ++n)
            {
                bool keyChanged = false;
                bool valuesChanged = false;
                FScriptMapHelper helper(p, (uint8*)base + n * p->ElementSize);

                for (int index = 0; index < helper.GetMaxIndex(); ++index)
                {
                    if (helper.IsValidIndex(index))
                    {
                        keyChanged |= addRefByProperty(collector, helper.GetKeyProperty(), helper.GetKeyPtr(index));
                        valuesChanged |= addRefByProperty(collector, helper.GetValueProperty(), helper.GetValuePtr(index));
                    }
                }

                if (keyChanged || valuesChanged)
                {
                    ret = true;
                    if (keyChanged)
                    {
                        helper.Rehash();
                    }
                }
            }
            return ret;
        }

        bool addRef(const FObjectProperty* p, void* base, FReferenceCollector &collector)
        {
            bool ret = false;
            for (int n = 0; n < p->ArrayDim; ++n)
            {
                UObject* obj = p->GetObjectPropertyValue(base);
                if (obj && obj->IsValidLowLevel())
                {
                    UObject* newobj = obj;
                    collector.AddReferencedObject(newobj);

                    if (newobj != obj)
                    {
                        ret = true;
                        p->SetObjectPropertyValue(base, newobj);
                    }
                }
            }
            return ret;
        }

        bool addRef(const FArrayProperty* p, void* base, FReferenceCollector& collector)
        {
            if (!isRefProperty(p->Inner))
                return false;
            
            bool ret = false;
            for (int n = 0; n < p->ArrayDim; ++n)
            {
                FScriptArrayHelper helper(p, (uint8*)base + n * p->ElementSize);
                for (int32 index = 0; index < helper.Num(); ++index)
                {
                    ret |= addRefByProperty(collector, p->Inner, helper.GetRawPtr(index));
                }
            }
            return ret;
        }

        bool addRef(const FStructProperty* p, void* base, FReferenceCollector& collector)
        {
            if (!isRefProperty(p))
                return false;

            addRefByStruct(collector, p->Struct, base);
            return false;
        }

        bool addRefByProperty(FReferenceCollector& collector, const FProperty* prop, void* base) {
            if (auto p = CastField<FStructProperty>(prop)) {
                return addRef(p, base, collector);
            }
            if (auto p = CastField<FArrayProperty>(prop))
            {
                return addRef(p, base, collector);
            }
            if (auto p = CastField<FObjectProperty>(prop)) {
                return addRef(p, base, collector);
            }
            if (auto p = CastField<FMapProperty>(prop))
            {
                return addRef(p, base, collector);
            }
            if (auto p = CastField<FSetProperty>(prop))
            {
                return addRef(p, base, collector);
            }
            return false;
        }
    }
}
