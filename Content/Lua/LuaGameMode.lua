local gamemode={}

function gamemode:ReceiveBeginPlay()
    -- call super ReceiveBeginPlay
    self:Super()
    print("gamemode:ReceiveBeginPlay")
end

return gamemode