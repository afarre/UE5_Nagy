// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

void ASword::BeginPlay() {
	if (WeaponsDataTable) {
		WeaponData = WeaponsDataTable->FindRow<FWeaponData>(FName(*WeaponMesh->GetStaticMesh()->GetName()), "");
		UE_LOG(LogTemp, Warning, TEXT("Name (sword): %s"), *WeaponData->Name.ToString())
	}
	
	WeaponType = Sword;

	if (WeaponData) {
		StowedSocketName = WeaponData->StowedSocketName;
		EquippedSocketName = WeaponData->EquippedSocketName;
		IsPrimary = WeaponData->IsPrimary;
		WeaponName = WeaponData->Name;
	}
}
