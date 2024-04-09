// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "NagyUI.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class MDVPROJECT2_API UNagyUI : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* Spell1Bar;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* Spell2Bar;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* DashBar;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* Spell1Icon;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* Spell2Icon;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* DashIcon;
	
	void SetPlayerHealth(float PlayerHealth);
};
