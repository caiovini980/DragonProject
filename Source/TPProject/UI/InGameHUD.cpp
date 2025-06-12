// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "Delegates/Delegate.h"
#include <Components/BackpackComponent.h>

void UInGameHUD::NativeConstruct()
{
	BackpackComponent = GetOwningPlayerPawn()->GetComponentByClass<UBackpackComponent>();// GetPlayerContext().GetPlayerController()->GetPawn()->GetComponentByClass<UBackpackComponent>();

	BackpackComponent.Get()->OnSetMaxBackpackCapacity.AddDynamic(this, &UInGameHUD::SetMaxBackpackCapacity);
	BackpackComponent.Get()->OnItemGrabbed.AddDynamic(this, &UInGameHUD::AddToBackpackCurrentCapacity);
	BackpackComponent.Get()->OnItemDropped.AddDynamic(this, &UInGameHUD::AddToBackpackCurrentCapacity);
}

void UInGameHUD::SetMaxBackpackCapacity(int NewCapacity)
{
	MaxBackpackCapacityText.Get()->SetText(ConvertIntegerToString(NewCapacity));
}

void UInGameHUD::AddToBackpackCurrentCapacity(int ValueToAdd)
{
	CurrentBackpackCapacity += ValueToAdd;
	CurrentBackpackCapacityText.Get()->	SetText(ConvertIntegerToString(CurrentBackpackCapacity));
}

FText UInGameHUD::ConvertIntegerToString(int Input)
{
	return FText(FText::FromString(FString::Printf(TEXT("%d"), Input)));
}
