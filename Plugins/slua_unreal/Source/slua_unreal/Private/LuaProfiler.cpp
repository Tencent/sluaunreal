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
#include "Serialization/ArrayWriter.h"
#include "Serialization/ArrayReader.h"
#include "LuaMemoryProfile.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "luasocket/auxiliar.h"
#include "luasocket/buffer.h"
#include "lua/lua.hpp"
#include "Stats/Stats2.h"

#if PLATFORM_WINDOWS
#pragma push_macro("TEXT")
#endif
#include "luasocket/tcp.h"

#if PLATFORM_WINDOWS
#include <winsock2.h>
#pragma pop_macro("TEXT")
#else
#include <sys/ioctl.h>
#endif

#ifdef ENABLE_PROFILER
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

	const char* LuaProfiler::ChunkName = "[ProfilerScript]";

	namespace {

		TMap<LuaState*, LuaVar> selfProfiler;
		bool ignoreHook = false;
		HookState currentHookState = HookState::UNHOOK;
		int64 profileTotalCost = 0;
		p_tcp tcpSocket = nullptr;
        
        // copy code from buffer.cpp in luasocket
        int buffer_get(p_buffer buf, size_t *count, FArrayReader& messageReader) {
            int err = IO_DONE;
            p_io io = buf->io;
            p_timeout tm = buf->tm;
            if (buf->first >= buf->last) {
                size_t got;
                err = io->recv(io->ctx, buf->data, BUF_SIZE, &got, tm);
                buf->first = 0;
                buf->last = got;
            }
            *count = buf->last - buf->first;
            messageReader.Insert((uint8 *)(buf->data + buf->first), *count, buf->first);
            return err;
        }
        
        // copy code from buffer.cpp in luasocket
        void buffer_skip(p_buffer buf, size_t count) {
            buf->received += count;
            buf->first += count;
            if (buf->first >= buf->last)
                buf->first = buf->last = 0;
        }
        
        // copy code from buffer.cpp in luasocket
        int recvraw(p_buffer buf, size_t wanted, FArrayReader& messageReader) {
            int err = IO_DONE;
            size_t total = 0;
            while (err == IO_DONE) {
                size_t count;
                err = buffer_get(buf, &count, messageReader);
                count = FGenericPlatformMath::Min(count, wanted - total);
                buffer_skip(buf, count);
                total += count;
                if(err == IO_DONE)
                if (total >= wanted) break;
            }
            return err;
        }
        
        bool receieveGCMessage(size_t wanted) {
            if(!tcpSocket) return false;
            
            int event = 0;
            FArrayReader messageReader = FArrayReader(true);
            messageReader.SetNumUninitialized(sizeof(int));
            
            int err = recvraw(&tcpSocket->buf, wanted, messageReader);
            if(err != IO_DONE) {
                return false;
            }
            
            messageReader << event;
            return event == PHE_MEMORY_GC;
        }
        
        void memoryGC(lua_State* L) {
            if(!tcpSocket) return;
            
            int wantedSize = 4;
            if(L && receieveGCMessage(wantedSize)) {
                int nowMemSize;
                int originMemSize = lua_gc(L, LUA_GCCOUNT, 0);
                
                lua_gc(L, LUA_GCCOLLECT, 0);
                nowMemSize = lua_gc(L, LUA_GCCOUNT, 0);
                Log::Log(("After GC , lua free %d KB"), originMemSize - nowMemSize);
            }
        }
    
    bool checkSocketRead() {
		int result;
		u_long nread = 0;
		t_socket fd = tcpSocket->sock;
		
        #if PLATFORM_WINDOWS
		result = ioctlsocket(fd, FIONREAD, &nread);
        #else
		result = ioctl(fd, FIONREAD, &nread);
        #endif
        
        return result == 0 && nread > 0;
    }

        
		void makeProfilePackage(FArrayWriter& messageWriter,
			int hookEvent, int64 time,
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

        void makeMemoryProfilePackage(FArrayWriter& messageWriter,
                                int hookEvent, TArray<LuaMemInfo>& memInfoList)
        {
            uint32 packageSize = 0;

            //first hookEvent used to distinguish the message belong to Memory or CPU
            messageWriter << packageSize;
            messageWriter << hookEvent;
            messageWriter << memInfoList;

            messageWriter.Seek(0);
            packageSize = messageWriter.TotalSize() - sizeof(uint32);
            messageWriter << packageSize;
            
        }
        
        // copy code from buffer.cpp in luasocket
        #define STEPSIZE 8192
        int sendraw(p_buffer buf, const char* data, size_t count, size_t * sent) {
            p_io io = buf->io;
            if (!io) return IO_CLOSED;
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

		void sendMessage(FArrayWriter& msg, lua_State* L) {
			QUICK_SCOPE_CYCLE_COUNTER(LuaProfiler_sendMessage)
			if (!tcpSocket) return;
			size_t sent;
			int err = sendraw(&tcpSocket->buf, (const char*)msg.GetData(), msg.Num(), &sent);
			if (err != IO_DONE) {
				auto& profiler = selfProfiler.FindChecked(LuaState::get(L));
				profiler.callField("disconnect");
			}
		}

		void takeSample(int event,int line,const char* funcname,const char* shortsrc, int64 startTime, lua_State* L) {
			QUICK_SCOPE_CYCLE_COUNTER(LuaProfiler_takeSample)
			// clear writer;
			static FArrayWriter s_messageWriter;
			s_messageWriter.Empty();
			s_messageWriter.Seek(0);
			makeProfilePackage(s_messageWriter, event, startTime - profileTotalCost, line, funcname, shortsrc);
			sendMessage(s_messageWriter, L);
		}

        void takeMemorySample(int event, TArray<LuaMemInfo>& memoryDetail, lua_State* L) {
			QUICK_SCOPE_CYCLE_COUNTER(LuaProfiler_takeMemorySample)
            // clear writer;
            static FArrayWriter s_memoryMessageWriter;
            s_memoryMessageWriter.Empty();
            s_memoryMessageWriter.Seek(0);
            makeMemoryProfilePackage(s_memoryMessageWriter, event, memoryDetail);
            sendMessage(s_memoryMessageWriter, L);
        }

		void debug_hook(lua_State* L, lua_Debug* ar) {
			int64 start = getTime();

			if (ignoreHook) return;
			
			lua_getinfo(L, "nSl", ar);

			// we don't care about LUA_HOOKLINE, LUA_HOOKCOUNT and LUA_HOOKTAILCALL
			if (ar->event > 1) 
				return;
			if (strstr(ar->short_src, LuaProfiler::ChunkName)) 
				return;

			int event = ar->event;
			if (ar->what && strcmp(ar->what, "C") == 0) {
				StkId o = L->ci ? L->ci->func : nullptr;
				if (ttislcf(o) && fvalue(o) == LuaProfiler::resumeFunc) {
					if (lua_isthread(L, 1)) {
						// coroutine enter/exit
						event += PHE_ENTER_COROUTINE;
					}
				}
			}

			takeSample(event, ar->linedefined, ar->name ? ar->name : "", ar->short_src, start, L);
			profileTotalCost = profileTotalCost + (getTime() - start);
		}

		int changeHookState(lua_State* L) {
			HookState state = (HookState)lua_tointeger(L, 1);

			if (state == currentHookState) return 0;
			currentHookState = state;

			if (state == HookState::UNHOOK) {
//                LuaMemoryProfile::stop();
				lua_sethook(L, nullptr, 0, 0);
			}
			else if (state == HookState::HOOKED) {
				profileTotalCost = 0;
                LuaMemoryProfile::onStart();

				auto& memoryDetail = LuaMemoryProfile::memDetail(LuaState::get(L));
				TArray<LuaMemInfo> memoryInfoList;
				memoryInfoList.Reserve(memoryDetail.Num());
				for (auto& memInfo : memoryDetail) {
					memoryInfoList.Add(memInfo.Value);
				}
				takeMemorySample(PHE_MEMORY_TICK, memoryInfoList, L);

				lua_sethook(L, debug_hook, LUA_MASKRET | LUA_MASKCALL, 0);
			}
			else
				luaL_error(L, "Set error value to hook state");

			auto& profiler = selfProfiler.FindChecked(LuaState::get(L));
			profiler.callField("changeCoroutinesHookState", profiler);
			return 0;
		}

		int changeCoroutineHookState(lua_State* L)
		{
			lua_settop(L, 2);

			lua_State* co = lua_tothread(L, 1);
			bool bCreated = !!lua_toboolean(L, 2);
			if (currentHookState == HookState::UNHOOK && !bCreated) {
				lua_sethook(co, nullptr, 0, 0);
			}
			else if (currentHookState == HookState::HOOKED) {
				lua_sethook(co, debug_hook, LUA_MASKRET | LUA_MASKCALL, 0);
			}
			return 0;
		}

		int setSocket(lua_State* L) {
			if (lua_isnil(L, 1)) {
				tcpSocket = nullptr;
				return 0;
			}
			tcpSocket = (p_tcp)luaL_checkudata(L, 1, "tcp{client}");
			if (!tcpSocket) luaL_error(L, "Set invalid socket");
			return 0;
		}
	}

	lua_CFunction LuaProfiler::resumeFunc = nullptr;
	
	void LuaProfiler::init(LuaState* LS)
	{
		lua_State* L = LS->getLuaState();
		ensure(L);
		auto& profiler = selfProfiler.Add(LS);
		profiler = LS->doBuffer((const uint8*)ProfilerScript,strlen(ProfilerScript), ChunkName);
		ensure(profiler.isValid());
		profiler.push(L);
		lua_pushcfunction(L, changeHookState);
		lua_setfield(L, -2, "changeHookState");
		lua_pushcfunction(L, changeCoroutineHookState);
		lua_setfield(L, -2, "changeCoroutineHookState");
		lua_pushcfunction(L, setSocket);
		lua_setfield(L, -2, "setSocket");
		// using native hook instead of lua hook for performance
		// set selfProfiler to global as slua_profiler
		lua_setglobal(L, "slua_profile");

		lua_getglobal(L, "coroutine");
		lua_getfield(L, -1, "resume");
		resumeFunc = lua_tocfunction(L, -1);
		lua_pop(L, 2);
		ensure(lua_gettop(L) == 0);
	}

	void LuaProfiler::tick(LuaState *LS)
	{
		QUICK_SCOPE_CYCLE_COUNTER(LuaProfiler_Tick)
		lua_State* L = LS->getLuaState();
		ignoreHook = true;
		auto& profiler = selfProfiler.FindChecked(LS);
		if (currentHookState == HookState::UNHOOK) {
			profiler.callField("reConnect", profiler);
            ignoreHook = false;
			return;
		}
        
		RunState currentRunState = (RunState)profiler.getFromTable<int>("currentRunState");
		if (currentRunState == RunState::CONNECTED) {          
            if(checkSocketRead()) memoryGC(L);
            takeMemorySample(PHE_MEMORY_INCREACE, LuaMemoryProfile::memIncreaceThisFrame(LS), L);
            takeSample(PHE_TICK, -1, "", "", getTime(), L);
		}
		LuaMemoryProfile::tick(LS);
		ignoreHook = false;
	}

	void LuaProfiler::clean(LuaState* LS)
	{
		lua_State* L = LS->getLuaState();
		ensure(L);
		auto& profiler = selfProfiler.FindChecked(LS);
		if (profiler.isValid())
		{
			profiler.callField("stop", profiler);
			selfProfiler.Remove(LS);
		}
		tcpSocket = nullptr;
		ignoreHook = false;
		currentHookState = HookState::UNHOOK;
		profileTotalCost = 0;
	}
    

	LuaProfiler::LuaProfiler(const char* funcName)
	{
        takeSample(PHE_CALL, 0, funcName, "", getTime(), *LuaState::get());
	}

	LuaProfiler::~LuaProfiler()
	{
        takeSample(PHE_RETURN, 0, "", "", getTime(), *LuaState::get());
	}

}
#endif
