#pragma once

#include "WidgetDataAsset.generated.h"

UCLASS()
class MDVPROJECT2_API UWidgetDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UUserWidget* MainMenu;

};