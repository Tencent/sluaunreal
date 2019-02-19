
local role = {}

-- override event from blueprint
function role:ReceiveBeginPlay()

    self.handle = self.OnFire:Add(function(value,name) 
        print("Trigger onfire",value,name)
    end)

    self:Super()
    print("role:ReceiveBeginPlay")
    
    print("setupfire")
end

-- override event from blueprint
function role:ReceiveEndPlay(reason)
    print("role:ReceiveEndPlay")
    self.OnFire:Remove(self.handle)
end

return role