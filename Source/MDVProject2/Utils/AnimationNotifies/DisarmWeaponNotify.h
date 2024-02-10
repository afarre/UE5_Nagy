#pragma once

class DisarmWeaponNotify : public UAnimNotify {
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
