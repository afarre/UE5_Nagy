// Fill out your copyright notice in the Description page of Project Settings.


#include "CppOnlyWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

UCppOnlyWidget::UCppOnlyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){
}

void UCppOnlyWidget::NativeConstruct() {
	Super::NativeConstruct();

}

void UCppOnlyWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	
	// Construct the necessary widgets
	Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	TestButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
	TestButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	// Set widget characteristics
	TestButtonText->SetText(FText::FromString("Created with C++"));

	// Add widgets hierarchically. Set widget location and weights
	TestButton->AddChild(TestButtonText);
	UCanvasPanelSlot* CanvasPanelSlot = Canvas->AddChildToCanvas(TestButton);
	if (CanvasPanelSlot) {
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetAnchors(FAnchors(.5, .5, .5, .5));
	}
	WidgetTree->RootWidget = Canvas;
}
