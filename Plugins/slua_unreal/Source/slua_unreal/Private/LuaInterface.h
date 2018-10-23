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
#include "lua/lua.hpp"
// for debugger integrate
#define PURE_API =0
namespace slua {
    struct LuaInterface {
        virtual const lua_Number *lua_version (lua_State *L) PURE_API;
        virtual const char *lua_pushstring (lua_State *L, const char *s) PURE_API;
        virtual int lua_gettop (lua_State *L) PURE_API;
        virtual void lua_settop (lua_State *L, int index) PURE_API;
        virtual int lua_pcallk (lua_State *L,
                int nargs,
                int nresults,
                int msgh,
                lua_KContext ctx,
                lua_KFunction k) PURE_API;
        virtual void lua_pushnumber (lua_State *L, lua_Number n) PURE_API;
        virtual const char *luaL_checklstring (lua_State *L, int arg, size_t *l) PURE_API;
        virtual const char *lua_tolstring (lua_State *L, int index, size_t *len) PURE_API;
        virtual int lua_type (lua_State *L, int index) PURE_API;
        virtual lua_Integer lua_tointegerx (lua_State *L, int index, int *isnum) PURE_API;
        virtual void lua_pushnil (lua_State *L) PURE_API;
        virtual int lua_getfield (lua_State *L, int index, const char *k) PURE_API;
        virtual int lua_next (lua_State *L, int index) PURE_API;
        virtual int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar) PURE_API;
        virtual void lua_sethook (lua_State *L, lua_Hook f, int mask, int count) PURE_API;
        virtual lua_Number luaL_checknumber (lua_State *L, int arg) PURE_API;
        virtual void lua_createtable (lua_State *L, int narr, int nrec) PURE_API;
        virtual void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) PURE_API;
        virtual int lua_getglobal (lua_State *L, const char *name) PURE_API;
    };
}

extern "C" {
#if defined(_WIN32)
	__declspec(dllexport)
#else
	extern
#endif
	slua::LuaInterface* GetLuaInterface();
}
