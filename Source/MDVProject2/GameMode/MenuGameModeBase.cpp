// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameModeBase.h"

#include "MDVProject2/UI/HUD/MenuHUD.h"

AMenuGameModeBase::AMenuGameModeBase() {
	
	HUDClass = AMenuHUD::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/CodeBlueprints/Characters/BP_MenuCameraPawn.BP_MenuCameraPawn_C'"));
	
	if (PlayerPawnBPClass.Class) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
