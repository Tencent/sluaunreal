if slua_profile then
    print"start slua profile"
    slua_profile.start("127.0.0.1",8081)

    local KismetSystemLibrary = import("KismetSystemLibrary")
    KismetSystemLibrary.ExecuteConsoleCommand(slua.getGameInstance(), "slua.StartMemoryTrack")
end