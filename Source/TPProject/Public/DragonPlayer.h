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

	bool CanCarryMoreItems() const;

	UFUNCTION(BlueprintCallable)
	int32 GetMaxBackpackCapacity() const;
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentBackpackCapacity() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnGrabObject();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDropObject();

protected:
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// EVENTS
	UFUNCTION(BlueprintNativeEvent)
	void OnDropAllObjects();
	

	// VARIABLES
	
	
	// COMPONENTS
	UPROPERTY(BlueprintReadOnly, Category="Components")
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* CameraArm;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	UPhysicsConstraintComponent* PhysicsConstraintComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
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
