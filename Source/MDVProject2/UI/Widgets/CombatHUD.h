// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "CombatHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MDVPROJECT2_API UCombatHUD : public UUserWidget {
	GENERATED_BODY()

public:
	UCombatHUD(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* Canvas;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* TestButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TestButtonText;
	
};
