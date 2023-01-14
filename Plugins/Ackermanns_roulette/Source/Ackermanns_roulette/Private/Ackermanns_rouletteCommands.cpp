// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ackermanns_rouletteCommands.h"

#define LOCTEXT_NAMESPACE "FAckermanns_rouletteModule"

void FAckermanns_rouletteCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Ackermanns_roulette", "Bring up Ackermanns_roulette window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
