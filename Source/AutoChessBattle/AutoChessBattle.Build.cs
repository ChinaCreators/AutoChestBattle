// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class AutoChessBattle : ModuleRules
{
	public AutoChessBattle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		// Add this section to include your DLL
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Path is relative to this .Build.cs file
			string DllPath = Path.Combine(ModuleDirectory, "../../ThirdParty/AutoChessBattleCore");

			// This ensures the DLL gets copied to the output directory
			RuntimeDependencies.Add("$(TargetOutputDir)/AutoChessBattleCore.dll",
				Path.Combine(DllPath, "AutoChessBattleCore.dll"));
		}
	}
}