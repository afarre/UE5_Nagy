// Fill out your copyright notice in the Description page of Project Settings.


#include "Spear.h"

void ASpear::TriggerInteraction() {
	Super::TriggerInteraction();
	UE_LOG(LogTemp, Warning, TEXT("I'm the spear!!"))
}


FName ASpear::GetSocket() {
	UE_LOG(LogTemp, Warning, TEXT("returning a name from sword"))
	return WeaponData->EquippedSocketName;
}

EWeaponType ASpear::GetWeaponType() {
	return Spear;
}

void ASpear::BeginPlay() {
	if (WeaponsDataTable) {
		WeaponData = WeaponsDataTable->FindRow<FWeaponData>(FName(*WeaponMesh->GetStaticMesh()->GetName()), "");
		UE_LOG(LogTemp, Warning, TEXT("Name (spear): %s"), *WeaponData->Name.ToString())
	}
}
