// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonWarrior.h"

#include "MDVProject2/Utils/DataStructures.h"

// Sets default values
ASkeletonWarrior::ASkeletonWarrior() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyNamesArray = EnemyStatisticsDataTable->GetRowNames();
	Settings = EnemyStatisticsDataTable->FindRow<FEnemySettings>(EnemyNamesArray[SkeletonWarrior], "SkeletonWarrior");
	
	HealthComponent->MaxHealth = HealthComponent->CurrentHealth = Settings->MaxHealth;
	DeathNiagaraEffect = Settings->DeathNiagaraEffect;
}

// Called when the game starts or when spawned
void ASkeletonWarrior::BeginPlay() {
	Super::BeginPlay();
	
}

void ASkeletonWarrior::TriggerDeathNiagaraEffect() {
	
}

// Called every frame
void ASkeletonWarrior::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

