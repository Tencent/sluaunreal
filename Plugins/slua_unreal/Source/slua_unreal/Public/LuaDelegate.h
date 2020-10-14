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
#include "SluaUtil.h"
#include "LuaObject.h"
#include "LuaDelegate.generated.h"

namespace NS_SLUA {
    class LuaVar;
}

UCLASS()
class SLUA_UNREAL_API ULuaDelegate : public UObject {
    GENERATED_UCLASS_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Lua|Delegate")
	void EventTrigger();

    ~ULuaDelegate();

    virtual void ProcessEvent( UFunction* Function, void* Parms );
    void bindFunction(NS_SLUA::lua_State *L, int p, UFunction *func);
    void bindFunction(NS_SLUA::lua_State *L, int p);
    void bindFunction(UFunction *func);
	void dispose();

#if WITH_EDITOR
	void setPropName(FString name) {
		pName = name;
	}

	FString getPropName() {
		return pName;
	}
#endif

private:
    NS_SLUA::LuaVar* luafunction;
    UFunction* ufunction;
#if WITH_EDITOR
	FString pName;
#endif
};

namespace NS_SLUA {

    class SLUA_UNREAL_API LuaMultiDelegate {
    public:
        static int push(lua_State* L,FMulticastScriptDelegate* delegate,UFunction* ufunc, FString pName);
    private:
        static int setupMT(lua_State* L);
        static int Add(lua_State* L);
        static int Remove(lua_State* L);
        static int Clear(lua_State* L);
        static int gc(lua_State* L);
    };

	template<typename R, typename ...ARGS>
	struct LuaDelegateWrapT {
		TBaseDelegate<R, ARGS...>& delegate;

		LuaDelegateWrapT(TBaseDelegate<R, ARGS...>& d) :delegate(d) {}
	};


	template<typename R, typename ...ARGS>
	struct TypeName<LuaDelegateWrapT<R, ARGS...>, false> {

		static SimpleString value() {
			SimpleString str;
			str.append("LuaDelegateWrapT_");
			MakeGeneircTypeName<R, ARGS...>::get(str,",");
			return str;
		}
	};

	class SLUA_UNREAL_API LuaDelegate {
	public:
		static int push(lua_State* L, FScriptDelegate* delegate, UFunction* ufunc, FString pName);

		template<class R, class ...ARGS>
		static int push(lua_State* L, TBaseDelegate<R, ARGS...>& delegate) {
			using T = LuaDelegateWrapT<R, ARGS...>;
			auto wrapobj = new T(delegate);
 			return LuaObject::pushType<T*>(L, wrapobj,
				TypeName<T>::value().c_str(), setupMTT<R,ARGS...>, gcT<R,ARGS...>);
		}

	private:
		static int setupMT(lua_State* L);
		static int Bind(lua_State* L);
		static int Clear(lua_State* L);
		static int gc(lua_State* L);

		template<class R, class ...ARGS>
		static int setupMTT(lua_State* L) {
			LuaObject::setupMTSelfSearch(L);
			lua_CFunction bind = BindT<R, ARGS...>;
			lua_CFunction clear = ClearT<R, ARGS...>;
			RegMetaMethodByName(L, "Bind", bind);
			RegMetaMethodByName(L, "Clear", clear);
			return 0;
		}

		template<class R, class ...ARGS>
		static int gcT(lua_State* L) {
			LuaDelegateWrapT<R, ARGS...>* ud = LuaObject::checkUD<LuaDelegateWrapT<R, ARGS...>>(L, 1);
			delete ud;
			return 0;
		}

		template<class R, class ...ARGS>
		static int BindT(lua_State* L) {
			LuaDelegateWrapT<R, ARGS...>* ud = LuaObject::checkUD<LuaDelegateWrapT<R, ARGS...>>(L,1);
			luaL_checktype(L, 2, LUA_TFUNCTION);
			LuaVar func(L, 2);
			if (func.isValid() && func.isFunction())
			{
				ud->delegate.BindLambda([=](ARGS ...args) {
					LuaVar result = func.call(std::forward<ARGS>(args) ...);
					return result.castTo<R>();
				});
			}
			return 0;
		}

		template<class R, class ...ARGS>
		static void clearT(LuaDelegateWrapT<R, ARGS...>* ud) {
			ud->delegate.Unbind();
		}


		template<class R, class ...ARGS>
		static int ClearT(lua_State* L) {
			LuaDelegateWrapT<R, ARGS...>* ud = LuaObject::checkUD<LuaDelegateWrapT<R, ARGS...>>(L, 1);
			if(ud) clearT(ud);
			return 0;
		}
	};

	template<class R, class ...ARGS>
	int LuaObject::push(lua_State* L, TBaseDelegate<R, ARGS...>& delegate) {
		return LuaDelegate::push(L,delegate);
	}
}

