// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MDVProject2/UI/Widgets/CombatHUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API AMyHUD : public AHUD {
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	UCombatHUD* CombatHUD;

};
