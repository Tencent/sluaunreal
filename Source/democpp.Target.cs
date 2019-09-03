// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class democppTarget : TargetRules
{
	public democppTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		bUsePCHFiles = false;
		ExtraModuleNames.AddRange( new string[] { "democpp" } );
    }
}
