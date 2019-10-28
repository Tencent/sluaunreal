
local WBL = import("WidgetBlueprintLibrary")

local panel ={}

function panel:Construct()
    print"panel:Construct"
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

function panel:MyOverride()
    print"MyOverride lua"
    self.Super:MyOverride()
    return false,"return from lua"
end

function panel:Destruct()
    print"panel:Destruct"
    self.imgs = nil
end

function panel:Tick(geom,dt)
    print("panel:tick")
    -- call parent super
    self.Super:Tick(geom,dt)
    local item = self.imgs[math.random(1,2)]
    local texture = slua.loadObject(item.src)
    self.Item.Image_42:SetBrushFromTexture( texture,false )
    self.Item.TextBlock_43:SetText(item.name)

    local m = self.ValMap
    print("over",m:Num())
    for k,v in pairs(m) do
        print("over",k,v)
    end
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