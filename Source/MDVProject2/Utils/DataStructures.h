#pragma once

#include "InputAction.h"
#include "NiagaraSystem.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPrimary;
	
	FWeaponData() {
		Name = "";
		Damage = 0;
		EquippedSocketName = "";
		StowedSocketName = "";
		IsPrimary = false;
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

USTRUCT(BlueprintType)
struct FAbilitiesSettings : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	FAbilitiesSettings() {
		Cooldown = 5;
		Duration = 0.1;
	}
};

USTRUCT(BlueprintType)
struct FEnemySettings : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* DeathNiagaraEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> DeathSequences;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* TakeDamage;

	FEnemySettings() {
		MaxHealth = 100;
		DeathNiagaraEffect = nullptr;
		DeathSequences = {};
		TakeDamage = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FSpellStatistics : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* BaseNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* HitNiagaraSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HitRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator HitRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LifeSpan;

	FSpellStatistics() {
		BaseNiagaraSystem = nullptr;
		BaseScale = 1;
		Rotation = FRotator(1);
		Velocity = 1000;
		BaseDamage = 50;
		HitNiagaraSystem = nullptr;
		HitScale = 1;
		HitRadius = 1;
		HitRotation = FRotator(1);
		LifeSpan = 1;
	}
};

USTRUCT()
struct FKeyBinds : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey DefaultValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* InputAction;
};

/* Enums */

UENUM()
enum EMovementType {
	Walking = 0,
	Sprinting = 1,
	Dashing = 2
};

UENUM()
enum EAbilities {
	Dash = 0,
	Spell1 = 1,
	Spell2 = 2
};

UENUM()
enum ESpells {
	PlasmaBall = 0,
	Laser = 1
};

UENUM()
enum EEnemy {
	SkeletonWarrior = 0
};

UENUM(BlueprintType)
enum EWeaponType {
	Unarmed = 0,
	Sword = 1,
	Spear = 2,
};
