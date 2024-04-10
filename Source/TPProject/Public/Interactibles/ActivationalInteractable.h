// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactibles/InteractibleBase.h"
#include "ActivationalInteractable.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API AActivationalInteractable : public AInteractibleBase
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	AActivationalInteractable();

protected:
	// Components
	UPROPERTY()
	UStaticMeshComponent* MovableMesh {};
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AnimationDuration{ 0.0f };

	// Methods
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Setup(UStaticMeshComponent* MovableStaticMesh);

	virtual void ToggleMovableObject();
	
private:
	// Variables
	float ElapsedTime{ 0.0f };
	bool bCanLerp{ false };
	bool bIsActivated{ false };

	virtual void ToggleInteractionWidget(bool isPlayerNear) override;
};
