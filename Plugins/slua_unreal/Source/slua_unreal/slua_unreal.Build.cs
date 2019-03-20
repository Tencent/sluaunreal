// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

using UnrealBuildTool;
using System.IO;

public class slua_unreal : ModuleRules
{
    public slua_unreal(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        // enable exception
        bEnableExceptions = true;
        bEnforceIWYU = false;
        bEnableUndefinedIdentifierWarnings = false;

        var externalSource = Path.Combine(ModuleDirectory, "../../External");
        var externalLib = Path.Combine(ModuleDirectory, "../../Library");

        PublicIncludePaths.AddRange(
            new string[] {
                externalSource,
                Path.Combine(externalSource, "lua"),
				// ... add public include paths required here ...
			}
            );

        switch (Target.Platform)
        {
            case UnrealTargetPlatform.IOS:
                {
                    PublicLibraryPaths.Add(Path.Combine(externalLib, "iOS"));
                    PublicAdditionalLibraries.Add("lua");
                    break;
                }
            case UnrealTargetPlatform.Android:
                {
                    PublicLibraryPaths.Add(Path.Combine(externalLib, "Android/armeabi-v7a"));
                    PublicLibraryPaths.Add(Path.Combine(externalLib, "Android/x86"));
                    PublicAdditionalLibraries.Add("lua");
                    break;
                }
            case UnrealTargetPlatform.Win32:
                {
                    PublicLibraryPaths.Add(Path.Combine(externalLib, "Win32"));
                    PublicAdditionalLibraries.Add("lua.lib");
                    break;
                }
            case UnrealTargetPlatform.Win64:
                {
                    PublicLibraryPaths.Add(Path.Combine(externalLib, "Win64"));
                    PublicAdditionalLibraries.Add("lua.lib");
                    break;
                }
            case UnrealTargetPlatform.Mac:
                {
					// Unreal ignores PublicLibraryPaths on Mac. But why? 
                    // PublicLibraryPaths.Add(Path.Combine(externalLib, "Mac"));
                    PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Mac/liblua.a"));
                    break;
                }
            case UnrealTargetPlatform.Linux:
                {
                    PublicLibraryPaths.Add(Path.Combine(externalLib, "Linux"));
                    PublicAdditionalLibraries.Add("lua");
                    break;
                }
        }

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				"UMG",
				// ... add other public dependencies that you statically link with here ...
			}
            );

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }


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
