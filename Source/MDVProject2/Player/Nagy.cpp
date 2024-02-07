// Fill out your copyright notice in the Description page of Project Settings.


#include "Nagy.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MDVProject2/Objects/Weapons/Weapon.h"
#include "MDVProject2/Utils/DataStructures.h"
#include "MDVProject2/Utils/InteractiveObject.h"

// Sets default values
ANagy::ANagy() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Auto Posses for this Character
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	InitComponents();
}

void ANagy::InitComponents() {
	// Initialize the Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetMesh(), "HeadSocket");
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 200;

	// Initialize the Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetArrowComponent()->bHiddenInGame = false;
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

	MyReferenceManager = Cast<AMyReferenceManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyReferenceManager::StaticClass()));
	AnimInstance = GetMesh()->GetAnimInstance();
	CharMovementFirstChange = false;
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
		EnhancedInputComponent->BindAction(InputDataAsset->DashInputAction, ETriggerEvent::Triggered, this, &ANagy::Dash);
		EnhancedInputComponent->BindAction(InputDataAsset->InteractInputAction, ETriggerEvent::Triggered, this, &ANagy::Interact);
		EnhancedInputComponent->BindAction(InputDataAsset->CameraZoomInputAction, ETriggerEvent::Triggered, this, &ANagy::CameraZoom);
		EnhancedInputComponent->BindAction(InputDataAsset->SprintInputAction, ETriggerEvent::Triggered, this, &ANagy::Sprint);
		EnhancedInputComponent->BindAction(InputDataAsset->Test, ETriggerEvent::Triggered, this, &ANagy::Test);
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
}

void ANagy::Block(const FInputActionValue& Value) {
	const bool Block = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("Block clicked: %d"), Block)
}

void ANagy::Dash(const FInputActionValue& Value) {
	if (GetCharacterMovement()->MaxWalkSpeed >= 750) {
		ModifyCharacterMovement(Dashing);
		GetMesh()->AnimScriptInstance->GetOwningComponent()->GlobalAnimRateScale = 0.0f;
		FTimerHandle MemberTimerHandle;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ANagy::DashTimerDelegate, 1.0f, false, .07f);
	}
}

void ANagy::Interact(const FInputActionValue& Value) {
	const bool InteractPressed = Value.Get<bool>();

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, UInteractiveInterface::StaticClass());

	if (!OverlappingActors.IsEmpty() && InteractPressed) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap"))
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
		CompleteDelegate.BindUObject(this, &ANagy::MontageEndDelegate);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(CompleteDelegate, AnimationDataAsset->InteractMontage);
	}
}

void ANagy::CameraZoom(const FInputActionValue& Value) {
	const FVector DirectionValue = Value.Get<FVector>();
    if (GetController()) {
    	if (DirectionValue.X != 0) {
    		const float NewTargetArmLength = CameraBoom->TargetArmLength + (-DirectionValue.X * CameraZoomDataAsset->ZoomStep);
    		const FVector TransformedVector = FVector(0, 0, DirectionValue.X);
		    static const FVector MaxCameraHeight = FVector(0, 0, CameraZoomDataAsset->MaxCameraZoom/2);
    		static const FVector MinCameraHeight = FVector(0, 0, CameraZoomDataAsset->MinCameraZoom);
    		CameraBoom->SetRelativeLocation(ClampVector(CameraBoom->GetRelativeLocation() + (-TransformedVector * CameraZoomDataAsset->ZoomStep / 2), MinCameraHeight, MaxCameraHeight));
    		CameraBoom->TargetArmLength = FMath::Clamp(NewTargetArmLength, CameraZoomDataAsset->MinCameraZoom, CameraZoomDataAsset->MaxCameraZoom);
    	}
    }
}

void ANagy::Sprint(const FInputActionValue& Value) {
	if (Value.Get<bool>() && !CharMovementFirstChange) {
		ModifyCharacterMovement(Sprinting);
		CharMovementFirstChange = true;
		CurrentMovementType = Sprinting;
	} 
	if (!Value.Get<bool>()) {
		ModifyCharacterMovement(Walking);
		CharMovementFirstChange = false;
		CurrentMovementType = Walking;
	}
}

void ANagy::Test(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Warning, TEXT("Test key pressed"))
}

/* Delegates */

void ANagy::DashTimerDelegate() {
	InputDataAsset->BlankMappingContext->UnmapAll();
	// Return to default Input Mapping Context
	if (Subsystem) {
		Subsystem->AddMappingContext(InputDataAsset->MappingContext, 1);
	}
	// Set the current movement type
	ModifyCharacterMovement(CurrentMovementType);
	GetMesh()->AnimScriptInstance->GetOwningComponent()->GlobalAnimRateScale = 1.0f;
}

void ANagy::MontageEndDelegate(UAnimMontage* AnimMontage, bool bInterrupted) {
	UE_LOG(LogTemp, Warning, TEXT("Montage completed!"))
	if (AnimMontage == AnimationDataAsset->InteractMontage) {
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors, UInteractiveInterface::StaticClass());
		EquippedWeapon = Cast<AWeapon>(OverlappingActors[0]);
	}

	InputDataAsset->BlankMappingContext->UnmapAll();
	// Return to default Input Mapping Context
	if (Subsystem) {
		Subsystem->AddMappingContext(InputDataAsset->MappingContext, 1);
	}
}

/* Movement handling */

void ANagy::ModifyCharacterMovement(const EMovementType MovementType) const {
	switch (MovementType) {
		case Walking:
			UE_LOG(LogTemp, Warning, TEXT("Walking"))
			GetCharacterMovement()->MaxWalkSpeed = 250;
			GetCharacterMovement()->MaxAcceleration = 2048;
			GetCharacterMovement()->GroundFriction = 8;
		break;
		case Sprinting:
			UE_LOG(LogTemp, Warning, TEXT("Sprinting"))
			GetCharacterMovement()->MaxWalkSpeed = 750;
			GetCharacterMovement()->MaxAcceleration = 2048;
			GetCharacterMovement()->GroundFriction = 8;
		break;
		case Dashing:
			UE_LOG(LogTemp, Warning, TEXT("Dashing"))
			GetCharacterMovement()->MaxWalkSpeed = 100000;
			GetCharacterMovement()->MaxAcceleration = 100000;
			GetCharacterMovement()->GroundFriction = 100;
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
		/*// ... find it in the default Input Mapping Context
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
		}*/
	}
}