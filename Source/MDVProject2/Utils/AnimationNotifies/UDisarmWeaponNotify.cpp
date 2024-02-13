#include "UDisarmWeaponNotify.h"

#include "MDVProject2/Objects/Weapons/Sword.h"
#include "MDVProject2/Player/Nagy.h"

void UDisarmWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	UE_LOG(LogTemp, Warning, TEXT("Over shoulder disarm notify"))
	ANagy* Nagy = Cast<ANagy>(MeshComp->GetAttachParentActor());
	if (Nagy) {
		Nagy->EquippedWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Nagy->EquippedWeapon->StowedSocketName);
		Nagy->StowedWeapon = Nagy->EquippedWeapon;
		Nagy->EquippedWeapon = nullptr;
	}
}
