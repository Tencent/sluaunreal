local LuaGameMode = {}

function LuaGameMode:ReceiveBeginPlay()
    -- call super ReceiveBeginPlay
    self.Super:ReceiveBeginPlay()
    print("gamemode:ReceiveBeginPlay")
end

function LuaGameMode:CppCallLuaFunctionWithArray(List)
    print(List:Num())
    for Index, Element in List:PairsLessGC() do
        print("Array of PlayerInfo: ", Element.PlayerName, Element.PlayerId)
    end
end

function LuaGameMode:CppCallLuaFunctionWithSet(Set)
    print(Set:Num())
    for Index, Element in pairs(Set) do
        print("Set of PlayerInfo: ", Element.PlayerName, Element.PlayerId)
    end
end

function LuaGameMode:CppCallLuaFunctionWithMap(Map)
    print(Map:Num())
    for Index, Element in pairs(Map) do
        print("Map of PlayerInfo: ", Index, Element.PlayerName, Element.PlayerId)
    end
end

return Class(nil, nil, LuaGameMode)