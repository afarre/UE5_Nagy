// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MDVProject2/Utils/DataAssets/NiagaraDataAsset.h"


ALaser::ALaser() {
	NiagaraSystem = LoadObject<UNiagaraSystem>(Super::GetClass(), TEXT("/Script/Niagara.NiagaraSystem'/Game/BigNiagaraBundle/NiagaraEffectMix2/Effects/NS_Flame_Painter.NS_Flame_Painter'"));
	SpellEffect->SetAsset(NiagaraSystem);
	SpellEffect->SetRelativeRotation(FRotator(-90, 0, 0));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ALaser::OnOverlapBegin);

	// Time until it self destroys (not related to HP)
	InitialLifeSpan = 4;
}

void ALaser::SetVelocity(const FVector& HitDirection) {
	ProjectileMovementComponent->Velocity = UKismetMathLibrary::Normal(HitDirection) * 10000;
}

void ALaser::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap!"))

	UGameplayStatics::ApplyDamage(OtherActor, 10, nullptr, this, UDamageType::StaticClass());
}

