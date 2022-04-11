// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyToolBoxCommands.h"

#define LOCTEXT_NAMESPACE "FMyToolBoxModule"

void FMyToolBoxCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MyToolBox", "Execute MyToolBox action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
