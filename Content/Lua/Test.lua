-- open profile
require 'TestProfile'

-- some.field come from c++
some.field.y = 103
EPropertyClass = import"EPropertyClass"
PrintLog("LuaStateInitCallback ok")
function begin(uworld,uactor)
    gworld=uworld
    gactor=uactor

    local Test=import('SluaTestCase');
    local t=Test();
    testobj = t
    weakptr = testobj.weakptr
    local v = FVector(10,20,30)
    local v2 = FVector(1,2,3)
    local i = 100
    local i2 = 200
    local s = "haha"
    local v3, v2, i2 = t:TestStruct(v, 2, v2, i, i2, s)

    local e = import("EMeshBufferAccess")
    for k,v in pairs(e) do
        print("eeee",k,v)
    end
  
    assert(TestEnum.TE_COUNT==2)
    assert(TestEnum2.COUNT==2)

    -- set from c++
    print(some,some.field)
    assert(somefield==102)
    assert(some.field.x==101)
    assert(some.field.y==103)
    assert(some.field.z==104)
    slua.threadGC("on")

    testcase()
end

function testcase()
    -- require 'TestPerf'
    require 'TestUI'
    require 'TestCase'
    require 'TestStruct'
    require 'TestCppBinding'
    TestBp=require 'TestBlueprint'
    TestBp:test(gworld,gactor)

    TestMap = require 'TestMap'
    TestArray = require 'TestArray'
    TestActor = require 'TestActor'
    TestSet = require "TestSet"

    -- slua can detect dead loop code
    -- if lua exec timeout ,slua will report an error and jump out function 
    -- you can comment out below code to test it
    -- while true do
    --     print("dead loop")
    -- end
end

local tt=0
function update(dt)
    tt=tt+dt
    
    TestActor.update(tt,gactor)
    TestArray.update(tt)
    TestMap.update(tt)
    TestBp:update(tt)
    TestSet.update(tt)

    -- test weak ptr is alive?
    if slua.isValid(weakptr) then
        print("weak ptr",weakptr,weakptr:GetClass())
    end
end