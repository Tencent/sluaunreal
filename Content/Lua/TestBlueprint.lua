
local GameplayStatics=import'GameplayStatics';

local testcase={}
local HitResult = import('HitResult');


function testcase:test(uworld,uactor)
    print("=====Begin test blueprint")
    local bpClass = import("/Game/TestActor.TestActor_C")
    -- get out TArray for actors
    local arr=GameplayStatics.GetAllActorsOfClass(uactor,bpClass,nil)

    for k,v in pairs(arr) do
        print("GetAllActorsOfClass",k,v)
    end

    self.bp = bpClass(uworld.CurrentLevel)
    print("blueprint",self.bp)
    self.bp:TestFoo("hello")
    self.bp:TestFoo("world")
    -- store old actor for map2 use, test a bug
    oldactor = self

    local bpClass = import("/Game/LuaBpActor.LuaBpActor_C")

    self.balls={}
    self.basepos={}
    self.rot={}
    for n=1,10 do
        local p = FVector(math.random(-100,100),math.random(-100,100),0)
        local actor = uworld:SpawnActor(bpClass,p,nil,nil)
        self.balls[n]=actor
        self.basepos[n]=p
        self.rot[n]=math.random(-100,100)
        uactor.objs:Add(actor)
        -- actor.Name = 'ActorCreateFromLua_'..tostring(n)
    end
    
    -- print("=====End test blueprint",self.bp.Name)
end

function testcase:update(tt)
    for i,actor in pairs(self.balls) do
        local p = self.basepos[i]
        local h = HitResult()
        local rot = self.rot[i]
        local v = FVector(math.sin(tt)*rot,0,0)
        local offset = FVector(0,math.cos(tt)*rot,0)
        local ok,h=actor:K2_SetActorLocation(p+v+offset,true,h,true)
    end
end

function bpcall(a,b,c,d)
    print("bpcall",a,b,c,d)
	return 1024,"return from lua 虚幻引擎"
end

function bpcall2()
    print "bpcall2 with empty args"
end

return testcase