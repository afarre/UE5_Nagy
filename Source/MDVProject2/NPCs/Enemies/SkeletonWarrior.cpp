// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonWarrior.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MDVProject2/UI/Widgets/EnemyHealthBar.h"
#include "MDVProject2/Utils/DataStructures.h"

// Sets default values
ASkeletonWarrior::ASkeletonWarrior() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyNamesArray = EnemyStatisticsDataTable->GetRowNames();
	Settings = EnemyStatisticsDataTable->FindRow<FEnemySettings>(EnemyNamesArray[SkeletonWarrior], "SkeletonWarrior");
	
	HealthComponent->MaxHealth = HealthComponent->CurrentHealth = Settings->MaxHealth;
	
	GetCharacterMovement()->MaxWalkSpeed = 250;
	GetCharacterMovement()->MaxAcceleration = 1024;
}

// Called when the game starts or when spawned
void ASkeletonWarrior::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void ASkeletonWarrior::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

float ASkeletonWarrior::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthComponent->CurrentHealth -= DamageAmount;
	GetMesh()->GetAnimInstance()->Montage_Play(Settings->TakeDamage, 1);
	
	EnemyHealthBar = Cast<UEnemyHealthBar>(HealthBarWidgetComponent->GetUserWidgetObject());
	EnemyHealthBar->UpdateHP(HealthComponent->CurrentHealth);
	
	if (HealthComponent->CurrentHealth <= 0) {
		EnemyHealthBar->PlayHealthBarAnimation();
		UAnimMontage* AnimMontage = Settings->DeathSequences[FMath::RandRange(0, Settings->DeathSequences.Num() - 1)];

		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontage, 1);
		MontageEndedDelegate.BindUObject(this, &ASkeletonWarrior::DeathEndDelegate);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, AnimMontage);
		
		GetCapsuleComponent()->DestroyComponent();
	}
	return 0;
}

/* Delegates */

void ASkeletonWarrior::DeathEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted) {
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Settings->DeathNiagaraEffect, GetMesh()->GetComponentLocation());
	Destroy();
}
