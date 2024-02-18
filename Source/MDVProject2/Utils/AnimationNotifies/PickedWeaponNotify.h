// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PickedWeaponNotify.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API UPickedWeaponNotify : public UAnimNotify {
	GENERATED_BODY()

public:
	UPickedWeaponNotify();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
