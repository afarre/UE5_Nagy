// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyBindListItem.h"

#include "SettingsWindow.h"
#include "Components/TextBlock.h"
#include "MDVProject2/UI/Data/SettingsListEntryData.h"

void UKeyBindListItem::NativeOnListItemObjectSet(UObject* ListItemObject) {
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	SettingsListEntryData = Cast<USettingsListEntryData>(ListItemObject);

	KeyName->SetText(SettingsListEntryData->VisibleKeyName);
	InputKeySelector->SetNoKeySpecifiedText(FText::FromString("[Empty]"));
	InputKeySelector->SetSelectedKey(SettingsListEntryData->CurrentKey);
}

void UKeyBindListItem::ResetToDefault() {
	SettingsListEntryData->CurrentKey = SettingsListEntryData->DefaultKey;
	InputKeySelector->SetSelectedKey(SettingsListEntryData->CurrentKey);
}

void UKeyBindListItem::OnInputKeySelected(FInputChord InputChord) {
	SettingsListEntryData->CurrentKey = InputChord.Key;
	InputKeySelector->SetSelectedKey(SettingsListEntryData->CurrentKey);
}
