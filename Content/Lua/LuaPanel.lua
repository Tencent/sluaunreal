
local WBL = import("WidgetBlueprintLibrary")

local Panel ={}

function Panel:ctor()
    self.printOnceInTick = true
end

function Panel:Initialize()

end

function Panel:Construct()
    print("panel:Construct")
    self.bHasScriptImplementedTick = true

    self.imgs = {
        {
        src="Texture2D'/Game/boy.boy'",
        name="boy",
        },
        {
        src="Texture2D'/Game/girl.girl'",
        name="girl",
        }
    }

    self:MyFunc()
    local ok,str = self:MyOverride()
    print("over ret",ok,str)
end

function Panel:MyOverride()
    print("MyOverride lua")
    self.Super:MyOverride()
    return false,"return from lua"
end

function Panel:Destruct()
    print("panel:Destruct")
    self.imgs = nil
end

function Panel:Tick(geom, dt)
    if self.printOnceInTick then
        print("panel:tick")
    end
    -- call parent super
    self.Super:Tick(geom,dt)
    local item = self.imgs[math.random(1,2)]
    local texture = slua.loadObject(item.src)
    self.Item.Image_42:SetBrushFromTexture( texture,false )
    self.Item.TextBlock_43:SetText(item.name)

    if self.printOnceInTick then
        local m = self.ValMap
        print("over",m:Num())
        for k,v in pairs(m) do
            print("over",k,v)
        end
    end

    self.printOnceInTick = false
end

function Panel:OnDestroy()
end

function Panel:OnKeyDown(Geometry, Event)
    print("panel:OnKeyDown")
end

local FKey = import "Key"
function Panel:OnMouseButtonDown(Geometry, Event)
    local key = FKey()
    key.KeyName = "LeftMouseButton"
    print("panel:OnMouseButtonDown",FKey,key)
    return WBL.DetectDragIfPressed(Event,self,key)
end

function Panel:OnFocusReceived(Geometry, Event)
    print("panel:OnFocusReceived")
end

function Panel:OnMouseMove(Geometry, Event)
    print("panel:OnMouseMove")
    return WBL.Handled()
end

local DragOPCls = import("/Game/MyDragOP.MyDragOP_C")
function Panel:OnDragDetected(Geometry, PointerEvent, Operation)
    return WBL.CreateDragDropOperation(DragOPCls)
end

function Panel:OnDragEnter(Geometry, Event, Operation)
    print("panel:OnDragEnter",Operation)
end

function Panel:OnDragLeave(Event, Operation)
    print("panel:OnDragLeave",Operation)
end

return Class(nil, nil, Panel)