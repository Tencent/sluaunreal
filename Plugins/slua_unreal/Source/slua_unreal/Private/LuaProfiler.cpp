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
#include "ArrayReader.h"
#include "MemorySnapshot.h"
#include "LuaMemoryProfile.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "luasocket/auxiliar.h"
#include "luasocket/buffer.h"
#include "lua/lua.hpp"

#if PLATFORM_WINDOWS
#ifdef TEXT
#undef TEXT
#endif
#endif
#include "luasocket/tcp.h"

#if PLATFORM_WINDOWS
#include <winsock2.h>
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

    namespace {
        int snapshotID = 0;
        int preSnapshotID = 0;
        int snapshotNum = 0;
        int snapshotDeleteID = 0;
        size_t lastReceived = 0;
		LuaVar selfProfiler;
		bool ignoreHook = false;
		HookState currentHookState = HookState::UNHOOK;
		int64 profileTotalCost = 0;
		p_tcp tcpSocket = nullptr;
		const char* ChunkName = "[ProfilerScript]";
        TMap<int, SnapshotMap> snapshotList;
        
        // copy code from buffer.cpp in luasocket
        int buffer_get(p_buffer buf, size_t *count, FArrayReader& messageReader) {
            int err = IO_DONE;
            p_io io = buf->io;
            p_timeout tm = buf->tm;
            if (buffer_isempty(buf)) {
                size_t got;
                err = io->recv(io->ctx, buf->data, BUF_SIZE, &got, tm);
                buf->first = 0;
                buf->last = got;
                lastReceived = buf->received;
            }
            
            // crash appers when the last buffer index is bigger than the received data size;
            int receive = buf->received - lastReceived;
            if(receive <= buf->last)
            {
                *count = buf->last - buf->first;
                messageReader.Insert((uint8 *)(buf->data + buf->first), *count, buf->first);
            }
            return err;
        }
        
        // copy code from buffer.cpp in luasocket
        void buffer_skip(p_buffer buf, size_t count) {
            buf->received += count;
            buf->first += count;
            if (buffer_isempty(buf))
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
        
        int receieveMessage(size_t wanted) {
            if(!tcpSocket) return false;
            
            int event = 0;
            int emptyID = 0;
           
            FArrayReader messageReader = FArrayReader(true);
            messageReader.SetNumUninitialized(sizeof(int) * 4);
            
            int err = recvraw(&tcpSocket->buf, wanted, messageReader);
            if(err != IO_DONE) {
                return false;
            }
            
            messageReader << event;
            
            switch(event) {
                case PHE_SNAPSHOT_COMPARE: {
                    messageReader << emptyID;
                    messageReader << preSnapshotID;
                    messageReader << snapshotID;
                }
                case PHE_MEMORY_SNAPSHOT: {
                    messageReader << snapshotNum;
                    messageReader << emptyID;
                    messageReader << emptyID;
                }
                case PHE_SNAPSHOT_DELETE: {
                    messageReader << snapshotDeleteID;
                    messageReader << emptyID;
                    messageReader << emptyID;
                }
            }
            return event;
        }
        
        void memoryGC(lua_State* L) {
            if(!tcpSocket) return;
            
            if(L) {
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
                                int hookEvent, TArray<LuaMemInfo> memInfoList)
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

		size_t sendMessage(FArrayWriter& msg) {
			if (!tcpSocket) return -1;
			size_t sent;
			int err = sendraw(&tcpSocket->buf, (const char*)msg.GetData(), msg.Num(), &sent);
			if (err != IO_DONE) {
				selfProfiler.callField("disconnect");
			}
            
            return sent;
		}

		void takeSample(int event,int line,const char* funcname,const char* shortsrc) {
			// clear writer;
			static FArrayWriter s_messageWriter;
			s_messageWriter.Empty();
			s_messageWriter.Seek(0);
			makeProfilePackage(s_messageWriter, event, getTime(), line, funcname, shortsrc);
			sendMessage(s_messageWriter);
		}

        void takeMemorySample(int event, TArray<LuaMemInfo> memoryInfoList) {
            // clear writer;
            static FArrayWriter s_memoryMessageWriter;
            s_memoryMessageWriter.Empty();
            s_memoryMessageWriter.Seek(0);
            makeMemoryProfilePackage(s_memoryMessageWriter, event, memoryInfoList);
            sendMessage(s_memoryMessageWriter);
        }
        
        size_t takeMemSnapshotSample(int event, double objSize, int memorySize, int snapshotId) {
            static FArrayWriter s_messageWriter;
            s_messageWriter.Empty();
            s_messageWriter.Seek(0);
            char *id = TCHAR_TO_ANSI(*FString::FromInt(snapshotId));
            makeProfilePackage(s_messageWriter, event, objSize, memorySize, id, "");
            return sendMessage(s_messageWriter);
        }
        
        void getMemorySnapshot(lua_State *L) {
            if(!tcpSocket) return;
            
            if(L) {
                MemorySnapshot snapshot;
                SnapshotMap map = snapshot.getMemorySnapshot(L, MARKED + 1);
                double objSize = (double)SnapshotMap::getSnapshotObjSize(map);
                int memSize = SnapshotMap::getSnapshotMemSize(map);
                size_t msgSent = takeMemSnapshotSample(PHE_MEMORY_SNAPSHOT, objSize, memSize, snapshotNum);
                if(msgSent && snapshotNum) snapshotList.Add(snapshotNum, map);
            }
        }
        
        TArray<LuaMemInfo> checkSnapshotDiff() {
            TArray<LuaMemInfo> emptyList;
            if(tcpSocket && snapshotList.Contains(preSnapshotID) && snapshotList.Contains(snapshotID)) {
                return snapshotList.FindRef(snapshotID).checkMemoryDiff(snapshotList.FindRef(preSnapshotID));
            }
            
            return emptyList;
        }
        
        void dispatchReceieveEvent(lua_State *L, int event) {
            switch (event) {
                case PHE_MEMORY_SNAPSHOT: {
                    getMemorySnapshot(L);
                    break;
                }
                case PHE_SNAPSHOT_COMPARE: {
                    // send the comparing result of two snapshots
                    takeMemorySample(NS_SLUA::ProfilerHookEvent::PHE_SNAPSHOT_COMPARE, checkSnapshotDiff());
                    break;
                }
                case PHE_SNAPSHOT_DELETE: {
                    if(snapshotList.Contains(snapshotDeleteID)) {
                        snapshotList.FindAndRemoveChecked(snapshotDeleteID);
                    }
                }
                case PHE_MEMORY_GC: {
                    memoryGC(L);
                    break;
                }
                case PHE_SNAPSHOT_DELETE_ALL: {
                    snapshotList.Empty();
                    break;
                }
            }
        }

		void debug_hook(lua_State* L, lua_Debug* ar) {
			if (ignoreHook) return;
			
			lua_getinfo(L, "nSl", ar);

			// we don't care about LUA_HOOKLINE, LUA_HOOKCOUNT and LUA_HOOKTAILCALL
			if (ar->event > 1) 
				return;
			if (strstr(ar->short_src, ChunkName)) 
				return;

            takeSample(ar->event,ar->linedefined, ar->name ? ar->name : "", ar->short_src);
		}

		int changeHookState(lua_State* L) {
			HookState state = (HookState)lua_tointeger(L, 1);
			currentHookState = state;
			if (state == HookState::UNHOOK) {
//                LuaMemoryProfile::stop();
				lua_sethook(L, nullptr, 0, 0);
			}
			else if (state == HookState::HOOKED) {
                LuaMemoryProfile::start();
				lua_sethook(L, debug_hook, LUA_MASKRET | LUA_MASKCALL, 0);
			}
			else
				luaL_error(L, "Set error value to hook state");
			return 0;
		}

		int setSocket(lua_State* L) {
			if (lua_isnil(L, 1)) {
				tcpSocket = nullptr;
				return 0;
			}
			tcpSocket = (p_tcp)auxiliar_checkclass(L, "tcp{client}", 1);
			if (!tcpSocket) luaL_error(L, "Set invalid socket");
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

	void LuaProfiler::tick(lua_State* L)
	{
		ignoreHook = true;
		if (currentHookState == HookState::UNHOOK) {
			selfProfiler.callField("reConnect", selfProfiler);
            ignoreHook = false;
			return;
		}
    
		RunState currentRunState = (RunState)selfProfiler.getFromTable<int>("currentRunState");
		if (currentRunState == RunState::CONNECTED) {
            TArray<LuaMemInfo> memoryInfoList;
            
            if(checkSocketRead()){
                int wantedSize = sizeof(int) * 4;
                dispatchReceieveEvent(L, receieveMessage(wantedSize));
            }
            
            for(auto& memInfo : NS_SLUA::LuaMemoryProfile::memDetail()) {
                memoryInfoList.Add(memInfo.Value);
            }
            
            takeMemorySample(NS_SLUA::ProfilerHookEvent::PHE_MEMORY_TICK, memoryInfoList);
            takeSample(NS_SLUA::ProfilerHookEvent::PHE_TICK, -1, "", "");
		}
		ignoreHook = false;
	}
    

	LuaProfiler::LuaProfiler(const char* funcName)
	{
        takeSample(ProfilerHookEvent::PHE_CALL, 0, funcName, "");
	}

	LuaProfiler::~LuaProfiler()
	{
        takeSample(ProfilerHookEvent::PHE_RETURN, 0, "", "");
	}

    void dumpLastSnapshotInfo() {
        if(snapshotList.Contains(snapshotList.Num()))
            SnapshotMap::printMap(snapshotList.FindRef(snapshotList.Num()));
    }
    
    static FAutoConsoleCommand CVarDumpLastSnpashotInfo(
                                                    TEXT("slua.DumpLastSnapshot"),
                                                    TEXT("Dump last memory snapshot information"),
                                                    FConsoleCommandDelegate::CreateStatic(dumpLastSnapshotInfo),
                                                    ECVF_Cheat);
    }

#endif
