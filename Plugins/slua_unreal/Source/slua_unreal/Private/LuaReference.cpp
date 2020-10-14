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
#include "Runtime/Launch/Resources/Version.h"

namespace NS_SLUA {
	namespace LuaReference {

		void addRefByStruct(FReferenceCollector& collector, UStruct* us, void* base, bool container) {
			for (TFieldIterator<const FProperty> it(us); it; ++it)
				addRefByProperty(collector, *it, base, container);
		}

		void addRefByDelegate(FReferenceCollector& collector, const FScriptDelegate&, bool container = true) {
			// TODO
		}

		void addRefByMulticastDelegate(FReferenceCollector& collector, const FMulticastScriptDelegate&, bool container = true) {
			// TODO
		}


		bool addRef(const FSetProperty* p, void* base, FReferenceCollector& collector, bool container = true)
		{
			bool ret = false;
			for (int32 n = 0; n < p->ArrayDim; ++n)
			{
				bool valuesChanged = false;
				FScriptSetHelper helper(p, p->ContainerPtrToValuePtr<void>(base, n));

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

		bool addRef(const FMapProperty* p, void* base, FReferenceCollector& collector, bool container = true)
		{
			bool ret = false;
			for (int n = 0; n < p->ArrayDim; ++n)
			{
				bool keyChanged = false;
				bool valuesChanged = false;
				FScriptMapHelper helper(p, p->ContainerPtrToValuePtr<void>(base, n));

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

		bool addRef(const FObjectProperty* p, void* base, FReferenceCollector &collector, bool container = true)
		{
			bool ret = false;
			for (int n = 0; n < p->ArrayDim; ++n)
			{
				void* value = container?p->ContainerPtrToValuePtr<void>(base, n):base;
				UObject* obj = p->GetObjectPropertyValue(value);
				if (obj && obj->IsValidLowLevel())
				{
					UObject* newobj = obj;
					collector.AddReferencedObject(newobj);

					if (newobj != obj)
					{
						ret = true;
						p->SetObjectPropertyValue(value, newobj);
					}
				}
			}
			return ret;
		}

		bool addRef(const FArrayProperty* p, void* base, FReferenceCollector& collector, bool container = true)
		{
			bool ret = false;
			for (int n = 0; n < p->ArrayDim; ++n)
			{
				FScriptArrayHelper helper(p, p->ContainerPtrToValuePtr<void>(base, n));
				for (int32 index = 0; index < helper.Num(); ++index)
				{
					ret |= addRefByProperty(collector, p->Inner, helper.GetRawPtr(index));
				}
			}
			return ret;
		}

		bool addRef(const FMulticastDelegateProperty* p, void* base, FReferenceCollector& collector, bool container = true)
		{
			for (int n = 0; n < p->ArrayDim; ++n)
			{
#if (ENGINE_MINOR_VERSION>=23) && (ENGINE_MAJOR_VERSION>=4)
				FMulticastScriptDelegate* Value = const_cast<FMulticastScriptDelegate*>(p->GetMulticastDelegate(container ? p->ContainerPtrToValuePtr<void>(base, n) : base));
#else
				FMulticastScriptDelegate* Value = p->GetPropertyValuePtr(container?p->ContainerPtrToValuePtr<void>(base, n):base);
#endif
				addRefByMulticastDelegate(collector, *Value);
			}
			return false;
		}

		bool addRef(const FStructProperty* p, void* base, FReferenceCollector& collector, bool container = true)
		{
			for (int n = 0; n < p->ArrayDim; ++n) {
				addRefByStruct(collector, p->Struct, container?p->ContainerPtrToValuePtr<void>(base, n):base);
			}
			return false;
		}

		//bool addRef(const UDelegateProperty* p, void* base, FReferenceCollector& collector, bool container = true)
		//{
		//	for (int n = 0; n < p->ArrayDim; ++n) {
		//		FScriptDelegate* value = p->GetPropertyValuePtr(container?p->ContainerPtrToValuePtr<void>(base, n):base);
		//		addRefByDelegate(collector, *value);
		//	}
		//	return false;
		//}

		bool addRefByProperty(FReferenceCollector& collector, const FProperty* prop, void* base, bool container) {
			
			if (auto p = CastField<FObjectProperty>(prop)) {
				return addRef(p, base, collector, container);
			}
			if (auto p = CastField<FArrayProperty>(prop))
			{
				return addRef(p, base, collector, container);
			}
			if (auto p = CastField<FStructProperty>(prop)) {
				return addRef(p, base, collector, container);
			}
			if (auto p = CastField<FMapProperty>(prop))
			{
				return addRef(p, base, collector, container);
			}
			if (auto p = CastField<FSetProperty>(prop))
			{
				return addRef(p, base, collector, container);
			}
			if (auto p = CastField<FMulticastDelegateProperty>(prop))
			{
				return addRef(p, base, collector, container);
			}
			return false;
		}
	}
}