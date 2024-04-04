// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/InputKeySelector.h"
#include "Framework/Commands/InputChord.h"
#include "KeyBindListItem.generated.h"

class USettingsListEntryData;
class UImage;
class UButton;
class UTextBlock;
class UHorizontalBox;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MDVPROJECT2_API UKeyBindListItem : public UUserWidget, public IUserObjectListEntry {
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* ItemHorizontalBox;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* KeyName;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UInputKeySelector* InputKeySelector;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ReturnToDefaultButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* ReturnToDefaultIcon;

	UPROPERTY()
	USettingsListEntryData* SettingsListEntryData;

	UFUNCTION(BlueprintCallable)
	void ResetToDefault();
	
	UFUNCTION(BlueprintCallable)
	void OnInputKeySelected(FInputChord InputChord);

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInAnimation;
};
