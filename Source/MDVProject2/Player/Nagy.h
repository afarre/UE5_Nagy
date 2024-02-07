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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadOnly)
	AWeapon* EquippedWeapon;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Camera elements
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UCameraComponent* FollowCamera;

	// Data assets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UInputDataAsset* InputDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UCameraZoomDataAsset* CameraZoomDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UAnimationDataAsset* AnimationDataAsset;

private:
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	AMyReferenceManager* MyReferenceManager;

	void InitComponents();

	// Input
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	
	// Input Action implementation functions
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	void Attack(const FInputActionValue& Value);

	void Block(const FInputActionValue& Value);

	void Dash(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void CameraZoom(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);

	void Test(const FInputActionValue& Value);

	// Delegates
	void DashTimerDelegate();

	void MontageEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted);

	// Montage
	FOnMontageEnded CompleteDelegate;

	FOnMontageEnded MontageEndedDelegate;
	
	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	// Movement handling
	void ModifyCharacterMovement(EMovementType MovementType) const;

	void AddInputMappings(TArray<UInputAction*> InputActionArray);

	bool CharMovementFirstChange;

	EMovementType CurrentMovementType;
};
