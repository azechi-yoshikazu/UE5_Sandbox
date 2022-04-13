// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FTabManager;

namespace MyToolBox
{
    namespace DebuggerTab
    {
        const FName TabName = "MyToolBox.DebuggerTab";

        void RegisterTabSpawner(const TSharedPtr<FTabManager>& TabManager);

    };// namespace DebuggerTab

    namespace UtilityTab
    {
        const FName TabName = "MyToolBox.UtilityTab";

        void RegisterTabSpawner(const TSharedPtr<FTabManager>& TabManager);

    };// namespace UtilityTab
};// namespace MyToolBox
