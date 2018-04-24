local B=require 'b'

print("UEnums.EForceInit.ForceInitToZero=" .. tostring(UEnums.EForceInit.ForceInitToZero))

print("test require",B.foo())

local r = FRotator()

local Test=import('SluaTestCase');
local t=Test();
local bb = t:GetWidget("Button");

local v = FVector(100,200,300)
t:TestStruct(v)

print(bb)

-- test
for i=1,10 do
    local arr=t:GetArray();
    print("arr len",arr:Num())
    for i=0,arr:Num()-1 do
        print("arr item",i,arr:Get(i))
    end
end

local Button = import('Button');
-- local ButtonStyle = import('ButtonStyle');
-- local TextBlock = import('TextBlock');
local btn=Button();
-- local txt=TextBlock();
local ui=slua.loadUI('/Game/Panel.Panel');
t:TwoArgs("fuck",100,1717,"1024",ui)
ui:AddToViewport(0);
-- local seq=ui.ActiveSequencePlayers;
-- print('seq',seq:Num());
local tree=ui.WidgetTree;
local btn2=tree:FindWidget('Button1');
local index = 1

btn2.OnClicked:Add(function() 
    index=index+1
    print('fuck',index) 
end);
local edit=tree:FindWidget('TextBox_0');
-- local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
-- edit.OnTextChanged:Remove(evt);
-- txt:SetText('fuck button');
-- local style=ButtonStyle();
-- btn:SetStyle(style);
-- btn:AddChild(txt);
-- print(btn:IsPressed(),btn.OnClicked);
-- local event=btn.OnClicked;
-- local index=1
-- event:Add(function() 
--     index=index+1
--     print('fuck',index) 
-- end);


local HitResult = import('HitResult');

function update(dt,actor)
    print("call update")
    local p = actor:K2_GetActorLocation()
    --print("actor pos",p[1])
    local h = HitResult()
    --local ok,h=actor:K2_SetActorLocation({20,0,0},true,h,true)
    local v = FVector(1,2,3)
    local ok,h=actor:K2_SetActorLocation(v,true,h,true)
    --print("hit info",h)
    -- test memory leak?
    local arr=t:GetArray();
    -- print("arr len",arr:Num())
    for i=0,arr:Num()-1 do
         -- print("arr item",i,arr:Get(i))
    end

    local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
    edit.OnTextChanged:Remove(evt);
    -- test free event twice
    edit.OnTextChanged:Remove(evt);

    return 1024,2,"s",{},function() end
end

function print_table(t)
    print("begin print table...")
    for k,v in pairs(t) do
        print(type(k),k,type(v),v)
    end
    print("end print table...")
end

print("=======================")
print(FVector)
local a = FVector()
print_table(getmetatable(a))
a:Set(100,200,300)
print(a:GetMax())
local b = FVector()
b:Set(1,2,3)
print(b:GetMax())

print("=======================")

local OneVector = FVector.OneVector
print(OneVector)
print(OneVector.X,OneVector.Y,OneVector.Z)
print(OneVector:ToString())

-- print(FVector)
-- for k,v in pairs(FVector) do
--     print(type(k),k,type(v),v)
--     print_table(getmetatable(v))
-- end

return 1024,2,"s",{},function() end