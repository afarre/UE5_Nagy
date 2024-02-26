// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


ALaser::ALaser() {
	Statistics = SpellStatistics->FindRow<FSpellStatistics>(Spells[Laser], nullptr);

	NiagaraSystem = Statistics->BaseNiagaraSystem;
	
	SpellEffect->SetAsset(NiagaraSystem);
	SpellEffect->SetRelativeScale3D(SpellEffect->GetRelativeScale3D() * Statistics->BaseScale);
	SpellEffect->SetRelativeRotation(Statistics->Rotation);
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ALaser::OnOverlapBegin);
	
	// Time until it self destroys (not related to HP)
	InitialLifeSpan = Statistics->LifeSpan;
}

void ALaser::SetVelocity(const FVector& HitDirection) {
	Super::SetVelocity(HitDirection);
	ProjectileMovementComponent->Velocity *= Statistics->Velocity;
}

void ALaser::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UGameplayStatics::ApplyDamage(OtherActor, Statistics->BaseDamage, nullptr, this, UDamageType::StaticClass());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Statistics->HitNiagaraSystem, SweepResult.Location,
		FRotator::ZeroRotator, FVector(Statistics->HitScale), true);
}

