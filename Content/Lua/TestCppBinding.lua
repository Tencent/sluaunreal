-- test cpp binding
local f1=Foo(1024)
assert(f1.value==1024)
f1.value=2048
assert(f1.value==2048)
local ee =f1:testEnum("hi",3)
print("enum is " ..  type(ee) .. " " .. tostring(ee))
local str=Foo.getStr()
-- f2 not collect
local f2=Foo.getInstance()
f1:bar(str)
f2:bar(str)
-- call base function
f1:baseFunc1()

-- test tfunction
f1:setCallback(function(i) print("callback from cppbinding",i) end)
f1:docall()
-- test lambda 
f1:helloWorld()

local f3=FooChild(2048)
assert(f3.value==2048)
f3.value=1024
assert(f3.value==1024)
f3:virtualFunc()
f3:bar("f3")
f3:baseFunc1()
f3:setEventListener(function()
    print("event fired")
end)
f3:eventTrigger()

local arr = slua.Array(EPropertyClass.Int)
arr:Add(1)
arr:Add(2)
arr:Add(3)
local map = slua.Map(EPropertyClass.Int, EPropertyClass.Str)
map:Add(4,"400")
map:Add(5,"500")
f3:testArrMap(100,arr,map)
local ret = f3:testArrMap2(200,arr,map)
print(tostring(ret))

local f=FooChild(0)
assert(f.value==0)
local arr = f:getTArray()
for i=1,arr:Num() do
    print("arr value",i,arr:Get(i-1))
end

local HR = import('HitResult');
local hit = HR()
hit.Time=0.1
hit.Distance=512
print(f:hit(hit))

local map = f:getTMap()
for k,v in pairs(map) do
    print("map value",k,v)
end

local boxptr = f:getBoxPtr()
assert(boxptr:getCount()==1024)
assert(boxptr:getCount()==1025)

local http = FHttpModule.Get()
local req = http:CreateRequest()
req:SetURL("http://www.baidu.com")
req:SetVerb("get")
print"http test begin"
--[[
req:OnRequestProgress():Bind(function(req,sent,recv)
    print("http",req,sent,recv)
end)
req:OnProcessRequestComplete():Bind(function(req,resp,ret)
    print("http complete",req,resp,ret)
end)
]]
req:ProcessRequest()