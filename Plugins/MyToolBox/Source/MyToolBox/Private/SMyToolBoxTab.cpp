// Copyright Epic Games, Inc. All Rights Reserved.

#include "SMyToolBoxTab.h"

// Engine
#include "Engine/World.h"
#include "Widgets/SCompoundWidget.h"

#define LOCTEXT_NAMESPACE "MyToolBox"

namespace MyToolBox
{
    namespace DebuggerTab
    {
        class SDebuggerWidget : public SCompoundWidget
        {
        public:
            SLATE_BEGIN_ARGS(SDebuggerWidget) {}
            SLATE_END_ARGS()

            SDebuggerWidget() : SCompoundWidget() {}
            virtual ~SDebuggerWidget() {}
        public:
            void Construct(const FArguments& InArgs)
            {
                TArray<IConsoleCommandExecutor*> CommandExecutors = IModularFeatures::Get().GetModularFeatureImplementations<IConsoleCommandExecutor>(IConsoleCommandExecutor::ModularFeatureName());

                CommandExecutor = CommandExecutors.Num() > 0 ? CommandExecutors[0] : nullptr;

                ChildSlot
                    [
                        SNew(SButton)
                        .Text(LOCTEXT("MyToolBox.Debug.ShowFPS", "Toggle FPS"))
                        .OnClicked_Raw<SDebuggerWidget, TCHAR*>(this, &SDebuggerWidget::ExecuteCommand, TEXT("stat fps"))
                    ];
            }

        protected:
            FReply ExecuteCommand(TCHAR* Command)
            {
                if (CommandExecutor != nullptr)
                {
                    if (CommandExecutor->Exec(Command))
                    {
                        return FReply::Handled();
                    }
                }

                return FReply::Unhandled();
            }

        protected:
            IConsoleCommandExecutor* CommandExecutor = nullptr;
        };

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
                            SNew(SDebuggerWidget)
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