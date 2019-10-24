
local actor={}

-- override event from blueprint
function actor:ReceiveBeginPlay()
    self.bCanEverTick = true
    -- set bCanBeDamaged property in parent
    self.bCanBeDamaged = false
    print("bpactor:ReceiveBeginPlay")
    -- call super ReceiveBeginPlay
    self.Super:ReceiveBeginPlay()
end

-- override event from blueprint
function actor:ReceiveEndPlay(reason)
    print("bpactor:ReceiveEndPlay")
    -- call super ReceiveEndPlay
    self.Super:ReceiveEndPlay(reason)
end

function actor:ReceiveTick(dt)
    print("bpactor:ReceiveTick",self,dt)
    local x = self.Val
    for k,v in pairs(x) do
        print("over",k,v)
    end
end

function actor:bpcall(value)
    assert(value==1024)
    print("called from blueprint",value)
end

return actor