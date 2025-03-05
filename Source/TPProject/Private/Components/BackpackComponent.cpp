// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BackpackComponent.h"

// Sets default values for this component's properties
UBackpackComponent::UBackpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UBackpackComponent::CorrectlyAddedToBackpack(AActor* Object)
{
	if(ObjectsCarried.Contains(Object))
	{
		UE_LOG(LogTemp, Warning, TEXT("Object already on the backpack."))
		return false;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Adding object to the backpack."))
	ObjectsCarried.Push(Object);
	return true;
}

bool UBackpackComponent::RemoveFromBackpack()
{
	if (ObjectsCarried.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("There are no objects on the backpack."))
		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Removing object to the backpack."))
	ObjectsCarried.Pop();
	return true;
}

// TSubclassOf<AActor> UBackpackComponent::GetNextCarriedItem()
AActor* UBackpackComponent::GetNextCarriedItem()
{
	if (ObjectsCarried.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("Objects carried is null!"))
		return nullptr;	
	}
	
	for (auto& Item : TypeOfObjectsToSpawn)
	{
		if (Item == ObjectsCarried.Top()->GetClass())
		{
			return ObjectsCarried.Top();
		}
	}

	return nullptr;
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

