local RpcTestActor ={}

function RpcTestActor:ReceiveBeginPlay()
    print("actor:ReceiveBeginPlay")
    self.Super:ReceiveBeginPlay()
    local Test=import('SluaTestCase')
    self.tt = Test();
end


-- function actor:HelloEvent()
--     self.Rpc:MultiClientEvent()
-- end

-- override event from blueprint
function RpcTestActor:ReceiveEndPlay(reason)
    print("actor:ReceiveEndPlay")
    self.Super:ReceiveEndPlay(reason)
end

function RpcTestActor:onPressH()
    local array = self.tt:GetArrayStr();

    self.Rpc:HelloEvent(121,array)
end

function RpcTestActor:MultiClientEvent()
    self:Output("[multi] actor:MultiClientEvent xx")
    -- can't call super function in RPC
    -- self.Super:MultiClientEvent()
end

function RpcTestActor:MyTest()
    print("actor:MyTest")
end

function RpcTestActor:Tick(dt)
end

return Class(nil, nil, RpcTestActor)