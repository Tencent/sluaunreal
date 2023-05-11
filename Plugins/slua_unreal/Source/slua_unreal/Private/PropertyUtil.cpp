// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "PropertyUtil.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UnrealType.h"
#if ENGINE_MAJOR_VERSION==5
#include "UObject/UnrealTypePrivate.h"
#endif

namespace NS_SLUA {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
    UObject* getPropertyOutter() {
        static TStrongObjectPtr<UStruct> propOuter;
        if (!propOuter.IsValid()) propOuter.Reset(NewObject<UStruct>((UObject*)GetTransientPackage()));
        return propOuter.Get();
    }

    FProperty* PropertyProto::createProperty(const PropertyProto& proto, UObject* outer, FName propName) {
        FProperty* p = nullptr;
        if (!outer)
        {
            outer = getPropertyOutter();
        }

        switch (proto.type) {
        case EPropertyClass::Byte:
            p = NewObject<FProperty>(outer, UByteProperty::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int8:
            p = NewObject<FProperty>(outer, UInt8Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int16:
            p = NewObject<FProperty>(outer, UInt16Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int:
            p = NewObject<FProperty>(outer, UIntProperty::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int64:
            p = NewObject<FProperty>(outer, UInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UInt16:
            p = NewObject<FProperty>(outer, UUInt16Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UInt32:
            p = NewObject<FProperty>(outer, UUInt32Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UInt64:
            p = NewObject<FProperty>(outer, UUInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UnsizedInt:
            p = NewObject<FProperty>(outer, UUInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UnsizedUInt:
            p = NewObject<FProperty>(outer, UUInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Float:
            p = NewObject<FProperty>(outer, UFloatProperty::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Double:
            p = NewObject<FProperty>(outer, UDoubleProperty::StaticClass(), propName);
            break;
        case EPropertyClass::Bool:
            p = NewObject<FProperty>(outer, UBoolProperty::StaticClass(), propName);
            break;
        case EPropertyClass::Str:
            p = NewObject<FProperty>(outer, UStrProperty::StaticClass());
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Object: {
            auto op = NewObject<UObjectProperty>(outer, UObjectProperty::StaticClass(), propName);
            op->SetPropertyClass(proto.cls);
            op->SetPropertyFlags(CPF_HasGetValueTypeHash);
            p = op;
            break;
        }
        case EPropertyClass::Struct: {
            auto sp = NewObject<UStructProperty>(outer, UStructProperty::StaticClass(), propName);
            UScriptStruct* scriptStruct = proto.scriptStruct;
            if (sp && scriptStruct)
            {
                sp->Struct = scriptStruct;
                if (scriptStruct->StructFlags & STRUCT_HasInstancedReference)
                {
                    sp->SetPropertyFlags(CPF_ContainsInstancedReference);
                }

                if (PropertyProto::structHasGetTypeHash(scriptStruct))
                {
                    sp->SetPropertyFlags(CPF_HasGetValueTypeHash);
                }
            }
            p = sp;
            break;
        }
        case EPropertyClass::Array: {
            auto arrayProperty = NewObject<UArrayProperty>(outer, UArrayProperty::StaticClass(), propName);
            FProperty* subProperty;
            if (proto.cls)
            {
                subProperty = createProperty(PropertyProto(EPropertyClass::Object, proto.cls), arrayProperty, NAME_None);
            }
            else if (proto.scriptStruct)
            {
                subProperty = createProperty(PropertyProto(EPropertyClass::Struct, proto.scriptStruct), arrayProperty, NAME_None);
            }
            else
            {
                subProperty = createProperty(PropertyProto(proto.subType), arrayProperty, NAME_None);
            }

            if (arrayProperty)
            {
                if (subProperty)
                {
                    if (subProperty->HasAnyPropertyFlags(CPF_ContainsInstancedReference))
                    {
                        arrayProperty->SetPropertyFlags(CPF_ContainsInstancedReference);
                    }

                    arrayProperty->Inner = subProperty;
                    p = arrayProperty;
                }
                else
                {
                    arrayProperty->MarkPendingKill();
                }
            }

            break;
        }
        default:
            break;
        }

        if (p) {
            FArchive ar;
            p->LinkWithoutChangingOffset(ar);
        }

        return p;
    }

    bool PropertyProto::structHasGetTypeHash(const UScriptStruct* structType)
    {
        if (structType->IsNative())
        {
            return structType->GetCppStructOps() && structType->GetCppStructOps()->HasGetTypeHash();
        }
        else
        {
            // if every member can be hashed (or is a UBoolProperty, which is specially 
            // handled by UScriptStruct::GetStructTypeHash) then we can hash the struct:
            for (TFieldIterator<FProperty> It(structType); It; ++It)
            {
                if (Cast<UBoolProperty>(*It))
                {
                    continue;
                }
                else
                {
                    if (!(*It)->HasAllPropertyFlags(CPF_HasGetValueTypeHash))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
#else
    const FName DefaultLuaPropertyName = "TransientLuaProperty";

    FFieldVariant* getPropertyOutter() {
        static FFieldVariant* FieldVar = nullptr;
        if (!FieldVar)
        {
            static TStrongObjectPtr<UStruct> propOuter;
            if (!propOuter.IsValid()) propOuter.Reset(NewObject<UStruct>((UObject*)GetTransientPackage()));
            FieldVar = new FFieldVariant(propOuter.Get());
        }
        return FieldVar;
    }

    template<typename FP = FProperty>
    FP* newProperty(const FFieldVariant* owner, FFieldClass* cls, FName propName)
    {
        FP* prop = CastField<FP>(cls->Construct(*owner, propName == NAME_None ? DefaultLuaPropertyName : propName, RF_NoFlags));
        if (prop)
        {
            prop->ArrayDim = 1;
            return prop;
        }
        return nullptr;
    }

    FProperty* PropertyProto::createProperty(const PropertyProto& proto, const UObject* owner, FName propName) {
        if (owner)
        {
            return createProperty(proto, FFieldVariant(owner), propName);
        }
        return createProperty(proto, static_cast<const FFieldVariant*>(nullptr), propName);
    }

    FProperty* PropertyProto::createProperty(const PropertyProto& p, const FFieldVariant& owner, FName propName) {
        return createProperty(p, &owner, propName);
    }

    FProperty* PropertyProto::createProperty(const PropertyProto& proto, const FFieldVariant* owner, FName propName) {
        FProperty* p = nullptr;
        if (!owner)
        {
            owner = getPropertyOutter();
        }
        switch (proto.type) {
        case EPropertyClass::Byte:
            p = newProperty(owner, FByteProperty::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int8:
            p = newProperty(owner, FInt8Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int16:
            p = newProperty(owner, FInt16Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int:
            p = newProperty(owner, FIntProperty::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Int64:
            p = newProperty(owner, FInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UInt16:
            p = newProperty(owner, FUInt16Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UInt32:
            p = newProperty(owner, FUInt32Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UInt64:
            p = newProperty(owner, FUInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UnsizedInt:
            p = newProperty(owner, FUInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::UnsizedUInt:
            p = newProperty(owner, FUInt64Property::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Float:
            p = newProperty(owner, FFloatProperty::StaticClass(), propName);
            p->SetPropertyFlags(CPF_HasGetValueTypeHash);
            break;
        case EPropertyClass::Double:
            p = newProperty(owner, FDoubleProperty::StaticClass(), propName);
            break;
        case EPropertyClass::Bool: {
            auto op = newProperty<FBoolProperty>(owner, FBoolProperty::StaticClass(), propName);
            op->SetBoolSize(sizeof(bool), true);
            p = op;
            break;
        }
        case EPropertyClass::Str:
            p = newProperty(owner, FStrProperty::StaticClass(), propName);
            break;
        case EPropertyClass::Object: {
            auto op = newProperty<FObjectPropertyBase>(owner, FObjectProperty::StaticClass(), propName);
            op->SetPropertyClass(proto.cls);
            p = op;
            break;
        }
        case EPropertyClass::Struct: {
            auto sp = newProperty<FStructProperty>(owner, FStructProperty::StaticClass(), propName);
            UScriptStruct* scriptStruct = proto.scriptStruct;
            if (sp && scriptStruct)
            {
                sp->Struct = scriptStruct;
                if (scriptStruct->StructFlags & STRUCT_HasInstancedReference)
                {
                    sp->SetPropertyFlags(CPF_ContainsInstancedReference);
                }

                if (PropertyProto::structHasGetTypeHash(scriptStruct))
                {
                    sp->SetPropertyFlags(CPF_HasGetValueTypeHash);
                }
            }
            p = sp;
            break;
        }
        case EPropertyClass::Array: {
            auto arrayProperty = newProperty<FArrayProperty>(owner, FArrayProperty::StaticClass(), propName);
            const FFieldVariant subPropOwner = arrayProperty;
            FProperty* subProperty;
            if (proto.cls)
            {
                subProperty = createProperty(PropertyProto(EPropertyClass::Object, proto.cls), subPropOwner, NAME_None);
            }
            else if (proto.scriptStruct)
            {
                subProperty = createProperty(PropertyProto(EPropertyClass::Struct, proto.scriptStruct), subPropOwner, NAME_None);
            }
            else
            {
                subProperty = createProperty(PropertyProto(proto.subType), subPropOwner, NAME_None);
            }

            if (arrayProperty)
            {
                if (subProperty)
                {
                    if (subProperty->HasAnyPropertyFlags(CPF_ContainsInstancedReference))
                    {
                        arrayProperty->SetPropertyFlags(CPF_ContainsInstancedReference);
                    }

                    arrayProperty->Inner = subProperty;
                    p = arrayProperty;
                }
                else
                {
#if (ENGINE_MINOR_VERSION<19) && (ENGINE_MAJOR_VERSION==4)
                    arrayProperty->MarkPendingKill();
#endif
                }
            }

            break;
        }
        }
        if (p) {
            FArchive ar;
            p->LinkWithoutChangingOffset(ar);
        }

        return p;
    }

    bool PropertyProto::structHasGetTypeHash(const UScriptStruct* structType)
    {
        if (structType->IsNative())
        {
            return structType->GetCppStructOps() && structType->GetCppStructOps()->HasGetTypeHash();
        }
        else
        {
            // if every member can be hashed (or is a UBoolProperty, which is specially 
            // handled by UScriptStruct::GetStructTypeHash) then we can hash the struct:
            for (TFieldIterator<FProperty> It(structType); It; ++It)
            {
                if (CastField<FBoolProperty>(*It))
                {
                    continue;
                }
                else
                {
                    if (!(*It)->HasAllPropertyFlags(CPF_HasGetValueTypeHash))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
#endif
}
