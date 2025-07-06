// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonPlayer.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/Vector.h"

#include "Animation/AnimMontage.h"

#include "Camera/CameraComponent.h"
#include "Components/AttributeComponent.h"
#include "Components/BackpackComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "CarriableObject.h"

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

	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("Backpack"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComponent"));
	PlayerAttributes = CreateDefaultSubobject<UPlayerAttributes>(TEXT("PlayerAttributes"));

	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetComponentByClass(UCharacterMovementComponent::StaticClass()));
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

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ADragonPlayer::CarryObject(ACarriableObject* objectToCarry)
{
	if (!BackpackComponent->TryAddObjectToBackpack(objectToCarry, this))
	{
		return; 
	}

	OnGrabObject();
	CharacterMovementComponent->MaxWalkSpeed = PlayerAttributes->Speed.GetCurrentValue();
}

void ADragonPlayer::ThrowObject(ACarriableObject* objectToThrow)
{
	if (!BackpackComponent->TryRemoveTopItemFromBackpack(this))
	{
		return;
	}

	if (!BackpackComponent->GetLastCarriedItem())
	{
		OnDropAllObjects();
	}

	OnDropObject();
	CharacterMovementComponent->MaxWalkSpeed = PlayerAttributes->Speed.GetCurrentValue();
}

// Inputs
void ADragonPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	float XMovementPercent = MovementVector.X;
	float YMovementPercent = MovementVector.Y;

	HandleJoystickInput(MovementVector, XMovementPercent, YMovementPercent);
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, YMovementPercent);
	AddMovementInput(Right, XMovementPercent);
}

void ADragonPlayer::HandleJoystickInput(const FVector2D& MovementVector, float& XMovementPercent, float& YMovementPercent) const
{
	if (FMath::Abs(MovementVector.X) > 1)
	{
		XMovementPercent = MovementVector.X / 100;
	}

	if (FMath::Abs(MovementVector.Y) > 1)
	{
		YMovementPercent = MovementVector.Y / 100;
	}

	// handle running threshold on joystick
	if (FMath::Abs(XMovementPercent) >= RunningThreshold)
	{
		XMovementPercent = MovementVector.X;
	}

	if (FMath::Abs(YMovementPercent) >= RunningThreshold)
	{
		YMovementPercent = MovementVector.Y;
	}
}

void ADragonPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D lookVector = Value.Get<FVector2D>();

	AddControllerPitchInput(lookVector.Y);
	AddControllerYawInput(lookVector.X);
}

void ADragonPlayer::ExecuteJump(const FInputActionValue& Value)
{
	if (Super::IsJumpProvidingForce())
	{
		UE_LOG(LogTemp, Warning, TEXT("Stop jump"));
		Super::StopJumping();
		return;
	}

	if (CharacterMovementComponent->IsMovingOnGround())
	UE_LOG(LogTemp, Warning, TEXT("Started jump"));
	Super::Jump();
}

void ADragonPlayer::HandleInteractTriggered(const FInputActionValue& Value)
{
	if (!BackpackComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Backpack Component is NULL on DragonPlayer.cpp"));
		return;
	}

	if (!BackpackComponent->HasReachedMaxCapacity())
	{
		if (ACarriableObject* CarriableObject = TryGetCarriableObject())
		{
			CarryObject(CarriableObject);
			return;
		}
	}

	if (ACarriableObject* LastCarriedItem = BackpackComponent->GetLastCarriedItem())
	{
		ThrowObject(LastCarriedItem);
	}
}

void ADragonPlayer::Attack(const FInputActionValue& Value)
{
	if (bCanAttack)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		
		if (AnimInstance && AttackMontage && CharacterMovementComponent)
		{
			AnimInstance->Montage_Play(AttackMontage);
			AnimInstance->Montage_JumpToSection(FName("Attack1"), AttackMontage);
		}
	}
}

ACarriableObject* ADragonPlayer::TryGetCarriableObject() const
{
	TArray<AActor*> OverlappingActors;
	GetMesh()->GetOverlappingActors(OverlappingActors);
	
	// carry first overlapping object
	for (const auto& Actor : OverlappingActors)
	{
		if (ACarriableObject* CarriableObject = Cast<ACarriableObject>(Actor))
		{
			return CarriableObject;
		}
	}

	return nullptr;
}

UAbilitySystemComponent* ADragonPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool ADragonPlayer::CanCarryMoreItems() const
{
	return !BackpackComponent->HasReachedMaxCapacity();
}

int32 ADragonPlayer::GetMaxBackpackCapacity() const
{
	return BackpackComponent->GetMaxCapacity();
}

int32 ADragonPlayer::GetCurrentBackpackCapacity() const
{
	return BackpackComponent->GetCurrentCapacity();
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

		// ATTACK
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADragonPlayer::Attack);
		
		// CARRY
		EnhancedInputComponent->BindAction(CarryAction, ETriggerEvent::Triggered, this, &ADragonPlayer::HandleInteractTriggered);
	}
	/**/
}

void ADragonPlayer::OnGrabObject_Implementation() {}

void ADragonPlayer::OnDropAllObjects_Implementation() {}
void ADragonPlayer::OnDropObject_Implementation() {}