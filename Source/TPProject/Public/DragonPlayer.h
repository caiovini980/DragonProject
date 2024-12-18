// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DragonPlayer.generated.h"

class ACarriableObject;
class UBackpackComponent;
class UPhysicsConstraintComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

class UAttributeComponent;

UCLASS()
class TPPROJECT_API ADragonPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ADragonPlayer();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector HoldPositionOffset{ FVector(50.f, 0.f, 0.f) };
	
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
	UAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBackpackComponent* BackpackComponent;
	
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
	// void Interact(const FInputActionValue& Value); TODO Refactor this
	void CarryObject(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);

	void CarryObject(ACarriableObject* objectToCarry) const;
};
