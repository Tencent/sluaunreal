

local actor={}

local EPropertyClass = import"EPropertyClass"
-- override event from blueprint
function actor:ReceiveBeginPlay()
    self.bCanEverTick = true
    -- set bCanBeDamaged property in parent
    self.bCanBeDamaged = false
    print("actor:ReceiveBeginPlay")

    local world = self:GetWorld()
    local bpClass = slua.loadClass("/Game/TestActor.TestActor")

    self.basepos={}
    self.rot={}
    self.ballarr = slua.Array(EPropertyClass.Object,bpClass)

    for n=1,10 do
        local p = FVector(math.random(-100,100),math.random(-100,100),0)
        local actor = world:SpawnActor(bpClass,p,nil,nil)
        self.ballarr:Add(actor)
        self.basepos[n]=p
        self.rot[n]=math.random(-100,100)
        actor.Name = 'ActorCreateFromLua_'..tostring(n)
    end
    self.Super:ReceiveBeginPlay()

    -- test an issue
    -- callLastMapActorMethod()
end

function callLastMapActorMethod()
    for k,v in pairs(gactor.objs) do
        print(k,v)
    end
end

-- override event from blueprint
function actor:ReceiveEndPlay(reason)
    print("actor:ReceiveEndPlay")
    self.Super:ReceiveEndPlay(reason)

end

local HitResult = import('HitResult');
local tt=0
function actor:Tick(dt)
    tt=tt+dt
    for i=1,10 do
        local actor = self.ballarr:Get(i-1)
        local p = self.basepos[i]
        local h = HitResult()
        local rot = self.rot[i]
        local v = FVector(math.sin(tt)*rot,0,0)
        local offset = FVector(0,math.cos(tt)*rot,0)
        local ok,h=actor:K2_SetActorLocation(p+v+offset,true,h,true)
    end
    self.Super:Tick(dt)
end

return actor