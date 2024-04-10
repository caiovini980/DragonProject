// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivationalInteractable.h"
#include "Math/UnrealMathUtility.h"
#include "Lever.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API ALever : public AActivationalInteractable
{
	GENERATED_BODY()

protected:
	// Variables
	UPROPERTY(EditAnywhere, Category = "Setup")
	FQuat InitialRotation { FQuat(0, 0, 0, 0) };

	UPROPERTY(EditAnywhere, Category = "Setup")
	FQuat FinalRotation { FQuat(0, 0, 0, 0) };

	// Methods
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleMovableObject() override;
	
private:
	// Variables
	float ElapsedTime{ 0.0f };
	bool CanLerp{ false };
	bool IsActivated{ false };
};
