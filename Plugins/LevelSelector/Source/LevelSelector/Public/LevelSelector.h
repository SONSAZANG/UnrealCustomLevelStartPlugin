// Copyright (c) 2025 SONSAZANG. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FLevelSelectorModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	TSharedRef<SWidget> GenerateDropdownMenu();
	FString SelectedMapName;
	void OnLevelSelected(FString LevelName);
	void OnPlayClicked();
private:

	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;

};
