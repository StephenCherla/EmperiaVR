// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Ackermanns_rouletteStyle.h"

class FAckermanns_rouletteCommands : public TCommands<FAckermanns_rouletteCommands>
{
public:

	FAckermanns_rouletteCommands()
		: TCommands<FAckermanns_rouletteCommands>(TEXT("Ackermanns_roulette"), NSLOCTEXT("Contexts", "Ackermanns_roulette", "Ackermanns_roulette Plugin"), NAME_None, FAckermanns_rouletteStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};