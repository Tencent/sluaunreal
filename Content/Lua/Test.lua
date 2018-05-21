
local Test=import('SluaTestCase');
local t=Test();


print(string.format("Brush=%s", tostring(t.Brush)))
print(string.format("Value=%s", tostring(t.Value)))
t.Value = 100
print(string.format("Value=%s", tostring(t.Value)))
print()
local v = FVector(10,20,30)
local v2 = FVector(1,2,3)
local i = 100
local i2 = 200
local s = "haha"
local v3, v2, i2 = t:TestStruct(v, 2, v2, i, i2, s)
print(string.format("v2 = %d,%d,%d", v2.X, v2.Y, v2.Z))
print(string.format("v3 = %d,%d,%d", v3.X, v3.Y, v3.Z))
print(string.format("i2=%d", i2))

local arr=t:GetArray();
print("arr len",arr:Num())
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end

print("begin TestInt_int")
local i = 100
i = t:TestInt_int(i)
print(string.format("lua TestInt_int i=%d", i))
print("end TestInt_int")

print("begin TestIntStr_Str")
local i = 100
local s = "hehe"
s = t:TestIntStr_Str(i, s)
print(string.format("lua TestIntStr_Str i=%d, s=%s", i, s))
print("end TestIntStr_Str")

print("begin TestIntStrEnum_Enum")
local i = 100
local s = "hehe"
local e = 1
e = t:TestIntStrEnum_Enum(i, s, e)
print(string.format("lua TestIntStrEnum_Enum i=%d, s=%s, e=%d", i, s, e))
print("end TestIntStrEnum_Enum")

print("begin TestIntStrEnum_Arr")
local i = 100
local s = "hehe"
local e = 1
local arr = t:TestIntStrEnum_Arr(i, s, e)
print(string.format("lua TestIntStrEnum_Arr i=%d, s=%s, e=%d", i, s, e))
print("arr len",arr:Num())
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end
print("end TestIntStrEnum_Arr")

print("begin TestOIntOStrOEnum")
local i = 100
local s = "hehe"
local e = 1
i, s, e = t:TestOIntOStrOEnum(i, i, s, s, e, e)
print(string.format("lua TestOIntOStrOEnum i=%d, s=%s, e=%d", i, s, e))
print("end TestOIntOStrOEnum")

local B=require 'b'

print("UEnums.EForceInit.ForceInitToZero=" .. tostring(UEnums.EForceInit.ForceInitToZero))

print("test require",B.foo())

local r = FRotator()

-- local Test=import('SluaTestCase');
-- local t=Test();

local brush = t:GetBrush()
local bb = t:GetWidget("Button");

-- local v = FVector(100,200,300)
-- t:TestStruct(v)

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

xx={}

function xx.text()
    print(t.Value)
    t.Value=1024
    print("set value",t.Value)
end


local HitResult = import('HitResult');

function update(dt,actor)
    print("call update")
    actor:SetFName("fuck")
    actor.FolderPath = "asdfasdfasdf"
    print("folder path",actor.FolderPath)
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