local LuaSubWidgetFirst ={}

function LuaSubWidgetFirst:Initialize()
    print("LuaSubWidgetFirst:Initialize")
end

function LuaSubWidgetFirst:Construct()
    print("LuaSubWidgetFirst:Construct")

end

function LuaSubWidgetFirst:Destruct()
    print("LuaSubWidgetFirst:Destruct")
end

function LuaSubWidgetFirst:OnDestroy()
end


return Class(nil, nil, LuaSubWidgetFirst)