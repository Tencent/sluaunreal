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

namespace NS_SLUA {

	const FName DefaultLuaPropertyName = "TransientLuaProperty";

    UObject* getPropertyOutter() {
		static TStrongObjectPtr<UStruct> propOuter;
		if (!propOuter.IsValid()) propOuter.Reset(NewObject<UStruct>((UObject*)GetTransientPackage()));
		return propOuter.Get();
	}

	template<typename FP = FProperty>
	FP* newProperty(UObject* outter, FFieldClass* cls)
    {
		FP* prop = CastFieldChecked<FP>(cls->Construct(outter, DefaultLuaPropertyName, RF_NoFlags));
    	if(prop)
    	{
			prop->ArrayDim = 1;
			return prop;
    	}
		return nullptr;
    }

    FProperty* PropertyProto::createProperty(const PropertyProto& proto) {
		FProperty* p = nullptr;
		UObject* outer = getPropertyOutter();
		switch (proto.type) {
			case EPropertyClass::Byte:
				p = newProperty(outer, FByteProperty::StaticClass());
                break;
			case EPropertyClass::Int8:
				p = newProperty(outer, FInt8Property::StaticClass());
                break;
			case EPropertyClass::Int16:
				p = newProperty(outer, FInt16Property::StaticClass());
                break;
			case EPropertyClass::Int:
				p = newProperty(outer, FIntProperty::StaticClass());
                break;
			case EPropertyClass::Int64:
				p = newProperty(outer, FInt64Property::StaticClass());
                break;
			case EPropertyClass::UInt16:
				p = newProperty(outer, FUInt16Property::StaticClass());
                break;
			case EPropertyClass::UInt32:
				p = newProperty(outer, FUInt32Property::StaticClass());
                break;
			case EPropertyClass::UInt64:
				p = newProperty(outer, FUInt64Property::StaticClass());
                break;
			case EPropertyClass::UnsizedInt:
				p = newProperty(outer, FUInt64Property::StaticClass());
                break;
			case EPropertyClass::UnsizedUInt:
				p = newProperty(outer, FUInt64Property::StaticClass());
                break;
			case EPropertyClass::Float:
				p = newProperty(outer, FFloatProperty::StaticClass());
                break;
			case EPropertyClass::Double:
				p = newProperty(outer, FDoubleProperty::StaticClass());
                break;
			case EPropertyClass::Bool: {
				auto op = newProperty<FBoolProperty>(outer, FBoolProperty::StaticClass());
				op->SetBoolSize(sizeof(bool), true);
				p = op;
				break;
			}
			case EPropertyClass::Object: {
				auto op = newProperty<FObjectPropertyBase>(outer, FObjectProperty::StaticClass());
				op->SetPropertyClass(proto.cls);
				p = op;
				break;
			}
			case EPropertyClass::Str:
				p = newProperty(outer, FStrProperty::StaticClass());
                break;
		}
		if (p) {
			FArchive ar;
			p->LinkWithoutChangingOffset(ar);
		}
			
        return p;
	}

}