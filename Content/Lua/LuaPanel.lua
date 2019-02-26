
local panel ={}

function panel:Construct()
    print"panel:Construct"
    self.bHasScriptImplementedTick = true
end

function panel:Tick()
    print("panel:tick")
    -- call parent super
    self:Super()
end

function panel:OnKeyDown(Geometry,Event)
    print"panel:OnKeyDown"
end

function panel:OnFocusReceived(Geometry,Event)
    print"panel:OnFocusReceived"
end

function panel:OnMouseMove(Geometry,Event)
    print"panel:OnMouseMove"
end

return panel