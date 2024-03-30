// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MDVProject2/UI/Widgets/MainMenu.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMenuHUD();
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> MenuWidget;
	
	UPROPERTY()
	UMainMenu* MainMenu;

	UPROPERTY()
	TSubclassOf<UUserWidget> SettingsWidget;
	
	UPROPERTY()
	UMainMenu* Settings;
};
