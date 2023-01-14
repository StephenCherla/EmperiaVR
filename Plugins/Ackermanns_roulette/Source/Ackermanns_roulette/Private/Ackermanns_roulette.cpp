// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ackermanns_roulette.h"
#include "Ackermanns_rouletteStyle.h"
#include "Ackermanns_rouletteCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName Ackermanns_rouletteTabName("Ackermanns_roulette");

#define LOCTEXT_NAMESPACE "FAckermanns_rouletteModule"

void FAckermanns_rouletteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAckermanns_rouletteStyle::Initialize();
	FAckermanns_rouletteStyle::ReloadTextures();

	FAckermanns_rouletteCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAckermanns_rouletteCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAckermanns_rouletteModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAckermanns_rouletteModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(Ackermanns_rouletteTabName, FOnSpawnTab::CreateRaw(this, &FAckermanns_rouletteModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAckermanns_rouletteTabTitle", "Ackermanns_roulette"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAckermanns_rouletteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAckermanns_rouletteStyle::Shutdown();

	FAckermanns_rouletteCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(Ackermanns_rouletteTabName);
}

TSharedRef<SDockTab> FAckermanns_rouletteModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//Define the slate design here (A Window with a button)
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().VAlign(VAlign_Top).AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.MaxWidth(90.0F)
		.Padding(0, 60, 40, 10)[
			SNew(SButton)
				.OnClicked_Raw(this, &FAckermanns_rouletteModule::HandleGenerateButtonClicked)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)[
					SNew(STextBlock)
						.Text(LOCTEXT("GenerateButton", "Generate"))
					]
				]
			]
		];
}

void FAckermanns_rouletteModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(Ackermanns_rouletteTabName);
}
FReply FAckermanns_rouletteModule::HandleGenerateButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("[FAckermanns_rouletteModule::HandleGenerateButtonClicked]Generate Buttton Clicked"));
	return FReply::Handled();
}
void FAckermanns_rouletteModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAckermanns_rouletteCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAckermanns_rouletteCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAckermanns_rouletteModule, Ackermanns_roulette)