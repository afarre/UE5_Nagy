// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MDVProject2/UI/Widgets/CppOnlyWidget.h"
#include "MDVProject2/UI/Widgets/MainMenu.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AGameHUD : public AHUD {
	GENERATED_BODY()

public:
	AGameHUD();
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	UCppOnlyWidget* CppOnlyWidget;

};
