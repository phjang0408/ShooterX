// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterX : ModuleRules
{
	public ShooterX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				// Initial Dependendcies.
				"Core", "CoreUObject", "Engine", "InputCore", 
				
				// Enhanced Input 추가
				"EnhancedInput",

				// JSON 모듈 추가
				"Json", "JsonUtilities",
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { "ShooterX" });
	}
}
