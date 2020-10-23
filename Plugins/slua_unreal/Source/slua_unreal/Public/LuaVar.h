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
#include "CoreMinimal.h"
#include "LuaObject.h"
#include "LuaCppBinding.h"
#include "Log.h"
#include <string>
#include <exception>
#include <utility>
#include <cstddef>

#ifdef _WIN32
#define strdup _strdup
#endif

namespace NS_SLUA {

    class SLUA_UNREAL_API LuaVar {
    public:
        enum Type {LV_NIL,LV_INT,LV_NUMBER,LV_BOOL,
            LV_STRING,LV_FUNCTION,LV_USERDATA,LV_LIGHTUD,LV_TABLE,LV_TUPLE};
        LuaVar();
        // copy construct for simple type
        LuaVar(lua_Integer v);
        LuaVar(int v);
        LuaVar(size_t v);
        LuaVar(lua_Number v);
		LuaVar(const char* v);
		LuaVar(const char* v, size_t len);
        LuaVar(bool v);

        LuaVar(lua_State* L,int p);
        LuaVar(lua_State* L,int p,Type t);

        LuaVar(const LuaVar& other):LuaVar() {
            clone(other);
        }
        LuaVar(LuaVar&& other):LuaVar() {
            move(MoveTemp(other));
        }

        void operator=(const LuaVar& other) {
            free();
            clone(other);
        }
        void operator=(LuaVar&& other) {
            free();
            move(MoveTemp(other));
        }

        virtual ~LuaVar();

        void set(lua_State* L,int p);
        void set(lua_Integer v);
        void set(int v);
        void set(lua_Number v);
		void set(const char* v, size_t len);
		void set(const LuaLString& lstr);
        void set(bool b);
		void free();

        // push luavar to lua state, 
        // if l is null, push luavar to L
        int push(lua_State *l=nullptr) const;

        bool isNil() const;
        bool isFunction() const;
        bool isTuple() const;
        bool isTable() const;
        bool isInt() const;
        bool isNumber() const;
        bool isString() const;
        bool isBool() const;
        bool isUserdata(const char* t) const;
        bool isLightUserdata() const;
        bool isValid() const;
        Type type() const;

        int asInt() const;
        int64 asInt64() const;
        float asFloat() const;
        double asDouble() const;
        const char* asString(size_t* outlen=nullptr) const;
		LuaLString asLString() const;
        bool asBool() const;
        void* asLightUD() const;
        template<typename T>
        T* asUserdata(const char* t) const {
            auto L = getState();
            push(L);
            UserData<T*>* ud = reinterpret_cast<UserData<T*>*>(luaL_testudata(L, -1, t));
            lua_pop(L,1);
            return ud?ud->ud:nullptr;
        }

        // iterate LuaVar if it's table
        // return true if has next item
        bool next(LuaVar& key,LuaVar& value);

        // return desc string for luavar, call luaL_tolstring
        const char* toString();


        template<class R>
        inline R castTo() {
            auto L = getState();
            push(L);
            R r = ArgOperatorOpt::readArg<typename remove_cr<R>::type>(L,-1);
            lua_pop(L,1);
            return MoveTemp(r);
        }


		template<typename R>
		inline void castTo(R& target) {
			if (isValid())
			{
				target = castTo<R>();
			}
		}

        // return count of luavar if it's table or tuple, 
        // otherwise it's return 1
        size_t count() const;

        // get at element by index if luavar is table or tuple
        LuaVar getAt(size_t index) const;

        // template function for return value
        template<typename R>
        R getAt(size_t index) const {
            return getAt(index).castTo<R>();
        }

        // if pos==-1 setAt push var to back of table,
        // otherwise push var to given position at pos
        template<typename T>
        void setAt(T v,int pos=-1) {
            ensure(isTable());
            auto L = getState();
            push(L);
            if(pos<=0) pos = lua_rawlen(L,-1)+1;
            LuaObject::push(L,v);
            lua_seti(L,-2,pos);
            lua_pop(L,1);
        }

        // get table by key, if luavar is table
        template<typename R,typename T>
        R getFromTable(T key,bool rawget=false) const {
            ensure(isTable());
            auto L = getState();
			if (!L) return R();
            AutoStack as(L);
            push(L);
            LuaObject::push(L,key);
			if (rawget) lua_rawget(L, -2);
			else lua_gettable(L,-2);
            return ArgOperatorOpt::readArg<typename remove_cr<R>::type>(L,-1);
        }

		template<typename R, typename T>
		void getFromTable(T key, R& target) const {
			target = getFromTable<R>(key);
		}

        // set table by key and value
        template<typename K,typename V>
        void setToTable(K k,V v) {
            ensure(isTable());
            auto L = getState();
            push(L);
            LuaObject::push(L,k);
            LuaObject::push(L,v);
            lua_settable(L,-3);
            lua_pop(L,1);
        }

        // call luavar if it's funciton
        // args is arguments passed to lua
        template<class ...ARGS>
        LuaVar call(ARGS&& ...args) const {
            if(!isFunction()) {
                Log::Error("LuaVar is not a function, can't be called");
                return LuaVar();
            }
            if(!isValid()) {
                Log::Error("State of lua function is invalid");
                return LuaVar();
            }
            auto L = getState();
            int n = pushArg(std::forward<ARGS>(args)...);
            int nret = docall(n);
            auto ret = LuaVar::wrapReturn(L,nret);
            lua_pop(L,nret);
            return ret;
        }

        template<class RET,class ...ARGS>
        RET call(ARGS&& ...args) const {
            LuaVar ret = call(std::forward<ARGS>(args)...);
            return ret.castTo<RET>();
        }

		template<class ...ARGS>
		LuaVar callField(const char* field, ARGS&& ...args) const {
			if (!isTable()) {
				Log::Error("LuaVar is not a table, can't call field");
				return LuaVar();
			}
			if (!isValid()) {
				Log::Error("State of lua function is invalid");
				return LuaVar();
			}
			LuaVar ret = getFromTable<LuaVar>(field);
			return ret.call(std::forward<ARGS>(args)...);
		}

        // call function with pre-pushed n args
        inline LuaVar callWithNArg(int n) {
            auto L = getState();
            int nret = docall(n);
            auto ret = LuaVar::wrapReturn(L,nret);
            lua_pop(L,nret);
            return ret;
        }

        bool toProperty(FProperty* p,uint8* ptr);
        bool callByUFunction(UFunction* ufunc,uint8* parms,struct FOutParmRec *outParams=nullptr,RESULT_DECL=nullptr,LuaVar* pSelf=nullptr);

		// get associate state
		lua_State* getState() const;
    private:
        friend class LuaState;

        // used to create number n of tuple
        LuaVar(lua_State* L,size_t n);

        void init(lua_State* L,int p,Type t);
        void initTuple(lua_State* L,size_t n);

        void alloc(int n);

        struct Ref {
            Ref():refCount(1) {}
            virtual ~Ref() {}
            void addRef() {
				refCount++;
            }
            void release() {
                ensure(refCount >0);
                if(--refCount ==0) {
                    delete this;
                }
            }
            int refCount;
        };

        struct RefStr : public Ref {
			RefStr(const char* s, size_t len)
				:Ref()
            {
				if (len == 0) len = strlen(s);
				// alloc extra space for '\0'
				buf = (char*) FMemory::Malloc(len+1);
				FMemory::Memcpy(buf, s, len);
				buf[len] = 0;
				length = len;
			}
            virtual ~RefStr() {
                FMemory::Free(buf);
            }
            char* buf;
			size_t length;
        };

        struct RefRef: public Ref {
            RefRef(lua_State* l);
            virtual ~RefRef();
            bool isValid() {
                return ref != LUA_NOREF;
            }
            void push(lua_State* l) {
                lua_geti(l,LUA_REGISTRYINDEX,ref);
            }
            int ref;
            int stateIndex;
        };

        int stateIndex;

        typedef struct {
            union {
                RefRef* ref;
                lua_Integer i;
                lua_Number d;
                RefStr* s;
                void* ptr;
                bool b;
            };
            Type luatype;
        } lua_var;

        lua_var* vars;
        size_t numOfVar;
    
        template<class F,class ...ARGS>
        int pushArg(F f,ARGS&& ...args) const {
            auto L = getState();
            LuaObject::push(L,f);
            return 1+pushArg(std::forward<ARGS>(args)...);
        }

        int pushArg() const {
            return 0;
        }

        static LuaVar wrapReturn(lua_State* L,int n) {
            ensure(n>=0);
            if(n==0)
                return LuaVar();
            else if (n==1)
                return LuaVar(L,-1);
            else
                return LuaVar(L,(size_t) n);
        }

        int docall(int argn) const;
        int pushArgByParms(FProperty* prop,uint8* parms);

        void clone(const LuaVar& other);
        void move(LuaVar&& other);
        void varClone(lua_var& tv,const lua_var& ov) const;
        void pushVar(lua_State* l,const lua_var& ov) const;
    };

    template<>
    inline LuaVar LuaObject::checkValue(lua_State* L, int p) {
        return LuaVar(L,p);
    }

	template<>
	inline void LuaVar::castTo()
	{
		return;
	}
    
}