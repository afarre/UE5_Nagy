// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.h"
#include "InteractiveObject.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UInteractiveInterface : public UInterface {
	GENERATED_BODY()
};

class IInteractiveInterface {
	GENERATED_BODY()

public:
	virtual void TriggerInteraction();

	virtual FName GetSocket();

	virtual EWeaponType GetWeaponType();
};

