// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPShooter : ModuleRules
{
	public TPShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TPShooter",
			"TPShooter/Variant_Platforming",
			"TPShooter/Variant_Platforming/Animation",
			"TPShooter/Variant_Combat",
			"TPShooter/Variant_Combat/AI",
			"TPShooter/Variant_Combat/Animation",
			"TPShooter/Variant_Combat/Gameplay",
			"TPShooter/Variant_Combat/Interfaces",
			"TPShooter/Variant_Combat/UI",
			"TPShooter/Variant_SideScrolling",
			"TPShooter/Variant_SideScrolling/AI",
			"TPShooter/Variant_SideScrolling/Gameplay",
			"TPShooter/Variant_SideScrolling/Interfaces",
			"TPShooter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
