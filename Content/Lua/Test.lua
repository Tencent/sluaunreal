
-- some.field come from c++
some.field.y = 103
EPropertyClass = import"EPropertyClass"
PrintLog("LuaStateInitCallback ok")
require("LuaNameTestNewLib").LuaNamePrintLog("this is lua name test model func")
function begin(uworld,uactor)
    world=uworld
    actor=uactor

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
    TestBp:test(world,actor)

    TestMap = require 'TestMap'
    TestArray = require 'TestArray'
    TestActor = require 'TestActor'

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
    
    TestActor.update(tt,actor)
    TestArray.update(tt)
    TestMap.update(tt)
    TestBp:update(tt)
end