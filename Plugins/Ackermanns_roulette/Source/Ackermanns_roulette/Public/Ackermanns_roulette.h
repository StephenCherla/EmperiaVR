// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAckermanns_rouletteModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	FReply HandleGenerateButtonClicked();

	class AAckermanns_Roulette_Manager* FindManagerActor();
	AAckermanns_Roulette_Manager* SpawnManagerActor();

	AAckermanns_Roulette_Manager* aackermannsRouletteManager;

private:

	void RegisterMenus();
	bool IsModuleInitialized = false;
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
