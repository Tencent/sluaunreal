
local WBL = import("WidgetBlueprintLibrary")

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

local FKey = import "Key"
function panel:OnMouseButtonDown(Geometry,Event)
    local key = FKey()
    key.KeyName = "LeftMouseButton"
    print("panel:OnMouseButtonDown",FKey,key)
    return WBL.DetectDragIfPressed(Event,self,key)
end

function panel:OnFocusReceived(Geometry,Event)
    print"panel:OnFocusReceived"
end

function panel:OnMouseMove(Geometry,Event)
    print"panel:OnMouseMove"
    return WBL.Handled()
end

local DragOPCls = slua.loadClass("/Game/MyDragOP.MyDragOP")
function panel:OnDragDetected(Geometry,PointerEvent,Operation)
    return WBL.CreateDragDropOperation(DragOPCls)
end

function panel:OnDragEnter(Geometry,Event,Operation)
    print("panel:OnDragEnter",Operation)
end

function panel:OnDragLeave(Event,Operation)
    print("panel:OnDragLeave",Operation)
end

return panel