// Fill out your copyright notice in the Description page of Project Settings.


#include "NagyUI.h"

#include "Components/ProgressBar.h"

void UNagyUI::SetPlayerHealth(float PlayerHealth) {
	UE_LOG(LogTemp, Warning, TEXT("PlayerHealth: %f"), PlayerHealth)
	HealthBar->SetPercent(PlayerHealth/100);
}
