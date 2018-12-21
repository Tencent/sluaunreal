
local GameplayStatics=import'GameplayStatics';

local testcase={}

function testcase.test(uworld,actor)
    print("=====Begin test blueprint")
    local bpClass = slua.loadClass("/Game/TestActor.TestActor")
    -- get out TArray for actors
    local arr=GameplayStatics.GetAllActorsOfClass(actor,bpClass,nil)

    for k,v in pairs(arr) do
        print("GetAllActorsOfClass",k,v)
    end

    local bp = bpClass(uworld.CurrentLevel)
    print("blueprint",bp)
    bp:TestFoo("hello")
    bp:TestFoo("world")

    print("=====End test blueprint")
end

function bpcall(a,b,c,d)
    print("bpcall",a,b,c,d)
	return 1024,"return from lua 虚幻引擎"
end

function bpcall2()
    print "bpcall2 with empty args"
end

return testcase