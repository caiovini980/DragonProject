// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/GrabbableInteractable.h"

AGrabbableInteractable::AGrabbableInteractable()
{
	InteractableType = EInteractableType::EIT_Grabbable;
}

void AGrabbableInteractable::Interact()
{
	Super::Interact();
}

void AGrabbableInteractable::ToggleInteractionWidget(bool isPlayerNear)
{
	if (bIsActivated) { return; }
	Super::ToggleInteractionWidget(isPlayerNear);
}
