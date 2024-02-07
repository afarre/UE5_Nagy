// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveObject.h"

void IInteractiveInterface::TriggerInteraction() {
	UE_LOG(LogTemp, Warning, TEXT("i'm the interface!"))
}

FName IInteractiveInterface::GetSocket() {
	UE_LOG(LogTemp, Warning, TEXT("returning nothing from the interface"))
	return "";
}
