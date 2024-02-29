// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "NiagaraFunctionLibrary.h"
#include "MDVProject2/Controller/MyAIController.h"
#include "MDVProject2/Objects/VFX/Laser.h"

// Sets default values
AEnemy::AEnemy() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	EnemyStatisticsDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_EnemySettings.DT_EnemySettings'"));
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	AIControllerClass = AMyAIController::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//TODO: Improve the code. Embed death niagara effect in the enemy? Handle health removal & death from the HealthComponent?
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("Taking damage in enemy: %s"), *GetActorLabel())
	//HealthComponent->TakeDamage(DamageAmount);
	HealthComponent->CurrentHealth -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("HealthComponent->CurrentHealth: %f"), HealthComponent->CurrentHealth)

	/*
	 *TODO: Use this on a delegate sent from the laser that provides the location of the hit
	if (DamageCauser->GetClass() == ALaser::StaticClass()) {
		UNiagaraFunctionLibrary::SpawnSystemAttached(TestEffect, GetMesh(), "",
        	FVector(0), FRotator(0), EAttachLocation::KeepRelativeOffset, false, true);
	}
	*/
	
	if (HealthComponent->CurrentHealth <= 0) {
		//DeathNiagaraEffectComponent->Activate();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DeathNiagaraEffect, GetActorLocation(), FRotator::ZeroRotator, FVector(1.3), true);
		Destroy();
	}
	return 0;
}


