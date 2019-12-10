

local actor={}

function actor:ReceiveBeginPlay()
    print("actor:ReceiveBeginPlay")
    self.Super:ReceiveBeginPlay()
    local Test=import('SluaTestCase')
    self.tt = Test();
end


-- function actor:HelloEvent()
--     self.Rpc:MultiClientEvent()
-- end

-- override event from blueprint
function actor:ReceiveEndPlay(reason)
    print("actor:ReceiveEndPlay")
    self.Super:ReceiveEndPlay(reason)
end

function actor:onPressH()
    local array = self.tt:GetArrayStr();

    self.Rpc:HelloEvent(121,array)
end

function actor:MultiClientEvent()
    self:Output("[multi] actor:MultiClientEvent xx")
    -- can't call super function in RPC
    -- self.Super:MultiClientEvent()
end

function actor:MyTest()
    print("actor:MyTest")
end

function actor:Tick(dt)
end

return actor