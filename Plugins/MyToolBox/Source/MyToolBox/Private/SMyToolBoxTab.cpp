// Copyright Epic Games, Inc. All Rights Reserved.

#include "SMyToolBoxTab.h"

#define LOCTEXT_NAMESPACE "MyToolBox"

namespace MyToolBox
{
    namespace DebuggerTab
    {
        void RegisterTabSpawner(const TSharedPtr<FTabManager>& TabManager)
        {
            TabManager->RegisterTabSpawner(
                TabName,
                FOnSpawnTab::CreateLambda(
                [=](const FSpawnTabArgs&)
                {
                    return SNew(SDockTab)
                        .TabRole(ETabRole::PanelTab)
                        .Label(LOCTEXT("MyToolBox.DebuggerTab.Title", "Debugger"))
                        [
                            SNew(SBox)
                            .VAlign(VAlign_Center)
                            .HAlign(HAlign_Center)
                            [
                                SNew(STextBlock)
                                .Text(LOCTEXT("MyToolBox.DebuggerTab.Content", "This is Debugger"))
                            ]
                        ];
                })
            )
            .SetDisplayName(LOCTEXT("MyToolBox.DebuggerTab.DisplayName", "Debugger"))
            .SetTooltipText(LOCTEXT("MyToolBox.DebuggerTab.Tooltip", "Open tab for debug."));
        }

    };// namespace DebuggerTab

    namespace UtilityTab
    {
        void RegisterTabSpawner(const TSharedPtr<FTabManager>& TabManager)
        {
            TabManager->RegisterTabSpawner(
                TabName,
                FOnSpawnTab::CreateLambda(
                        [=](const FSpawnTabArgs&)
                {
                    return SNew(SDockTab)
                        .TabRole(ETabRole::PanelTab)
                        .Label(LOCTEXT("MyToolBox.UtilityTab.Title", "Utility"))
                        [
                            SNew(SBox)
                            .VAlign(VAlign_Center)
                            .HAlign(HAlign_Center)
                            [
                                SNew(STextBlock)
                                .Text(LOCTEXT("MyToolBox.UtilityTab.Content", "This is Utility"))
                            ]
                        ];
                }
                    )
                )
                .SetDisplayName(LOCTEXT("MyToolBox.UtilityTab.DisplayName", "Utility"))
                .SetTooltipText(LOCTEXT("MyToolBox.UtilityTab.Tooltip", "Open tab for utility."));
        }

    };// namespace UtilityTab

};// namespace MyToolBox

#undef LOCTEXT_NAMESPACE