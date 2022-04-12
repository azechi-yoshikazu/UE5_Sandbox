// Copyright Epic Games, Inc. All Rights Reserved.

#include "SMyToolBox.h"

// Engine
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "MyToolBox"

SMyToolBox::SMyToolBox()
{

}

SMyToolBox::~SMyToolBox()
{

}

void SMyToolBox::Construct(const FArguments& InArgs)
{
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

#undef LOCTEXT_NAMESPACE