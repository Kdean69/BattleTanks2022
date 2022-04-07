// Copyright � 2021 Kdean Games. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTanksTarget : TargetRules
{
	public BattleTanksTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BattleTanks" } );
	}
}
