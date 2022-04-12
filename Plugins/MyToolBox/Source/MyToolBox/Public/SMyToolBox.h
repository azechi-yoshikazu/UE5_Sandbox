// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FTabManager;
class SDockTab;


class SMyToolBox : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMyToolBox) 
        : _Text(FText())
        {}
        SLATE_ARGUMENT(TSharedPtr<FTabManager>, TabManager)
        SLATE_ATTRIBUTE(FText, Text)
    SLATE_END_ARGS()

    SMyToolBox();
    virtual ~SMyToolBox();

    void Construct(const FArguments& InArgs);

public:
    static TSharedRef<SDockTab> Spawn(const FSpawnTabArgs& InArgs);

private:
    TSharedPtr<FTabManager> TabManager;
};
