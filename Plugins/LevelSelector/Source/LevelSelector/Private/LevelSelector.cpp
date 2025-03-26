#include "LevelSelector.h"
#include "LevelSelectorStyle.h"
#include "LevelSelectorCommands.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"
#include "FileHelpers.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "ToolMenus.h"

static const FName LevelSelectorTabName("LevelSelector");

#define LOCTEXT_NAMESPACE "FLevelSelectorModule"

void FLevelSelectorModule::StartupModule()
{
	FLevelSelectorStyle::Initialize();
	FLevelSelectorStyle::ReloadTextures();

	FLevelSelectorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLevelSelectorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FLevelSelectorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLevelSelectorModule::RegisterMenus));
}

void FLevelSelectorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FLevelSelectorStyle::Shutdown();

	FLevelSelectorCommands::Unregister();
}

void FLevelSelectorModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FLevelSelectorModule::PluginButtonClicked()")),
							FText::FromString(TEXT("LevelSelector.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FLevelSelectorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	{
		FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
		Section.AddMenuEntryWithCommandList(FLevelSelectorCommands::Get().PluginAction, PluginCommands);
	}

	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar"); 
	{
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
		FToolMenuEntry DropdownEntry = FToolMenuEntry::InitComboButton(
			"LevelSelectorDropdown",
			FUIAction(),
			FOnGetContent::CreateRaw(this, &FLevelSelectorModule::GenerateDropdownMenu),
			LOCTEXT("LevelSelectorDropdown_Label", "Level Selector"),
			LOCTEXT("LevelSelectorDropdown_Tooltip", "Select a level to open"),
			FSlateIcon(FLevelSelectorStyle::GetStyleSetName(), "LevelSelector.Icon")
		);
		Section.AddEntry(DropdownEntry);

		FToolMenuEntry PlayButtonEntry = FToolMenuEntry::InitToolBarButton(
			"PlaySelectedLevel",
			FUIAction(FExecuteAction::CreateRaw(this, &FLevelSelectorModule::OnPlayClicked)),
			LOCTEXT("PlayLevel_Label", "Play Level"),
			LOCTEXT("PlayLevel_Tooltip", "Play selected level"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Play")
		);
		Section.AddEntry(PlayButtonEntry);
	}
}

TSharedRef<SWidget> FLevelSelectorModule::GenerateDropdownMenu()
{
	TArray<FString> MapNames;
	const FString MapsDir = FPaths::ProjectContentDir() + TEXT("Maps/");
	IFileManager::Get().FindFilesRecursive(MapNames, *MapsDir, TEXT("*.umap"), true, false);

	FMenuBuilder MenuBuilder(true, PluginCommands);

	for (const FString& MapPath : MapNames)
	{
		FString NameOnly = FPaths::GetBaseFilename(MapPath);
		MenuBuilder.AddMenuEntry(
			FText::FromString(*NameOnly),
			FText::FromString(*NameOnly),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FLevelSelectorModule::OnLevelSelected, NameOnly))
		);
	}
	return MenuBuilder.MakeWidget();
}

void FLevelSelectorModule::OnLevelSelected(FString LevelName)
{
	SelectedMapName = LevelName;
	UE_LOG(LogTemp, Log, TEXT("Selected Level: %s"), *LevelName);
}

void FLevelSelectorModule::OnPlayClicked()
{
	if (SelectedMapName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Level Selected!"));
	}

	const FString MapPath = FString::Printf(TEXT("/Game/Maps/%s"), *SelectedMapName);
	if (!FPackageName::DoesPackageExist(MapPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Map does not exist : %s"), *SelectedMapName);
	}

	UEditorLoadingAndSavingUtils::LoadMap(MapPath);
	
	FLevelEditorModule &LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TSharedPtr<IAssetViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveViewport();

	if (GUnrealEd)
	{
		FRequestPlaySessionParams Params;
		Params.WorldType = EPlaySessionWorldType::PlayInEditor;
		Params.SessionDestination = EPlaySessionDestinationType::InProcess;
		Params.DestinationSlateViewport = ActiveLevelViewport;
		GUnrealEd->RequestPlaySession(Params);
	}
	UE_LOG(LogTemp, Log, TEXT("OnPlayClicked: %s"), *SelectedMapName);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLevelSelectorModule, LevelSelector)