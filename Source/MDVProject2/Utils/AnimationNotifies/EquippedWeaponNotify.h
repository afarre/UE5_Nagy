#pragma once

#include "EquippedWeaponNotify.generated.h"

UCLASS()
class UEquippedWeaponNotify : public UAnimNotify {
	GENERATED_BODY()
	
public:
	UEquippedWeaponNotify();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
