// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuCameraPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMenuCameraPawn::AMenuCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMenuCameraPawn::BeginPlay() {
	Super::BeginPlay();

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	// Enable cursor
	MyController->bShowMouseCursor = true; 
	MyController->bEnableClickEvents = true; 
	MyController->bEnableMouseOverEvents = true;

	// Get the "Enhanced Input Local Player Subsystem" blueprint
    
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyController->GetLocalPlayer())) {
		// Assign our mapping context to the aforementioned Subsystem
		Subsystem->AddMappingContext(PawnMappingContext, 0);
	}
}

// Called every frame
void AMenuCameraPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMenuCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
