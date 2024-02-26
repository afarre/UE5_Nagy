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

	virtual void SetVelocity(const FVector& HitDirection) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
