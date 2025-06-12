// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/Delegate.h"
#include "BackpackComponent.generated.h"

class UPhysicsConstraintComponent;
class ACarriableObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemGrabbed, int, AmountGrabbed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDropped, int, AmountDropped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetMaxBackpackCapacity, int, MaxBackpackCapacity);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPROJECT_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpackComponent();

	FOnItemGrabbed OnItemGrabbed;
	FOnItemDropped OnItemDropped;
	FOnSetMaxBackpackCapacity OnSetMaxBackpackCapacity;

	UFUNCTION()
	bool TryAddObjectToBackpack(ACarriableObject* Object, AActor* Owner);

	UFUNCTION()
	bool TryRemoveTopItemFromBackpack(AActor* Owner);

	UFUNCTION()
	ACarriableObject* GetLastCarriedItem();

	UFUNCTION()
	TArray<ACarriableObject*> GetAllCarriedItems();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category="Data")
	TArray<ACarriableObject*> ObjectsCarried;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxCapacity{ 2 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector DropPositionOffset{ FVector(100.f, 0.f, 0.f) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector CarryPositionOffset{ FVector(0, -20.f, 0.f) }; // Dragon TODO: This isn't working properly

private:

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
