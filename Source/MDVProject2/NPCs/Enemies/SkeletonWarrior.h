// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MDVProject2/UI/Widgets/EnemyHealthBar.h"
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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UEnemyHealthBar* EnemyHealthBar;
private:
	FEnemySettings* Settings;

	// Delegates
	FOnMontageEnded MontageEndedDelegate;
	
	void DeathEndDelegate(UAnimMontage* AnimMontage, bool bArg);

};
