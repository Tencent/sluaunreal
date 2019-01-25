
function begin(uworld,uactor)
    world=uworld
    actor=uactor

    print("Unreal enum",UEnums.LogLevel.LL_Warning)

    testcase()
end

function testcase()
    -- require 'TestPerf'
    require 'TestUI'
    require 'TestCase'
    require 'TestStruct'
    require 'TestCppBinding'
    local test=require 'TestBlueprint'
    test.test(world,actor)

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

    collectgarbage("collect")
end