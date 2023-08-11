

local a = FVector(1,1,1)
local b = FVector(2,2,2)

local KismetsystemLibrary = import("KismetSystemLibrary")
local EngineVersion = KismetsystemLibrary.GetEngineVersion()
print("EngineVersion: ", EngineVersion)
if string.sub(EngineVersion, 1, 1) == "4" then
    local c = a+b*3.14
    local d = FVector(1,1,1)*3.14*2+FVector(1,1,1)
    assert(c==d)
end

if FLinkStruct then
    st = FLinkStruct()
    b2d = st.b2d
    min = b2d.Min

    print("------")
    print(1, min.X)
    print(2, b2d.Min.X)
    print(3, st.b2d.Min.X)
    collectgarbage("collect")

    print("------")
    min.X = 100
    print(1, min.X)
    print(2, b2d.Min.X)
    print(3, st.b2d.Min.X)
    collectgarbage("collect")

    print("------")
    b2d.Min.X = 200
    print(1, min.X)
    print(2, b2d.Min.X)
    print(3, st.b2d.Min.X)
    collectgarbage("collect")

    print("------")
    st.b2d.Min.X = 300
    print(1, min.X)
    print(2, b2d.Min.X)
    print(3, st.b2d.Min.X)
    collectgarbage("collect")

    b2d = nil
    collectgarbage("collect")


    print("------")
    local ret,err=pcall(function()
        print(1, min.X)
    end)
    print(ret,err)

    st = nil
    collectgarbage("collect")

    print("------")
    local ret,err=pcall(function()
        print(2, b2d.Min)
    end)
    print(ret,err)
end