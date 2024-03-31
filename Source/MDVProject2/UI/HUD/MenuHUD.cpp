// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"

#include "MDVProject2/UI/Widgets/SettingsWindow.h"

AMenuHUD::AMenuHUD() {
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/CodeBlueprints/UI/WB_MainMenu.WB_MainMenu_C'"));
	if (MenuWidgetClassFinder.Class) {
		MenuWidget = MenuWidgetClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SettingsWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/CodeBlueprints/UI/WP_SettingsWindow.WP_SettingsWindow_C'"));
	if (SettingsWidgetClassFinder.Class) {
		SettingsWidget = SettingsWidgetClassFinder.Class;
	}

}

void AMenuHUD::BeginPlay() {
	Super::BeginPlay();
	
	if (MenuWidget) {
		MainMenu = CreateWidget<UMainMenu>(GetWorld(), MenuWidget);
		if (MainMenu) {
			MainMenu->AddToViewport();
		}
	}
}

void AMenuHUD::DisplaySettingsWidow() {
	if (SettingsWidget) {
		Settings = CreateWidget<USettingsWindow>(GetWorld(), SettingsWidget);
		if (Settings) {
			Settings->AddToViewport();
			MainMenu->RemoveFromParent();
		}
	}
}

