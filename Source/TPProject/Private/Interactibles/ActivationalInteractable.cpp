// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/ActivationalInteractable.h"

AActivationalInteractable::AActivationalInteractable()
{
	InteractableType = EInteractableType::EIT_Activable;
}

void AActivationalInteractable::Setup(UStaticMeshComponent* MovableStaticMesh)
{
	MovableMesh = MovableStaticMesh;
}

void AActivationalInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActivationalInteractable::Interact()
{
	Super::Interact();

	if (!bIsActivated)
	{
		// hide widget
		ToggleInteractionWidget(false);
		// disable collision
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ToggleMovableObject();
		// play SFX
		// change lights color
		bIsActivated = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interactible already activated!"));
	}
}

void AActivationalInteractable::ToggleInteractionWidget(bool isPlayerNear)
{
	if (bIsActivated) { return; }
	Super::ToggleInteractionWidget(isPlayerNear);
}

void AActivationalInteractable::ToggleMovableObject()
{}
