// The MIT License (MIT)

// Copyright 2015 Siney/Pangweiwei siney@yeah.net
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include "lua/lua.hpp"
#include <utility>
#include <cstddef>

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
            static T invoke(lua_State * L,void* ptr) noexcept {
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
            static AT readArg(lua_State * L, int p) {
                return LuaObject::checkValue<AT>(L,p);
            }

            // index is int-list based 0, so should plus Offset to get first arg 
            // (not include obj ptr if it's a member function)
            static void invoke(lua_State * L,void* ptr) noexcept {
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

    template<typename T>
    struct TypeName {
        static const char* value();
    };

    template<typename T>
    struct LuaValuePush {
        static int push(lua_State* L,T);
    };

    template<typename T,T>
    struct LuaCppBinding;

    template<typename RET,typename ...ARG,RET (*func)(ARG...)>
    struct LuaCppBinding< RET (*)(ARG...), func> {
        static int LuaCFunction(lua_State* L) {
            return 0;
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
            if(!p) luaL_error(L,"expect userdata %s",TypeName<T>::value());
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
            if(!p) luaL_error(L,"expect userdata %s",TypeName<T>::value());
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
            if(!p) luaL_error(L,"expect userdata %s",TypeName<T>::value());
            using f = FunctionBind<void (*)(lua_State *, void*, ARG...), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    #define DefLuaClass(CLS) \
        template<> \
        struct TypeName<CLS> { \
            static const char* value() { \
                return #CLS; \
            } \
        }; \
        int Lua##CLS##_setupMT(lua_State* L) { \
        LuaObject::setupMTSelfSearch(L); \
        
    #define EndDef()  return 0; }

    //#define DefLuaMethod(M) 
    #define DefLuaMethod(NAME,M) { lua_CFunction x=LuaCppBinding<decltype(M),M>::LuaCFunction; \
        lua_pushcfunction(L,x); \
        lua_setfield(L,-2,#NAME); \
    }

    #define LuaClass(CLS) Lua##CLS##_setupMT
}

