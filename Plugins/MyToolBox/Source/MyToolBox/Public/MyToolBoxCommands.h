// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MyToolBoxStyle.h"

class FMyToolBoxCommands : public TCommands<FMyToolBoxCommands>
{
public:

	FMyToolBoxCommands()
		: TCommands<FMyToolBoxCommands>(TEXT("MyToolBox"), NSLOCTEXT("Contexts", "MyToolBox", "MyToolBox Plugin"), NAME_None, FMyToolBoxStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
