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
#include "CoreMinimal.h"
#include "LuaObject.h"
#include "lua/lua.hpp"
#include "Log.h"
#include <string>
#include <exception>

#if defined(_NOEXCEPT)
#define __NOEXCEPT _NOEXCEPT
#elif defined(_GLIBCXX_NOEXCEPT)
#define __NOEXCEPT _GLIBCXX_NOEXCEPT
#else
#define __NOEXCEPT noexcept
#endif

namespace slua {

    class SLUA_UNREAL_API LuaVarExcetpion : public std::exception {
    public:
        LuaVarExcetpion(const char* err):errormsg(err) {}
        virtual const char* what() const __NOEXCEPT {
            return TCHAR_TO_UTF8(*errormsg);
        }
    private:
        FString errormsg;
    };

    class SLUA_UNREAL_API LuaVarBadCastException : public LuaVarExcetpion {
    public:
        LuaVarBadCastException():LuaVarExcetpion("bad cast") {}
    };

    class SLUA_UNREAL_API LuaVarBadCall : public LuaVarExcetpion {
    public:
        LuaVarBadCall(const char* err):LuaVarExcetpion(err) {}
    };

    class SLUA_UNREAL_API LuaVar {
    public:
        enum Type {LV_NIL,LV_INT,LV_NUMBER,LV_BOOL,LV_STRING,LV_FUNCTION,LV_TABLE,LV_TUPLE};
        LuaVar();
        
        LuaVar(lua_State* L,int p);
        LuaVar(lua_State* L,int p,Type t);
        LuaVar(lua_State* L,lua_Integer v);
        LuaVar(lua_State* L,lua_Number v);
        LuaVar(lua_State* L,const char* v);

        LuaVar(const LuaVar& other):LuaVar() {
            clone(other);
        }
        LuaVar(LuaVar&& other):LuaVar() {
            move(std::move(other));
        }

        void operator=(const LuaVar& other) {
            free();
            clone(other);
        }
        void operator=(LuaVar&& other) {
            free();
            move(std::move(other));
        }

        virtual ~LuaVar();

        void set(lua_State* L,int p);
        void set(lua_Integer v);
        void set(lua_Number v);
        void set(const char* v);
        void set(bool b);

        int push(lua_State *l=nullptr) const;

        bool isNil() const;
        bool isFunction() const;
        bool isTuple() const;
        bool isTable() const;
        Type type() const;

        int asInt() const;
        float asFloat() const;
        double asDouble() const;
        const char* asString() const;
        bool asBool() const;

        size_t count() const;
        LuaVar getAt(size_t index) const;
        LuaVar getFromTable(const LuaVar& key) const;
        void setToTable(const LuaVar& key,const LuaVar& value);

        template<class ...ARGS>
        LuaVar call(ARGS ...args) {
            if(!isFunction()) {
                Log::Error("LuaVar is not a function, can't be called");
                return LuaVar();
            }

            int n = pushArg(args...);
            int nret = docall(n);
            auto ret = LuaVar::wrapReturn(L,nret);
            lua_pop(L,nret);
            return ret;
        }

        template<class T>
        static T autocast(const LuaVar& lv);

        template<class RET,class ...ARGS>
        RET call(ARGS ...args) {
            LuaVar ret = call(args...);
            return autocast<RET>(ret);
        }

        bool toProperty(UProperty* p,uint8* ptr);
        void callByUFunction(UFunction* ufunc,uint8* parms);
    private:
        friend class LuaState;
        // init number n of element
        LuaVar(int n);
        // used to create number n of tuple
        LuaVar(lua_State* L,size_t n);

        void init(lua_State* L,int p,Type t);
        void initTuple(size_t n);

        void free();
        void alloc(int n);

        struct Ref {
            Ref():ref(1) {}
            virtual ~Ref() {}
            void addRef() {
                ref++;
            }
            void release() {
                ensure(ref>0);
                if(--ref==0) {
                    delete this;
                }
            }
            int ref;
        };

        struct RefStr : public Ref {
            RefStr(const char* s)
                :Ref()
                ,str(strdup(s))
            {}
            virtual ~RefStr() {
                ::free(str);
            }
            char* str;
        };

        struct RefRef: public Ref {
            RefRef(lua_State* l):Ref() {
                this->L = l;
                ref=luaL_ref(l,LUA_REGISTRYINDEX);
            }
            virtual ~RefRef() {
                luaL_unref(L,LUA_REGISTRYINDEX,ref);
            }
            bool isValid() {
                return ref != LUA_NOREF;
            }
            void push(lua_State* l) {
                lua_geti(l,LUA_REGISTRYINDEX,ref);
            }
            int ref;
            lua_State* L;
        };

        lua_State* L;
        typedef struct {
            union {
                RefRef* ref;
                lua_Integer i;
                lua_Number d;
                RefStr* s;
                bool b;
            };
            Type luatype;
        } lua_var;

        lua_var* vars;
        size_t numOfVar;
    
        template<class F,class ...ARGS>
        int pushArg(F f,ARGS ...args) {
            LuaObject::push(L,f);
            return 1+pushArg(args...);
        }

        int pushArg() {
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

        int docall(int argn);
        int pushArgByParms(UProperty* prop,uint8* parms);

        void clone(const LuaVar& other);
        void move(LuaVar&& other);
        void varClone(lua_var& tv,const lua_var& ov) const;
        void pushVar(lua_State* l,const lua_var& ov) const;
    };


    template<>
    inline int LuaVar::autocast(const LuaVar& lv) {
        return lv.asInt();
    }

    template<>
    inline float LuaVar::autocast(const LuaVar& lv) {
        return lv.asFloat();
    }

    template<>
    inline double LuaVar::autocast(const LuaVar& lv) {
        return lv.asDouble();
    }

    template<>
    inline bool LuaVar::autocast(const LuaVar& lv) {
        return lv.asBool();
    }

    template<>
    inline const char* LuaVar::autocast(const LuaVar& lv) {
        return lv.asString();
    }
}