// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyReferenceManager.generated.h"

class AWeapon;
class ANagy;
class AMyController;
class AMyHUD;

UCLASS()
class MDVPROJECT2_API AMyReferenceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyReferenceManager();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	ANagy* Nagy;

	UPROPERTY()
	AMyController* MyController;

	UPROPERTY()
	AMyHUD* MyHUD;

	UPROPERTY()
	AWeapon* Weapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
