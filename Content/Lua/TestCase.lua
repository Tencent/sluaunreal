
local Test=import('SluaTestCase');
local t=Test();

local han = t.OnTestAAA:Add(function(s)
    print(s)
    RemoveAAA()
end)

t:TestLuaCallback(function() print("callback bpvar") end)

function RemoveAAA()
    print("AAAAAAAAAAAAAAAAA")
    t.OnTestAAA:Remove(han)
end

t:TestAAA("abc AAAA")

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

local info = t:GetUserInfo()
print("info.name",info.name)
assert(info.name=="女战士")
assert(info.id==1001001)
assert(info.level==12)

t.OnTestGetCount:Bind(function (s)
    print(s)
    return 1111
end)

t:TestUnicastDelegate("test unicast delegate")

local FArrayToBinStringTest = import("ArrayToBinStringTest")
local ArrayToBinStringTest = FArrayToBinStringTest()
ArrayToBinStringTest.binString = "binString"
assert(type(ArrayToBinStringTest.binString) == "string")
print(ArrayToBinStringTest.binString)

-- test TArray<UObject>

foos = t.foos
t:setupfoo(t)
print("get foos",foos,foos:Num())
for i=1,foos:Num() do
    print("foos property",i,foos:Get(i-1))
end

userInfo = t.userInfo
print("userInfo",userInfo)

t.userArray = {}
print("t.userArray", t.userArray, t.userArray)
assert(t.userArray == t.userArray)
userArray = t.userArray
print("userArray",userArray)

info = t.info
print("info",info)

map1 = t:GetMap()
print("map1",map1)

local SluaTestCase=import('SluaTestCase');
local t=SluaTestCase()
for k, v in pairs(t) do
    print("SluaTestCase iter", k, v)
end
print("SluaTestCase weakptr:", t.weakptr) ---expect as uobject type not LuaArray.