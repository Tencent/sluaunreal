// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaInterface.h"

namespace slua {
    struct LuaInterfaceImp : public LuaInterface {
        virtual const lua_Number *lua_version (lua_State *L) {
            return slua::lua_version(L);
        }
        virtual const char *lua_pushstring (lua_State *L, const char *s) {
            return slua::lua_pushstring(L,s);
        }
        virtual int lua_gettop (lua_State *L) {
            return slua::lua_gettop(L);
        }
        virtual void lua_settop (lua_State *L, int index) {
            slua::lua_settop(L,index);
        }
        virtual int lua_pcallk (lua_State *L,
                int nargs,
                int nresults,
                int msgh,
                lua_KContext ctx,
                lua_KFunction k) {
            return slua::lua_pcallk(L,nargs,nresults,msgh,ctx,k);
        }
        virtual void lua_pushnumber (lua_State *L, lua_Number n) {
            slua::lua_pushnumber(L,n);
        }
        virtual const char *luaL_checklstring (lua_State *L, int arg, size_t *l) {
            return slua::luaL_checklstring(L,arg,l);
        }
        virtual const char *lua_tolstring (lua_State *L, int index, size_t *len) {
            return slua::lua_tolstring(L,index,len);
        }
        virtual int lua_type (lua_State *L, int index) {
            return slua::lua_type(L,index);
        }
        virtual lua_Integer lua_tointegerx (lua_State *L, int index, int *isnum) {
            return slua::lua_tointegerx(L,index,isnum);
        }
        virtual void lua_pushnil (lua_State *L) {
            slua::lua_pushnil(L);
        }
        virtual int lua_getfield (lua_State *L, int index, const char *k) {
            return slua::lua_getfield(L,index,k);
        }
        virtual int lua_next (lua_State *L, int index) {
            return slua::lua_next(L,index);
        }
        virtual int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar) {
            return slua::lua_getinfo(L,what,ar);
        }
        virtual void lua_sethook (lua_State *L, lua_Hook f, int mask, int count) {
            slua::lua_sethook(L,f,mask,count);
        }
        virtual lua_Number luaL_checknumber (lua_State *L, int arg) {
            return slua::luaL_checknumber(L,arg);
        }
        virtual void lua_createtable (lua_State *L, int narr, int nrec) {
            slua::lua_createtable(L,narr,nrec);
        }
        virtual void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
            slua::luaL_setfuncs(L,l,nup);
        }
        virtual int lua_getglobal (lua_State *L, const char *name) {
            return slua::lua_getglobal(L,name);
        }
    };
}


extern "C" {
#if defined(_WIN32)
	__declspec(dllexport)
#else
	extern
#endif
	slua::LuaInterface* GetLuaInterface() {
		static slua::LuaInterfaceImp interface;
		return &interface;
	}
}