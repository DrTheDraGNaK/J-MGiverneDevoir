// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPS_A2_CPP_API : ModuleRules
{
	public TPS_A2_CPP_API(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
