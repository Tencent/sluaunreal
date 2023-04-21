
local ui=slua.loadUI('/Game/Panel.Panel',gworld);
ui:AddToViewport(0);
local btn2=ui:FindWidget('btnClose');
local index = 1
local handler = btn2.OnClicked:Add(function() 
    index=index+1
    print('panel closed',index) 
	remove()
	ui:RemoveFromViewport()
	ui=nil
end);

-- can use key to index ui
local bpClass = import("/Game/TestActor.TestActor_C")

local btn1 = ui["Button_0"]
local h_openmap = btn1.OnClicked:Add(function()
	print("open new map")
	local bp = bpClass(gworld.CurrentLevel)
	bp:LoadNewMap("Map2")
end);

function remove()
	print("before remove")
	local leaks = slua.dumpUObjects()
	for k,v in pairs(leaks) do
		print(k,v)
	end
	btn2.OnClicked:Remove(handler)
	btn2=nil
	btn1.OnClicked:Remove(h_openmap)
	btn1=nil

	print("after remove")
	local leaks = slua.dumpUObjects()
	for k,v in pairs(leaks) do
		print(k,v)
	end
end