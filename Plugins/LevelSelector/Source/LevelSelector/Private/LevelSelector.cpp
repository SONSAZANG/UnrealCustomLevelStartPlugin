#include "LevelSelector.h"
#include "LevelSelectorStyle.h"
#include "LevelSelectorCommands.h"
#include "Misc/MessageDialog.h"
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
		FToolMenuEntry Entry = FToolMenuEntry::InitComboButton(
			"LevelSelectorDropdown",
			FUIAction(),
			FOnGetContent::CreateRaw(this, &FLevelSelectorModule::GenerateDropdownMenu),
			LOCTEXT("LevelSelectorDropdown_Label", "Level Selector"),
			LOCTEXT("LevelSelectorDropdown_Tooltip", "Select a level to open"),
			FSlateIcon(FLevelSelectorStyle::GetStyleSetName(), "LevelSelector.Icon")
		);
		Section.AddEntry(Entry);
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

	/*MenuBuilder.AddMenuEntry(
		LOCTEXT("Level1", "Open Level 1"),
		LOCTEXT("Level1_Tooltip", "Opens Level 1"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FLevelSelectorModule::OnOpenLevel1))
	);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("Level2", "Open Level 2"),
		LOCTEXT("Level2_Tooltip", "Opens Level 2"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FLevelSelectorModule::OnOpenLevel2))
	);*/

	return MenuBuilder.MakeWidget();
}

void FLevelSelectorModule::OnLevelSelected(FString LevelName)
{
	SelectedMapName = LevelName;
	UE_LOG(LogTemp, Log, TEXT("Selected Level: %s"), *LevelName);
}

void FLevelSelectorModule::OnOpenLevel1()
{
	UE_LOG(LogTemp, Log, TEXT("Level 1 선택됨"));
}

void FLevelSelectorModule::OnOpenLevel2()
{
	UE_LOG(LogTemp, Log, TEXT("Level 2 선택됨"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLevelSelectorModule, LevelSelector)