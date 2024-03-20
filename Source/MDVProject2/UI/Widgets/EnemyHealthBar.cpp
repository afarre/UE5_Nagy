// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"

void UEnemyHealthBar::NativeConstruct() {
	Super::NativeConstruct();
	HealthProgressBar->SetPercent(1);
}

void UEnemyHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UEnemyHealthBar::UpdateHP(float CurrentHealth) {
	if (HealthProgressBar) {
		UE_LOG(LogTemp, Warning, TEXT("HealthProgressBar currenthealth: %f"), CurrentHealth/100)
		HealthProgressBar->SetPercent(CurrentHealth/100);
	}
}

void UEnemyHealthBar::PlayHealthBarAnimation() {
	if (HealthFadeAnimation) {
		PlayAnimation(HealthFadeAnimation, 0 , 1, EUMGSequencePlayMode::Forward, 1);
	}
}

