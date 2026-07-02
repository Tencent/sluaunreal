// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class democppEditorTarget : TargetRules
{
	public democppEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
#if UE_5_4_OR_LATER
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		WindowsPlatform.bStrictConformanceMode = true;
#endif
#if UE_5_5_OR_LATER
		DefaultBuildSettings = BuildSettingsVersion.Latest;
#endif

		ExtraModuleNames.AddRange( new string[] { "democpp" } );
	}
}
