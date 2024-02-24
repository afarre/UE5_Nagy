// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MDVProject2/Controller/MyReferenceManager.h"
#include "MDVProject2/Utils/DataAssets/AnimationDataAsset.h"
#include "MDVProject2/Utils/DataAssets/InputDataAsset.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "MDVProject2/Utils/DataAssets/CameraZoomDataAsset.h"
#include "MDVProject2/Utils/DataAssets/NiagaraDataAsset.h"
#include "Nagy.generated.h"

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

	// Visible to Blueprints
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerNiagaraDashEffect();

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
	void TriggerSpell1(UClass* Class);
	
	UFUNCTION(BlueprintCallable)
	void TriggerSpell2();
	
	FHitResult CalculateTraceTrajectory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Character components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UChildActorComponent* DashChildBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UNiagaraComponent* TrailNiagaraEffect;
	
	// Data assets/Tables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UInputDataAsset* InputDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UCameraZoomDataAsset* CameraDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UNiagaraDataAsset* NiagaraDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTables)
	UDataTable* MovementSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTables)
	UDataTable* AbilitiesSettings;
	
private:
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	AMyReferenceManager* MyReferenceManager;

	void InitComponents();
	
	// Input Action implementation functions
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	void Attack(const FInputActionValue& Value);

	void Block(const FInputActionValue& Value);

	void Dash(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void CameraZoom(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);

	void Test(const FInputActionValue& Value);
	
	void ChangeWeapon(const FInputActionValue& Value);

	void Spell1Triggered(const FInputActionValue& InputActionValue);
	
	void Spell2Ongoing();
	
	void Spell2();
	
	// Delegates
	FOnMontageEnded MontageEndedDelegate;
	
	void DashAbilityTimerDelegate();
	
	void DashCooldownTimerDelegate();

	void InteractMontageEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted);
	
	void UnderArmDisarmEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted, bool Pickup);

	void OverShoulderDisarmEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted, bool Pickup);

	// Montage
	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	// Movement handling
	void ModifyCharacterMovement(EMovementType MovementType) const;

	void AddInputMappings(TArray<UInputAction*> InputActionArray);

	bool MovementFirstChange;

	EMovementType CurrentMovementType;

	TArray<FName> MovementSettingsArray;

	// Weapon handling
	void HandleWeaponInteract(const AWeapon* Weapon);
	
	void PickUpWeapon();

	// Abilities
	TArray<FName> AbilitiesArray;
};
