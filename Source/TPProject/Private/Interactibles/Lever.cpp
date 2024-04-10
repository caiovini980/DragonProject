// Fill out your copyright notice in the Description page of Project Settings.
#include "Interactibles/Lever.h"

void ALever::Tick(float DeltaTime)
{
	if (!CanLerp) { return; }

	if (ElapsedTime < AnimationDuration)
	{
		if (MovableMesh)
		{
			MovableMesh->SetRelativeRotation(
				FMath::Lerp<FQuat>(InitialRotation, FinalRotation, ElapsedTime / AnimationDuration)
			);
		}
		
		// Keep track of elapsed time
		ElapsedTime += DeltaTime;
	}
	else
	{
		CanLerp = false;
	}
}

void ALever::ToggleMovableObject()
{
	Super::ToggleMovableObject();
	CanLerp = true;
}

