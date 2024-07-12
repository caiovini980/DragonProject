// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonPlayer.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/Quat.h"
#include "Math/Vector.h"

#include "Animation/AnimMontage.h"

#include "Camera/CameraComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactibles/InteractibleBase.h"

/**/
// Sets default values
ADragonPlayer::ADragonPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// EARLY SETUP
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetGenerateOverlapEvents(true);

	// CREATE SUBOBJECTS
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 500.f;
	CameraArm->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->bInheritPitch = true;
	CameraArm->bInheritYaw = true;
	CameraArm->bInheritRoll = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(CameraArm);

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetComponentByClass(UCharacterMovementComponent::StaticClass()));

	/**/
}

// Called when the game starts or when spawned
void ADragonPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ADragonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADragonPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);
}

void ADragonPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D lookVector = Value.Get<FVector2D>();

	AddControllerPitchInput(lookVector.Y);
	AddControllerYawInput(lookVector.X);
}

void ADragonPlayer::Run(const FInputActionValue& Value)
{
	// if (const bool IsRunning = Value.Get<bool>())
	// {
	// 	GetCharacterMovement()->MaxWalkSpeed = AttributeComponent->GetWalkSpeed();
	// 	return;
	// }
	//
	// GetCharacterMovement()->MaxWalkSpeed = AttributeComponent->GetRunSpeed();
}

void ADragonPlayer::ExecuteJump(const FInputActionValue& Value)
{
	if (Super::IsJumpProvidingForce())
	{
		UE_LOG(LogTemp, Warning, TEXT("Stop jump"));
		Super::StopJumping();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Started jump"));
	Super::Jump();
}

void ADragonPlayer::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACT INPUT PRESSED"));
	
	if (IsHoldingObject)
	{
		IsHoldingObject = false;
		return;
	}
	
	HandleInteraction();
}

void ADragonPlayer::Attack(const FInputActionValue& Value)
{
	if (bCanAttack)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		
		if (AnimInstance && AttackMontage && CharacterMovementComponent)
		{
			CharacterMovementComponent->MaxWalkSpeed = AttributeComponent->GetWalkSpeed();
			AnimInstance->Montage_Play(AttackMontage);
			AnimInstance->Montage_JumpToSection(FName("Attack1"), AttackMontage);
		}
	}
}

void ADragonPlayer::HandleInteraction()
{
	// I can just get the overlapping items
	// search for the interface on each one of them
	// activate the interface whenever we press INTERACT
	TArray<AActor*> OverlappingActors;
	GetMesh()->GetOverlappingActors(OverlappingActors);

	for (const auto OverlappingActor : OverlappingActors)
	{
		AInteractibleBase* Interactable{ Cast<AInteractibleBase>(OverlappingActor) };
		if (!Interactable) { return; }

		if (Interactable->GetInteractableType() == EInteractableType::EIT_Grabbable)
		{
			// HOLD ITEM
			IsHoldingObject = true;
		}
			
		else if (Interactable->GetInteractableType() == EInteractableType::EIT_Activable)
		{
			// ACTIVATE ITEM
		}

		else if (Interactable->GetInteractableType() == EInteractableType::EIT_Movable)
		{
			// MOVE ITEM
		}

		else if (Interactable->GetInteractableType() == EInteractableType::EIT_Pressable)
		{
			// PRESS ITEM
		}

		Interactable->Interact();
		break;
	}
}

// Called every frame
void ADragonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADragonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// MOVE
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADragonPlayer::Move);

		// LOOK
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADragonPlayer::Look);

		// JUMP
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADragonPlayer::ExecuteJump);

		// RUN
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ADragonPlayer::Run);

		// ATTACK
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADragonPlayer::Attack);

		// INTERACT
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADragonPlayer::Interact);
	}
	/**/
}


