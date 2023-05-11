
local MyRole = {}

-- override event from blueprint
function MyRole:ReceiveBeginPlay()

    self.handle = self.OnFire:Add(function(value,name) 
        print("Trigger onfire",value,name)
    end)

    self.Super:ReceiveBeginPlay()
    print("role:ReceiveBeginPlay")
    
    print("setupfire")
end

-- override event from blueprint
function MyRole:ReceiveEndPlay(reason)
    print("role:ReceiveEndPlay")
    self.OnFire:Remove(self.handle)
end

return Class(nil, nil, MyRole)