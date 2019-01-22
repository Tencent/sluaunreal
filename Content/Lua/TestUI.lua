
local ui=slua.loadUI('/Game/Panel.Panel');
ui:AddToViewport(0);
local btn2=ui:FindWidget('Button1');
local index = 1
local handler = btn2.OnClicked:Add(function() 
    index=index+1
    print('say helloworld',index) 
	remove()
	ui:RemoveFromViewport()
	ui=nil
end);

function remove()
	print("before remove")
	local leaks = slua.dumpUObjects()
	for k,v in pairs(leaks) do
		print(k,v)
	end
	collectgarbage("collect")

	btn2.OnClicked:Remove(handler)
	btn2=nil

	print("after remove")
	local leaks = slua.dumpUObjects()
	for k,v in pairs(leaks) do
		print(k,v)
	end
end