// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


const char* ProfilerScript = R"code(
local ConsoleLogLevel = 2           --打印在控制台(print)的日志等级 0 : all/ 1: info/ 2: error.
local ConnectTimeoutSec = 0.005
local AttachInterval = 1

local this = {}
local sock -- tcp socket
local connectHost
local connectPort
local stopConnectTime = 0
local currentHookState
local coroutinePool = setmetatable({}, {__mode = "v"})
local coroutineCreate = nil

local RunState = {
    DISCONNECT = 0,
    CONNECTED = 1,
}

local HookState = {
    UNHOOK = 0,               --断开连接
    HOOK = 1,                 --全局无断点
};

function this.start(host, port)
    host = tostring(host or "127.0.0.1")
    port = tonumber(port) or 8081
    this.printToConsole("Profile start. connect host:" .. host .. " port:".. tostring(port), 1)
    if sock ~= nil then
        this.printToConsole("[Warning] Profiler已经启动，请不要再次调用start()" , 1)
        return
    end
    this.setSocket(nil)

    --尝试初次连接
    this.changeRunState(RunState.DISCONNECT)
    this.reGetSock()
    connectHost = host
    connectPort = port
    local sockSuccess = sock and sock:connect(connectHost, connectPort)
    if sockSuccess ~= nil then
        this.printToConsole("first connect success!")
        this.setSocket(sock)
        this.connectSuccess()
    else
        this.printToConsole("first connect failed!")
        this.changeHookState(HookState.UNHOOK)
    end
end

-- 把日志打印在控制台
-- @str: 日志内容
-- @printLevel: all(0)/info(1)/error(2)
function this.printToConsole(str, printLevel)
    printLevel = printLevel or 0
    if ConsoleLogLevel > printLevel then
        return
    end
    print("[Slua Profile] ".. tostring(str))
end

function this.changeRunState(state)
    this.currentRunState = state
end

function this.reGetSock()
    if sock ~= nil then
        pcall(function() sock:close() end)
    end

    if pcall(function() sock = require("socket.core").tcp() end) then
        this.printToConsole("reGetSock success")
        sock:settimeout(ConnectTimeoutSec)
    else
        this.printToConsole("[Error] reGetSock fail", 2)
    end
end

local function startsWith(source, start)
    return string.sub(source,1,string.len(start))== start
end


-- 定时进行attach连接
function this.reConnect()
    
    if not connectHost then return end

    if os.time() - stopConnectTime < AttachInterval then
        this.printToConsole("Reconnect time less than 1s")
        this.printToConsole("os.time:".. os.time() .. " | stopConnectTime:" ..stopConnectTime)
    end

    if not sock then
        this.reGetSock()
    end

    local sockSuccess, status = sock:connect(connectHost, connectPort)
	this.setSocket(sock)
    if sockSuccess == 1 or status == "already connected" then
        this.printToConsole("reconnect success")
        this.connectSuccess()
    else
        this.printToConsole("reconnect failed . retCode:" .. tostring(sockSuccess) .. "  status:" .. status)
        stopConnectTime = os.time()
    end
end

function this.connectSuccess()
    this.changeRunState(RunState.CONNECTED)
    this.printToConsole("connectSuccess", 1)
    this.changeHookState(HookState.HOOK)
end

function this.disconnect()
    this.stop()
    
    this.reGetSock()
end

function this.stop()
    this.printToConsole("Profiler disconnect", 1)

    this.changeHookState( HookState.UNHOOK )
    stopConnectTime = os.time()
    this.changeRunState(RunState.DISCONNECT)

    this.setSocket(nil)

    if sock ~= nil then
        sock:close()
    end
end

function this.changeCoroutinesHookState()
	for k, co in pairs(coroutinePool) do
        if coroutine.status(co) == "dead" then
			coroutinePool[k] = nil
        else
            this.changeCoroutineHookState(co)
        end
    end
end

local function replaceCoroutineFuncs()
    if coroutineCreate == nil and type(coroutine.create) == "function" then
        this.printToConsole("change coroutine.resume")
        coroutineCreate = coroutine.create
        coroutine.create = function (...)
            local co = coroutineCreate(...)
            table.insert(coroutinePool, co)
            this.changeCoroutineHookState(co, true)
            return co
        end
    end
end

replaceCoroutineFuncs()

return this
)code";
