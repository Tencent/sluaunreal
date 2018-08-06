

local Test=import('SluaTestCase');
local t=Test();

-- test array
local arr=t:GetArray();
assert(arr:Num()==8)
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end
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
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end
arr:Add("shijie")
for i=0,arr:Num()-1 do
    print("arr item",i,arr:Get(i))
end
assert(arr:Num()==4)
print('array<fstring> test successful')

arr:Clear()

-- create TArray<int>
local arr = slua.Array(UEnums.EPropertyClass.Int)
arr:Add(1)
arr:Add(2)
arr:Add(3)
print('size of arr',arr:Num())

-- create TArray<FString>
local arr = slua.Array(UEnums.EPropertyClass.Str)
arr:Add("jamy")
arr:Add("valen")
arr:Add("kyo")
print('size of arr',arr:Num())
t:SetArrayStr(arr)
t:SetArrayStrEx(arr)

TestArray={}

function TestArray.update()
    -- test memory valid?
    for i=0,arr:Num()-1 do
        print("arr item",i,arr:Get(i))
    end
end


return TestArray


