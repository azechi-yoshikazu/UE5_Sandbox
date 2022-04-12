// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class SMyToolBox : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMyToolBox) 
        : _Text(FText())
        {}
        SLATE_ATTRIBUTE(FText, Text)
    SLATE_END_ARGS()

    SMyToolBox();
    virtual ~SMyToolBox();

    void Construct(const FArguments& InArgs);
};
