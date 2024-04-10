// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Rock.h"
#include "DragonPlayer.h"
#include "GameFramework/Character.h"

ARock::ARock()
{
	this->bIsPortable = true;
}

void ARock::AttachTo(const ACharacter* Character, const FName& SocketName) const
{
	if (Character)
	{
		const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		ItemMesh->AttachToComponent(Character->GetMesh(), TransformRules, SocketName);
	}
}
