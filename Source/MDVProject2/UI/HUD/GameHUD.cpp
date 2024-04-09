// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "Kismet/GameplayStatics.h"
#include "MDVProject2/Player/Nagy.h"
#include "MDVProject2/UI/Widgets/NagyUI.h"
#include "MDVProject2/Utils/Components/HealthComponent.h"

class UMainMenu;

AGameHUD::AGameHUD() {
	static ConstructorHelpers::FClassFinder<UUserWidget> NagyUIClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/CodeBlueprints/UI/WB_NagyUI.WB_NagyUI_C'"));
	if (NagyUIClassFinder.Class) {
		NagyUIWidget = NagyUIClassFinder.Class;
	}
}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	HealthComponent = UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetComponentByClass<UHealthComponent>();

	if (HealthComponent) {
		HealthComponent->HealthDelegateBinder.AddDynamic(this, &AGameHUD::HealthChanged);
	}
	
	CppOnlyCrosshair = CreateWidget<UCppOnlyWidget>(GetWorld(), UCppOnlyWidget::StaticClass());
	if (CppOnlyCrosshair) {
		CppOnlyCrosshair->AddToViewport();
	}

	if (NagyUIWidget) {
		NagyUI = CreateWidget<UNagyUI>(GetWorld(), NagyUIWidget);
		if (NagyUI) {
			NagyUI->SetPlayerHealth(HealthComponent->CurrentHealth);
			NagyUI->AddToViewport();
		}
	}
}


void AGameHUD::HealthChanged(const float& CurrentHealth) {
	NagyUI->SetPlayerHealth(CurrentHealth);
}
