// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class R200_Hand_Tracking : ModuleRules
{
	public R200_Hand_Tracking(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicAdditionalLibraries.Add("C:/Users/Granger/Documents/Unreal Projects/R200_Hand_Tracking/ThirdParty/librealsense/Libraries/realsense.lib");
        PublicIncludePaths.Add("C:/Users/Granger/Documents/Unreal Projects/R200_Hand_Tracking/ThirdParty/librealsense/Includes");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
