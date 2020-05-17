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

    FProperty* PropertyProto::createProperty(const PropertyProto& proto) {
		FProperty* p = nullptr;
	/*	UObject* outer = getPropertyOutter();
		switch (proto.type) {
			case EPropertyClass::Byte:
				p = NewObject<FProperty>(outer, FByteProperty::StaticClass());
                break;
			case EPropertyClass::Int8:
				p = NewObject<FProperty>(outer, FInt8Property::StaticClass());
                break;
			case EPropertyClass::Int16:
				p = NewObject<FProperty>(outer, FInt16Property::StaticClass());
                break;
			case EPropertyClass::Int:
				p = NewObject<FProperty>(outer, FIntProperty::StaticClass());
                break;
			case EPropertyClass::Int64:
				p = NewObject<FProperty>(outer, FInt64Property::StaticClass());
                break;
			case EPropertyClass::UInt16:
				p = NewObject<FProperty>(outer, FUInt16Property::StaticClass());
                break;
			case EPropertyClass::UInt32:
				p = NewObject<FProperty>(outer, FUInt32Property::StaticClass());
                break;
			case EPropertyClass::UInt64:
				p = NewObject<FProperty>(outer, FUInt64Property::StaticClass());
                break;
			case EPropertyClass::UnsizedInt:
				p = NewObject<FProperty>(outer, FUInt64Property::StaticClass());
                break;
			case EPropertyClass::UnsizedUInt:
				p = NewObject<FProperty>(outer, FUInt64Property::StaticClass());
                break;
			case EPropertyClass::Float:
				p = NewObject<FProperty>(outer, FFloatProperty::StaticClass());
                break;
			case EPropertyClass::Double:
				p = NewObject<FProperty>(outer, FDoubleProperty::StaticClass());
                break;
			case EPropertyClass::Bool:
				p = NewObject<FProperty>(outer, FBoolProperty::StaticClass());
                break;
			case EPropertyClass::Object: {
				auto op = NewObject<FObjectProperty>(outer, FObjectProperty::StaticClass());
				op->SetPropertyClass(proto.cls);
				p = op;
				break;
			}
			case EPropertyClass::Str:
				p = NewObject<FProperty>(outer, FStrProperty::StaticClass());
                break;
		}
		if (p) {
			FArchive ar;
			p->LinkWithoutChangingOffset(ar);
		}*/
			
        return p;
	}

}