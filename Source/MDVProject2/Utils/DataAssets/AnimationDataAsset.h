#pragma once

#include "AnimationDataAsset.generated.h"

UCLASS()
class MDVPROJECT2_API UAnimationDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* InteractMontage;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* OverShoulderEquip;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* OverShoulderDisarm;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* UnderArmEquip;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* UnderArmDisarm;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* UpwardsThrust;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* Slash;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* Spell1;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* Spell2;
};