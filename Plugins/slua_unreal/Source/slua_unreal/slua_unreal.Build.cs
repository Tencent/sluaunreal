// Some copyright should be here...

using UnrealBuildTool;

public class slua_unreal : ModuleRules
{
	public slua_unreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        // enable exception
        bEnableExceptions = true;
        bEnforceIWYU = false;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            Definitions.Add("LUA_BUILD_AS_DLL");
        }
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			Definitions.Add("_DARWIN_C_SOURCE=1");
		}

        PublicIncludePaths.AddRange(
			new string[] {
				"slua_unreal/Public",
				"slua_unreal/Private",
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"slua_unreal/Private",
				"slua_unreal/Public",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
