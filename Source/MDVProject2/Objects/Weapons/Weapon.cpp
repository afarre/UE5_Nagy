// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    /*const FSoftObjectPath WeaponDataTablePath = FSoftObjectPath(TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_WeaponStatistics.DT_WeaponStatistics'"));
	WeaponsDataTable = Cast<UDataTable>(WeaponDataTablePath.ResolveObject());*/
	WeaponsDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_WeaponStatistics.DT_WeaponStatistics'"));
	WeaponNamesArray = WeaponsDataTable->GetRowNames();
	
	InitComponents();
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap!"))
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay() {
	Super::BeginPlay();
}

void AWeapon::EnableOverlap() {
	DamageCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
}

void AWeapon::DisableOverlap() {
	DamageCollisionBox->OnComponentBeginOverlap.Clear();
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
