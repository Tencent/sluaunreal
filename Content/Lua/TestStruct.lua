

local a = FVector(1,1,1)
local b = FVector(2,2,2)
local c = a+b*3.14
local d = FVector(1,1,1)*3.14*2+FVector(1,1,1)
assert(c==d)