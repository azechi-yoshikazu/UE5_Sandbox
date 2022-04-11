// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyToolBoxCommands.h"

#define LOCTEXT_NAMESPACE "FMyToolBoxModule"

void FMyToolBoxCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MyToolBox", "Bring up MyToolBox window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
