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

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "iOS/liblua.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
#if UE_4_25_OR_LATER
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Android/armeabi-v7a/liblua.a"));
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Android/armeabi-arm64/liblua.a"));
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Android/x86/liblua.a"));
#elif UE_4_24_OR_LATER
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Android/armeabi-arm64/liblua.a"));
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Android/armeabi-v7a/liblua.a"));
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Android/x86/liblua.a"));
#else
            PublicLibraryPaths.Add(Path.Combine(externalLib, "Android/armeabi-arm64"));
            PublicLibraryPaths.Add(Path.Combine(externalLib, "Android/armeabi-v7a"));
            PublicLibraryPaths.Add(Path.Combine(externalLib, "Android/x86"));
            PublicAdditionalLibraries.Add("lua");
#endif
        }
        else if (Target.Platform == UnrealTargetPlatform.Win32 )
        {
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Win32/lua.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Win64/lua.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Mac/liblua.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(Path.Combine(externalLib, "Linux/liblua.a"));
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

#if UE_4_21_OR_LATER
        PublicDefinitions.Add("ENABLE_PROFILER");
#else
        Definitions.Add("ENABLE_PROFILER");
#endif


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
        bLegacyPublicIncludePaths = false;
    }
}
