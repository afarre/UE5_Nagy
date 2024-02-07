// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MDVProject2/Player/Nagy.h"
#include "MDVProject2/UI/HUD/MyHUD.h"

void AMyGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

AMyGameModeBase::AMyGameModeBase() {
	HUDClass = AMyHUD::StaticClass();
	DefaultPawnClass = ANagy::StaticClass();
}
