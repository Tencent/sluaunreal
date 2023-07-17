local LuaBpActor =
{
}

-- override event from blueprint
function LuaBpActor:ReceiveBeginPlay()
    LuaBpActor.__super.ReceiveBeginPlay(self)
    self.bCanEverTick = true
    -- set bCanBeDamaged property in parent
    self.bCanBeDamaged = false
    print("bpactor:ReceiveBeginPlay")
    -- call super ReceiveBeginPlay
    self.Super:ReceiveBeginPlay()

    print("SoftObjectTest:", self.SoftObjectTest:ToString())
    print("ChangeSoftObject")
    self:ChangeSoftObject()
    print(self.SoftObjectTest:ToString())
    -- self.SoftObjectTest = FSoftObjectPtr("/Game/BallActor.BallActor")

    print("SoftClassTest:", self.SoftClassTest:ToString())
    print("ChangeSoftClass")
    self:ChangeSoftClass()
    print(self.SoftClassTest:ToString())
    self.SoftClassTest = FSoftObjectPtr("/Game/BallActor.BallActor_C")
    print(self.SoftClassTest:ToString())
end

function LuaBpActor:ChangeSoftObject()
    self.SoftObjectTest = slua.loadObject('/Game/ParticleSystemForTest.ParticleSystemForTest')
end

function LuaBpActor:ChangeSoftClass()
    self.SoftClassTest = import('/Game/LuaActor.LuaActor_C')
    -- self.SoftClassTest = import('/Game/Item.Item_C')
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