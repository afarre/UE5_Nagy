#pragma once

#include "AnimationDataAsset.generated.h"

UCLASS()
class MDVPROJECT2_API UAnimationDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* DodgeMontage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* InteractMontage;
};