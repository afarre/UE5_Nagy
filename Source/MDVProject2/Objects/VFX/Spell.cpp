
#include "Spell.h"

#include "NiagaraComponent.h"


ASpell::ASpell() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	RootComponent = CollisionSphere;
	
	SpellEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SpellEffect"));
	SpellEffect->SetRelativeScale3D(SpellEffect->GetRelativeScale3D() * 0.1);
	SpellEffect->SetupAttachment(CollisionSphere);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetHiddenInGame(false);
	ArrowComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent2"));
	ProjectileMovementComponent->bAutoActivate = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void ASpell::BeginPlay() {
	Super::BeginPlay();
}



