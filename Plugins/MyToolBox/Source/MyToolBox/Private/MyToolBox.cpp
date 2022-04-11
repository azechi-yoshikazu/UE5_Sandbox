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

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyToolBoxTabName, FOnSpawnTab::CreateRaw(this, &FMyToolBoxModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("MyToolBox.Title", "MyToolBox"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
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
	FGlobalTabmanager::Get()->TryInvokeTab(MyToolBoxTabName);
}

TSharedRef<SDockTab> FMyToolBoxModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	const FText OwnerWindowName = SpawnTabArgs.GetOwnerWindow().IsValid() ? SpawnTabArgs.GetOwnerWindow()->GetTitle() : LOCTEXT("MyToolBox.None", "None");
	const FText WidgetText = FText::Format(LOCTEXT("MyToolBox.MainWindow.Text", "MyToolBox in {0}"), OwnerWindowName);

    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            // Put your tab content here!
            SNew(SBox)
            .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            SNew(STextBlock)
            .Text(WidgetText)
        ]
        ];
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