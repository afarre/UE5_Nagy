// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"


AMyAIController::AMyAIController() {
	BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/AI/SkeletonWarrior/BT_SkeletonWarrior.BT_SkeletonWarrior'"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	//TODO: Create and add senses to the AI Controller
	/*
	UAISenseConfig AISenseConfig;
	AISenseConfig.
	AIPerceptionComponent->ConfigureSense(AISenseConfig);
	*/
	
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPercerption"));
}

void AMyAIController::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	
}

void AMyAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	BlackboardComponent->SetValueAsVector(FName("Position"), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
}
