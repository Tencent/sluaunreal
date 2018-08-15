local Test=import('SluaTestCase');
local t=Test();

local t = {t:GetMap(), slua.Map(UEnums.EPropertyClass.Int, UEnums.EPropertyClass.Str)}
for i,v in ipairs(t) do
    local map = v
    map:Add(5,"500")
    print("map:Get(5)", map:Get(5))

    map:Add(1,"100")
    map:Add(2,"200")
    print("map num", map:Num())

    map:Add(8,"800")
    map:Add(9,"900")
    print("map num", map:Num())

    print("map get(1)", map:Get(1))
    print("map get(2)", map:Get(2))

    print("map remove(1)", map:Remove(1))
    print("map num", map:Num())

    print("map:Get(8)", map:Get(8))
    print("map:Get(9)", map:Get(9))

    local v,r = map:Get(100)
    print("map:Get(100)", v, r)

    print("map num", map:Num())

    print("foreach begin...")
    for k,v in map:Pairs() do
        print(k,v)
    end
    print("foreach end...")

    print("foreach begin...")
    for k,v in pairs(map) do
        print(k,v)
    end
    print("foreach end...")

    map:Clear()
    print("map num", map:Num())
end