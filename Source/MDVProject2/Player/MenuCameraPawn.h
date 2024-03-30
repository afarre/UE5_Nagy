// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "MenuCameraPawn.generated.h"

UCLASS()
class MDVPROJECT2_API AMenuCameraPawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMenuCameraPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//TODO: null for now, might be required for the settings tab. If not, remove
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PawnMappingContext;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
