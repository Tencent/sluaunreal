local LuaBpActor = {}

-- override event from blueprint
function LuaBpActor:ReceiveBeginPlay()
    LuaBpActor.__super.ReceiveBeginPlay(self)
    self.bCanEverTick = true
    -- set bCanBeDamaged property in parent
    self.bCanBeDamaged = false
    print("bpactor:ReceiveBeginPlay")
    -- call super ReceiveBeginPlay
    self.Super:ReceiveBeginPlay()
end

-- override event from blueprint
function LuaBpActor:ReceiveEndPlay(reason)
    print("bpactor:ReceiveEndPlay")
    -- call super ReceiveEndPlay
    self.Super:ReceiveEndPlay(reason)
end

function LuaBpActor:ReceiveTick(dt)
    print("bpactor:ReceiveTick",self,dt)
    local x = self.Val
    for k,v in pairs(x) do
        print("over",k,v)
    end
end

function LuaBpActor:bpcall(value)
    assert(value==1024)
    print("called from blueprint",value)
end

local CLuaActor = require("LuaActor")
return Class(CLuaActor, nil, LuaBpActor)