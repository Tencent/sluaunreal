

local Test=import('SluaTestCase');
local t=Test();

-- test array
local arr=t:GetArray();
assert(arr:Num()==8)
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end
print("begin for paris...")
for i,v in pairs(arr) do
    print("arr item",i,v)
end
print("end for paris...")
local num = arr:Add(1024)
assert(arr:Num()==9)
assert(arr:Get(8)==1024)
arr:Remove(8)
assert(arr:Num()==8)
arr:Insert(1,2028)
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end

print('arr size',arr:Num(),arr:Get(1))
assert(arr:Get(1)==2028)
assert(arr:Num()==9)
print('array<int> test successful')

-- test array<fstring>
local arr=t:GetArrayStr()
assert(arr:Num()==3)
assert(arr:Get(0)=="hello")
assert(arr:Get(1)=="world")
assert(arr:Get(2)=="nihao")
arr:Add("shijie")
assert(arr:Num()==4)
assert(arr:Get(3)=="shijie")
print('array<fstring> test successful')
arr:Clear()
assert(arr:Num()==0)

-- create TArray<int>
local arr = slua.Array(EPropertyClass.Int)
arr:Add(1)
arr:Add(2)
arr:Add(3)
assert(arr:Num()==3)

-- create TArray<FString>
local arr = slua.Array(EPropertyClass.Str)
arr:Add("jamy")
arr:Add("valen")
arr:Add("kyo")
print('size of arr',arr:Num())
t:SetArrayStr(arr)
t:SetArrayStrEx(arr)

local strs = t.strs
strs:Add("1")
strs:Add("2")
assert(t.strs:Num()==2)
assert(t.strs:Get(0)=="1")
strs:Clear()
assert(t.strs:Num()==0)

local TestArray={}

function TestArray.update()
    -- test memory valid?
    assert(arr:Num()==3)
    assert(arr:Get(0)=="jamy")
end


return TestArray


