// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MDVProject2/UI/HUD/GameHUD.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase() {
	HUDClass = AGameHUD::StaticClass();

	// All of the below methods work. If a Blueprint specified before the path is added, the _C is required, otherwise it's not.
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_Nagy.BP_Nagy_C'"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_Nagy.BP_Nagy_C'"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/CodeBlueprints/Characters/BP_Nagy"));

	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
