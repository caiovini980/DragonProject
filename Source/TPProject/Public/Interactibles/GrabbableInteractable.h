// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactibles/InteractibleBase.h"
#include "GrabbableInteractable.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API AGrabbableInteractable : public AInteractibleBase
{
	GENERATED_BODY()
public:
	AGrabbableInteractable();
	
protected:
	// Overrides
	virtual void Interact() override;
	virtual void ToggleInteractionWidget(bool isPlayerNear) override;

private:
	//Variables
	bool bIsActivated{ false };
};
