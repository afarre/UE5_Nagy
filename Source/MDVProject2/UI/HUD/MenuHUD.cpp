// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"

#include "Kismet/GameplayStatics.h"
#include "MDVProject2/UI/Widgets/SettingsWindow.h"
#include "MDVProject2/Utils/DataStructures.h"

AMenuHUD::AMenuHUD() {
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/CodeBlueprints/UI/WB_MainMenu.WB_MainMenu_C'"));
	if (MenuWidgetClassFinder.Class) {
		MenuWidget = MenuWidgetClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SettingsWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/CodeBlueprints/UI/WP_SettingsWindow.WP_SettingsWindow_C'"));
	if (SettingsWidgetClassFinder.Class) {
		SettingsWidget = SettingsWidgetClassFinder.Class;
	}

}

void AMenuHUD::BeginPlay() {
	Super::BeginPlay();
	DisplayMenuWidow();
}

void AMenuHUD::DisplaySettingsWidow() {
	KeyBindsDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_KeyBinds.DT_KeyBinds'"));
	
	if (SettingsWidget) {
		Settings = CreateWidget<USettingsWindow>(GetWorld(), SettingsWidget);
		if (Settings) {
			Settings->AddToViewport();
			MainMenu->RemoveFromParent();
		}
	}
}

void AMenuHUD::DisplayMenuWidow() {
	if (MenuWidget) {
		MainMenu = CreateWidget<UMainMenu>(GetWorld(), MenuWidget);
		if (MainMenu) {
			MainMenu->AddToViewport();
		}
	}
}

void AMenuHUD::LoadNewGame() {
	//TODO: Find the means to load a new map that is not a submap, that changes the game mode and that has a callback to remove the "loading" widget
	/*
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "LevelLoadCallback";
	LatentActionInfo.UUID = 1;
	LatentActionInfo.Linkage = 1;

	UGameplayStatics::LoadStreamLevel(UGameplayStatics::GetGameInstance(this), FName(TEXT("Test")), true, true, LatentActionInfo);
	*/
	
	/*bool LoadMapSuccess;
	ULevelStreamingDynamic::LoadLevelInstance(UGameplayStatics::GetGameInstance(this), TEXT("Project2_Playable"), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FRotator(0), LoadMapSuccess);
	if (LoadMapSuccess) {
		UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().ToString())
		UE_LOG(LogTemp, Warning, TEXT("LoadMapSuccess true"))
		MainMenu->RemoveFromParent();
	}else {
		UE_LOG(LogTemp, Warning, TEXT("LoadMapSuccess false"))
	}*/
	
	/*
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(UGameplayStatics::GetGameInstance(this), FName(TEXT("asd")), true, true, LatentInfo);
	*/
	
	UGameplayStatics::OpenLevel(UGameplayStatics::GetGameInstance(this), FName(TEXT("Project2_Playable")));
	
	UE_LOG(LogTemp, Warning, TEXT("Done"))
}

void AMenuHUD::SaveKeyBindConfiguration(const TArray<UObject*> KeyBindConfiguration) {

	TSharedPtr<FKeyBinds> KeyBindsPtr = MakeShared<FKeyBinds>();
	FKeyBinds KeyBinds;
	KeyBinds.CurrentValue = EKeys::U;
	KeyBinds.DefaultValue = EKeys::U;
	KeyBinds.InputAction = nullptr;
	*KeyBindsPtr = KeyBinds;
	
	KeyBindsDataTable->AddRow(TEXT("Angel"), *KeyBindsPtr);

	//TODO: Find a way to have the changes persist on disk
	bool result = KeyBindsDataTable->MarkPackageDirty();
	if (result) {
		UE_LOG(LogTemp, Warning, TEXT("result true"))	
	}
	
	KeyBindsDataTable->PostEditChange();
	UE_LOG(LogTemp, Warning, TEXT("SaveKeyBindConfiguration"))
}

void AMenuHUD::LevelLoadCallback() {
	UE_LOG(LogTemp, Warning, TEXT("LevelLoadCallback"))
	FLatentActionInfo LatentActionInfo;
	UGameplayStatics::UnloadStreamLevel(UGameplayStatics::GetGameInstance(this), FName(UGameplayStatics::GetCurrentLevelName(UGameplayStatics::GetGameInstance(this))), LatentActionInfo, false);
	
	
	/*
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "LevelLoadCallback";
	LatentActionInfo.UUID = 1;
	LatentActionInfo.Linkage = 0;

	UGameplayStatics::LoadStreamLevel(this, "Project2_Playable", true, true, LatentActionInfo);
	*/
}
