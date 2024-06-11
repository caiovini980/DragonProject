// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPROJECT_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float WalkSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float RunSpeed;
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	// float JumpForce;

public:
	// Health
	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(float Delta);

	// Speed
	UFUNCTION(Category="Attributes")
	float GetWalkSpeed() const;

	UFUNCTION(Category="Attributes")
	float GetRunSpeed() const;

	// Jump
	// UFUNCTION(Category="Attributes")
	// float GetJumpForce() const;
};
