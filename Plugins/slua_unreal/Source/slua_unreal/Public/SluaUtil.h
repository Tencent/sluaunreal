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

}