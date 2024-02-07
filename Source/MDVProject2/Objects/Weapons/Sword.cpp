// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

#include "MDVProject2/Utils/DataStructures.h"

void ASword::TriggerInteraction() {
	Super::TriggerInteraction();
	UE_LOG(LogTemp, Warning, TEXT("i'm the sword!!"))
}

FName ASword::GetSocket() {
	UE_LOG(LogTemp, Warning, TEXT("returning a name from sword"))
	return WeaponData->SocketName;
}

void ASword::BeginPlay() {
	if (WeaponsDataTable) {
		WeaponData = WeaponsDataTable->FindRow<FWeaponData>(FName(*WeaponMesh->GetStaticMesh()->GetName()), "");
		UE_LOG(LogTemp, Warning, TEXT("Name (sword): %s"), *WeaponData->Name.ToString())
	}
}
