local LuaActor =
{
    ServerRPC = {},     --C2S类RPC列表，类似UFUNCTION宏中的Server
    ClientRPC = {},     --S2C类RPC列表，类似UFUNCTION宏中的Client
    MulticastRPC = {},  --多播类RPC列表，类似UFUNCTION宏中的NetMulticast
}

local EPropertyClass = import("EPropertyClass")
LuaActor.ClientRPC.ClientRPC_SetAddressRPC = {
    -- 是否可靠RPC
    Reliable = true,
    -- 定义参数列表
    Params =
    {
        EPropertyClass.Str,
    }
}

-- override event from blueprint
function LuaActor:ReceiveBeginPlay()
    self.bCanEverTick = true
    -- set bCanBeDamaged property in parent
    self.bCanBeDamaged = false
    print("actor:ReceiveBeginPlay")
end

-- override event from blueprint
function LuaActor:ReceiveEndPlay(Reason)
    print("actor:ReceiveEndPlay")
end

function LuaActor:ClientRPC_SetAddressRPC(Address)
    print("LuaActor:ClientRPC_SetAddressRPC", Address)
end

function LuaActor:Tick(DeltaTime)
    print("actor:Tick",self, DeltaTime)
    -- call actor function
    local pos = self:K2_GetActorLocation()
    -- can pass self as Actor*
    local dist = self:GetHorizontalDistanceTo(self)
    print("actor pos",pos,dist)
end

return Class(nil, nil, LuaActor)