// Fill out your copyright notice in the Description page of Project Settings.


#include "PlasmaBall.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MDVProject2/Utils/DataStructures.h"

APlasmaBall::APlasmaBall() {
	Statistics = SpellStatistics->FindRow<FSpellStatistics>(Spells[PlasmaBall], nullptr);

	NiagaraSystem = Statistics->BaseNiagaraSystem;
	
	SpellEffect->SetAsset(NiagaraSystem);
	SpellEffect->SetRelativeScale3D(SpellEffect->GetRelativeScale3D() * Statistics->BaseScale);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APlasmaBall::OnOverlapBegin);

	// Time until it self destroys (not related to HP)
	InitialLifeSpan = Statistics->LifeSpan;
	
}

void APlasmaBall::SetVelocity(const FVector& HitDirection) {
	Super::SetVelocity(HitDirection);
	ProjectileMovementComponent->Velocity *= Statistics->Velocity;
}

void APlasmaBall::BeginPlay() {
	Super::BeginPlay();
}

void APlasmaBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin: %s"), *OtherActor->GetActorNameOrLabel())
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Statistics->HitNiagaraSystem, SweepResult.Location,
		FRotator::ZeroRotator, FVector(Statistics->HitScale), true);
	
	TArray<FHitResult> HitResults;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), Statistics->HitRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore,
		EDrawDebugTrace::None, HitResults, true, FLinearColor::Yellow, FLinearColor::Red, 20);

	for (FHitResult HitResult : HitResults) {
		UE_LOG(LogTemp, Warning, TEXT("SphereTraceMulti: %s"), *HitResult.GetActor()->GetActorNameOrLabel())
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), Statistics->BaseDamage, nullptr, this, UDamageType::StaticClass());
	}

	Destroy();
}
