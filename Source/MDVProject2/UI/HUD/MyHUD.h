// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MDVProject2/UI/Widgets/MainMenu.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AMyHUD : public AHUD {
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	UDataAsset* WidgetDataAsset;

	

};
