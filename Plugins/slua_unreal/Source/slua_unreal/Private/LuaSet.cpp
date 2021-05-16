#include "LuaSet.h"
#include "LuaObject.h"
#include "SluaLib.h"
#include "LuaState.h"
#include "LuaReference.h"

#define GET_SET_CHECKER() \
	const auto ElementChecker = LuaObject::getChecker(UD->InElementProperty);\
	if (!ElementChecker) { \
		const auto tn = UD->InElementProperty->GetClass()->GetName(); \
		luaL_error(L, "Nonsupport type %s", TCHAR_TO_UTF8(*tn)); \
		return 0; \
	}

namespace NS_SLUA
{

	DefTypeName(LuaSet::Enumerator);

	LuaSet::LuaSet(FProperty* Property, FScriptSet* Buffer) :
		Set(new FScriptSet),
		InElementProperty(Property),
		SetProperty(nullptr),
		PropertyObject(nullptr),
		Helper(FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, Set)),
		ShouldFree(true)
	{
		clone(Set, Property, Buffer);
	}

	LuaSet::LuaSet(FSetProperty* Property, UObject* Object) :
		Set(Property->ContainerPtrToValuePtr<FScriptSet>(Object)),
		InElementProperty(Property->ElementProp),
		SetProperty(Property),
		PropertyObject(Object),
		Helper(Property, Set),
		ShouldFree(false)
	{
	}

	LuaSet::~LuaSet()
	{
		if (ShouldFree)
		{
			clear();
			ensure(Set);
			SafeDelete(Set);
		}
		InElementProperty = nullptr;
		SetProperty = nullptr;
		PropertyObject = nullptr;
	}

	void LuaSet::reg(lua_State* L)
	{
		SluaUtil::reg(L, "Set", __ctor);
	}

	void LuaSet::clone(FScriptSet* DstSet, FProperty* InElementProperty, const FScriptSet* SrcSet)
	{
		if (!SrcSet || SrcSet->Num() == 0)
			return;

		FScriptSetHelper SrcHelper = FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, SrcSet);
		FScriptSetHelper DstHelper = FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, DstSet);
		DstHelper.EmptyElements(SrcHelper.Num());

		for (auto n = 0; n < SrcHelper.GetMaxIndex(); n++)
		{
			if (SrcHelper.IsValidIndex(n))
			{
				const auto ElementPtr = SrcHelper.GetElementPtr(n);
				DstHelper.AddElement(ElementPtr);
			}
		}
	}

	int LuaSet::push(lua_State* L, FProperty* Property, FScriptSet* Set)
	{
		LuaSet* NewSet = new LuaSet(Property, Set);
		return LuaObject::pushType(L, NewSet, "LuaSet", setupMT, gc);
	}

	int LuaSet::push(lua_State* L, FSetProperty* prop, UObject* obj)
	{
		const auto ScriptSet = prop->ContainerPtrToValuePtr<FScriptSet>(obj);
		if (LuaObject::getObjCache(L, ScriptSet, "LuaSet"))
			return 1;

		LuaSet* luaSet = new LuaSet(prop, obj);
		const int r = LuaObject::pushType(L, luaSet, "LuaSet", setupMT, gc);
		if (r)
			LuaObject::cacheObj(L, luaSet->Set);
		return 1;
	}

	int LuaSet::__ctor(lua_State* L)
	{
		FScriptSet Set = FScriptSet();

		const auto ElementType = static_cast<EPropertyClass>(LuaObject::checkValue<int>(L, 1));
		const auto UnClass = LuaObject::checkValueOpt<UClass*>(L, 2, nullptr);

		if (ElementType == EPropertyClass::Object && !UnClass)
		{
			luaL_error(L, "The 2nd parameter should be UClass for the set of UObject");
		}
		
		return push(L, PropertyProto::createProperty(PropertyProto(ElementType, UnClass)), &Set);
	}

	int LuaSet::Num(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		return LuaObject::push(L, UD->num());
	}

	int LuaSet::Get(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		GET_SET_CHECKER()
		const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
		const auto ElementPtr = tempElement.GetObjAddress();
		ElementChecker(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr), 2);

		const auto Index = UD->Helper.FindElementIndexFromHash(ElementPtr);
		if (Index != INDEX_NONE)
		{
			LuaObject::push(L, UD->InElementProperty, UD->Helper.GetElementPtr(Index));
			LuaObject::push(L, true);
		}
		else
		{
			LuaObject::pushNil(L);
			LuaObject::push(L, false);
		}
		return 2;
	}

	int LuaSet::Add(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		GET_SET_CHECKER();
		const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
		const auto ElementPtr = tempElement.GetObjAddress();
		ElementChecker(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr), 2);
		UD->Helper.AddElement(ElementPtr);
		return 0;
	}

	int LuaSet::Remove(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		GET_SET_CHECKER();
		const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
		const auto ElementPtr = tempElement.GetObjAddress();
		ElementChecker(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr), 2);
		return LuaObject::push(L, UD->removeElement(ElementPtr));
	}

	int LuaSet::Clear(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		UD->clear();
		return 0;
	}

	int LuaSet::Pairs(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		Enumerator* Iter = new Enumerator();
		// Hold reference of LuaSet, avoiding GC
		Iter->Holder = new LuaVar(L, 1);
		Iter->Set = UD;
		Iter->Index = 0;
		Iter->Num = UD->Helper.Num();

		lua_pushcfunction(L, LuaSet::Enumerable);
		LuaObject::pushType(L, Iter, "LuaSet::Enumerator", nullptr, Enumerator::gc);
		LuaObject::pushNil(L);
		return 3;
	}

	int LuaSet::Enumerable(lua_State* L)
	{
		CheckUD(LuaSet::Enumerator, L, 1);
		LuaSet* Set = UD->Set;
		FScriptSetHelper& Helper = Set->Helper;

		while (UD->Num > 0)
		{
			if (Helper.IsValidIndex(UD->Index))
			{
				const auto ElementPtr = Helper.GetElementPtr(UD->Index);
				LuaObject::push(L, UD->Index);
				LuaObject::push(L, Set->InElementProperty, ElementPtr);
				UD->Index += 1;
				UD->Num -= 1;
				return 2;
			}
			UD->Index += 1;
		}
		return 0;
	}

	void LuaSet::AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (InElementProperty)
			InElementProperty->AddReferencedObjects(Collector);
		if (SetProperty)
			SetProperty->AddReferencedObjects(Collector);
		if (PropertyObject)
			Collector.AddReferencedObject(PropertyObject);
		
		if ((!ShouldFree && !PropertyObject) || num() <= 0)
			return;
		
		bool Rehash = false;
		for (int Index = Helper.GetMaxIndex() - 1; Index>= 0; Index--)
		{
			if (Helper.IsValidIndex(Index))
			{
				const auto ElementPtr = Helper.GetElementPtr(Index);
				const bool ElementChanged = LuaReference::addRefByProperty(Collector, InElementProperty, ElementPtr, false);
				if (ElementChanged)
				{
					removeAt(Index);
					Rehash = true;
				}
			}
		}
		if (Rehash) Helper.Rehash();
	}

	int LuaSet::num() const
	{
		return Helper.Num();
	}

	void LuaSet::clear()
	{
		if (!InElementProperty)
			return;
		emptyElements();
	}

	FScriptSet* LuaSet::get() const
	{
		return Set;
	}

	// Rewrite FScriptSetHelper::EmptyElements by adding ShouldFree judgment. If it's true, cal the original one.
	void LuaSet::emptyElements(int32 Slack)
	{
		if (ShouldFree) 
		{
			Helper.EmptyElements();
		}
		else 
		{
			checkSlow(Slack >= 0);
			const int32 OldNum = num();
			if (OldNum || Slack) 
			{
				Set->Empty(Slack, Helper.SetLayout);
			}
		}
	}

	// Modify FScriptSetHelper::RemoveAt by adding ShouldFree judgment. If it's true, call the original one.
	void LuaSet::removeAt(int32 Index, int32 Count)
	{
		if (ShouldFree) {
			Helper.RemoveAt(Index);
		}
		else {
			check(Helper.IsValidIndex(Index));
			for (; Count; ++Index) {
				if (Helper.IsValidIndex(Index)) {
					Set->RemoveAt(Index, Helper.SetLayout);
					--Count;
				}
			}
		}
	}

	// Modify FScriptSetHelper::RemoveAt for the use of our custom removeAt.
	bool LuaSet::removeElement(const void* ElementToRemove)
	{
		FProperty* LocalElementPropForCapture = InElementProperty;
		const auto FoundIndex = Set->FindIndex(
			ElementToRemove,
			Helper.SetLayout,
			[LocalElementPropForCapture](const void* Element) { return LocalElementPropForCapture->GetValueTypeHash(Element); },
			[LocalElementPropForCapture](const void* A, const void* B) { return LocalElementPropForCapture->Identical(A, B); }
		);
		if (FoundIndex != INDEX_NONE)
		{
			removeAt(FoundIndex);
			return true;
		}
		else
		{
			return false;
		}
	}

	int LuaSet::setupMT(lua_State* L)
	{
		LuaObject::setupMTSelfSearch(L);

		RegMetaMethod(L, Num);
		RegMetaMethod(L, Get);
		RegMetaMethod(L, Add);
		RegMetaMethod(L, Remove);
		RegMetaMethod(L, Clear);
		RegMetaMethod(L, Pairs);
		
		RegMetaMethodByName(L, "__pairs", Pairs);
		return 0;
	}

	int LuaSet::gc(lua_State* L)
	{
		CheckUD(LuaSet, L, 1);
		LuaObject::deleteFGCObject(L, UD);
		return 0;
	}

	int LuaSet::Enumerator::gc(lua_State* L)
	{
		CheckUD(LuaSet::Enumerator, L, 1);
		delete UD;
		return 0;
	}

	LuaSet::Enumerator::~Enumerator()
	{
		SafeDelete(Holder);
	}
}
