// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyToolBox.h"
#include "MyToolBoxStyle.h"
#include "MyToolBoxCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName MyToolBoxTabName("MyToolBox");

#define LOCTEXT_NAMESPACE "FMyToolBoxModule"

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
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FMyToolBoxModule::PluginButtonClicked()")),
							FText::FromString(TEXT("MyToolBox.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
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