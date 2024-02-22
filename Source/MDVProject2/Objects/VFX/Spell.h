#pragma once
#include "NiagaraSystem.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Spell.generated.h"

class UNiagaraDataAsset;

UCLASS()
class MDVPROJECT2_API ASpell : public AActor {
	GENERATED_BODY()
	
public:
	ASpell();

	virtual void BeginPlay() override;

	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UNiagaraComponent* SpellEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UNiagaraDataAsset* NiagaraEffects;
};
