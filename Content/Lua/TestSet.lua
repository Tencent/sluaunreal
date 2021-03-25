local M = {}
local Test = import("SluaTestCase")
local t = Test()
local set = t:GetSet()

function M:Run()
    self:IntTest()
    self:StringTest()
    self:ObjectTest()
    self:GetSetTest()
end

function M:IntTest()
    local x = slua.Set(EPropertyClass.Int)
    local obj1 = 1
    local obj2 = 2
    self:Test(x, obj1, obj2)
    print("[TestSet] Pass IntTest")
end

function M:StringTest()
    local x = slua.Set(EPropertyClass.Str)
    local obj1 = "string1"
    local obj2 = "string2"
    self:Test(x, obj1, obj2)
    print("[TestSet] Pass StringTest")
end

function M:ObjectTest()
    local UUserWidget = import("UserWidget")
    local UIPath1 = "/Game/LuaPanel.LuaPanel"
    local UIPath2 = "/Game/Panel.Panel"
    local x = slua.Set(EPropertyClass.Object, UUserWidget)
    local obj1 = slua.loadUI(UIPath1)
    local obj2 = slua.loadUI(UIPath2)
    self:Test(x, obj1, obj2)
    print("[TestSet] Pass ObjectTest")
end

function M:Test(x, obj1, obj2)
    assert(x:Num() == 0)

    x:Add(obj1)
    assert(x:Num() == 1)

    local a, b = x:Get(obj1)
    assert(a == obj1)
    assert(b == true)

    x:Add(obj1)
    assert(x:Num() == 1)

    a, b = x:Get(obj1)
    assert(a == obj1)
    assert(b == true)

    x:Add(obj2)
    assert(x:Num() == 2)

    a, b = x:Get(obj2)
    assert(a == obj2)
    assert(b == true)

    x:Remove(obj1)
    assert(x:Num() == 1)

    a, b = x:Get(obj1)
    assert(a == nil)
    assert(b == false)

    x:Clear()
    assert(x:Num() == 0)
end

function M:GetSetTest()
    for i, v in pairs(set) do
        local a, b = set:Get(v)
        print("[SetTest] Item :", i, a, b)
        assert(a == v)
        assert(b == true)
    end

    set:Clear()
    self:Test(set, 65535, 2147483647)
    print("[SetTest] pass GetSetTest")
end

function M.update()
    assert(set:Num() == 2)
    assert(set:Get(65535) == 65535, true)
end

M:Run()
set:Add(65535)
set:Add(2147483647)

return M