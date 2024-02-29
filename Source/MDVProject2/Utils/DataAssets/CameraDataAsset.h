#pragma once

#include "CameraDataAsset.generated.h"

UCLASS()
class MDVPROJECT2_API UCameraDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZOffset = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomStep = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinCameraZoom = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraZoom = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetArmLength = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraLagSpeed = 3;
};
