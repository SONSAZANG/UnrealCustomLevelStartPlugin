// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestBPPluginBPLibrary.h"
#include "TestBPPlugin.h"

FString UTestBPPluginBPLibrary::UserName = TEXT("Unknown");

UTestBPPluginBPLibrary::UTestBPPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UTestBPPluginBPLibrary::SetUserName(const FString& NewName)
{
	UserName = NewName;
	UE_LOG(LogTemp, Log, TEXT("UserName set to : %s"), *UserName);
}

FString UTestBPPluginBPLibrary::GetUserName()
{
	return UserName;
}
