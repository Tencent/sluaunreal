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

namespace NS_SLUA {

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

	template<typename CallableType, typename ReturnType, typename ... ArgTypes>
	struct CallableExpand
	{
		typedef CallableType* FuncType;
		typedef TFunction<ReturnType(ArgTypes...)> TFunctionType;

		inline static ReturnType invoke(lua_State* L, void* ptr, ArgTypes&& ... args)
		{
			return Func != nullptr ? (*Func)(std::forward<ArgTypes>(args)...) : ReturnType();
		}

		inline static TFunctionType makeTFunctionProxy(lua_State* L, int p);

		static int LuaCFunction(lua_State* L);

		static FuncType Func;
	};

	template<typename CallableType, typename ReturnType, typename ... ArgTypes>
	typename CallableExpand<CallableType, ReturnType, ArgTypes ...>::FuncType CallableExpand<CallableType, ReturnType, ArgTypes ...>::Func = nullptr;
			
	template<typename CallableType>
	struct LuaCallableBinding
	{
		template<typename ClassType, typename ReturnType, typename ... ArgType>
		static auto DeducePrototype(ReturnType(ClassType::*)(ArgType ...) const)
		{
			return CallableExpand<CallableType, ReturnType, ArgType ...>();
		}

		template<typename ClassType, typename ReturnType, typename ... ArgType>
		static auto DeducePrototype(ReturnType(ClassType::*)(ArgType ...))
		{
			return CallableExpand<CallableType, ReturnType, ArgType ...>();
		}

		typedef decltype(DeducePrototype(&CallableType::operator())) Prototype;
	};

	struct ArgOperator {

		template <typename T>
		static typename std::enable_if<TIsTArray<T>::Value, T>::type readArg(lua_State * L, int p) {
			return LuaObject::checkTArray<T>(L, p);
		}

		template <typename T>
		static typename std::enable_if<TIsTMap<T>::Value, T>::type readArg(lua_State * L, int p) {
			return LuaObject::checkTMap<T>(L, p);
		}

		template <typename T>
		static typename std::enable_if<TIsTSet<T>::Value, T>::type readArg(lua_State * L, int p) {
            return LuaObject::checkTSet<T>(L, p);
		}

		template <typename T>
		static typename std::enable_if<std::is_enum<T>::value, T>::type readArg(lua_State * L, int p) {
			return LuaObject::checkEnumValue<T>(L, p);
		}

		template <typename T> struct TIsTFunction { enum { Value = false }; };
		template <typename FuncType> struct TIsTFunction<TFunction<FuncType>> { enum { Value = true }; };

		template <typename T>
		static typename std::enable_if<TIsTFunction<T>::Value, T>::type readArg(lua_State * L, int p) {
			return LuaCallableBinding<T>::Prototype::makeTFunctionProxy(L, p); 
		}

		template <typename T>
		static typename std::enable_if<!TIsTArray<T>::Value && !TIsTMap<T>::Value && !TIsTFunction<T>::Value && !std::is_enum<T>::value, T>::type readArg(lua_State * L, int p) {
			return LuaObject::checkValue<T>(L, p);
		}

	};

	struct ArgOperatorOpt {

		template <typename T>
		static typename std::enable_if<TIsTArray<T>::Value, T>::type readArg(lua_State * L, int p) {
			if (!lua_isuserdata(L, p))
				return T();
			return LuaObject::checkTArray<T>(L, p);
		}

		template <typename T>
		static typename std::enable_if<TIsTMap<T>::Value, T>::type readArg(lua_State * L, int p) {
			if (!lua_isuserdata(L, p))
				return T();
			return LuaObject::checkTMap<T>(L, p);
		}

		template <typename T>
		static typename std::enable_if<TIsTSet<T>::Value, T>::type readArg(lua_State * L, int p) {
            if (!lua_isuserdata(L, p))
                return T();
            return LuaObject::checkTSet<T>(L, p);
		}

		template <typename T>
		static typename std::enable_if<std::is_enum<T>::value, T>::type readArg(lua_State * L, int p) {
			if (!lua_isinteger(L, p))
				return T();
			return LuaObject::checkEnumValue<T>(L, p);
		}

		template <typename T> struct TIsTFunction { enum { Value = false }; };
		template <typename FuncType> struct TIsTFunction<TFunction<FuncType>> { enum { Value = true }; };

		template <typename T>
		static typename std::enable_if<TIsTFunction<T>::Value, T>::type readArg(lua_State * L, int p) {
			if (!lua_isfunction(L, p))
				return T();
			return LuaCallableBinding<T>::Prototype::makeTFunctionProxy(L, p);
		}

		template <typename T>
		static typename std::enable_if<!TIsTArray<T>::Value && !TIsTMap<T>::Value && !TIsTFunction<T>::Value && !std::is_enum<T>::value, T>::type readArg(lua_State * L, int p) {
			return LuaObject::checkValueOpt<T>(L, p);
		}

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

            // index is int-list based 0, so should plus Offset to get first arg 
            // (not include obj ptr if it's a member function)
            static T invoke(lua_State * L,void* ptr) {
                return target(L, ptr, ArgOperator::readArg<typename remove_cr<Args>::type>(L, index + Offset)...);
            }
        };

        template<typename VT, bool value = std::is_pointer<T>::value>
        struct ReturnPointer {
            constexpr static void* GetValue(VT& t) {
                return (void*)t;
            }
        };

        template<typename VT>
        struct ReturnPointer<VT, false> {
            constexpr static void* GetValue(VT& t) {
                return (void*)(&t);
            }
        };

        static int invoke(lua_State * L,void* ptr) {
            // make int list for arg index
            using I = MakeIntList<sizeof...(Args)>;
            T ret = Functor<I>::invoke(L,ptr);
            void* v = ReturnPointer<T>::GetValue(ret);
            if(v==nullptr) return LuaObject::pushNil(L);
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

            // index is int-list based 0, so should plus Offset to get first arg 
            // (not include obj ptr if it's a member function)
            static void invoke(lua_State * L,void* ptr) {
                target(L, ptr, ArgOperator::readArg<typename remove_cr<Args>::type>(L, index + Offset)...);
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

		static constexpr bool IsStatic = !std::is_member_function_pointer<decltype(func)>::value;

        static RET invoke(lua_State* L,void* ptr,ARG&&... args) {
            return func( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            using f = FunctionBind<decltype(&invoke), invoke, Offset>;
            return f::invoke(L,nullptr);
        }
    };

    template<typename T,typename RET,typename ...ARG,RET (T::*func)(ARG...) const>
    struct LuaCppBinding< RET (T::*)(ARG...) const, func> {

		static constexpr bool IsStatic = !std::is_member_function_pointer<decltype(func)>::value;

        static RET invoke(lua_State* L,void* ptr,ARG&&... args) {
            T* thisptr = (T*)ptr;
            return (thisptr->*func)( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            // check and get obj ptr;
            void* p = LuaObject::checkUD<T>(L,1);
            using f = FunctionBind<decltype(&invoke), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    template<typename T,typename RET,typename ...ARG,RET (T::*func)(ARG...)>
    struct LuaCppBinding< RET (T::*)(ARG...), func> {

		static constexpr bool IsStatic = !std::is_member_function_pointer<decltype(func)>::value;

        static RET invoke(lua_State* L,void* ptr,ARG&&... args) {
            T* thisptr = (T*)ptr;
            return (thisptr->*func)( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            // check and get obj ptr;
            void* p = LuaObject::checkUD<T>(L,1);
            using f = FunctionBind<decltype(&invoke), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    template<typename T,typename ...ARG,void (T::*func)(ARG...)>
    struct LuaCppBinding< void (T::*)(ARG...), func> {

		static constexpr bool IsStatic = !std::is_member_function_pointer<decltype(func)>::value;

        static void invoke(lua_State* L,void* ptr,ARG&&... args) {
            T* thisptr = (T*)ptr;
            (thisptr->*func)( std::forward<ARG>(args)... );
        }

        static int LuaCFunction(lua_State* L) {
            // check and get obj ptr;
            T* p = LuaObject::checkUD<T>(L,1);
            using f = FunctionBind<decltype(&invoke), invoke, 2>;
            return f::invoke(L,p);
        }
    };

    template<int (*func)(lua_State* L),int Offset>
    struct LuaCppBinding< int (lua_State* L), func, Offset> {

        static int LuaCFunction(lua_State* L) {
            return func(L);
        }
	};

    template<int Offset>
    struct LuaCppBinding<decltype(nullptr), nullptr, Offset> {

        static int LuaCFunction(lua_State* L) {
            luaL_error(L,"Can't be accessed");
            return 0;
        }
    };

	template<typename CallableType, typename ReturnType, typename ... ArgTypes>
	int CallableExpand<CallableType, ReturnType, ArgTypes...>::LuaCFunction(lua_State* L)
	{
		return FunctionBind<decltype(&invoke), invoke, 1>::invoke(L, nullptr);
	}

    struct SLUA_UNREAL_API LuaClass {
        LuaClass(lua_CFunction reg);
        static void reg(lua_State* L);
    };

    template <typename C,typename U=void>
    struct TypeNameFromPtr {
        static const char* value(C*) {
            return nullptr;
        }
    };

    template <typename C>
    struct TypeNameFromPtr<C,
        typename std::enable_if<
            // check if C has a member function named LUA_typename
            std::is_convertible< decltype(std::declval<C>().LUA_typename()), const char*>::value
        >::type
    > {
        static const char* value(C* ptr) {
            return ptr->LUA_typename();
        }
    };

    template<typename T>
    inline const char* typeNameFromPtr(T* ptr) {
        return TypeNameFromPtr<T>::value(ptr);
    }

    inline int NoConstructor(lua_State* L) {
        luaL_error(L,"Can't be call");
        return 0;
    }

    #define LuaClassBody() \
        public: \
        virtual SimpleString LUA_typename() const { \
            return TypeName<decltype(this)>::value(); \
        } \

    #define __DefTypeName(CLS) \
        template<> \
        SimpleString TypeName<CLS>::value() { \
            return SimpleString(#CLS); \
        } \

    #define __DefTypeNameExtern(MODULE_API,CLS) \
        template<> \
        MODULE_API SimpleString TypeName<CLS>::value() { \
            return SimpleString(#CLS); \
        } \
    
    #define __DefLuaClassTail(CLS) \
        static int Lua##CLS##_gc(lua_State* L) { \
            UserData<CLS*>* UD = reinterpret_cast<UserData<CLS*>*>(lua_touserdata(L,1)); \
            if(UD->flag & UD_AUTOGC) delete UD->ud; \
            return 0;\
        } \
        static int Lua##CLS##_tostring(lua_State* L) { \
            void* p = lua_touserdata(L,1); \
            char buf[128]; \
            snprintf(buf,128,"%s(@%p)",#CLS,p); \
            lua_pushstring(L,buf); \
            return 1; \
        } \
        static int Lua##CLS##_setup(lua_State* L); \
        static LuaClass Lua##CLS##__(Lua##CLS##_setup); \
        int Lua##CLS##_setup(lua_State* L) { \
			static_assert(!std::is_base_of<UObject, CLS>::value, "UObject class shouldn't use LuaCppBinding. Use REG_EXTENSION instead."); \
            AutoStack autoStack(L); \

    #define DefLuaClassBase(CLS) \
        __DefTypeName(CLS) \
        __DefLuaClassTail(CLS) \

    #define DefLuaClassBaseExtern(MODULE_API,CLS) \
        __DefTypeNameExtern(CLS,MODULE_API) \
        __DefLuaClassTail(CLS) \

    #define DefLuaClass(CLS, ...) \
        DefLuaClassBase(CLS) \
        LuaObject::newTypeWithBase(L,#CLS,std::initializer_list<const char*>{#__VA_ARGS__}); \

    #define DefLuaClassExtern(MODULE_API,CLS, ...) \
        DefLuaClassBaseExtern(MODULE_API,CLS) \
        LuaObject::newTypeWithBase(L,#CLS,std::initializer_list<const char*>{#__VA_ARGS__}); \

    #define EndDef(CLS,M)  \
        lua_CFunction x=LuaCppBinding<decltype(M),M,2>::LuaCFunction; \
        LuaObject::finishType(L, #CLS, x, Lua##CLS##_gc, Lua##CLS##_tostring); \
        return 0; } \

    #define DefLuaMethod(NAME,M) { \
        lua_CFunction x=LuaCppBinding<decltype(M),M>::LuaCFunction; \
        constexpr bool inst=std::is_member_function_pointer<decltype(M)>::value; \
        LuaObject::addMethod(L, #NAME, x, inst); \
    } \

    #define DefLuaMethod_With_Type(NAME,M,T) { \
        lua_CFunction x=LuaCppBinding<T,M>::LuaCFunction; \
        constexpr bool inst=std::is_member_function_pointer<T>::value; \
        LuaObject::addMethod(L, #NAME, x, inst); \
    } \

    #define DefLuaMethod_With_Lambda(NAME,Static,...) { \
        static auto lambda = __VA_ARGS__; \
		using BindType = LuaCallableBinding<decltype(lambda)>::Prototype; \
		BindType::Func = &lambda; \
		LuaObject::addMethod(L, #NAME, BindType::LuaCFunction, !Static); \
    }

	#define DefLuaProperty(NAME,GET,SET,INST) { \
        lua_CFunction get=LuaCppBinding<decltype(GET),GET>::LuaCFunction; \
        lua_CFunction set=LuaCppBinding<decltype(SET),SET>::LuaCFunction; \
        LuaObject::addField(L,#NAME,get,set,INST); \
    }

    #define DefGlobalMethod(NAME,M) { \
        lua_CFunction x=LuaCppBinding<decltype(M),M>::LuaCFunction; \
        LuaObject::addGlobalMethod(L, #NAME, x); \
    } \

    #define DefGlobalMethod_With_Type(NAME,M,T) { \
        lua_CFunction x=LuaCppBinding<T,M>::LuaCFunction; \
        LuaObject::addGlobalMethod(L, #NAME, x); \
    } \

    #define DefGlobalMethod_With_Imp(NAME,BODY) { \
        LuaObject::addGlobalMethod(L, #NAME,[](lua_State* L)->int BODY); }

    #define DefGlobalMethod_With_Lambda(NAME,...) { \
        static auto lambda = __VA_ARGS__; \
        using BindType = LuaCallableBinding<decltype(lambda)>::Prototype; \
        BindType::Func = &lambda; \
        LuaObject::addGlobalMethod(L, #NAME, BindType::LuaCFunction); \
    }

	#define DefEnum(NAME,...) \
		static int LuaEnum##NAME##_setup(lua_State* L) { \
			LuaObject::newEnum(L, #NAME, #__VA_ARGS__, std::initializer_list<int>{(int)__VA_ARGS__}); \
			return 0;\
		} \
		static LuaClass LuaEnum##NAME##__(LuaEnum##NAME##_setup); \

	#define DefEnumClass(NAME,...) \
		static int LuaEnum##NAME##_setup(lua_State* L) { \
			LuaObject::newEnum(L, #NAME, #__VA_ARGS__, std::initializer_list<NAME>{__VA_ARGS__}); \
			return 0;\
		} \
		static LuaClass LuaEnum##NAME##__(LuaEnum##NAME##_setup); \

    #define REG_EXTENSION_METHOD(U,N,M) { \
		using BindType = LuaCppBinding<decltype(M),M>; \
        LuaObject::addExtensionMethod(U::StaticClass(),N,BindType::LuaCFunction, BindType::IsStatic); }

    #define REG_EXTENSION_METHOD_WITHTYPE(U,N,M,T) { \
		using BindType = LuaCppBinding<T,M>; \
        LuaObject::addExtensionMethod(U::StaticClass(),N,BindType::LuaCFunction, BindType::IsStatic); }

    #define REG_EXTENSION_METHOD_IMP(U,N,BODY) { \
        LuaObject::addExtensionMethod(U::StaticClass(),N,[](lua_State* L)->int BODY); }

    #define REG_EXTENSION_METHOD_IMP_STATIC(U,N,BODY) { \
        LuaObject::addExtensionMethod(U::StaticClass(),N,[](lua_State* L)->int BODY,true); }

	#define REG_EXTENSION_METHOD_LAMBDA(U,N, Static, LAMBDA) { \
		static auto lambda = LAMBDA; \
		using BindType = LuaCallableBinding<decltype(lambda)>::Prototype; \
		BindType::Func = &lambda; \
		LuaObject::addExtensionMethod(U::StaticClass(), N, BindType::LuaCFunction, Static); \
	}

	#define REG_EXTENSION_PROPERTY(U,N,GETTER,SETTER) { \
		using GetType = LuaCppBinding<decltype(GETTER),GETTER>; \
		using SetType = LuaCppBinding<decltype(SETTER),SETTER>; \
        LuaObject::addExtensionProperty(U::StaticClass(),N,GetType::LuaCFunction,SetType::LuaCFunction,GetType::IsStatic); }

}

