// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "MDVProject2/Controller/MyAIController.h"

// Sets default values
AEnemy::AEnemy() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	EnemyStatisticsDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataStructures/DT_EnemySettings.DT_EnemySettings'"));
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/BP_EnemyHealthBar.BP_EnemyHealthBar'"));
	HealthBarWidgetComponent->SetWidgetClass(MenuWidgetClassFinder.Class);
	
	AIControllerClass = AMyAIController::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay() {
	Super::BeginPlay();
	HealthBarWidgetComponent->InitWidget();
}

// Called every frame
void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

//Unused (for now)
float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthComponent->CurrentHealth -= DamageAmount;
	
	return 0;
}


