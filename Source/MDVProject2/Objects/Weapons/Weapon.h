// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "MDVProject2/Utils/InteractiveObject.h"
#include "Weapon.generated.h"

UCLASS(Abstract)
class MDVPROJECT2_API AWeapon : public AActor, public IInteractiveInterface {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual TWeakObjectPtr<AActor> GetObjectType() override;

	virtual void DisableInteractCollisionBox();

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EWeaponType> WeaponType;

	FName StowedSocketName;

	FName EquippedSocketName;

	bool IsEquipped;

	bool IsPrimary;

	FName WeaponName;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UBoxComponent* PickupCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UBoxComponent* DamageCollisionBox;

	void InitComponents();

	// Data asset for weapon statistics
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataAssets)
	UDataTable* WeaponsDataAsset;
	
	UPROPERTY()
	UDataTable* WeaponsDataTable;
};
