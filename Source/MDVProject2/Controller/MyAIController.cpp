// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

void AMyAIController::BeginPlay() {
	Super::BeginPlay();
	FAIMoveRequest AIMoveRequest;
	FVector CurrentLocation = GetPawn()->GetActorLocation();
	AIMoveRequest.SetGoalLocation(CurrentLocation + FVector(200));
	MoveTo(AIMoveRequest);
	UE_LOG(LogTemp, Warning, TEXT("Executed AI controller beginplay"))
}
