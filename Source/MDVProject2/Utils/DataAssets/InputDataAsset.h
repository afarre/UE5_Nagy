// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMappingContext.h"
#include "InputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API UInputDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = InputMappingContext)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category = InputMappingContext)
	UInputMappingContext* BlankMappingContext;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* AttackInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* BlockInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* DashInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* InteractInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* CameraZoomInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* SprintInputAction;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* Test;
	
	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* ChangeWeapon;
	
	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* Spell1;

	UPROPERTY(EditAnywhere, Category = InputAction)
	UInputAction* Spell2;
};
