// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MDVPROJECT2_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void UpdateHP(float CurrentHealth);

	void PlayHealthBarAnimation();

private:
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;
	
	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* HealthFadeAnimation;
};
