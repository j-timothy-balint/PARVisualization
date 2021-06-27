// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class Visualizer : ModuleRules
{
    private string PARPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(
                ModuleDirectory,
                "../../../../../GitHub/PAR/"
            ));
        }
    }

    public Visualizer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        LoadPAR(Target);
        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }

    public bool LoadPAR(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) ||
            (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "" : "d";
            string PythonString = (Target.Platform == UnrealTargetPlatform.Win64) ? "" : "_d";
            string LibrariesPath = Path.Combine(PARPath, "libs");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "lwnet" + PlatformString + ".lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "database" + PlatformString + ".lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "agentProc" + PlatformString + ".lib"));

            //Add in the other two libraries required
            string python_path = Environment.GetEnvironmentVariable("PYTHON_ROOT");
            PublicAdditionalLibraries.Add(Path.Combine(python_path,"libs" ,"Python39" + PythonString + ".lib"));
            //If, for some reason, it fails to find the ENV variable, you can hardcode it in
            string connector_path = "E:\\External Libraries\\sqlite\\libs\\Release";// Environment.GetEnvironmentVariable("SQLITE_ROOT");
            PublicAdditionalLibraries.Add(Path.Combine(connector_path, "sqlite3.lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(PARPath, "agentProc"));
            PublicIncludePaths.Add(Path.Combine(PARPath, "database"));
            PublicIncludePaths.Add(Path.Combine(PARPath, "lwnets"));

        }

        Definitions.Add(string.Format("WITH_PAR_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}
