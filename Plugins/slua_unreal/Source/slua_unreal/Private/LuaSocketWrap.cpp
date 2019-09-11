// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaSocketWrap.h"
#include "LuaObject.h"
#include "LuaState.h"
#include "luasocket/luasocket.h"
#include "luasocket/mime.h"

namespace NS_SLUA {

    namespace LuaSocket {

        int luaopen_url(lua_State *L) {
            auto str =
#include "luasocket/url.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_tp(lua_State *L) {
            auto str =
#include "luasocket/tp.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_socket(lua_State *L) {
            auto str =
#include "luasocket/socket.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_smtp(lua_State *L) {
            auto str =
#include "luasocket/smtp.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_mime(lua_State *L) {
            auto str =
#include "luasocket/mime.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_mbox(lua_State *L) {
            auto str =
#include "luasocket/mbox.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_ltn12(lua_State *L) {
            auto str =
#include "luasocket/ltn12.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_socket_headers(lua_State *L) {
            auto str =
#include "luasocket/headers.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_http(lua_State *L) {
            auto str =
#include "luasocket/http.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        int luaopen_ftp(lua_State *L) {
            auto str =
#include "luasocket/ftp.lua.inc"
                luaL_dostring(L, str);
            return 1;
        }

        void init(lua_State *L) {
            luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);

            lua_pushcfunction(L, luaopen_socket_core);
            lua_setfield(L, -2, "socket.core");

            lua_pushcfunction(L, luaopen_socket_headers);
            lua_setfield(L, -2, "socket.headers");

            lua_pushcfunction(L, luaopen_mime_core);
            lua_setfield(L, -2, "mime.core");

            lua_pushcfunction(L, luaopen_url);
            lua_setfield(L, -2, "socket.url");

            lua_pushcfunction(L, luaopen_tp);
            lua_setfield(L, -2, "socket.tp");

            lua_pushcfunction(L, luaopen_socket);
            lua_setfield(L, -2, "socket");

            lua_pushcfunction(L, luaopen_smtp);
            lua_setfield(L, -2, "socket.smtp");

            lua_pushcfunction(L, luaopen_mime);
            lua_setfield(L, -2, "mime");

            lua_pushcfunction(L, luaopen_mbox);
            lua_setfield(L, -2, "mbox");

            lua_pushcfunction(L, luaopen_ltn12);
            lua_setfield(L, -2, "ltn12");
             
            lua_pushcfunction(L, luaopen_http);
            lua_setfield(L, -2, "socket.http");

            lua_pushcfunction(L, luaopen_ftp);
            lua_setfield(L, -2, "socket.ftp");

            lua_pop(L, 1);
        }
    }
}