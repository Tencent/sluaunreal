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

public class slua_profile : ModuleRules
{
    public slua_profile(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        // enable exception
        bEnableExceptions = true;
        bEnforceIWYU = false;
        bEnableUndefinedIdentifierWarnings = false;

        PrivateDependencyModuleNames.AddRange(new string[] { "slua_unreal" });
        PublicIncludePathModuleNames.AddRange(new string[] { "slua_unreal" });
#if UE_4_21_OR_LATER
        PublicDefinitions.Add("ENABLE_PROFILER");
#else
        Definitions.Add("ENABLE_PROFILER");
#endif


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
            PrivateDependencyModuleNames.Add("EditorStyle");
            PrivateDependencyModuleNames.Add("LevelEditor");
        }


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "EditorStyle",
                "InputCore",
                "Networking",
                "Sockets",
				// ... add private dependencies that you statically link with here ...	
			}
        );

        bLegacyPublicIncludePaths = false;
    }
}
