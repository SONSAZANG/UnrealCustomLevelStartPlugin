#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestBPPluginBPLibrary.generated.h"

UCLASS()
class UTestBPPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	static FString UserName;

	UFUNCTION(BlueprintCallable, Category = "BP_Test")
	static void SetUserName(const FString& NewName);
	UFUNCTION(BlueprintCallable, Category = "BP_Test")
	static FString GetUserName();
};
