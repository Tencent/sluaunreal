#pragma once

#include "SluaMicro.h"
#include "UObject/UnrealType.h"
#include "UObject/GCObject.h"
#include "PropertyUtil.h"
#include "lauxlib.h"

namespace NS_SLUA {

    // Traits class which determines whether or not a type is a TSet.
    template <typename T> struct TIsTSet { enum { Value = false }; };

    template <typename InElementType, typename KeyFuncs, typename Allocator>
    struct TIsTSet<               TSet<InElementType, KeyFuncs, Allocator>> { enum { Value = true }; };

    template <typename InElementType, typename KeyFuncs, typename Allocator>
    struct TIsTSet<const          TSet<InElementType, KeyFuncs, Allocator>> { enum { Value = true }; };

    template <typename InElementType, typename KeyFuncs, typename Allocator>
    struct TIsTSet<      volatile TSet<InElementType, KeyFuncs, Allocator>> { enum { Value = true }; };

    template <typename InElementType, typename KeyFuncs, typename Allocator>
    struct TIsTSet<const volatile TSet<InElementType, KeyFuncs, Allocator>> { enum { Value = true }; };

    class SLUA_UNREAL_API LuaSet : public FGCObject {

    public:
        static void reg(lua_State* L);
        
        LuaSet(FProperty* property, FScriptSet* buffer, bool bIsRef, bool bIsNewInner);
        LuaSet(FSetProperty* property, FScriptSet* buffer, bool bIsRef, struct FLuaNetSerializationProxy* netProxy, uint16 replicatedIndex);
        ~LuaSet();
        
        static void clone(FScriptSet* dstSet, FProperty* prop, const FScriptSet* srcSet);
        static int push(lua_State* L, FProperty* prop, FScriptSet* set, bool bIsNewInner);
        static int push(lua_State* L, LuaSet* luaSet);

        template<typename T>
        static typename std::enable_if<DeduceType<T>::value != EPropertyClass::Struct, int>::type push(lua_State* L, const TSet<T>& v)
        {
            FProperty* property = PropertyProto::createDeduceProperty<T>();
            const FScriptSet* set = reinterpret_cast<const FScriptSet*>(&v);
            return push(L, property, const_cast<FScriptSet*>(set), false);
        }

        template<typename T>
        static typename std::enable_if<DeduceType<T>::value == EPropertyClass::Struct, int>::type push(lua_State* L, const TSet<T>& v)
        {
            FProperty* property = PropertyProto::createDeduceProperty<T>(T::StaticStruct());
            const FScriptSet* set = reinterpret_cast<const FScriptSet*>(&v);
            return push(L, property, const_cast<FScriptSet*>(set), false);
        }

        static bool markDirty(LuaSet* luaSet);

        // Otherwise the LuaSet is an abstract class and can't be created.
        virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

#if !((ENGINE_MINOR_VERSION<20) && (ENGINE_MAJOR_VERSION==4))
        virtual FString GetReferencerName() const override
        {
            return "LuaSet";
        }
#endif

        FScriptSet* get() const
        {
            return set;
        }
        
        FProperty* getInnerProp() const
        {
            return inner;
        }

        template<typename T>
        const TSet<T>& asTSet(lua_State* L) const
        {
            if (sizeof(T) != inner->ElementSize)
                luaL_error(L, "Cast to TSet error, element size doesn't match (%d, %d)", sizeof(T), inner->ElementSize);
            return *(reinterpret_cast<const TSet<T>*>(set));
        }
        
    protected:
        static int __ctor(lua_State* L);
        static int Num(lua_State* L);
        static int Get(lua_State* L);
        static int Add(lua_State* L);
        static int Remove(lua_State* L);
        static int Clear(lua_State* L);
        static int Pairs(lua_State* L);
        static int Iterate(lua_State* L);
        static int IterateReverse(lua_State* L);
        static int PushElement(lua_State* L, LuaSet* UD, int32 Index);
        static int CreateElementTypeObject(lua_State* L);

    private:
        FScriptSet* set;
        FProperty* inner;
        FScriptSetHelper helper;

        bool isRef;
        bool isNewInner;

        struct FLuaNetSerializationProxy* proxy;
        uint16 luaReplicatedIndex;

        static int setupMT(lua_State* L);
        static int gc(lua_State* L);

        int32 num() const;
        void clear();
        void emptyElements(int32 slack = 0);
        void removeAt(int32 index, int32 count = 1);
        bool removeElement(const void* elementToRemove);
    };
}
