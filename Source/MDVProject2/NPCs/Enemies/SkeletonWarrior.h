// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "SkeletonWarrior.generated.h"

UCLASS()
class MDVPROJECT2_API ASkeletonWarrior : public AEnemy {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkeletonWarrior();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TriggerDeathNiagaraEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FEnemySettings* Settings;
};
