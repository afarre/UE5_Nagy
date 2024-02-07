#pragma once

#include "CameraZoomDataAsset.generated.h"

UCLASS()
class MDVPROJECT2_API UCameraZoomDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomStep = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinCameraZoom = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraZoom = 500.0f;
};
