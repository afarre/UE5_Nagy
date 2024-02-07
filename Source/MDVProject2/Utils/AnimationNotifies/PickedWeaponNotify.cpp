// Fill out your copyright notice in the Description page of Project Settings.


#include "PickedWeaponNotify.h"

#include "MDVProject2/Objects/Weapons/Weapon.h"

void UPickedWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	UE_LOG(LogTemp, Warning, TEXT("Pick montage notify"))

	TArray<AActor*> OverlappingActors;
	MeshComp->GetAttachParentActor()->GetOverlappingActors(OverlappingActors, UInteractiveInterface::StaticClass());
	if (!OverlappingActors.IsEmpty()) {
		IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(OverlappingActors[0]);
		InteractiveInterface->TriggerInteraction();
		OverlappingActors[0]->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), InteractiveInterface->GetSocket());
	}
}
