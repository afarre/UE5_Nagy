// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

class UMainMenu;

AGameHUD::AGameHUD() {

}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();
	CppOnlyWidget = CreateWidget<UCppOnlyWidget>(GetWorld(), UCppOnlyWidget::StaticClass());
	
	if (CppOnlyWidget) {
		CppOnlyWidget->AddToViewport();
	}
}
