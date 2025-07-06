// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BackpackComponent.h"

#include "CarriableObject.h"

UBackpackComponent::UBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBackpackComponent::OnSetMaxBackpackCapacity_Implementation(int32 Amount)
{
}


void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();
	OnSetMaxBackpackCapacity(MaxCapacity);
}


// Called every frame
void UBackpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBackpackComponent::TryAddObjectToBackpack(ACarriableObject* ObjectToCarry, AActor* Owner)
{
	if(ObjectsCarried.Contains(ObjectToCarry) || bReachedMaxCapacity)
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
	bReachedMaxCapacity = ObjectsCarried.Num() >= MaxCapacity;

	// ViewModel->SetCurrentBackpackCapacity(GetAllCarriedItems().Num());
	
	// OnItemGrabbed.Broadcast(1); // TODO - Magic number
	// OnItemGrabbed();

	return true;
}

bool UBackpackComponent::TryRemoveTopItemFromBackpack(AActor* Owner)
{
	if (ACarriableObject* LastCarriedItem = GetLastCarriedItem())
	{
		LastCarriedItem->BeDropped(Owner->GetActorLocation() + DropPositionOffset);
		LastCarriedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ObjectsCarried.Pop(); 
		// OnItemDropped.Broadcast(-1); // TODO - Magic number
		// OnItemDropped();
		bReachedMaxCapacity = false;
		return true;
	}

	return false;
}

bool UBackpackComponent::HasReachedMaxCapacity() const
{
	return bReachedMaxCapacity;
}

int32 UBackpackComponent::GetMaxCapacity() const
{
	return MaxCapacity;
}

int32 UBackpackComponent::GetCurrentCapacity() const
{
	return ObjectsCarried.Num();
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

