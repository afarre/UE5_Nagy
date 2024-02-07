// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

void UMainMenu::NewGamePressed() const {
	UE_LOG(LogTemp, Warning, TEXT("NewGamePressed"))
}

void UMainMenu::LoadGamePressed() const {
	UE_LOG(LogTemp, Warning, TEXT("LoadGamePressed"))
}

void UMainMenu::SettingsPressed() const {
	UE_LOG(LogTemp, Warning, TEXT("SettingsPressed"))
}

void UMainMenu::ExitPressed() const {
	UE_LOG(LogTemp, Warning, TEXT("ExitPressed"))
}
