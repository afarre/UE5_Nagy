// Fill out your copyright notice in the Description page of Project Settings.


#include "MyReferenceManager.h"

#include "MyController.h"
#include "Kismet/GameplayStatics.h"
#include "MDVProject2/Objects/Weapons/Weapon.h"
#include "MDVProject2/Player/Nagy.h"
#include "MDVProject2/UI/HUD/GameHUD.h"

// Sets default values
AMyReferenceManager::AMyReferenceManager() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyReferenceManager::BeginPlay() {
	Super::BeginPlay();
	
	Nagy = Cast<ANagy>(UGameplayStatics::GetActorOfClass(GetWorld(), ANagy::StaticClass()));

	MyController = Cast<AMyController>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyController::StaticClass()));
	
	MyHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Weapon = Cast<AWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), AWeapon::StaticClass()));
}

// Called every frame
void AMyReferenceManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}