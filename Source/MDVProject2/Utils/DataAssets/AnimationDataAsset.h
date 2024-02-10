#pragma once

#include "AnimationDataAsset.generated.h"

UCLASS()
class MDVPROJECT2_API UAnimationDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Movement)
	UAnimMontage* InteractMontage;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* OverShoulderEquip;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* OverShoulderDisarm;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* UnderArmEquip;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UAnimMontage* UnderArmDisarm;
};