// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BackpackComponent.h"

// Sets default values for this component's properties
UBackpackComponent::UBackpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UBackpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBackpackComponent::AddToBackpack(ACarriableObject* ObjectToCarry)
{
	if(ObjectsCarried.Contains(ObjectToCarry))
	{
		return;
	}
	
	ObjectsCarried.Push(ObjectToCarry);
}

bool UBackpackComponent::HasRemovedTopItemFromBackpack()
{
	if (ObjectsCarried.Num() <= 0)
	{
		return false;
	}

	ObjectsCarried.Pop();
	return true;
}

// TSubclassOf<AActor> UBackpackComponent::GetNextCarriedItem()
ACarriableObject* UBackpackComponent::GetLastCarriedItem()
{
	if (ObjectsCarried.IsEmpty())
	{
		return nullptr;	
	}
	
	return ObjectsCarried.Top();
}

TArray<ACarriableObject*> UBackpackComponent::GetAllCarriedItems()
{
	return ObjectsCarried;
}

