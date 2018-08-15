// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaObject.h"
#include "LuaState.h"
#include "LuaSocket/luasocket.h"

namespace slua {

    int luasocket(lua_State *L){
        luaopen_socket_core(L);
        return 1;
    }

    void initLuaSocketExt(lua_State *L) {
		auto state = LuaState::get(L);
		#include "luasocket/url.lua.inc"
		#include "luasocket/tp.lua.inc"
		#include "luasocket/socket.lua.inc"
		#include "luasocket/smtp.lua.inc"
		#include "luasocket/mime.lua.inc"
		#include "luasocket/mbox.lua.inc"
		#include "luasocket/ltn12.lua.inc"
		#include "luasocket/http.lua.inc"
		#include "luasocket/headers.lua.inc"
		#include "luasocket/ftp.lua.inc"
    }

    void initDebugExtension(lua_State *L){
		AutoStack autoStack(L);
		
		lua_pushglobaltable(L); // _G
		lua_newtable(L);		// _G, t
		lua_pushvalue(L, -1);	// _G, t, t
		lua_setfield(L, -3, "lua_extension"); // _G, t
		
        lua_pushcfunction(L, luasocket);   // _G, t, f
		lua_setfield(L, -2, "luasocket");  // _G, t
    }
}