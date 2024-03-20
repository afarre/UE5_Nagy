#pragma once
#include "NiagaraSystem.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MDVProject2/Utils/DataStructures.h"

#include "Spell.generated.h"

UCLASS()
class MDVPROJECT2_API ASpell : public AActor {
	GENERATED_BODY()
	
public:
	ASpell();

	virtual void BeginPlay() override;

	virtual void SetVelocity(const FVector& HitDirection);

	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UNiagaraComponent* SpellEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* NiagaraSystem;
	
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* SpellStatistics;

	TArray<FName> Spells;

	FSpellStatistics* Statistics;
};
