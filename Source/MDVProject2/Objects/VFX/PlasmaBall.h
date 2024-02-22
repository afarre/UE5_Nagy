// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "PlasmaBall.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API APlasmaBall : public ASpell {
	GENERATED_BODY()

public:
	APlasmaBall();
	
	void SetVelocity(const FVector& HitDirection);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* NiagaraSystem;
};
