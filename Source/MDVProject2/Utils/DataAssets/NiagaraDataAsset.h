#pragma once

#include "NiagaraSystem.h"
#include "NiagaraDataAsset.generated.h"

UCLASS(Blueprintable)
class UNiagaraDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = MovementEffects)
	UNiagaraSystem* PlasmaBall;

	UPROPERTY(EditAnywhere, Category = MovementEffects)
	UNiagaraSystem* Laser;
};
