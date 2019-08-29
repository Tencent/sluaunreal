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
#include <functional>

#ifndef SafeDelete
#define SafeDelete(ptr) if(ptr) { delete ptr;ptr=nullptr; }
#endif

namespace slua {

    template<typename T>
    struct AutoDeleteArray {
        AutoDeleteArray(T* p):ptr(p) {}
        ~AutoDeleteArray() { delete[] ptr; }
        T* ptr;
    };

    struct Defer {
        Defer(const std::function<void()>& f):func(f) {}
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
}