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
#include "CoreMinimal.h"
#include "lua/lua.hpp"
#include "lua/lstate.h"
#include <functional>
#include <cstddef>
#include <cstring>
#include "SlateCore.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#ifndef SafeDelete
#define SafeDelete(ptr) if(ptr) { delete ptr;ptr=nullptr; }
#endif

namespace NS_SLUA {

	template<typename T>
	struct AutoDeleteArray {
		AutoDeleteArray(T* p) :ptr(p) {}
		~AutoDeleteArray() { delete[] ptr; }
		T* ptr;
	};

	struct Defer {
		Defer(const std::function<void()>& f) :func(f) {}
		~Defer() { func(); }
		const std::function<void()>& func;
	};

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

	template<typename T>
	struct remove_cr<T&&>
	{
		typedef typename remove_cr<T>::type type;
	};

	template<class T>
	struct remove_ptr_const
	{
		typedef T type;
	};

	template<class T>
	struct remove_ptr_const<const T*>
	{
		typedef T* type;
	};

	template<class T>
	bool typeMatched(int luatype) {
		if (std::is_same<T, int32>::value
			|| std::is_same<T, uint32>::value
			|| std::is_same<T, int64>::value
			|| std::is_same<T, uint64>::value
			|| std::is_same<T, int16>::value
			|| std::is_same<T, uint16>::value
			|| std::is_same<T, int8>::value
			|| std::is_same<T, uint8>::value
			|| std::is_same<T, double>::value
			|| std::is_same<T, float>::value
			|| std::is_enum<T>::value)
			return luatype == LUA_TNUMBER;
		else if (std::is_same<T, bool>::value)
			return luatype == LUA_TBOOLEAN;
		else if (std::is_same<T, const char*>::value
			|| std::is_same<T, FString>::value
			|| std::is_same<T, FText>::value)
			return luatype == LUA_TSTRING;
		else if (std::is_base_of<T, UObject>::value
			|| std::is_same<T, UObject>::value)
			return luatype == LUA_TUSERDATA;
		else if (std::is_same<T, void*>::value)
			return luatype == LUA_TLIGHTUSERDATA || luatype == LUA_TUSERDATA;
		else
			return luatype != LUA_TNIL && luatype != LUA_TNONE;
	}

	// modified FString::Split function to return left if no InS to search
	static bool strSplit(const FString& S, const FString& InS, FString* LeftS, FString* RightS, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase,
		ESearchDir::Type SearchDir = ESearchDir::FromStart)
	{
		if (S.IsEmpty()) return false;


		int32 InPos = S.Find(InS, SearchCase, SearchDir);

		if (InPos < 0) {
			*LeftS = S;
			*RightS = "";
			return true;
		}

		if (LeftS) { *LeftS = S.Left(InPos); }
		if (RightS) { *RightS = S.Mid(InPos + InS.Len()); }

		return true;
	}

	// why not use std::string?
	// std::string in unreal4 will caused crash
	// why not use FString
	// FString store wchar_t, we only need char
	struct SimpleString {
		TArray<char> data;
		void append(const char* str) {
			if (data.Num() > 0 && data[data.Num() - 1] == 0)
				data.RemoveAt(data.Num() - 1);
			for (auto it = str; *it; it++)
				data.Add(*it);
			data.Add(0);
		}
		void append(const SimpleString& str) {
			append(str.c_str());
		}
		const char* c_str() const {
			return data.GetData();
		}
		void clear() {
			data.Empty();
		}
		SimpleString(const char* str) { append(str); }
		SimpleString() {
			data.Add(0);
		}
	};

	template<typename T, bool isUObject = std::is_base_of<UObject, T>::value>
	struct TypeName {
		static SimpleString value();
	};

	template<typename T>
	struct TypeName<T, true> {
		static SimpleString value() {
			return "UObject";
		}
	};

	template<typename T>
	struct TypeName<const T, false> {
		static SimpleString value() {
			return TypeName<T>::value();
		}
	};

	template<typename T>
	struct TypeName<const T*, false> {
		static SimpleString value() {
			return TypeName<T>::value();
		}
	};

	template<typename T>
	struct TypeName<T*, false> {
		static SimpleString value() {
			return TypeName<T>::value();
		}
	};

#define DefTypeName(T) \
    template<> \
    struct TypeName<T, false> { \
        static SimpleString value() { \
            return SimpleString(#T);\
        }\
    };\

#define DefTypeNameWithName(T,TN) \
    template<> \
    struct TypeName<T, false> { \
        static SimpleString value() { \
            return SimpleString(#TN);\
        }\
    };\

	DefTypeName(void);
	DefTypeName(int32);
	DefTypeName(uint32);
	DefTypeName(int16);
	DefTypeName(uint16);
	DefTypeName(int8);
	DefTypeName(uint8);
	DefTypeName(float);
	DefTypeName(double);
	DefTypeName(FString);
	DefTypeName(bool);
	DefTypeName(lua_State);
	// add your custom Type-Maped here
	DefTypeName(FHitResult);
	DefTypeName(FActorSpawnParameters);
	DefTypeName(FSlateFontInfo);
	DefTypeName(FSlateBrush);
	DefTypeName(FMargin);
	DefTypeName(FGeometry);
	DefTypeName(FSlateColor);
	DefTypeName(FRotator);
	DefTypeName(FTransform);
	DefTypeName(FLinearColor);
	DefTypeName(FColor);
	DefTypeName(FVector);
	DefTypeName(FVector2D);
	DefTypeName(FRandomStream);
	DefTypeName(FGuid);
	DefTypeName(FBox2D);
	DefTypeName(FFloatRangeBound);
	DefTypeName(FFloatRange);
	DefTypeName(FInt32RangeBound);
	DefTypeName(FInt32Range);
	DefTypeName(FFloatInterval);
	DefTypeName(FInt32Interval);
	DefTypeName(FPrimaryAssetType);
	DefTypeName(FPrimaryAssetId);
	DefTypeName(FActorComponentTickFunction);
	DefTypeName(FDateTime);
	
	template<typename T,ESPMode mode>
	struct TypeName<TSharedPtr<T, mode>, false> {
		static SimpleString value() {
			SimpleString str;
			str.append("TSharedPtr<");
			str.append(TypeName<T>::value());
			str.append(">");
			return str;
		}
	};

	template<typename T>
	struct TypeName<TArray<T>, false> {
		static SimpleString value() {
			SimpleString str;
			str.append("TArray<");
			str.append(TypeName<T>::value());
			str.append(">");
			return str;
		}
	};
	template<typename K,typename V>
	struct TypeName<TMap<K,V>, false> {
		static SimpleString value() {
			SimpleString str;
			str.append("TMap<");
			str.append(TypeName<K>::value());
			str.append(",");
			str.append(TypeName<V>::value());
			str.append(">");
			return str;
		}
	};

	

	template<class R, class ...ARGS>
	struct MakeGeneircTypeName {
		static void get(SimpleString& output, const char* delimiter) {
			MakeGeneircTypeName<R>::get(output, delimiter);
			MakeGeneircTypeName<ARGS...>::get(output, delimiter);
		}
	};

	template<class R>
	struct MakeGeneircTypeName<R> {
		static void get(SimpleString& output, const char* delimiter) {
			output.append(TypeName<typename remove_cr<R>::type>::value());
			output.append(delimiter);
		}
	};

	// return true if T is UObject or is base of UObject
	template<class T>
	struct IsUObject {
		enum { value = std::is_base_of<UObject, T>::value || std::is_same<UObject, T>::value };
	};

	template<class T>
	struct IsUObject<T*> {
		enum { value = IsUObject<T>::value };
	};

	template<class T>
	struct IsUObject<const T*> {
		enum { value = IsUObject<T>::value };
	};
	
	// lua long string 
	// you can call push(L,{str,len}) to push LuaLString
	struct LuaLString {
		const char* buf;
		size_t len;
	};

	// SFINAE test class has a specified member function
	template <typename T>
	class Has_LUA_typename
	{
	private:
		typedef char WithType;
		typedef int WithoutType;

		template <typename C> 
		static WithType test(decltype(&C::LUA_typename));
		template <typename C> 
		static WithoutType test(...);

	public:
		enum { value = sizeof(test<T>(0)) == sizeof(WithType) };
	};

	FString SLUA_UNREAL_API getUObjName(UObject* obj);
	bool SLUA_UNREAL_API isUnrealStruct(const char* tn, UScriptStruct** out);


	int64_t SLUA_UNREAL_API getTime();
}