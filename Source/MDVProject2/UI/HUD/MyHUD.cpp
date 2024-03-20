// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

void AMyHUD::BeginPlay() {
	Super::BeginPlay();

	CombatHUD = CreateWidget<UCombatHUD>(GetWorld(), UCombatHUD::StaticClass());
	
	if (CombatHUD) {
		//CombatHUD->AddToViewport();
	}
}
