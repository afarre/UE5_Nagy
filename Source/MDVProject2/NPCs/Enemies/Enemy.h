// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "MDVProject2/Utils/Components/HealthComponent.h"
#include "Enemy.generated.h"

class UBoxComponent;

UCLASS()
class MDVPROJECT2_API AEnemy : public ACharacter {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTables)
	UDataTable* EnemyStatisticsDataTable;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* DamageCollisionBox;

	// Other
	TArray<FName> EnemyNamesArray;
};
