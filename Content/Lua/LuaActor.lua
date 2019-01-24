

local actor={}

-- override event from blueprint
function actor:BeginPlay()
    self.bCanEverTick = true
    print("actor:BeginPlay")
end

function actor:Tick(dt)
    print("actor:Tick",self,dt)
    -- call actor function
    local pos = self:K2_GetActorLocation()
    -- can pass self as Actor*
    local dist = self:GetHorizontalDistanceTo(self)
    print("actor pos",pos,dist)
end

return actor