// Fill out  your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "SettingsWindow.generated.h"

class AMenuHUD;
/**
 * 
 */
UCLASS()
class MDVPROJECT2_API USettingsWindow : public UUserWidget {
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* KeyBindListView;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* TestListView;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BackButton;

private:
	UPROPERTY()
	AMenuHUD* MenuHUD;
	
	UPROPERTY()
	UDataTable* KeyBindsDataTable;

	UFUNCTION(BlueprintCallable)
	void BackButtonPressed();
};
