// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerAttributes.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

#include "DragonPlayer.generated.h"

class ACarriableObject;
class UBackpackComponent;
class UPhysicsConstraintComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerAttributes;
class UAnimMontage;

class UAttributeComponent;

UCLASS()
class TPPROJECT_API ADragonPlayer : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADragonPlayer();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// EVENTS
	UFUNCTION(BlueprintNativeEvent)
	void OnGrabObject();

	UFUNCTION(BlueprintNativeEvent)
	void OnDropObject();

	// METHODS
	UFUNCTION(BlueprintCallable)
	void SetSpeed(float NewSpeed);

	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector DropPositionOffset{ FVector(200.f, 100.f, 0.f) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector CarryPositionOffset{ FVector(160.f, -43.f, 0.f) }; // Dragon TODO: This isn't working properly
	
	// COMPONENTS
	UPROPERTY(BlueprintReadOnly, Category="Components")
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* CameraArm;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	UPhysicsConstraintComponent* PhysicsConstraintComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBackpackComponent* BackpackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPlayerAttributes* PlayerAttributes;

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<AActor> ActorToSpawn;
	
	// INPUTS
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CarryAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

private:
	// VARIABLES
	UPROPERTY(VisibleAnywhere, Category = "Joystick")
	float RunningThreshold{ 0.85 };
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsJumping{ false };

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool bCanAttack{ true };

	UPROPERTY(EditAnywhere, Category = "Interact")
	float DistanceToInteract{ 0 };

	// ANIMATION MONTAGES
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackMontage;
	
	// METHODS
	void HandleJoystickInput(const FVector2D& MovementVector, float& XMovementPercent, float& YMovementPercent) const;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ExecuteJump(const FInputActionValue& Value);
	void HandleInteractTriggered(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);

	void CarryObject(ACarriableObject* objectToCarry);
	void ThrowObject(ACarriableObject* objectToThrow);
	
	ACarriableObject* TryGetCarriableObject() const;
};
