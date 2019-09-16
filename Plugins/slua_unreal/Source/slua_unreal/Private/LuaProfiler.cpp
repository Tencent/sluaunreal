// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaProfiler.h"
#include "Log.h"
#include "LuaState.h"
#include "ArrayWriter.h"
#include "luasocket/tcp.h"
#include "luasocket/auxiliar.h"
#include "luasocket/buffer.h"

namespace NS_SLUA {

	#include "LuaProfiler.inl"

	enum class HookState {
		UNHOOK=0,
		HOOKED=1,
	};

	enum class RunState {
		DISCONNECT = 0,
		CONNECTED = 1,
	};

	namespace {

		LuaVar selfProfiler;
		bool ignoreHook = false;
		HookState currentHookState = HookState::UNHOOK;
		int64_t profileTotalCost = 0;
		bool openAttachMode = true;
		p_tcp tcpSocket = nullptr;
		const char* ChunkName = "[ProfilerScript]";

		void makeProfilePackage(FArrayWriter& messageWriter,
			int hookEvent, int64_t time,
			int lineDefined, const char* funcName,
			const char* shortSrc)
		{
			uint32 packageSize = 0;

			FString fname = FString(funcName);
			FString fsrc = FString(shortSrc);

			messageWriter << packageSize;
			messageWriter << hookEvent;
			messageWriter << time;
			messageWriter << lineDefined;
			messageWriter << fname;
			messageWriter << fsrc;

			messageWriter.Seek(0);
			packageSize = messageWriter.TotalSize() - sizeof(uint32);
			messageWriter << packageSize;
		}

		// copy code from buffer.cpp in luasocket
		#define STEPSIZE 8192
		int sendraw(p_buffer buf, const char* data, size_t count, size_t * sent) {
			p_io io = buf->io;
			p_timeout tm = buf->tm;
			size_t total = 0;
			int err = IO_DONE;
			while (total < count && err == IO_DONE) {
				size_t done = 0;
				size_t step = (count - total <= STEPSIZE) ? count - total : STEPSIZE;
				err = io->send(io->ctx, data + total, step, &done, tm);
				total += done;
			}
			*sent = total;
			buf->sent += total;
			return err;
		}

		void sendMessage(FArrayWriter& msg) {
			if (!tcpSocket) return;
			size_t sent;
			int err = sendraw(&tcpSocket->buf, (const char*)msg.GetData(), msg.Num(), &sent);
			if (err == IO_CLOSED) {
				selfProfiler.callField("disconnect");
			}
		}

		void takeSample(int event,int line,const char* funcname,const char* shortsrc) {
			// clear writer;
			static FArrayWriter s_messageWriter;
			s_messageWriter.Empty();
			s_messageWriter.Seek(0);
			makeProfilePackage(s_messageWriter, event, getTime(), line, funcname, shortsrc);
			sendMessage(s_messageWriter);
		}

		void debug_hook(lua_State* L, lua_Debug* ar) {
			if (ignoreHook) return;
			
			if (currentHookState == HookState::UNHOOK) {
				selfProfiler.callField("reConnect", selfProfiler);
				return;
			}
			
			lua_getinfo(L, "nSl", ar);

			// we don't care about LUA_HOOKLINE, LUA_HOOKCOUNT and LUA_HOOKTAILCALL
			if (ar->event > 1) 
				return;
			if (strstr(ar->short_src, ChunkName)) 
				return;

			takeSample(ar->event,ar->linedefined, ar->name ? ar->name : "", ar->short_src ? ar->short_src : "");
		}

		int changeHookState(lua_State* L) {
			HookState state = (HookState)lua_tointeger(L, 1);
			currentHookState = state;
			if (state == HookState::UNHOOK) {
				if (openAttachMode)
					lua_sethook(L, debug_hook, LUA_MASKRET, 1000000);
				else
					lua_sethook(L, nullptr, 0, 0);
			}
			else if (state == HookState::HOOKED) {
				lua_sethook(L, debug_hook, LUA_MASKRET | LUA_MASKCALL, 0);
			}
			else
				luaL_error(L, "Set error value to hook state");
			return 0;
		}

		int setSocket(lua_State* L) {
			tcpSocket = (p_tcp)auxiliar_checkclass(L, "tcp{client}", 1);
			if (!tcpSocket) luaL_error(L, "Can't set nil socket");
			return 0;
		}
	}

	void LuaProfiler::init(lua_State* L)
	{
		auto ls = LuaState::get(L);
		ensure(ls);
		selfProfiler = ls->doBuffer((const uint8*)ProfilerScript,strlen(ProfilerScript), ChunkName);
		ensure(selfProfiler.isValid());
		selfProfiler.push(L);
		lua_pushcfunction(L, changeHookState);
		lua_setfield(L, -2, "changeHookState");
		lua_pushcfunction(L, setSocket);
		lua_setfield(L, -2, "setSocket");
		// using native hook instead of lua hook for performance
		// set selfProfiler to global as slua_profiler
		lua_setglobal(L, "slua_profile");
		ensure(lua_gettop(L) == 0);
	}

	void LuaProfiler::tick()
	{
		ignoreHook = true;
		RunState currentRunState = (RunState)selfProfiler.getFromTable<int>("currentRunState");
		if (currentRunState == RunState::CONNECTED) {
			takeSample(-1, -1, "", "");
		}
		ignoreHook = false;
	}

	LuaProfiler::LuaProfiler(const char* funcName)
	{
		takeSample(0, 0, funcName, "");
	}

	LuaProfiler::~LuaProfiler()
	{
		takeSample(1, 0, "", "");
	}

}