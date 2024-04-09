// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "CppOnlyWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MDVPROJECT2_API UCppOnlyWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UCppOnlyWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* Image;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* TestButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TestButtonText;
	
};
