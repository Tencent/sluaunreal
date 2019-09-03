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

    UObject* getPropertyOutter() {
		static TStrongObjectPtr<UStruct> propOuter;
		if (!propOuter.IsValid()) propOuter.Reset(NewObject<UStruct>((UObject*)GetTransientPackage()));
		return propOuter.Get();
	}

    UProperty* PropertyProto::createProperty(const PropertyProto& proto) {
		UProperty* p = nullptr;
		UObject* outer = getPropertyOutter();
		switch (proto.type) {
			case EPropertyClass::Byte:
				p = NewObject<UProperty>(outer, UByteProperty::StaticClass());
                break;
			case EPropertyClass::Int8:
				p = NewObject<UProperty>(outer, UInt8Property::StaticClass());
                break;
			case EPropertyClass::Int16:
				p = NewObject<UProperty>(outer, UInt16Property::StaticClass());
                break;
			case EPropertyClass::Int:
				p = NewObject<UProperty>(outer, UIntProperty::StaticClass());
                break;
			case EPropertyClass::Int64:
				p = NewObject<UProperty>(outer, UInt64Property::StaticClass());
                break;
			case EPropertyClass::UInt16:
				p = NewObject<UProperty>(outer, UUInt16Property::StaticClass());
                break;
			case EPropertyClass::UInt32:
				p = NewObject<UProperty>(outer, UUInt32Property::StaticClass());
                break;
			case EPropertyClass::UInt64:
				p = NewObject<UProperty>(outer, UUInt64Property::StaticClass());
                break;
			case EPropertyClass::UnsizedInt:
				p = NewObject<UProperty>(outer, UUInt64Property::StaticClass());
                break;
			case EPropertyClass::UnsizedUInt:
				p = NewObject<UProperty>(outer, UUInt64Property::StaticClass());
                break;
			case EPropertyClass::Float:
				p = NewObject<UProperty>(outer, UFloatProperty::StaticClass());
                break;
			case EPropertyClass::Double:
				p = NewObject<UProperty>(outer, UDoubleProperty::StaticClass());
                break;
			case EPropertyClass::Bool:
				p = NewObject<UProperty>(outer, UBoolProperty::StaticClass());
                break;
			case EPropertyClass::Object: {
				auto op = NewObject<UObjectProperty>(outer, UObjectProperty::StaticClass());
				op->SetPropertyClass(proto.cls);
				p = op;
				break;
			}
			case EPropertyClass::Str:
				p = NewObject<UProperty>(outer, UStrProperty::StaticClass());
                break;
		}
		if (p) {
			FArchive ar;
			p->LinkWithoutChangingOffset(ar);
		}
			
        return p;
	}

}