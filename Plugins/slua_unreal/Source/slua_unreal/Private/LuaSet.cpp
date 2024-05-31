#include "LuaSet.h"

#include "LuaObject.h"
#include "SluaLib.h"
#include "LuaState.h"
#include "LuaReference.h"
#include "LuaNetSerialization.h"

#define GET_SET_CHECKER() \
    const auto elementChecker = LuaObject::getChecker(UD->inner);\
    if (!elementChecker) { \
        const auto tn = UD->inner->GetClass()->GetName(); \
        luaL_error(L, "Nonsupport type %s", TCHAR_TO_UTF8(*tn)); \
        return 0; \
    }

namespace NS_SLUA
{
    void LuaSet::reg(lua_State* L)
    {
        SluaUtil::reg(L, "Set", __ctor);
    }
    
    LuaSet::LuaSet(FProperty* property, FScriptSet* buffer, bool bIsRef, bool bIsNewInner)
        : set(bIsRef ? buffer : new FScriptSet())
        , inner(property)
        , helper(FScriptSetHelper::CreateHelperFormElementProperty(inner, set))
        , isRef(bIsRef)
        , isNewInner(bIsNewInner)
        , proxy(nullptr)
        , luaReplicatedIndex(InvalidReplicatedIndex)
    {
        if (!isRef)
        {
            clone(set, property, buffer);
        }
    }

    LuaSet::LuaSet(FSetProperty* property, FScriptSet* buffer, bool bIsRef, FLuaNetSerializationProxy* netProxy, uint16 replicatedIndex)
        : set(bIsRef ? buffer : new FScriptSet())
        , inner(property->ElementProp)
        , helper(FScriptSetHelper::CreateHelperFormElementProperty(inner, set))
        , isRef(bIsRef)
        , isNewInner(false)
        , proxy(netProxy)
        , luaReplicatedIndex(replicatedIndex)
    {
        if (!isRef)
        {
            clone(set, property, buffer);
        }
    }

    LuaSet::~LuaSet()
    {
        if (!isRef)
        {
            clear();
            ensure(set);
            delete set;
            set = nullptr;
        }

        if (isNewInner)
        {
#if !((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
            delete inner;
#endif
        }
        inner = nullptr;
    }

    void LuaSet::clone(FScriptSet* dstSet, FProperty* prop, const FScriptSet* srcSet)
    {
        if (!srcSet)
            return;

        FScriptSetHelper dstHelper = FScriptSetHelper::CreateHelperFormElementProperty(prop, dstSet);
        if (srcSet->Num() == 0)
        {
            dstHelper.EmptyElements(0);
            return;
        }
        FScriptSetHelper srcHelper = FScriptSetHelper::CreateHelperFormElementProperty(prop, srcSet);
        dstHelper.EmptyElements(srcHelper.Num());

        for (auto n = 0; n < srcHelper.GetMaxIndex(); n++)
        {
            if (srcHelper.IsValidIndex(n))
            {
                const auto ElementPtr = srcHelper.GetElementPtr(n);
                dstHelper.AddElement(ElementPtr);
            }
        }
    }

    int LuaSet::push(lua_State* L, FProperty* prop, FScriptSet* set, bool bIsNewInner)
    {
        LuaSet* newSet = new LuaSet(prop, set, false, bIsNewInner);
        LuaObject::addLink(L, newSet->get());
        return push(L, newSet);
    }

    int LuaSet::push(lua_State* L, LuaSet* luaSet)
    {
        return LuaObject::pushType(L, luaSet, "LuaSet", setupMT, gc);
    }

    int LuaSet::__ctor(lua_State* L)
    {
        FScriptSet set = FScriptSet();

        FProperty* prop;
        auto type = (EPropertyClass)LuaObject::checkValue<int>(L,1);
        switch (type)
        {
        case EPropertyClass::Object:
            {
                auto cls = LuaObject::checkValueOpt<UClass*>(L, 2, nullptr);
                if (!cls)
                    luaL_error(L, "Set of UObject should have 2nd parameter is UClass");
                prop = PropertyProto::createProperty(PropertyProto(type, cls));
            }
            break;
        case EPropertyClass::Struct:
            {
                auto scriptStruct = LuaObject::checkValueOpt<UScriptStruct*>(L, 2, nullptr);
                if (!scriptStruct)
                    luaL_error(L, "Set of Struct should have 2nd parameter is UStruct");
                prop = PropertyProto::createProperty(PropertyProto(type, scriptStruct));
            }
            break;
        default:
            prop = PropertyProto::createProperty(PropertyProto(type));
            break;
        }
        
        return push(L, prop, &set, true);
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
        const FDefaultConstructedPropertyElement tempElement(UD->inner);
        const auto elementPtr = tempElement.GetObjAddress();
        elementChecker(L, UD->inner, static_cast<uint8*>(elementPtr), 2, true);

        const auto index = UD->helper.FindElementIndexFromHash(elementPtr);
        if (index != INDEX_NONE)
        {
            LuaObject::push(L, UD->inner, UD->helper.GetElementPtr(index));
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
        const FDefaultConstructedPropertyElement tempElement(UD->inner);
        const auto elementPtr = tempElement.GetObjAddress();
        elementChecker(L, UD->inner, static_cast<uint8*>(elementPtr), 2, true);
        UD->helper.AddElement(elementPtr);

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
        const FDefaultConstructedPropertyElement tempElement(UD->inner);
        const auto elementPtr = tempElement.GetObjAddress();
        elementChecker(L, UD->inner, static_cast<uint8*>(elementPtr), 2, true);

        markDirty(UD);

        return LuaObject::push(L, UD->removeElement(elementPtr));
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

        bool bReverse = !!lua_toboolean(L, 2);

        if (bReverse)
        {
            lua_pushcfunction(L, LuaSet::IterateReverse);
            lua_pushvalue(L, 1);
            lua_pushinteger(L, UD->helper.GetMaxIndex());
        }
        else
        {
            lua_pushcfunction(L, LuaSet::Iterate);
            lua_pushvalue(L, 1);
            lua_pushinteger(L, -1);
        }

        return 3;
    }

    int LuaSet::Iterate(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);

        auto set = UD->set;
        int32 num = UD->helper.GetMaxIndex();
        for (int32 i = luaL_checkinteger(L, 2) + 1; i < num; ++i)
        {
            if (set->IsValidIndex(i))
            {
                return PushElement(L, UD, i);
            }
        }

        return 0;
    }

    int LuaSet::IterateReverse(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        
        auto set = UD->set;
        for (int32 i = luaL_checkinteger(L, 2) - 1; i >= 0; --i)
        {
            if (set->IsValidIndex(i))
            {
                return PushElement(L, UD, i);
            }
        }

        return 0;
    }

    int LuaSet::PushElement(lua_State* L, LuaSet* UD, int32 Index)
    {
        auto set = UD->set;
        if (set->IsValidIndex(Index))
        {
            auto inner = UD->inner;
            auto parms = UD->helper.GetElementPtr(Index);
            lua_pushinteger(L, Index);
            LuaObject::push(L, inner, parms);
            return 2;
        }

        return 0;
    }

    int LuaSet::CreateElementTypeObject(lua_State* L)
    {
        CheckUD(LuaSet, L, 1);
        auto cls = UD->inner->GetClass();
        if (cls)
        {
            const FDefaultConstructedPropertyElement tempElement(UD->inner);
            const auto elementPtr = tempElement.GetObjAddress();
            if (elementPtr)
                return LuaObject::push(L, UD->inner, static_cast<uint8*>(elementPtr));
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
        if (inner) 
        {
#if (ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4)
            Collector.AddReferencedObject(inner);
#else
#if ENGINE_MAJOR_VERSION==5 && ENGINE_MINOR_VERSION >= 4
            TObjectPtr<UObject> ownerObject = inner->GetOwnerUObject();
#else
            auto ownerObject = inner->GetOwnerUObject();
#endif
            Collector.AddReferencedObject(ownerObject);
#endif
        }
        
        if (isRef || num() <= 0)
            return;

        if (!LuaReference::isRefProperty(inner))
            return;
        
        bool rehash = false;
        for (int index = helper.GetMaxIndex() - 1; index>= 0; index--)
        {
            if (helper.IsValidIndex(index))
            {
                const auto elementPtr = helper.GetElementPtr(index);
                const bool bElementChanged = LuaReference::addRefByProperty(Collector, inner, elementPtr);
                if (bElementChanged)
                {
                    removeAt(index);
                    rehash = true;
                }
            }
        }
        if (rehash) helper.Rehash();
    }

    int LuaSet::num() const
    {
        return helper.Num();
    }

    void LuaSet::clear()
    {
        if (!inner)
            return;
        emptyElements();
    }

    // Rewrite FScriptSetHelper::EmptyElements by adding ShouldFree judgment. If it's true, cal the original one.
    void LuaSet::emptyElements(int32 slack)
    {
        if (!isRef) 
        {
            helper.EmptyElements();
        }
        else 
        {
            checkSlow(slack >= 0);
            const int32 OldNum = num();
            if (OldNum || slack) 
            {
                set->Empty(slack, helper.SetLayout);
            }
        }
    }

    // Modify FScriptSetHelper::RemoveAt by adding ShouldFree judgment. If it's true, call the original one.
    void LuaSet::removeAt(int32 index, int32 count)
    {
        if (!isRef) {
            helper.RemoveAt(index);
        }
        else {
            check(helper.IsValidIndex(index));
            for (; count; ++index) {
                if (helper.IsValidIndex(index)) {
                    set->RemoveAt(index, helper.SetLayout);
                    --count;
                }
            }
        }
    }

    // Modify FScriptSetHelper::RemoveAt for the use of our custom removeAt.
    bool LuaSet::removeElement(const void* elementToRemove)
    {
        FProperty* localElementPropForCapture = inner;
        const auto foundIndex = set->FindIndex(
            elementToRemove,
            helper.SetLayout,
            [localElementPropForCapture](const void* Element) { return localElementPropForCapture->GetValueTypeHash(Element); },
            [localElementPropForCapture](const void* A, const void* B) { return localElementPropForCapture->Identical(A, B); }
        );
        if (foundIndex != INDEX_NONE)
        {
            removeAt(foundIndex);
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
        auto userdata = (UserData<LuaSet*>*)lua_touserdata(L, 1);
        auto self = userdata->ud;
        if (!userdata->parent && !(userdata->flag & UD_HADFREE))
            LuaObject::releaseLink(L, self->get());
        if (self->isRef) {
            LuaObject::unlinkProp(L, userdata);
        }
        delete self;
        return 0;
    }
}
