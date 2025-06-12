// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BackpackComponent.h"

#include "CarriableObject.h"

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

bool UBackpackComponent::TryAddObjectToBackpack(ACarriableObject* ObjectToCarry, AActor* Owner)
{
	if(ObjectsCarried.Contains(ObjectToCarry) || ObjectsCarried.Num() >= MaxCapacity)
	{
		return false;
	}
	
	ObjectToCarry->BeCarried();
	if (ACarriableObject* LastCarriedItem = GetLastCarriedItem())
	{
		ObjectToCarry->AttachToComponent(LastCarriedItem->GetActorMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("UpSocket"));
		ObjectToCarry->SetActorRelativeLocation(CarryPositionOffset);
	}
	else
	{
		ObjectToCarry->AttachToComponent(Owner->GetComponentByClass<USkeletalMeshComponent>(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CarrySocket"));
	}

	ObjectsCarried.Push(ObjectToCarry);
	return true;
}

bool UBackpackComponent::TryRemoveTopItemFromBackpack(AActor* Owner)
{
	if (ACarriableObject* LastCarriedItem = GetLastCarriedItem())
	{
		LastCarriedItem->BeDropped(Owner->GetActorLocation() + DropPositionOffset);
		LastCarriedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		//LastCarriedItem->SetActorLocation(Owner->GetActorForwardVector() + DropPositionOffset);
		ObjectsCarried.Pop();
		return true;
	}

	return false;
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

