--[[
 Tencent is pleased to support the open source community by making sluaunreal available.

 Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
 Licensed under the BSD 3-Clause License (the "License");
 you may not use this file except in compliance with the License. You may obtain a copy of the License at

 https://opensource.org/licenses/BSD-3-Clause

 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and limitations under the License.
]]

local ConsoleLogLevel = 2           --打印在控制台(print)的日志等级 0 : all/ 1: info/ 2: error.
local ConnectTimeoutSec = 0.005
local OpenAttachMode = true         --打开自动附加模式，随时可以连接profile
local AttachInterval = 1

local this = {}
local sock -- tcp socket
local connectHost
local connectPort
local currentRunState
local currentHookState
local stopConnectTime = 0
local profileTotalCost = 0

local ignoreHook = false

local RunState = {
    DISCONNECT = 0,
    CONNECTED = 1,
}

local HookState = {
    UNHOOK = 0,               --断开连接
    HOOK = 1,                 --全局无断点
};

local EventID = {
    ["call"] = 0,
    ["return"] = 1,
}

local function getTime()
    return slua.getNanoseconds()
end

function this.start(host, port)
    host = tostring(host or "127.0.0.1")
    port = tonumber(port) or 8081
    this.printToConsole("Profile start. connect host:" .. host .. " port:".. tostring(port), 1)
    if sock ~= nil then
        this.printToConsole("[Warning] Profiler已经启动，请不要再次调用start()" , 1)
        return
    end

    --尝试初次连接
    this.changeRunState(RunState.DISCONNECT)
    this.reGetSock()
    connectHost = host
    connectPort = port
    local sockSuccess = sock and sock:connect(connectHost, connectPort)
    if sockSuccess ~= nil then
        this.printToConsole("first connect success!")
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
    currentRunState = state
end

function this.changeHookState(state)
    currentHookState = state

    if currentHookState == HookState.UNHOOK then
        profileTotalCost = 0
        if OpenAttachMode == true then
            debug.sethook(this.debug_hook, "r", 1000000)
        else
            debug.sethook()
        end
    elseif currentHookState == HookState.HOOK then
        debug.sethook(this.debug_hook, "rc")
    end
end

function this.reGetSock()
    if sock ~= nil then
        pcall(function() sock:close() end)
    end

    if pcall(function() sock =  require("socket.core").tcp() end) then
        this.printToConsole("reGetSock success")
        sock:settimeout(ConnectTimeoutSec)
    else
        this.printToConsole("[Error] reGetSock fail", 2)
    end
end

local function startsWith(source, start)
    return string.sub(source,1,string.len(start))== start
end

function this.debug_hook(event)
    local start = getTime()
    if ignoreHook then
        return
    end

    if this.reConnect() then
        return
    end

    local eventID = EventID[event]
    if eventID == nil then
        return
    end

    local info = debug.getinfo(2, "nSl")
    if info.short_src and startsWith(info.short_src, "slua_profile.lua") then
        return
    end

    local block = slua.makeProfilePackage(eventID, start - profileTotalCost, info.linedefined, info.name or "", info.short_src or "")
    this.sendMsg(block)

    profileTotalCost = profileTotalCost + (getTime() - start)
end

function this.sendMsg(msg)
    local succ,err;
    if pcall(function() succ,err = sock:send(msg) end) then
        if succ == nil then
            if err == "closed" then
                this.disconnect();
            end
        end
    end
end

-- 定时(以函数return为时机) 进行attach连接
function this.reConnect()
    if currentHookState == HookState.UNHOOK then
        if os.time() - stopConnectTime < AttachInterval then
            this.printToConsole("Reconnect time less than 1s")
            this.printToConsole("os.time:".. os.time() .. " | stopConnectTime:" ..stopConnectTime)
            return true
        end

        if not sock then
            this.reGetSock()
        end

        local sockSuccess, status = sock:connect(connectHost, connectPort)
        if sockSuccess == 1 or status == "already connected" then
            this.printToConsole("reconnect success")
            this.connectSuccess()
        else
            this.printToConsole("reconnect failed . retCode:" .. tostring(sockSuccess) .. "  status:" .. status)
            stopConnectTime = os.time()
        end

        return true
    end

    return false
end

function this.connectSuccess()
    this.changeRunState(RunState.CONNECTED)
    this.printToConsole("connectSuccess", 1)
    this.changeHookState(HookState.HOOK)
end

function this.disconnect()
    this.printToConsole("Profiler disconnect", 1)

    this.changeHookState( HookState.UNHOOK )
    stopConnectTime = os.time()
    this.changeRunState(RunState.DISCONNECT)

    if sock ~= nil then
        sock:close()
    end
    this.reGetSock()
end

local function profileTick(deltaTime)
    ignoreHook = true
    if currentRunState == RunState.CONNECTED then
        local block = slua.makeProfilePackage(-1, getTime(), -1, "", "")
        this.sendMsg(block)
    end
    ignoreHook = false
end

slua.setTickFunction(profileTick)

return this