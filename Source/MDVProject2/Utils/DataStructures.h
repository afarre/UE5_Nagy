#pragma once

#include "Engine/DataTable.h"
#include "DataStructures.generated.h"

/* Data Tables */

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EquippedSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StowedSocketName;
	
	FWeaponData() {
		Name = "";
		Damage = 0;
		EquippedSocketName = "";
		StowedSocketName = "";
	}
};

USTRUCT(BlueprintType)
struct FMovementSetting : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GroundFriction;

	FMovementSetting() {
		MaxWalkSpeed = 250;
		MaxAcceleration = 2048;
		GroundFriction = 8;
	}
};

/* Enums */

UENUM()
enum EMovementType {
	Walking = 0,
	Sprinting = 1,
	Dashing = 2
};

UENUM(BlueprintType)
enum EWeaponType {
	Unarmed = 0,
	Sword = 1,
	Spear = 2,
};
