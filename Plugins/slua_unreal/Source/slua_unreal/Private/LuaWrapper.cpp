// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaWrapper.h"
#include "LuaObject.h"
#include "LuaNetSerialization.h"

#define SLUA_GCSTRUCT(typeName) auto flag = udptr->flag; \
                    if (udptr->parent) { \
                        LuaObject::unlinkProp(L, udptr); \
                    } \
                    else if (!(flag & UD_HADFREE) && (flag & UD_AUTOGC)) { \
                        LuaObject::releaseLink(L, self); \
                    } \
                    if ((flag & UD_AUTOGC) && !(flag & UD_HADFREE)) delete self

#define SLUA_MARK_NETPROP if (udptr->flag & UD_NETTYPE) \
{ \
    auto proxy = udptr->proxy; \
    if (proxy) \
    { \
        auto luaReplicatedIndex = udptr->luaReplicatedIndex; \
        proxy->dirtyMark.Add(luaReplicatedIndex); \
        proxy->assignTimes++; \
    } \
}

#define SLUA_GET_NETINFO FLuaNetSerializationProxy* proxy = nullptr; \
uint16 luaReplicatedIndex = InvalidReplicatedIndex; \
if (udptr->flag & UD_NETTYPE) \
{ \
    luaReplicatedIndex = udptr->luaReplicatedIndex; \
}


namespace NS_SLUA {
    UScriptStruct* StaticGetBaseStructureInternal(const TCHAR* Name)
    {
	    static UPackage* CoreUObjectPkg = FindObjectChecked<UPackage>(nullptr, TEXT("/Script/CoreUObject"));
	    return FindObjectSafe<UScriptStruct>(CoreUObjectPkg, Name);
    }

#if ((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
    #include "LuaWrapper4.18.inc"
#elif ((ENGINE_MINOR_VERSION>=25) && (ENGINE_MAJOR_VERSION==4))
    #include "LuaWrapper4.25.inc"
#elif ((ENGINE_MINOR_VERSION==1) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.1.inc"
#elif ((ENGINE_MINOR_VERSION==2) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.2.inc"
#elif ((ENGINE_MINOR_VERSION>=3) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.3.inc"
#endif

    static inline FSoftObjectPtr* __newFSoftObjectPtr() {
        return new FSoftObjectPtr();
    }

    static void __pushFSoftObjectPtr(lua_State* L, FStructProperty* p, uint8* parms) {
        auto ptr = __newFSoftObjectPtr();
        p->CopyCompleteValue(ptr, parms);
        LuaObject::push<FSoftObjectPtr>(L, "FSoftObjectPtr", ptr, UD_AUTOGC | UD_VALUETYPE);
    }

    static void* __checkFSoftObjectPtr(lua_State* L, FStructProperty* p, uint8* parms, int i) {
        auto v = LuaObject::checkValue<FSoftObjectPtr*>(L, i);
        if (!v) {
            luaL_error(L, "check FSoftObjectPtr nil value");
            return nullptr;
        }
        p->CopyCompleteValue(parms, v);
        return v;
    }

    struct FSoftObjectPtrWrapper {

        static int __ctor(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                auto self = new FSoftObjectPtr();
                LuaObject::push<FSoftObjectPtr>(L, "FSoftObjectPtr", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            if (argc == 2) {
                auto path = lua_tostring(L, 2);
                FSoftObjectPath softObjectPath(UTF8_TO_TCHAR(path));
                auto self = new FSoftObjectPtr(softObjectPath);
                LuaObject::push<FSoftObjectPtr>(L, "FSoftObjectPtr", self, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPtr() error, argc=%d", argc);
            return 0;
        }

        static int clone(lua_State* L) {
            CheckSelf(FSoftObjectPtr);
            auto ret = __newFSoftObjectPtr();
            *ret = *self;
            LuaObject::push<FSoftObjectPtr>(L, "FSoftObjectPtr", ret, UD_AUTOGC | UD_VALUETYPE);
            return 1;
        }

        static int __gc(lua_State* L) {
            CheckSelfSafe(FSoftObjectPtr);
            SLUA_GCSTRUCT(FSoftObjectPtr);
            return 0;
        }

        static int ToSoftObjectPath(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPtr);
                auto ret = __newFSoftObjectPath();
                *ret = self->ToSoftObjectPath();
                LuaObject::push<FSoftObjectPath>(L, "FSoftObjectPath", ret, UD_AUTOGC | UD_VALUETYPE);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPtr::ToSoftObjectPath error, argc=%d", argc);
            return 0;
        }

        static int ToString(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPtr);
                auto ret = self->ToString();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPtr::ToString error, argc=%d", argc);
            return 0;
        }

        static int GetLongPackageName(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPtr);
                auto ret = self->GetLongPackageName();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPtr::GetLongPackageName error, argc=%d", argc);
            return 0;
        }

        static int GetAssetName(lua_State* L) {
            auto argc = lua_gettop(L);
            if (argc == 1) {
                CheckSelf(FSoftObjectPtr);
                auto ret = self->GetAssetName();
                LuaObject::push(L, ret);
                return 1;
            }
            luaL_error(L, "call FSoftObjectPtr::GetAssetName error, argc=%d", argc);
            return 0;
        }

        static void bind(lua_State* L) {
            AutoStack autoStack(L);
            LuaObject::newType(L, "FSoftObjectPtr");
            LuaObject::addMethod(L, "ToSoftObjectPath", ToSoftObjectPath, true);
            LuaObject::addMethod(L, "ToString", ToString, true);
            LuaObject::addMethod(L, "GetLongPackageName", GetLongPackageName, true);
            LuaObject::addMethod(L, "GetAssetName", GetAssetName, true);
            LuaObject::addMethod(L, "clone", clone, true);
            LuaObject::finishType(L, "FSoftObjectPtr", __ctor, __gc);
        }
    };

    void LuaWrapper::initExt(lua_State* L)
    {
        init(L);
        FSoftObjectPtrWrapper::bind(L);
    }
}