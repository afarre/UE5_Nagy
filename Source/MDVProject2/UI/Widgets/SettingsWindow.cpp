// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWindow.h"

#include "KeyBindListItem.h"
#include "MDVProject2/UI/Data/SettingsListEntryData.h"
#include "MDVProject2/UI/HUD/MenuHUD.h"
#include "MDVProject2/Utils/DataStructures.h"


void USettingsWindow::NativeOnInitialized() {
	Super::NativeOnInitialized();
	MenuHUD = Cast<AMenuHUD>(GetOwningPlayer()->GetHUD());
}

void USettingsWindow::NativeConstruct() {
	Super::NativeConstruct();

	MenuHUD->KeyBindsDataTable->ForeachRow<FKeyBinds>("IterateKeyBinds", [&](const FName& Name, const FKeyBinds& KeyBind) {
		// Do something here
		if (KeyBindListView->GetDefaultEntryClass()) {
			USettingsListEntryData* SettingsListEntryData = NewObject<USettingsListEntryData>();
			SettingsListEntryData->VisibleKeyName = FText::FromName(Name);
			SettingsListEntryData->CurrentKey = KeyBind.CurrentValue;
			SettingsListEntryData->DefaultKey = KeyBind.DefaultValue;
			KeyBindListView->AddItem(SettingsListEntryData);
		}
	});
}

void USettingsWindow::BackButtonPressed() {
	//TODO: Save new inputs from the player in the DataTable and change the input mappings to reflect the changes
	RemoveFromParent();
	MenuHUD->SaveKeyBindConfiguration(KeyBindListView->GetListItems());
	MenuHUD->DisplayMenuWidow();
}
