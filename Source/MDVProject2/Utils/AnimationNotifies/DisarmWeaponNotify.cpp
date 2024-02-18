#include "DisarmWeaponNotify.h"

#include "MDVProject2/Objects/Weapons/Sword.h"
#include "MDVProject2/Player/Nagy.h"

UDisarmWeaponNotify::UDisarmWeaponNotify() {
	#if WITH_EDITOR
		bShouldFireInEditor = false;
	#endif
}

void UDisarmWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	ANagy* Nagy = Cast<ANagy>(MeshComp->GetAttachParentActor());
	if (Nagy) {
		Nagy->EquippedWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Nagy->EquippedWeapon->StowedSocketName);
		Nagy->EquippedWeapon->IsEquipped = false;
		Nagy->EquippedWeapon = nullptr;
	}
}
