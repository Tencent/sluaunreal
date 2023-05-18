local Test=import('SluaTestCase');
local t=Test();

local mm = {t:GetMap(), slua.Map(EPropertyClass.Int, EPropertyClass.Str)}

local function test()
	for i,v in ipairs(mm) do
		local map = v
		map:Add(5,"500")
		print("map:Get(5)", map:Get(5))

		map:Add(1,"100")
		map:Add(2,"200")
		print("map num", map:Num())

		map:Add(8,"800")
		map:Add(9,"900")
		print("map num", map:Num())

		print("map get(1)", map:Get(1))
		print("map get(2)", map:Get(2))

		print("map remove(1)", map:Remove(1))
		print("map num", map:Num())

		print("map:Get(8)", map:Get(8))
		print("map:Get(9)", map:Get(9))

		local v,r = map:Get(100)
		print("map:Get(100)", v, r)

		print("map num", map:Num())

		print("foreach begin...")
		for k,v in map:Pairs() do
			print(k,v)
		end
		print("foreach end...")

		print("foreach begin...")
		for k,v in pairs(map) do
			print(k,v)
		end
		print("foreach end...")

		map:Clear()
		assert(map:Num()==0)
	end

	local mm = t.maps
	mm:Add("name","bill")
	mm:Add("age","12")

	assert(t.maps:Num()==2)
	assert(t.maps:Get("name")=="bill")
	assert(t.maps:Get("age")=="12")
	mm:Clear()
	assert(t.maps:Num()==0)
end

local TestMap={}
function TestMap:ReceiveBeginPlay()
    test()
end

function TestMap:update()
	
end

return Class(ni, nil, TestMap)