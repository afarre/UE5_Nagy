// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API ASword : public AWeapon {
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FWeaponData* WeaponData;
};
