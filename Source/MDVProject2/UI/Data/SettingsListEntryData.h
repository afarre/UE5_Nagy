// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "SettingsListEntryData.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API USettingsListEntryData : public UBlueprint {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FKey CurrentKey;
	
	UPROPERTY(BlueprintReadWrite)
	FKey DefaultKey;

	UPROPERTY(BlueprintReadWrite)
	FText VisibleKeyName;
};
