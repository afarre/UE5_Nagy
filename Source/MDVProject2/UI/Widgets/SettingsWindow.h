// Fill out  your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "SettingsWindow.generated.h"

/**
 * 
 */
UCLASS()
class MDVPROJECT2_API USettingsWindow : public UUserWidget {
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* ItemHorizontalBox;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* KeyDescription;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* KeyBindChangeButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* KeyBind;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ReturnToDefaultButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* ReturnToDefaultIcon;

private:
	UFUNCTION(BlueprintCallable)
	void ChangeKeyBind() const;

	UFUNCTION(BlueprintCallable)
	void ReturnToDefault() const;
	
};
