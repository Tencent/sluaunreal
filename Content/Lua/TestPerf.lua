

local SluaTestCase=import('SluaTestCase');
local t=SluaTestCase();

local TestCount = 1000000
local start = os.clock()
for i=1,TestCount do
    t:EmptyFunc(t)
end
print("1m call EmptyFunc, take time",os.clock()-start)

local start = os.clock()
for i=1,TestCount do
    t:ReturnInt()
end
print("1m call ReturnInt, take time",os.clock()-start)

local start = os.clock()
for i=1,TestCount do
    t:ReturnIntWithInt(i)
end
print("1m call ReturnIntWithInt, take time",os.clock()-start)

local start = os.clock()
for i=1,TestCount do
    t:FuncWithStr("hello world")
end
print("1m call FuncWithStr, take time",os.clock()-start)

-- cppbinding performance test
local t=PerfTest(0)
local start = os.clock()
for i=1,TestCount do
    t:EmptyFunc(t)
end
print("1m call EmptyFunc(cppbinding), take time",os.clock()-start)

local start = os.clock()
for i=1,TestCount do
    t:ReturnInt()
end
print("1m call ReturnInt(cppbinding), take time",os.clock()-start)

local start = os.clock()
for i=1,TestCount do
    t:ReturnIntWithInt(i)
end
print("1m call ReturnIntWithInt(cppbinding), take time",os.clock()-start)

local start = os.clock()
for i=1,TestCount do
    t:FuncWithStr("hello world")
end
print("1m call FuncWithStr(cppbinding), take time",os.clock()-start)