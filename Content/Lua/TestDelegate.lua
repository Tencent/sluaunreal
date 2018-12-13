local Test=import('SluaTestCase');

-- test coroutine
local co = coroutine.create( function()
    ccb = slua.createDelegate(function(p)
        print("LoadAssetClass callback in coroutine",p) 
    end)
    Test.LoadAssetClass(ccb)

    
end )
coroutine.resume( co )
co = nil