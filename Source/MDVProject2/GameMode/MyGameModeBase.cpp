// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MDVProject2/Player/Nagy.h"
#include "MDVProject2/UI/HUD/GameHUD.h"
#include "MDVProject2/UI/HUD/MenuHUD.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase() {
	HUDClass = AGameHUD::StaticClass();
	
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("/Game/Blueprints/CodeBlueprints/Characters/BP_TestCharacter.BP_TestCharacter_C"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_TestCharacter.BP_TestCharacter_C'"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_TestCharacter.BP_TestCharacter_C'"));

	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_Nagy.BP_Nagy_C'"));
	
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
