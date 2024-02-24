// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatHUD.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

UCombatHUD::UCombatHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){
}

void UCombatHUD::NativeConstruct() {
	Super::NativeConstruct();

}

void UCombatHUD::NativeOnInitialized() {
	Super::NativeOnInitialized();
	
	// Construct the necessary widgets
	Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	TestButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
	TestButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	// Set widget characteristics
	TestButtonText->SetText(FText::FromString("Creado con C++"));

	// Add widgets hierarchically. Set widget location and weights
	TestButton->AddChild(TestButtonText);
	UCanvasPanelSlot* CanvasPanelSlot = Canvas->AddChildToCanvas(TestButton);
	if (CanvasPanelSlot) {
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetAnchors(FAnchors(.5, .5, .5, .5));
	}
	WidgetTree->RootWidget = Canvas;
}
