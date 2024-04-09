// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MDVProject2/UI/Widgets/MainMenu.h"
#include "MDVProject2/UI/Widgets/SettingsWindow.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AMenuHUD : public AHUD {
	GENERATED_BODY()

public:
	AMenuHUD();
	
	virtual void BeginPlay() override;

	void DisplaySettingsWidow();

	void DisplayMenuWidow();
	
	void LoadNewGame();
	
	void SaveKeyBindConfiguration(const TArray<UObject*> KeyBindConfiguration);

	UPROPERTY()
	UDataTable* KeyBindsDataTable;
	
private:
	UPROPERTY()
	TSubclassOf<UUserWidget> MenuWidget;
	
	UPROPERTY(EditAnywhere, Category="Widget")
	UMainMenu* MainMenu;

	UPROPERTY()
	TSubclassOf<UUserWidget> SettingsWidget;
	
	UPROPERTY(EditAnywhere, Category="Widget")
	USettingsWindow* Settings;

	UFUNCTION(BlueprintCallable, Category = Game)
	void LevelLoadCallback();
};
