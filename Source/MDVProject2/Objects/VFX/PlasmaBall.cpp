// Fill out your copyright notice in the Description page of Project Settings.


#include "PlasmaBall.h"

#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"


APlasmaBall::APlasmaBall() {
	NiagaraSystem = LoadObject<UNiagaraSystem>(Super::GetClass(), TEXT("/Script/Niagara.NiagaraSystem'/Game/BigNiagaraBundle/NiagaraEffectMix3/Effects/NS_PlasmaSphere.NS_PlasmaSphere'"));
	SpellEffect->SetAsset(NiagaraSystem);
}

void APlasmaBall::SetVelocity(const FVector& HitDirection) {
	ProjectileMovementComponent->Velocity = UKismetMathLibrary::Normal(HitDirection) * -1000;
}
