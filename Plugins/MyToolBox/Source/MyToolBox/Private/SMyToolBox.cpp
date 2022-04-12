// Copyright Epic Games, Inc. All Rights Reserved.

#include "SMyToolBox.h"

// Engine
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "MyToolBox"

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

    ChildSlot
    [
        SNew(SBox)
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        [
            SNew(STextBlock)
            .Text(InArgs._Text)
        ]
    ];
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
        .Text(LOCTEXT("MyToolBox.Title", "My Tool Box"));

    NomadTab->SetContent(MainWidget);

    return NomadTab;
}

#undef LOCTEXT_NAMESPACE