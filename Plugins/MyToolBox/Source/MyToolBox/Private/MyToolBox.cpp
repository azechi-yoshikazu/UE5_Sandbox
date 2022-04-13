// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyToolBox.h"
// Engine
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
// MyToolBox
#include "MyToolBoxStyle.h"
#include "MyToolBoxCommands.h"
#include "SMyToolBox.h"

#define LOCTEXT_NAMESPACE "MyToolBox"

void FMyToolBoxModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMyToolBoxStyle::Initialize();
	FMyToolBoxStyle::ReloadTextures();

	FMyToolBoxCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMyToolBoxCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMyToolBoxModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMyToolBoxModule::RegisterMenus));

	SMyToolBox::RegisterTabSpawner();
}

void FMyToolBoxModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMyToolBoxStyle::Shutdown();

	FMyToolBoxCommands::Unregister();
}

void FMyToolBoxModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(SMyToolBox::TabName);
}

void FMyToolBoxModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMyToolBoxCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMyToolBoxCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyToolBoxModule, MyToolBox)
