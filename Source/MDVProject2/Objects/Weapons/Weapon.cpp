// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    const FSoftObjectPath WeaponDataTablePath = FSoftObjectPath(TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_WeaponStatistics.DT_WeaponStatistics'"));
	WeaponsDataTable = Cast<UDataTable>(WeaponDataTablePath.ResolveObject());

	InitComponents();
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

TWeakObjectPtr<AActor> AWeapon::GetObjectType() {
	return this;
}

void AWeapon::DisableInteractCollisionBox() {
	PickupCollisionBox->DestroyComponent();
}

void AWeapon::InitComponents() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	
	PickupCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupCollisionBox"));
	PickupCollisionBox->SetupAttachment(WeaponMesh);

	DamageCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollisionBox"));
	DamageCollisionBox->SetupAttachment(WeaponMesh);
}
