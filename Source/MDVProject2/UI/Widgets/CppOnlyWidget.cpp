// Fill out your copyright notice in the Description page of Project Settings.


#include "CppOnlyWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
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
	Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	TestButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
	TestButtonText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	// Populate the widgets
	FString CrosshairImagePath = FString("/Script/Engine.Texture2D'/Game/Icons/Crosshair.Crosshair'");
	UTexture2D* CrosshairTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *CrosshairImagePath));
	Image->SetBrushFromTexture(CrosshairTexture);
	
	TestButtonText->SetText(FText::FromString("Created with C++"));

	// Create widget hierarchy
	TestButton->AddChild(TestButtonText);

	// Set widget location, anchors, alignment...
	UCanvasPanelSlot* CanvasPanelSlot = Canvas->AddChildToCanvas(TestButton);
	if (CanvasPanelSlot) {
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetAnchors(FAnchors(0, 0, 0, 0));
	}
	
	CanvasPanelSlot = Canvas->AddChildToCanvas(Image);
	if (CanvasPanelSlot) {
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetAnchors(FAnchors(.5, .5, .5, .5));
		CanvasPanelSlot->SetAlignment(FVector2d(.5, .5));
	}
	
	WidgetTree->RootWidget = Canvas;
}
