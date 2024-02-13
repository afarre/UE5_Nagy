#pragma once

#include "UDisarmWeaponNotify.generated.h"

UCLASS()
class UDisarmWeaponNotify : public UAnimNotify {
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
