#pragma once

class EquippedWeaponNotify : public UAnimNotify {
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
