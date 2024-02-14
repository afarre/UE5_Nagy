// Fill out your copyright notice in the Description page of Project Settings.


#include "Spear.h"

void ASpear::BeginPlay() {
	if (WeaponsDataTable) {
		WeaponData = WeaponsDataTable->FindRow<FWeaponData>(FName(*WeaponMesh->GetStaticMesh()->GetName()), "");
		UE_LOG(LogTemp, Warning, TEXT("Name (spear): %s"), *WeaponData->Name.ToString())
	}
	
	WeaponType = Spear;

	if (WeaponData) {
		StowedSocketName = WeaponData->StowedSocketName;
		EquippedSocketName = WeaponData->EquippedSocketName;
		IsPrimary = WeaponData->IsPrimary;
		WeaponName = WeaponData->Name;
	}
}
