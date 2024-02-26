
#include "Spell.h"

#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"


ASpell::ASpell() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpellStatistics = LoadObject<UDataTable>(GetClass(), TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_SpellStatistics.DT_SpellStatistics'"));
	Spells = SpellStatistics->GetRowNames();
	
	// Create components
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	RootComponent = CollisionSphere;
	
	SpellEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SpellEffect"));
	SpellEffect->SetupAttachment(CollisionSphere);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetHiddenInGame(false);
	ArrowComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void ASpell::BeginPlay() {
	Super::BeginPlay();
}

void ASpell::SetVelocity(const FVector& HitDirection) {
	ProjectileMovementComponent->Velocity = UKismetMathLibrary::Normal(HitDirection);
}