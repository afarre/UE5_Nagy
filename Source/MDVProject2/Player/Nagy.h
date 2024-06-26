// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "Nagy.generated.h"

class AWeapon;
class UCameraDataAsset;
class UInputDataAsset;
class UNiagaraComponent;
class UAnimationDataAsset;
class UHealthComponent;

UCLASS()
class MDVPROJECT2_API ANagy : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANagy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Weapon pointers
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AWeapon> EquippedWeapon;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AWeapon> PrimaryWeapon;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AWeapon> SecondaryWeapon;

	// Data assets/Tables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UAnimationDataAsset* AnimationDataAsset;

	// Trigger spells from AnimBlueprint
	UFUNCTION(BlueprintCallable)
	void TriggerSpell(UClass* Class);

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Character components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UNiagaraComponent* DashNiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UNiagaraComponent* TrailNiagaraEffect;
	
	// Data assets/Tables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UInputDataAsset* InputDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UCameraDataAsset* CameraDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTables)
	UDataTable* MovementSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTables)
	UDataTable* AbilitiesSettings;
	
private:
	UPROPERTY()
	APlayerController* PlayerController;

	void InitComponents();
	
	// Input Action implementation functions
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	void Attack(const FInputActionValue& Value);

	void Block();

	void Dash();

	void Interact();

	void CameraZoom(const FInputActionValue& Value);

	void Sprint();

	void Test(const FInputActionValue& Value);
	
	void ChangeWeapon();
	
	void Spell1();
	
	void Spell2();
	
	// Delegates
	FOnMontageEnded MontageEndedDelegate;
	
	void DashAbilityTimerDelegate();
	
	void DashCooldownTimerDelegate();

	void InteractMontageEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted);
	
	void UnderArmDisarmEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted, bool Pickup);

	void OverShoulderDisarmEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted, bool Pickup);

	// Anim
	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	// Movement handling
	void ModifyCharacterMovement(EMovementType MovementType) const;

	void AddInputMappings(TArray<UInputAction*> InputActionArray);
	
	EMovementType CurrentMovementType;

	UPROPERTY()
	TArray<FName> MovementSettingsArray;

	// Weapon handling
	void HandleWeaponInteract(const AWeapon* Weapon);
	
	void PickUpWeapon();

	// Abilities
	UPROPERTY()
	TArray<FName> AbilitiesArray;

};
