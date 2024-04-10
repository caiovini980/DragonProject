// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/IInteractable.h"
#include "DragonPlayer.generated.h"

class UPhysicsConstraintComponent;
class UCharacterMovementComponent;
class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;
class UAnimMontage;

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

	// VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool IsHoldingObject{ false };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector HoldPositionOffset{ FVector(50.f, 0.f, 0.f) };
	
	// COMPONENTS
	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* PlayerCamera;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraArm;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* HoldObjectPosition;
	UPROPERTY(VisibleDefaultsOnly)
	UPhysicsConstraintComponent* PhysicsConstraintComponent;

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
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

private:
	// VARIABLES
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed{ 0 };

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed{ 0 };

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
	void HandleInteraction();
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void ExecuteJump(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
};
