

local actor={}

function actor:ReceiveBeginPlay()
    -- print("actor:ReceiveBeginPlay")
    -- self.Super:ReceiveBeginPlay()
    print("call rpc begin")
    self.Rpc:OnBloodChange("cc","dd")
    print("call rpc end")
end


-- override event from blueprint
function actor:ReceiveEndPlay(reason)
    print("actor:ReceiveEndPlay")
    self.Super:ReceiveEndPlay(reason)
end

-- server event
function actor:OnBloodChange()
    print("actor:OnBloodChange rpc")
    -- print("call super begin")
    -- self.Super:OnBloodChange("aa","bb")
    -- print("call super end")
end

function actor:Tick(dt)
end

return actor