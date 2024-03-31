// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MDVProject2/UI/HUD/MenuHUD.h"

void UMainMenu::NativeOnInitialized() {
	Super::NativeOnInitialized();
	MenuHUD = Cast<AMenuHUD>(GetOwningPlayer()->GetHUD());
}

void UMainMenu::NewGamePressed() const {
	//TODO: Remove level name hardcode
	UGameplayStatics::OpenLevel(UGameplayStatics::GetGameInstance(this), FName(TEXT("Project2_Playable")));
}

void UMainMenu::LoadGamePressed() const {
	UE_LOG(LogTemp, Warning, TEXT("LoadGamePressed"))
}

void UMainMenu::SettingsPressed() const {
	MenuHUD->DisplaySettingsWidow();
	UE_LOG(LogTemp, Warning, TEXT("SettingsPressed"))
}

void UMainMenu::ExitPressed() const {
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit,false);
}
