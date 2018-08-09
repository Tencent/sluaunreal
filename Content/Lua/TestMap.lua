local Test=import('SluaTestCase');
local t=Test();

map = t:GetMap()

map:Add(5,"500")
print("map:Get(5)", map:Get(5))

map:Add(1,"100")
map:Add(2,"200")
print("map num", map:Num())

-- local map = slua.Map(UEnums.EPropertyClass.Int, UEnums.EPropertyClass.Str)
map:Add(8,"800")
map:Add(9,"900")
print("map num", map:Num())

print("map get(1)", map:Get(1))
print("map get(2)", map:Get(2))

print("map remove(1)", map:Remove(1))
print("map num", map:Num())

print("map:Get(8)", map:Get(8))
print("map:Get(9)", map:Get(9))
print("map num", map:Num())

map:Clear()
print("map num", map:Num())
