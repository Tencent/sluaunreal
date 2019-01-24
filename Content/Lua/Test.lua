
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
end

local tt=0
function update(dt)
    tt=tt+dt
    
    TestActor.update(tt,actor)
    TestArray.update(tt)
	TestMap.update(tt)

    collectgarbage("collect")
end