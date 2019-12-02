

local actor={}

function actor:ReceiveBeginPlay()
    print("actor:ReceiveBeginPlay")
    self.Super:ReceiveBeginPlay()
end


-- override event from blueprint
function actor:ReceiveEndPlay(reason)
    print("actor:ReceiveEndPlay")
    self.Super:ReceiveEndPlay(reason)
end

-- server event
function actor:OnBloodChange()
    print("actor:OnBloodChange rpc")
end

function actor:Tick(dt)
end

return actor