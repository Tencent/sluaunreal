local gamemode={}

function gamemode:ReceiveBeginPlay()
    -- call super ReceiveBeginPlay
    self:Super()
    print("gamemode:ReceiveBeginPlay")

    local gs = import"GameplayStatics"
    local world = self:GetWorld()
    local ctrl = gs.GetPlayerController(world,0)
    local input = ctrl.PlayerInput
    print("player controller",ctrl,input,input.Fire)

end

return gamemode