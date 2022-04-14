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

                static const FMargin CommandButtonPadding = FMargin(10.0f, 5.0f);

                auto HorizontalBox =
                    SNew(SHorizontalBox);

                HorizontalBox->AddSlot()
                    .AutoWidth()
                    .VAlign(VAlign_Top)
                    .Padding(CommandButtonPadding)
                    [
                        SNew(SButton)
                        .Text(LOCTEXT("Debugger.ShowFPS.Text", "Show FPS"))
                        .ToolTipText(LOCTEXT("Debugger.ShowFPS.ToolTip", "Toggle FPS for debug. ( It's same to execute command as \"stat fps\". )"))
                        .OnClicked_Raw<SDebuggerWidget, TCHAR*>(this, &SDebuggerWidget::ExecuteCommand, TEXT("stat fps"))
                    ];
                
                HorizontalBox->AddSlot()
                    .AutoWidth()
                    .VAlign(VAlign_Top)
                    .Padding(CommandButtonPadding)
                    [
                        SNew(SButton)
                        .Text(LOCTEXT("Debugger.ShowStat.Text", "Show Stat"))
                        .ToolTipText(LOCTEXT("Debugger.ShowStat.ToolTip", "Toggle stat for debug. ( It's same to execute command as \"stat unit\". )"))
                        .OnClicked_Raw<SDebuggerWidget, TCHAR*>(this, &SDebuggerWidget::ExecuteCommand, TEXT("stat unit"))
                    ];

                ChildSlot
                    [
                        HorizontalBox
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
                        .Label(LOCTEXT("Debugger.Tab.Title", "Debugger"))
                        [
                            SNew(SDebuggerWidget)
                        ];
                })
            )
            .SetDisplayName(LOCTEXT("Debugger.Tab.DisplayName", "Debugger"))
            .SetTooltipText(LOCTEXT("Debugger.Tab.Tooltip", "Open tab for debug."));
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
                        .Label(LOCTEXT("Utility.Tab.Title", "Utility"))
                        [
                            SNew(SBox)
                            .VAlign(VAlign_Center)
                            .HAlign(HAlign_Center)
                            [
                                SNew(STextBlock)
                                .Text(LOCTEXT("Utility.Tab.Content", "This is Utility"))
                            ]
                        ];
                }
                    )
                )
                .SetDisplayName(LOCTEXT("Utility.Tab.DisplayName", "Utility"))
                .SetTooltipText(LOCTEXT("Utility.Tab.Tooltip", "Open tab for utility."));
        }

    };// namespace UtilityTab

};// namespace MyToolBox

#undef LOCTEXT_NAMESPACE