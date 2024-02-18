#pragma once

#include "DisarmWeaponNotify.generated.h"

UCLASS()
class UDisarmWeaponNotify : public UAnimNotify {
	GENERATED_BODY()
	
public:
	UDisarmWeaponNotify();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
