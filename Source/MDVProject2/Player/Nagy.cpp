// Fill out your copyright notice in the Description page of Project Settings.


#include "Nagy.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MDVProject2/Objects/VFX/PlasmaBall.h"
#include "MDVProject2/Objects/Weapons/Weapon.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "MDVProject2/Utils/Components/HealthComponent.h"
#include "MDVProject2/Utils/DataAssets/AnimationDataAsset.h"
#include "MDVProject2/Utils/DataAssets/CameraDataAsset.h"
#include "MDVProject2/Utils/DataAssets/InputDataAsset.h"
#include "MDVProject2/Utils/Interfaces/InteractiveObject.h"

// Sets default values
ANagy::ANagy() {
 	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Auto Posses for this Character
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	InitComponents();
}

void ANagy::InitComponents() {
	// Initialize the Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 200;
	//CameraBoom->CameraLagSpeed = 30;

	// Initialize the Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Add dash Niagara effect
	DashNiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>("DashNiagaraEffect");
	DashNiagaraEffect->SetupAttachment(GetMesh());
	DashNiagaraEffect->SetAutoActivate(false);

	// Add sprinting Niagara effect
	TrailNiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>("TrailNiagaraEffect");
	TrailNiagaraEffect->SetupAttachment(GetMesh());
	TrailNiagaraEffect->SetAutoActivate(false);

	// Add Health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->InitValues(100, 100);
}

void ANagy::TriggerSpell(UClass* Class) {
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = this;

	FVector PlayerTraceStart = GetMesh()->GetSocketLocation("LeftHandSocket");
	ASpell* Spell = GetWorld()->SpawnActor<ASpell>(Class, PlayerTraceStart, FollowCamera->GetComponentRotation(), ActorSpawnParameters);

	FHitResult TraceHit;
	FVector TraceStart = FollowCamera->GetComponentLocation();
	FVector TraceEnd = FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector() * 10000.0f;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);
	if (Spell) {
		if (TraceHit.bBlockingHit && IsValid(TraceHit.GetActor())) {
			FVector TraceHitLocation = FVector(TraceHit.ImpactPoint.X, TraceHit.ImpactPoint.Y, TraceHit.ImpactPoint.Z);
			//DrawDebugLine(GetWorld(), FollowCamera->GetComponentLocation(), TraceHitLocation, FColor::Blue, false, 5.0f, 0, 2.0f);
			FVector ProjectileMovementComponentVelocity = TraceHitLocation - PlayerTraceStart;
			Spell->SetVelocity(ProjectileMovementComponentVelocity);
		} else {
			Spell->SetVelocity(FollowCamera->GetForwardVector());
		}
	}
}

// Called when the game starts or when spawned
void ANagy::BeginPlay() {
	Super::BeginPlay();
	// Get the player controller
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && InputDataAsset) {
		// Get the "Enhanced Input Local Player Subsystem" blueprint
		Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			// Assign our mapping context to the aforementioned Subsystem
			Subsystem->AddMappingContext(InputDataAsset->MappingContext, 1);
			Subsystem->AddMappingContext(InputDataAsset->BlankMappingContext, 1);
		}
	}

	CameraBoom->AddRelativeLocation(FVector(0, 0, CameraDataAsset->ZOffset));
	MovementSettingsArray = MovementSettings->GetRowNames();
	AbilitiesArray = AbilitiesSettings->GetRowNames();
	AnimInstance = GetMesh()->GetAnimInstance();
	//TrailNiagaraEffect->Deactivate();
	CurrentMovementType = Walking;
}

// Called every frame
void ANagy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANagy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(InputDataAsset->MoveInputAction, ETriggerEvent::Triggered, this, &ANagy::Move);
		EnhancedInputComponent->BindAction(InputDataAsset->LookInputAction, ETriggerEvent::Triggered, this, &ANagy::Look);
		EnhancedInputComponent->BindAction(InputDataAsset->AttackInputAction, ETriggerEvent::Triggered, this, &ANagy::Attack);
		EnhancedInputComponent->BindAction(InputDataAsset->BlockInputAction, ETriggerEvent::Triggered, this, &ANagy::Block);
		EnhancedInputComponent->BindAction(InputDataAsset->DashInputAction, ETriggerEvent::Started, this, &ANagy::Dash);
		EnhancedInputComponent->BindAction(InputDataAsset->InteractInputAction, ETriggerEvent::Triggered, this, &ANagy::Interact);
		EnhancedInputComponent->BindAction(InputDataAsset->CameraZoomInputAction, ETriggerEvent::Triggered, this, &ANagy::CameraZoom);
		EnhancedInputComponent->BindAction(InputDataAsset->SprintInputAction, ETriggerEvent::Triggered, this, &ANagy::Sprint);
		EnhancedInputComponent->BindAction(InputDataAsset->Test, ETriggerEvent::Triggered, this, &ANagy::Test);
		EnhancedInputComponent->BindAction(InputDataAsset->ChangeWeapon, ETriggerEvent::Triggered, this, &ANagy::ChangeWeapon);
		EnhancedInputComponent->BindAction(InputDataAsset->Spell1, ETriggerEvent::Triggered, this, &ANagy::Spell1);
		EnhancedInputComponent->BindAction(InputDataAsset->Spell2, ETriggerEvent::Triggered, this, &ANagy::Spell2);
	}
}

/* Input Action implementation functions */

void ANagy::Move(const FInputActionValue& Value) {
	// Get the value of our movement, which can be a bool, a float, a FVector2d or FVector (3D)
	const FVector2d DirectionValue = Value.Get<FVector2d>();
	if (GetController()) {
		const FVector Forward = GetActorForwardVector();
		const FVector Sideways = GetActorRightVector();
		FRotator MeshRotator = FollowCamera->GetComponentRotation();
		MeshRotator.Pitch = 0;
		SetActorRotation(MeshRotator);

		AddMovementInput(Forward, DirectionValue.X);
		AddMovementInput(Sideways, DirectionValue.Y);
		if (DirectionValue.X < 0 && CurrentMovementType == Sprinting) {
			TrailNiagaraEffect->Deactivate();
			ModifyCharacterMovement(Walking);
		}
	}
}

void ANagy::Look(const FInputActionValue& Value) {
	const FVector2d LookAxisValue = Value.Get<FVector2d>();
	if (GetController()) {
		// Clamp camera Y axis
		FRotator ClampedRotator = GetController()->GetControlRotation();
		ClampedRotator.Pitch = UKismetMathLibrary::ClampAngle(ClampedRotator.Pitch, 320, 28);
		GetController()->SetControlRotation(ClampedRotator);
	
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(-LookAxisValue.Y);
	}
}

void ANagy::Attack(const FInputActionValue& Value) {
	const bool Attack = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("Attack clicked %d: "), Attack)
	if (PrimaryWeapon.IsValid() && PrimaryWeapon->IsEquipped) {
		AnimInstance->Montage_Play(AnimationDataAsset->UpwardsThrust, 1);
	} else if (SecondaryWeapon.IsValid() && SecondaryWeapon->IsEquipped) {
		AnimInstance->Montage_Play(AnimationDataAsset->Slash, 1);
	}
}

void ANagy::Block() {
	UE_LOG(LogTemp, Warning, TEXT("Block clicked"))
}

void ANagy::Dash() {
	// TODO: Deactivate all inputs other than camera and WASD (to avoid interacting mid dash for example). Prerequisite: learn how to add input modifiers for the WASD input
	if (GetCharacterMovement()->MaxWalkSpeed >= MovementSettings->FindRow<FMovementSetting>(MovementSettingsArray[Sprinting], "", true)->MaxWalkSpeed) {
		DashNiagaraEffect->Activate(); // Activates on the player
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashNiagaraEffect->GetAsset(), GetActorLocation()); // Activates on the initial player position
		ModifyCharacterMovement(Dashing);
		GetMesh()->AnimScriptInstance->GetOwningComponent()->GlobalAnimRateScale = 0.0f;

		const FAbilitiesSettings* AbilitySettings = AbilitiesSettings->FindRow<FAbilitiesSettings>(AbilitiesArray[EAbilities::Dash], "", true);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ANagy::DashAbilityTimerDelegate, 1.0f, false, AbilitySettings->Duration);
	}
}

void ANagy::Interact() {
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, UInteractiveInterface::StaticClass());
	if (!OverlappingActors.IsEmpty()) {
		IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(OverlappingActors[0]);
		if (InteractiveInterface && InteractiveInterface->GetObjectType().Get()->GetClass()->IsChildOf(AWeapon::StaticClass())){
			HandleWeaponInteract(Cast<AWeapon>(InteractiveInterface));
		}
	}
}

void ANagy::CameraZoom(const FInputActionValue& Value) {
	const FVector DirectionValue = Value.Get<FVector>();
    if (GetController()) {
    	if (DirectionValue.X != 0) {
    		const float NewTargetArmLength = CameraBoom->TargetArmLength + (-DirectionValue.X * CameraDataAsset->ZoomStep);
    		const FVector TransformedVector = FVector(0, 0, DirectionValue.X);
		    static const FVector MaxCameraHeight = FVector(0, 0, CameraDataAsset->MaxCameraZoom / 2);
    		static const FVector MinCameraHeight = FVector(0, 0, CameraDataAsset->ZOffset);
    		CameraBoom->SetRelativeLocation(ClampVector(CameraBoom->GetRelativeLocation() + (-TransformedVector * CameraDataAsset->ZoomStep / 2), MinCameraHeight, MaxCameraHeight));
    		CameraBoom->TargetArmLength = FMath::Clamp(NewTargetArmLength, CameraDataAsset->MinCameraZoom, CameraDataAsset->MaxCameraZoom);
    	}
    }
}

void ANagy::Sprint() {
	//TODO: The trail activates when the player is not moving and pressing shift. Add another Idle Movement type and make distinction between walk and idle for this use case
	if (CurrentMovementType != Sprinting) {
		//CameraBoom->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "HeadSocket");
		// TODO: Attaching to HeadSocket when running has issues. Implement a camera shake instead.
		TrailNiagaraEffect->Activate();
		ModifyCharacterMovement(Sprinting);
		CurrentMovementType = Sprinting;
	} else {
		//CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		TrailNiagaraEffect->Deactivate();
		ModifyCharacterMovement(Walking);
		CurrentMovementType = Walking;
	}
}

void ANagy::Test(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Warning, TEXT("Test key pressed"))
}

void ANagy::ChangeWeapon() {
	for (FKey Key : Subsystem->QueryKeysMappedToAction(InputDataAsset->ChangeWeapon)) {
		if (PlayerController->IsInputKeyDown(Key)) {
			// Player wants to equip primary weapon
			if (Key == EKeys::One && PrimaryWeapon.IsValid() && PrimaryWeapon->IsEquipped == false) {
				AnimInstance->Montage_Play(AnimationDataAsset->UnderArmDisarm, 1);
				// Create delegate to notify end of montage
				MontageEndedDelegate.BindUObject(this, &ANagy::UnderArmDisarmEndDelegate, false);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimationDataAsset->UnderArmDisarm);
			} else if (Key == EKeys::Two && SecondaryWeapon.IsValid() && SecondaryWeapon->IsEquipped == false) {
				AnimInstance->Montage_Play(AnimationDataAsset->OverShoulderDisarm, 1);
				// Create delegate to notify end of montage
				MontageEndedDelegate.BindUObject(this, &ANagy::OverShoulderDisarmEndDelegate, false);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimationDataAsset->OverShoulderDisarm);
			}
		}
	}
}

void ANagy::Spell1() {
	AnimInstance->Montage_Play(AnimationDataAsset->Spell1, 1);
}

void ANagy::Spell2() {
	AnimInstance->Montage_Play(AnimationDataAsset->Spell2, 1);
}

/* Delegates */

void ANagy::DashAbilityTimerDelegate() {
	// Set the current movement type
	ModifyCharacterMovement(CurrentMovementType);
	GetMesh()->AnimScriptInstance->GetOwningComponent()->GlobalAnimRateScale = 1.0f;

	const FAbilitiesSettings* AbilitySettings = AbilitiesSettings->FindRow<FAbilitiesSettings>(AbilitiesArray[EAbilities::Dash], "", true);
	InputDataAsset->MappingContext->UnmapKey(InputDataAsset->DashInputAction, EKeys::SpaceBar);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ANagy::DashCooldownTimerDelegate, 1.0f, false, AbilitySettings->Cooldown);
}

void ANagy::DashCooldownTimerDelegate() {
	InputDataAsset->MappingContext->MapKey(InputDataAsset->DashInputAction, EKeys::SpaceBar);
}

void ANagy::InteractMontageEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted) {
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* AttachedActor : AttachedActors) {
		if (AttachedActor->GetClass()->IsChildOf(AWeapon::StaticClass())) {
			AWeapon* Weapon = Cast<AWeapon>(AttachedActor);
			if (Weapon->IsEquipped) {
				EquippedWeapon = Weapon;
			}
			if (Weapon->IsPrimary) {
				PrimaryWeapon = Weapon;
			} else {
				SecondaryWeapon = Weapon;
			}
		}
	}
	
	InputDataAsset->BlankMappingContext->UnmapAll();
	// Return to default Input Mapping Context
	if (Subsystem) {
		Subsystem->AddMappingContext(InputDataAsset->MappingContext, 1);
	}
}

void ANagy::UnderArmDisarmEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted, bool Pickup) {
	if (Pickup) {
		PickUpWeapon();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("must equip main weapon"))
		AnimInstance->Montage_Play(AnimationDataAsset->OverShoulderEquip, 1);
	}
}

void ANagy::OverShoulderDisarmEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted, bool Pickup) {
	if (Pickup) {
		PickUpWeapon();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("must equip secondary weapon"))
		AnimInstance->Montage_Play(AnimationDataAsset->UnderArmEquip, 1);
	}
}

/* Movement handling */

void ANagy::ModifyCharacterMovement(const EMovementType MovementType) const {
	const FMovementSetting* MovementSetting = MovementSettings->FindRow<FMovementSetting>(MovementSettingsArray[MovementType], "", true);
	switch (MovementType) {
		case Walking:
			GetCharacterMovement()->MaxWalkSpeed = MovementSetting->MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = MovementSetting->MaxAcceleration;
			GetCharacterMovement()->GroundFriction = MovementSetting->GroundFriction;
		break;
		case Sprinting:
			GetCharacterMovement()->MaxWalkSpeed = MovementSetting->MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = MovementSetting->MaxAcceleration;
			GetCharacterMovement()->GroundFriction = MovementSetting->GroundFriction;
		break;
		case Dashing:
			GetCharacterMovement()->MaxWalkSpeed = MovementSetting->MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = MovementSetting->MaxAcceleration;
			GetCharacterMovement()->GroundFriction = MovementSetting->GroundFriction;
		break;
	}
}

void ANagy::AddInputMappings(TArray<UInputAction*> InputActionArray) {
	// For each Input Action listed...
	for (UInputAction* InputAction : InputActionArray) {
		TArray<FKey> Keys = Subsystem->QueryKeysMappedToAction(InputAction);
		for (FKey Key : Keys) {
			for (FEnhancedActionKeyMapping MappingContextMappings : InputDataAsset->MappingContext->GetMappings()) {
				if (MappingContextMappings.Key == Key) {
					InputDataAsset->BlankMappingContext->MapKey(InputAction, Key);
					TArray<TObjectPtr<UInputModifier>> Modifiers = InputDataAsset->BlankMappingContext->GetMappings().Last().Modifiers;
					TArray<TObjectPtr<UInputModifier>> Modifiers2 = MappingContextMappings.Modifiers;
					
					//InputDataAsset->BlankMappingContext->GetMappings().Last().Modifiers = MappingContextMappings.Modifiers;
				}
			}
		}

		//TODO: Figure how to create and add input modifiers (to negate and swizzle WASD movement) 
		/*
		// ... find it in the default Input Mapping Context
		for (FEnhancedActionKeyMapping Element : InputDataAsset->MappingContext->GetMappings()) {
			// When found...
			if (InputAction == Element.Action) {
				// ... get all the keys used to trigger the Input Action and add them to the new Input Mapping Context
				TArray<FKey> Keys = Subsystem->QueryKeysMappedToAction(InputAction);
				for (FKey Key : Keys) {
					//AddMappings(InputDataAsset->BlankMappingContext->GetMappings());
					TArray<FEnhancedActionKeyMapping> EnhancedActionKeyMapping = InputDataAsset->BlankMappingContext->GetMappings();
					EnhancedActionKeyMapping.Add(Element);
				}
			}
		}
		*/
	}
}

 /* Weapon handling */

void ANagy::HandleWeaponInteract(const AWeapon* Weapon) {
	if (Weapon->IsPrimary && !PrimaryWeapon.IsValid()) {
		if (SecondaryWeapon.IsValid()) {
			AnimInstance->Montage_Play(AnimationDataAsset->UnderArmDisarm, 1);
			// Create delegate to notify end of montage
			MontageEndedDelegate.BindUObject(this, &ANagy::UnderArmDisarmEndDelegate, true);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimationDataAsset->UnderArmDisarm);
		} else {
			PickUpWeapon();
		}
	} else if (!Weapon->IsPrimary && !SecondaryWeapon.IsValid()) {
		if (PrimaryWeapon.IsValid()) {
			AnimInstance->Montage_Play(AnimationDataAsset->OverShoulderDisarm, 1);
			// Create delegate to notify end of montage
			MontageEndedDelegate.BindUObject(this, &ANagy::OverShoulderDisarmEndDelegate, true);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimationDataAsset->OverShoulderDisarm);
		} else {
			PickUpWeapon();
		}
	}
}

void ANagy::PickUpWeapon() {
	if (CurrentMovementType == Sprinting || CurrentMovementType == Dashing) {
		TrailNiagaraEffect->Deactivate();
		ModifyCharacterMovement(Walking);
	}
	// Create and change to a new Input Mapping Context
	InputDataAsset->BlankMappingContext->MapKey(InputDataAsset->LookInputAction, Subsystem->QueryKeysMappedToAction(InputDataAsset->LookInputAction)[0]);
	InputDataAsset->BlankMappingContext->MapKey(InputDataAsset->CameraZoomInputAction, Subsystem->QueryKeysMappedToAction(InputDataAsset->CameraZoomInputAction)[0]);

	//TODO: Figure how to create and add input modifiers (to negate and swizzle WASD movement) 
	/*
	TArray<UInputAction*> InputActionArray;
	/*InputActionArray.Add(InputDataAsset->LookInputAction);
	InputActionArray.Add(InputDataAsset->CameraZoomInputAction);#1#

	InputActionArray.Add(InputDataAsset->MoveInputAction);
	
	AddMappings(InputActionArray);
	
	InputDataAsset->BlankMappingContext->MapKey(InputDataAsset->MoveInputAction, EKeys::W);
	InputDataAsset->BlankMappingContext->MapKey(InputDataAsset->MoveInputAction, EKeys::S);
	InputDataAsset->BlankMappingContext->MapKey(InputDataAsset->MoveInputAction, EKeys::A);
	InputDataAsset->BlankMappingContext->MapKey(InputDataAsset->MoveInputAction, EKeys::D);

	UInputModifier Modifier;
	Modifier.ModifyRaw(Subsystem->GetPlayerInput(), );
	
	TArray<TObjectPtr<UInputModifier>> Modifiers;
	Modifiers.Add(Modifier);
	InputDataAsset->MoveInputAction->Modifiers = Modifiers;*/
		
	if (Subsystem) {
		Subsystem->RemoveMappingContext(InputDataAsset->MappingContext);
	}

	//InputDataAsset->MappingContext->GetMappings()[0].Action

	UE_LOG(LogTemp, Warning, TEXT("time played: %f"), AnimInstance->Montage_Play(AnimationDataAsset->InteractMontage, 1))

	// Create delegate to notify end of montage
	MontageEndedDelegate.BindUObject(this, &ANagy::InteractMontageEndDelegate);
	AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimationDataAsset->InteractMontage);
}
