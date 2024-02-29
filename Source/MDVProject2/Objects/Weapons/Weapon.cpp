// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "KismetTraceUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponsDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_WeaponStatistics.DT_WeaponStatistics'"));
	WeaponNamesArray = WeaponsDataTable->GetRowNames();
	
	InitComponents();
}

void AWeapon::WeaponCollisionDelegate() {
	TArray<FHitResult> HitResults;
	
	GetWorld()->LineTraceMultiByProfile(HitResults, InitDamageCollisionBoxPos, DamageCollisionBox->GetComponentLocation(),
		FName("Pawn"), CollisionQueryParams);
	
	DrawDebugLine(GetWorld(), InitDamageCollisionBoxPos, DamageCollisionBox->GetComponentLocation(),
		FColor::Blue, false, 10.0f, 0, 1.0f);
	
	DrawDebugSweptBox(GetWorld(), InitDamageCollisionBoxPos, DamageCollisionBox->GetComponentLocation(),
		DamageCollisionBox->GetComponentRotation(), DamageCollisionBox->GetScaledBoxExtent()/2, FColor::Emerald, false, 10);
	
	for (FHitResult HitResult : HitResults) {
		UE_LOG(LogTemp, Warning, TEXT("Registered this hit: %s"), *HitResult.GetActor()->GetName())
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 40, nullptr, this, UDamageType::StaticClass());
		CollisionQueryParams.AddIgnoredActor(HitResult.GetActor());
	}
	InitDamageCollisionBoxPos = DamageCollisionBox->GetComponentLocation();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWeapon::WeaponCollisionDelegate, 1.0f, false, .01);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay() {
	Super::BeginPlay();
}

void AWeapon::InitWeaponTraceHitTimer() {
	InitDamageCollisionBoxPos = DamageCollisionBox->GetComponentLocation();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWeapon::WeaponCollisionDelegate, 0.01, false, 0);
	CollisionQueryParams.AddIgnoredActor(this);
}

void AWeapon::EndWeaponTraceHitTimer() {
	GetWorldTimerManager().ClearTimer(TimerHandle);
	CollisionQueryParams.ClearIgnoredActors();
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
