#include "LuaSet.h"

#include "LuaObject.h"
#include "SluaLib.h"
#include "LuaState.h"
#include "LuaReference.h"
#include "LuaNetSerialization.h"

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

    LuaSet::LuaSet(FProperty* Property, FScriptSet* Buffer, bool bIsRef, bool bIsNewInner)
        : Set(bIsRef ? Buffer : new FScriptSet())
        , InElementProperty(Property)
        , Helper(FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, Set))
        , IsRef(bIsRef)
        , isNewInner(bIsNewInner)
        , proxy(nullptr)
        , luaReplicatedIndex(InvalidReplicatedIndex)
    {
        if (!IsRef)
        {
            clone(Set, Property, Buffer);
        }
    }

    LuaSet::LuaSet(FSetProperty* Property, FScriptSet* Buffer, bool bIsRef, FLuaNetSerializationProxy* netProxy, uint16 replicatedIndex)
        : Set(bIsRef ? Buffer : new FScriptSet())
        , InElementProperty(Property->ElementProp)
        , Helper(FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, Set))
        , IsRef(bIsRef)
        , isNewInner(false)
        , proxy(netProxy)
        , luaReplicatedIndex(replicatedIndex)
    {
        if (!IsRef)
        {
            clone(Set, Property, Buffer);
        }
    }

    LuaSet::~LuaSet()
    {
        if (!IsRef)
        {
            clear();
            ensure(Set);
            SafeDelete(Set);
        }

        if (isNewInner)
        {
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
            delete InElementProperty;
#endif
        }
        InElementProperty = nullptr;
    }

    void LuaSet::reg(lua_State* L)
    {
        SluaUtil::reg(L, "Set", __ctor);
    }

    void LuaSet::clone(FScriptSet* DstSet, FProperty* InElementProperty, const FScriptSet* SrcSet)
    {
        if (!SrcSet)
            return;

        FScriptSetHelper DstHelper = FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, DstSet);
        if (SrcSet->Num() == 0)
        {
            DstHelper.EmptyElements(0);
            return;
        }
        FScriptSetHelper SrcHelper = FScriptSetHelper::CreateHelperFormElementProperty(InElementProperty, SrcSet);
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

    int LuaSet::push(lua_State* L, FProperty* Property, FScriptSet* Set, bool bIsNewInner)
    {
        LuaSet* NewSet = new LuaSet(Property, Set, false, bIsNewInner);
        LuaObject::addLink(L, NewSet->get());
        return push(L, NewSet);
    }

    int LuaSet::push(lua_State* L, LuaSet* luaSet)
    {
        return LuaObject::pushType(L, luaSet, "LuaSet", setupMT, gc);
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
        
        return push(L, PropertyProto::createProperty(PropertyProto(ElementType, UnClass)), &Set, true);
    }

    int LuaSet::Num(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaSet, but got nil!");
        }
        return LuaObject::push(L, UD->num());
    }

    int LuaSet::Get(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaSet, but got nil!");
        }
        GET_SET_CHECKER()
        const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
        const auto ElementPtr = tempElement.GetObjAddress();
        ElementChecker(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr), 2, true);

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
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaSet, but got nil!");
        }
        GET_SET_CHECKER();
        const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
        const auto ElementPtr = tempElement.GetObjAddress();
        ElementChecker(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr), 2, true);
        UD->Helper.AddElement(ElementPtr);

        markDirty(UD);

        return 0;
    }

    int LuaSet::Remove(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaSet, but got nil!");
        }
        GET_SET_CHECKER();
        const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
        const auto ElementPtr = tempElement.GetObjAddress();
        ElementChecker(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr), 2, true);

        markDirty(UD);

        return LuaObject::push(L, UD->removeElement(ElementPtr));
    }

    int LuaSet::Clear(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaSet, but got nil!");
        }
        UD->clear();

        markDirty(UD);

        return 0;
    }

    int LuaSet::Pairs(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        if (!UD) {
            luaL_error(L, "arg 1 expect LuaSet, but got nil!");
        }
        Enumerator* Iter = new Enumerator();

        Iter->Set = UD;
        Iter->Index = 0;
        Iter->Num = UD->Helper.Num();

        lua_pushcfunction(L, LuaSet::Enumerable);
        LuaObject::pushType(L, Iter, "LuaSet::Enumerator", nullptr, Enumerator::gc);
        // Hold reference of LuaSet, avoiding GC
        lua_pushvalue(L, 1);
        lua_setuservalue(L, 3);
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

    int LuaSet::CreateElementTypeObject(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        auto UnClass = UD->InElementProperty->GetClass();
        if (UnClass)
        {
            const FDefaultConstructedPropertyElement tempElement(UD->InElementProperty);
            const auto ElementPtr = tempElement.GetObjAddress();
            if (ElementPtr)
                return LuaObject::push(L, UD->InElementProperty, static_cast<uint8*>(ElementPtr));
        }
        return 0;
    }

    bool LuaSet::markDirty(LuaSet* luaSet)
    {
        auto proxy = luaSet->proxy;
        if (proxy)
        {
            proxy->dirtyMark.Add(luaSet->luaReplicatedIndex);
            proxy->assignTimes++;
            return true;
        }

        return false;
    }

    void LuaSet::AddReferencedObjects(FReferenceCollector& Collector)
    {
        if (InElementProperty)
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            Collector.AddReferencedObject(InElementProperty);
#else
            InElementProperty->AddReferencedObjects(Collector);
#endif
        
        if (IsRef || num() <= 0)
            return;

        if (!LuaReference::isRefProperty(InElementProperty))
            return;
        
        bool Rehash = false;
        for (int Index = Helper.GetMaxIndex() - 1; Index>= 0; Index--)
        {
            if (Helper.IsValidIndex(Index))
            {
                const auto ElementPtr = Helper.GetElementPtr(Index);
                const bool ElementChanged = LuaReference::addRefByProperty(Collector, InElementProperty, ElementPtr);
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
        if (!IsRef) 
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
        if (!IsRef) {
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
        RegMetaMethod(L, CreateElementTypeObject);
        
        RegMetaMethodByName(L, "__pairs", Pairs);
        return 0;
    }

    int LuaSet::gc(lua_State* L)
    {
        auto userdata = (UserData<LuaSet*>*)luaL_testudata(L, 1, "LuaSet");
        auto self = userdata->ud;
        if (!userdata->parent && !(userdata->flag & UD_HADFREE))
            LuaObject::releaseLink(L, self->get());
        if (self->IsRef) {
            LuaObject::unlinkProp(L, userdata);
        }
        delete userdata->ud;
        return 0;
    }

    int LuaSet::Enumerator::gc(lua_State* L)
    {
        CheckUD(LuaSet::Enumerator, L, 1);
        delete UD;
        return 0;
    }
}
