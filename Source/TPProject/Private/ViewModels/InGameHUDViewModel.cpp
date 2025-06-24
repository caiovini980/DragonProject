// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/InGameHUDViewModel.h"
#include "Delegates/Delegate.h"
#include <Components/BackpackComponent.h>

void UInGameHUDViewModel::NativeConstruct()
{
	BackpackComponent = GetOwningPlayerPawn()->GetComponentByClass<UBackpackComponent>();// GetPlayerContext().GetPlayerController()->GetPawn()->GetComponentByClass<UBackpackComponent>();

	BackpackComponent.Get()->OnSetMaxBackpackCapacity.AddDynamic(this, &UInGameHUDViewModel::SetMaxBackpackCapacity);
	BackpackComponent.Get()->OnItemGrabbed.AddDynamic(this, &UInGameHUDViewModel::AddToBackpackCurrentCapacity);
	BackpackComponent.Get()->OnItemDropped.AddDynamic(this, &UInGameHUDViewModel::AddToBackpackCurrentCapacity);
}

void UInGameHUDViewModel::SetMaxBackpackCapacity(int NewCapacity)
{
	MaxBackpackCapacityText.Get()->SetText(ConvertIntegerToString(NewCapacity));
}

void UInGameHUDViewModel::AddToBackpackCurrentCapacity(int ValueToAdd)
{
	CurrentBackpackCapacity += ValueToAdd;
	CurrentBackpackCapacityText.Get()->	SetText(ConvertIntegerToString(CurrentBackpackCapacity));
}

FText UInGameHUDViewModel::ConvertIntegerToString(int Input)
{
	return FText(FText::FromString(FString::Printf(TEXT("%d"), Input)));
}
