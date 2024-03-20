// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AMyAIController : public AAIController {
	GENERATED_BODY()

public:
	AMyAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=AI, meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;
	
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	
	UPROPERTY()
	UAIPerceptionComponent* AIPerceptionComponent;
};
