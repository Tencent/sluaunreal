// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.
#pragma once

#include "SluaMicro.h"
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION<=4)
#include "UObject/WeakObjectPtr.h"
#else
#include "UObject/WeakFieldPtr.h"
#endif

#if !((ENGINE_MINOR_VERSION<22) && (ENGINE_MAJOR_VERSION==4))
#include "EPropertyClassUEnum.h"
#else
#include "EPropertyClass.h"
#endif

namespace NS_SLUA {

    template<typename T>
    struct DeduceType;

    // convert T to EPropertyClass
    #define DefDeduceType(A,B) \
    template<> struct DeduceType<A> { \
        static const EPropertyClass value = EPropertyClass::B; \
    };\
    
    DefDeduceType(uint8, Byte);
    DefDeduceType(int8, Int8);
    DefDeduceType(int16, Int16);
    DefDeduceType(int, Int);
    DefDeduceType(int64, Int64);
    DefDeduceType(uint16, UInt16);
    DefDeduceType(uint32, UInt32);
    DefDeduceType(uint64, UInt64);
    DefDeduceType(float, Float);
    DefDeduceType(double, Double);
    DefDeduceType(bool, Bool);
    DefDeduceType(UObject*, Object);
    DefDeduceType(FString, Str);

#if ENGINE_MAJOR_VERSION==5
    FORCEINLINE int32 GetPropertyAlignment(FProperty* InProperty)
    {
        return InProperty->GetMinAlignment();
    }
#endif

    // definition of property
    struct SLUA_UNREAL_API PropertyProto {
        PropertyProto(EPropertyClass t) :type(t), subType(EPropertyClass::Byte), cls(nullptr), scriptStruct(nullptr)
        {
            if (type == EPropertyClass::Object)
            {
                cls = UObject::StaticClass();
            }
        }
        PropertyProto(EPropertyClass t, UClass* c) :type(t), subType(EPropertyClass::Byte), cls(c), scriptStruct(nullptr)
        {
            if (type == EPropertyClass::Object && cls == nullptr)
            {
                cls = UObject::StaticClass();
            }
        }
        PropertyProto(EPropertyClass t, UScriptStruct* st) :type(t), subType(EPropertyClass::Byte), cls(nullptr), scriptStruct(st) {}
        PropertyProto(EPropertyClass t, EPropertyClass InSubType) :type(t), subType(InSubType), cls(nullptr), scriptStruct(nullptr) {}
        template<typename T>
        static PropertyProto get() {
            return PropertyProto(DeduceType<T>::value);
        }

        template<typename T>
        static FProperty* createDeduceProperty() {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            static TWeakObjectPtr<FProperty> CacheProperty[(int)EPropertyClass::Enum + 1];
#else
            static TWeakFieldPtr<FProperty> CacheProperty[(int)EPropertyClass::Enum + 1];
#endif
            auto propertyClass = DeduceType<T>::value;
            FProperty* prop = CacheProperty[(int)propertyClass].Get();
            if (!prop)
            {
                prop = createProperty(PropertyProto(propertyClass));
                CacheProperty[(int)propertyClass] = prop;
            }
            return prop;
        }

        EPropertyClass type;
        EPropertyClass subType;
        UClass* cls;
        UScriptStruct* scriptStruct;
        // create FProperty by PropertyProto
        // returned FProperty should be collect by yourself
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
        static FProperty* createProperty(const PropertyProto& p, UObject* owner = nullptr, FName propName = NAME_None);
#else
        static FProperty* createProperty(const PropertyProto& p, const FFieldVariant* owner, FName propName);
        static FProperty* createProperty(const PropertyProto& p, const FFieldVariant& owner, FName propName);
        static FProperty* createProperty(const PropertyProto& p, const UObject* owner = nullptr, FName propName = NAME_None);
#endif
        static bool structHasGetTypeHash(const UScriptStruct* StructType);
    };
}
