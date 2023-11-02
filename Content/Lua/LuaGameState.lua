local LuaGameState =
{
    ServerRPC = {},     --C2S类RPC列表，类似UFUNCTION宏中的Server
    ClientRPC = {},     --S2C类RPC列表，类似UFUNCTION宏中的Client
    MulticastRPC = {},  --多播类RPC列表，类似UFUNCTION宏中的NetMulticast
}

local EPropertyClass = import("EPropertyClass")

LuaGameState.ServerRPC.TestServerRPC = {
    -- 是否可靠RPC
    Reliable = true,
    -- 定义参数列表
    Params =
    {
        EPropertyClass.Int,
        EPropertyClass.Str,
        EPropertyClass.bool,
    }
}

LuaGameState.ClientRPC.TestClientRPC = {
    -- 是否可靠RPC
    Reliable = true,
    -- 定义参数列表
    Params =
    {
        EPropertyClass.Int,
        EPropertyClass.Str,
        EPropertyClass.bool,
    }
}

LuaGameState.MulticastRPC.TestMulticastRPC = {
    -- 是否可靠RPC
    Reliable = true,
    -- 定义参数列表
    Params =
    {
        EPropertyClass.Int,
        EPropertyClass.Str,
        EPropertyClass.bool,
    }
}

function LuaGameState:ctor(selfType)
    print("LuaGameState ctor", selfType, assert(selfType == require("LuaGameState")))
    self.Name = "LuaGameStateTestName"
end

function LuaGameState:_PostConstruct()
    self:AddLuaNetListener("Position", function (Value)
        print("LuaGameState On Position Assign:", Value.X, Value.Y, Value.Z)
    end)
end

function LuaGameState:TestServerRPC(ArgInt, ArgStr, ArgBool)
    print("LuaGameState:TestServerRPC", ArgInt, ArgStr, ArgBool)
end

function LuaGameState:TestClientRPC(ArgInt, ArgStr, ArgBool)
    print("LuaGameState:TestClientRPC", ArgInt, ArgStr, ArgBool)
end

function LuaGameState:TestMulticastRPC(ArgInt, ArgStr, ArgBool)
    print("LuaGameState:TestMulticastRPC", ArgInt, ArgStr, ArgBool)
end

function LuaGameState:GetLifetimeReplicatedProps()
    local ELifetimeCondition = import("ELifetimeCondition")
    local FVectorType = import("Vector")
    return {
        { "Name", ELifetimeCondition.COND_InitialOnly, EPropertyClass.Str},
        { "HP", ELifetimeCondition.COND_OwnerOnly, EPropertyClass.Float},
        { "Position", ELifetimeCondition.COND_SimulatedOnly, FVectorType},
        { "TeamateNameList", ELifetimeCondition.COND_None, EPropertyClass.Array, EPropertyClass.Str},
        { "TeamatePositions", ELifetimeCondition.COND_None, EPropertyClass.Array, FVectorType},
    }
end

-- override event from blueprint
function LuaGameState:ReceiveBeginPlay()
    self.bCanEverTick = true
    -- set bCanBeDamaged property in parent
    self.bCanBeDamaged = false
    print("LuaGameState:ReceiveBeginPlay")

    local KismetSystemLibrary = import("KismetSystemLibrary")
    if KismetSystemLibrary.IsDedicatedServer(self) then
        self:TestClientRPC(1, "TestClientRPC", false)
        self:TestMulticastRPC(2, "TestMulticastRPC", true)
    else
        self:TestServerRPC(3, "TestServerRPC", true)
    end

    self.Name = "Poli"
    self.Hp = 100
    --self.Position = FVector(100, 200, 300)
    self.Position.X = 100
    self.Position.Y = 200
    self.Position.Z = 300
    --self.TeamateNameList = {"Teamate1", "Teamate2", "Teamate3", "Teamate4", "Teamate5"}
    for i = 1, 5 do
        self.TeamateNameList:Add("Teamate"..i)
    end

    local TeamatePos = FVector(100, 200, 300)
    local TeamatePositions = self.TeamatePositions
    TeamatePositions:Add(TeamatePos)
    TeamatePos.X = 101
    TeamatePositions:Add(TeamatePos)
    TeamatePos.X = 102
    TeamatePositions:Add(TeamatePos)
    TeamatePos.X = 103
    TeamatePositions:Add(TeamatePos)
    --- Mark TeamatePositions dirty to sync
    --- self.TeamatePositions = TeamatePositions
end

function LuaGameState:OnRep_Name(OldName)
    print("LuaGameState:OnRep_Name: ", OldName, self.Name)
end

function LuaGameState:OnRep_HP(OldHP)
    print("LuaGameState:OnRep_HP: ", OldHP, self.HP)
end

function LuaGameState:OnRep_Position(OldPosition)
    local Position = self.Position
    print("LuaGameState:OnRep_Position: ", OldPosition.X, OldPosition.Y, OldPosition.Z, "New Position:", Position.X, Position.Y, Position.Z)
end

function LuaGameState:OnRep_TeamateNameList(OldNameList)
    print("LuaGameState:OnRep_TeamateNameList: ")
    for k, v in pairs(self.TeamateNameList) do
        print("Teamate:", k, v)
    end
end

function LuaGameState:OnRep_TeamatePositions()
    print("LuaGameState:OnRep_TeamatePositions: ")
    for k, v in pairs(self.TeamatePositions) do
        print("TeamatePositions: ", k, "Pos:", v.X, v.Y, v.Z)
    end
end

-- override event from blueprint
function LuaGameState:ReceiveEndPlay(reason)
    print("LuaGameState:ReceiveEndPlay")
end


return Class(nil, nil, LuaGameState)