#include "EquippedWeaponNotify.h"

#include "MDVProject2/Objects/Weapons/Weapon.h"
#include "MDVProject2/Player/Nagy.h"
#include "MDVProject2/Player/TestCharacter.h"


UEquippedWeaponNotify::UEquippedWeaponNotify() {
	#if WITH_EDITOR
		bShouldFireInEditor = false;
	#endif
}

void UEquippedWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	ANagy* Nagy = Cast<ANagy>(MeshComp->GetAttachParentActor());
	if (Nagy) {
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

	ATestCharacter* TestCharacter = Cast<ATestCharacter>(MeshComp->GetAttachParentActor());
	if (TestCharacter) {
		if (Animation == TestCharacter->AnimationDataAsset->OverShoulderEquip) {
			TestCharacter->PrimaryWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TestCharacter->PrimaryWeapon->EquippedSocketName);
			TestCharacter->PrimaryWeapon->IsEquipped = true;
			TestCharacter->EquippedWeapon = TestCharacter->PrimaryWeapon.Get(); 
		} else if (Animation == TestCharacter->AnimationDataAsset->UnderArmEquip){
			TestCharacter->SecondaryWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), TestCharacter->SecondaryWeapon->EquippedSocketName);
			TestCharacter->SecondaryWeapon->IsEquipped = true;
			TestCharacter->EquippedWeapon = TestCharacter->SecondaryWeapon.Get();
		}
	}
}
