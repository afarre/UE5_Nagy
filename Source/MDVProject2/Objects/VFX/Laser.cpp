// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MDVProject2/Utils/DataAssets/NiagaraDataAsset.h"


ALaser::ALaser() {
	NiagaraSystem = LoadObject<UNiagaraSystem>(Super::GetClass(), TEXT("/Script/Niagara.NiagaraSystem'/Game/BigNiagaraBundle/NiagaraEffectMix2/Effects/NS_Flame_Painter.NS_Flame_Painter'"));
	SpellEffect->SetAsset(NiagaraSystem);
	//NiagaraSystem = NiagaraEffects->Laser;
	SpellEffect->SetRelativeRotation(FRotator(90, 0, 0));
}

void ALaser::SetVelocity(const FVector& HitDirection) {
	ProjectileMovementComponent->Velocity = UKismetMathLibrary::Normal(HitDirection) * -10000;
}

