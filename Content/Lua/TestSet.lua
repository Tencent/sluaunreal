local EPropertyClass = import("EPropertyClass")
local set = slua.Set(EPropertyClass.Int)
for i = 1, 10, 2 do
    set:Add(i)
end

set:Remove(5)

for k, v in set:Pairs() do
    print("test set iterate:", k, v)
end

for k, v in set:Pairs(true) do
    print("test set iterate reverse:", k, v)
end