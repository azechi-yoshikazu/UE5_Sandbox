// Copyright Epic Games, Inc. All Rights Reserved.

#include "SMyToolBox.h"

// Engine
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

// MyToolBox
#include "SMyToolBoxTab.h"

#define LOCTEXT_NAMESPACE "MyToolBox"

const FName SMyToolBox::TabName = "MyToolBoxTab";

SMyToolBox::SMyToolBox()
    : TabManager(nullptr)
{

}

SMyToolBox::~SMyToolBox()
{

}

void SMyToolBox::Construct(const FArguments& InArgs)
{
    TabManager = InArgs._TabManager;

    // Register our tab to manager
    MyToolBox::DebuggerTab::RegisterTabSpawner(TabManager);
    MyToolBox::UtilityTab::RegisterTabSpawner(TabManager);

    TSharedPtr<FTabManager::FLayout> ToolBoxLayout = FTabManager::NewLayout("MyToolBoxLayout");
    ToolBoxLayout->AddArea(
        FTabManager::NewPrimaryArea()
        ->SetOrientation(Orient_Horizontal)
        ->Split
        (
            FTabManager::NewSplitter()
            ->SetOrientation(Orient_Vertical)
            ->SetSizeCoefficient(0.3f)
            ->Split
            (
                FTabManager::NewStack()
                ->SetSizeCoefficient(0.8f)
                ->AddTab(MyToolBox::UtilityTab::TabName, ETabState::OpenedTab)
                ->AddTab(MyToolBox::DebuggerTab::TabName, ETabState::OpenedTab)
                ->SetForegroundTab(MyToolBox::UtilityTab::TabName)
            )
        )
    );

    TSharedRef<SWidget> TabContents = TabManager->RestoreFrom(ToolBoxLayout.ToSharedRef(), TSharedPtr<SWindow>()).ToSharedRef();

    ChildSlot
    [
        SNew(SBox)
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        [
            TabContents
        ]
    ];
}

void SMyToolBox::RegisterTabSpawner()
{
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateStatic(&SMyToolBox::Spawn))
        .SetDisplayName(LOCTEXT("MyToolBox.Title", "MyToolBox"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

TSharedRef<SDockTab> SMyToolBox::Spawn(const FSpawnTabArgs& InArgs)
{
    auto NomadTab = 
        SNew(SDockTab)
        .TabRole(ETabRole::NomadTab);    

    auto TabManager = FGlobalTabmanager::Get()->NewTabManager(NomadTab);

    auto MainWidget = 
        SNew(SMyToolBox)
        .TabManager(TabManager)
        .Text(LOCTEXT("MyToolBox.Title", "MyToolBox"));

    NomadTab->SetContent(MainWidget);

    return NomadTab;
}

#undef LOCTEXT_NAMESPACE
