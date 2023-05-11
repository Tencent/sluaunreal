local LuaSubWidgetSecond ={}

function LuaSubWidgetSecond:Initialize()
    print("LuaSubWidgetSecond:Initialize")
end

function LuaSubWidgetSecond:Construct()
    print("LuaSubWidgetSecond:Construct")

end

function LuaSubWidgetSecond:Destruct()
    print("LuaSubWidgetSecond:Destruct")
end

function LuaSubWidgetSecond:OnDestroy()
end


return Class(nil, nil, LuaSubWidgetSecond)