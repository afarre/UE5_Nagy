// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MDVProject2/UI/Widgets/CppOnlyWidget.h"
#include "GameHUD.generated.h"

class UHealthComponent;
class ANagy;
class UNagyUI;
/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AGameHUD : public AHUD {
	GENERATED_BODY()

public:
	AGameHUD();
	
	virtual void BeginPlay() override;
	
	UFUNCTION() // necessary
	void HealthChanged(const float& CurrentHealth);

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	UCppOnlyWidget* CppOnlyCrosshair;

	UPROPERTY()
	TSubclassOf<UUserWidget> NagyUIWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	UNagyUI* NagyUI;

};
