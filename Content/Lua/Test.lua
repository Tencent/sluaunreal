require 'TestCase'
require 'TestStruct'
require 'TestCppBinding'
local TestArray = require 'TestArray'



local Test=import('SluaTestCase');
print("Test static func",Test.StaticFunc())


local B=require 'TestModule'

print("UEnums.EForceInit.ForceInitToZero=" .. tostring(UEnums.EForceInit.ForceInitToZero))

print("test require",B.foo())

local r = FRotator()

local Test=import('SluaTestCase');
local t=Test();
local brush = t:GetBrush()
local bb = t:GetWidget("Button");

local v = FVector(100,200,300)
local r1,r2,r3=t:TestStruct(v,0,v,1024,0,"hello world")
assert(r1==v*4)
assert(r2==FVector(200,400,600))
assert(r3==1024)

print(bb)

local Button = import('Button');
local ButtonStyle = import('ButtonStyle');
local TextBlock = import('TextBlock');
local btn=Button();
local txt=TextBlock();
local ui=slua.loadUI('/Game/Panel.Panel');
t:TwoArgs("helloworld",100,1717,"1024",ui)
ui:AddToViewport(0);
local seq=ui.ActiveSequencePlayers;
print('seq',seq:Num());
local btn2=ui:FindWidget('Button1');
local index = 1

btn2.OnClicked:Add(function() 
    index=index+1
    print('say helloworld',index) 
end);
local edit=ui:FindWidget('TextBox_0');
local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
edit.OnTextChanged:Remove(evt);
txt:SetText('helloworld button');
local style=ButtonStyle();
btn:SetStyle(style);
btn:AddChild(txt);
print(btn:IsPressed(),btn.OnClicked);
local event=btn.OnClicked;
local index=1
event:Add(function() 
    index=index+1
    print('helloworld',index) 
end);

xx={}

function xx.text()
end

function bpcall(a,b,c,d)
    --print("call from bp",a,b,c,d)
    return 1024,"return from lua 虚幻引擎"
end

local HitResult = import('HitResult');
local count=0
local tt=0

-- test coroutine
local co = coroutine.create( function()
    ccb = slua.createDelegate(function(p)
        print("LoadAssetClass callback in coroutine",p) 
    end)
    Test.LoadAssetClass(ccb)
end )
coroutine.resume( co )
co = nil

function update(dt,actor)
    tt=tt+dt
    local p = actor:K2_GetActorLocation()
    local h = HitResult()
    local v = FVector(math.sin(tt)*100,2,3)
    local offset = FVector(0,math.cos(tt)*50,0)
    local ok,h=actor:K2_SetActorLocation(v+offset,true,h,true)

    local evt=edit.OnTextChanged:Add(function(txt) print('text changed',txt) end);
    edit.OnTextChanged:Remove(evt);
    -- test free event twice
    edit.OnTextChanged:Remove(evt);

    TestArray.update()

    collectgarbage("collect")
    return 1024,2,"s",{1,2,3,4},function() end
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

print(FVector)
for k,v in pairs(FVector) do
    print(type(k),k,type(v),v)
    print_table(getmetatable(v))
end

return 1024,2,"s",{1,2,3,4,5},function() end