// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Kismet/KismetSystemLibrary.h"
#include "MDVProject2/UI/HUD/MenuHUD.h"

void UMainMenu::NativeOnInitialized() {
	Super::NativeOnInitialized();
	MenuHUD = Cast<AMenuHUD>(GetOwningPlayer()->GetHUD());
}

void UMainMenu::NewGamePressed() const {
	UE_LOG(LogTemp, Warning, TEXT("NewGamePressed"))
	MenuHUD->LoadNewGame();
}

void UMainMenu::LoadGamePressed() const {
	UE_LOG(LogTemp, Warning, TEXT("LoadGamePressed"))
}

void UMainMenu::SettingsPressed() const {
	MenuHUD->DisplaySettingsWidow();
}

void UMainMenu::ExitPressed() const {
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit,false);
}
