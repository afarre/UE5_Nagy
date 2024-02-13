// Fill out your copyright notice in the Description page of Project Settings.


#include "PickedWeaponNotify.h"

#include "MDVProject2/Objects/Weapons/Weapon.h"

void UPickedWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	UE_LOG(LogTemp, Warning, TEXT("Picked montage notify"))

	TArray<AActor*> OverlappingActors;
	MeshComp->GetAttachParentActor()->GetOverlappingActors(OverlappingActors, UInteractiveInterface::StaticClass());
	if (!OverlappingActors.IsEmpty()) {
		IInteractiveInterface* InteractiveClass = Cast<IInteractiveInterface>(OverlappingActors[0]);
		if (InteractiveClass){
			if (InteractiveClass->GetObjectType().Get()->GetClass()->IsChildOf(AWeapon::StaticClass())) {
				AWeapon* Weapon = Cast<AWeapon>(InteractiveClass);
				Weapon->DisableInteractCollisionBox();
				Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Weapon->EquippedSocketName);
			}
		}
	}
}
