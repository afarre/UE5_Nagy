// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MDVPROJECT2_API UMainMenu : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UVerticalBox* VerticalBox;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* NewGame;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* LoadGame;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* Settings;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* Exit;

private:
	UFUNCTION(BlueprintCallable)
	void NewGamePressed() const;

	UFUNCTION(BlueprintCallable)
	void LoadGamePressed() const;

	UFUNCTION(BlueprintCallable)
	void SettingsPressed() const;

	UFUNCTION(BlueprintCallable)
	void ExitPressed() const;

};
