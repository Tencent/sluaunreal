// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#pragma once
#define LUA_LIB
#include "lua/lua.hpp"
#include <utility>
#include <cstddef>
#include <type_traits>
#include "SluaUtil.h"

namespace slua {

    template<int ...>
    struct IntList {};

    template <typename L, typename R>
    struct Concat;

    template <int... TL, int... TR>
    struct Concat<IntList<TL...>, IntList<TR...>> {
        typedef IntList<TL..., TR...> type;
    };

    template <int n>
    struct MakeIntList_t {
        typedef typename Concat< typename MakeIntList_t<n-1>::type,IntList<n-1>>::type type;
    };

    template <>
    struct MakeIntList_t<0> {
        typedef IntList<> type;
    };

    template <int n>
    using MakeIntList = typename MakeIntList_t<n>::type;


    template<typename T>
	struct remove_cr
	{
		typedef T type;
	};

    template<typename T>
	struct remove_cr<const T&>
	{
		typedef typename remove_cr<T>::type type;
	};

    template<typename T>
	struct remove_cr<T&>
	{
		typedef typename remove_cr<T>::type type;
	};

    template <typename T, T,int Offset>
    struct FunctionBind;

    template <lua_CFunction target,int Offset>
    struct FunctionBind<lua_CFunction, target, Offset> {
        static int invoke(lua_State * L) { 
            return target(L); 
        }
    };

    template <typename T,typename... Args,
          T (*target)(lua_State * L, void*, Args...),int Offset>
    struct FunctionBind<T (*)(lua_State * L, void* ,Args...), target, Offset> {
        
        template <typename X>
        struct Functor;

        template <int... index>
        struct Functor<IntList<index...>> {

            template <typename AT>
            static AT readArg(lua_State * L, int p) {
                return LuaObject::checkValue<AT>(L,p);
            }

            // index is int-list based 0, so should plus Offset to get first arg 
            // (not include obj ptr if it's a member function)
            static T invoke(lua_State * L,void* ptr) {
                return target(L, ptr, readArg<typename remove_cr<Args>::type>(L, index + Offset)...);
            }
        };

        static int invoke(lua_State * L,void* ptr) {
            // make int list for arg index
            using I = MakeIntList<sizeof...(Args)>;
            T ret = Functor<I>::invoke(L,ptr);
            return LuaObject::push(L,ret);
        }
    };

    template <typename... Args,
          void (*target)(lua_State * L, void*, Args...),int Offset>
    struct FunctionBind<void (*)(lua_State * L, void* ,Args...), target, Offset> {
        
        template <typename X>
        struct Functor;

        template <int... index>
        struct Functor<IntList<index...>> {

            template <typename AT>
            static typename TEnableIf<!TIsTArray<AT>::Value,AT>::Type readArg(lua_State * L, int p) {
                return LuaObject::checkValue<AT>(L,p);
            }

            template <typename AT>
            static typename TEnableIf<TIsTArray<AT>::Value,AT>::Type readArg(lua_State * L, int p) {
                return LuaObject::checkTArray<AT>(L,p);
            }

            // index is int-list based 0, so should plus Offset to get first arg 
            // (not include obj ptr if it's a member function)
            static void invoke(lua_State * L,void* ptr) {
                target(L, ptr, readArg<typename remove_cr<Args>::type>(L, index + Offset)...);
            }
        };

        static int invoke(lua_State * L,void* ptr) {
            // make int list for arg index
            using I = MakeIntList<sizeof...(Args)>;
            Functor<I>::invoke(L,ptr);
            return 0;
        }
    };

    template<typename T,T,int Offset=1>
    struct LuaCppBinding;

    template<typename RET,typename ...ARG,RET (*func)(ARG...),int Offset>
    struct LuaCppBinding< RET (*)(ARG...), func, Offset> {

        static RET invoke(lua_State* L,void* ptr,ARG... args) {
            return func( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            using f = FunctionBind<RET (*)(lua_State *, void*, ARG...), invoke, Offset>;
            return f::invoke(L,nullptr);
        }
    };



    template<typename T,typename RET,typename ...ARG,RET (T::*func)(ARG...) const>
    struct LuaCppBinding< RET (T::*)(ARG...) const, func> {

        static RET invoke(lua_State* L,void* ptr,ARG... args) {
            UserData<T*>* ud = reinterpret_cast<UserData<T*>*>(ptr);
            T* thisptr = ud->ud;
            return (thisptr->*func)( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            // check and get obj ptr;
            void* p = luaL_checkudata(L,1,TypeName<T>::value());
            using f = FunctionBind<RET (*)(lua_State *, void*, ARG...), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    template<typename T,typename RET,typename ...ARG,RET (T::*func)(ARG...)>
    struct LuaCppBinding< RET (T::*)(ARG...), func> {

        static RET invoke(lua_State* L,void* ptr,ARG... args) {
            UserData<T*>* ud = reinterpret_cast<UserData<T*>*>(ptr);
            T* thisptr = ud->ud;
            return (thisptr->*func)( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            // check and get obj ptr;
            void* p = luaL_checkudata(L,1,TypeName<T>::value());
            using f = FunctionBind<RET (*)(lua_State *, void*, ARG...), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    template<typename T,typename ...ARG,void (T::*func)(ARG...)>
    struct LuaCppBinding< void (T::*)(ARG...), func> {

        static void invoke(lua_State* L,void* ptr,ARG... args) {
            UserData<T*>* ud = reinterpret_cast<UserData<T*>*>(ptr);
            T* thisptr = ud->ud;
            (thisptr->*func)( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            // check and get obj ptr;
            void* p = luaL_checkudata(L,1,TypeName<T>::value());
            using f = FunctionBind<void (*)(lua_State *, void*, ARG...), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    struct SLUA_UNREAL_API LuaClass {
        LuaClass(lua_CFunction reg);

        static void reg(lua_State* L);
    };

    #define DefLuaClass(CLS) \
        template<> \
        const char* TypeName<CLS>::value() { \
            return #CLS; \
        } \
        static int Lua##CLS##_gc(lua_State* L) { \
            UserData<CLS*>* UD = reinterpret_cast<UserData<CLS*>*>(lua_touserdata(L,1)); \
            if(UD->owned) delete UD->ud; \
            return 0;\
        } \
        static int Lua##CLS##_setup(lua_State* L); \
        LuaClass Lua##CLS##__(Lua##CLS##_setup); \
        int Lua##CLS##_setup(lua_State* L) { \
            AutoStack autoStack(L); \
            LuaObject::newType(L,#CLS); \

    #define EndDef(CLS,M)  \
        lua_CFunction x=LuaCppBinding<decltype(M),M,2>::LuaCFunction; \
        LuaObject::finishType(L, #CLS, x, Lua##CLS##_gc); \
        return 0; } \

    #define DefLuaMethod(NAME,M) { \
        lua_CFunction x=LuaCppBinding<decltype(M),M>::LuaCFunction; \
        constexpr bool inst=std::is_member_function_pointer<decltype(M)>::value; \
        LuaObject::addMethod(L, #NAME, x, inst); \
    }
    
}

