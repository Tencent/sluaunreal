

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
assert(arr:Get(1)==2048)
assert(arr:Num()==9)
