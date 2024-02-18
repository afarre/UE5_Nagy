#include "EquippedWeaponNotify.h"

#include "MDVProject2/Objects/Weapons/Weapon.h"
#include "MDVProject2/Player/Nagy.h"


UEquippedWeaponNotify::UEquippedWeaponNotify() {
	#if WITH_EDITOR
		bShouldFireInEditor = false;
	#endif
}

void UEquippedWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	ANagy* Nagy = Cast<ANagy>(MeshComp->GetAttachParentActor());
	if (Animation == Nagy->AnimationDataAsset->OverShoulderEquip) {
		Nagy->PrimaryWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Nagy->PrimaryWeapon->EquippedSocketName);
		Nagy->PrimaryWeapon->IsEquipped = true;
		Nagy->EquippedWeapon = Nagy->PrimaryWeapon.Get(); 
	} else if (Animation == Nagy->AnimationDataAsset->UnderArmEquip){
		Nagy->SecondaryWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Nagy->SecondaryWeapon->EquippedSocketName);
		Nagy->SecondaryWeapon->IsEquipped = true;
		Nagy->EquippedWeapon = Nagy->SecondaryWeapon.Get();
	}
}
