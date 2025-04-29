// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"

class UPhysicsConstraintComponent;
class ACarriableObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPROJECT_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpackComponent();

	UFUNCTION()
	void AddToBackpack(ACarriableObject* Object);

	UFUNCTION()
	bool RemoveTopItemFromBackpack();

	UFUNCTION()
	ACarriableObject* GetLastCarriedItem();

	UFUNCTION()
	TArray<ACarriableObject*> GetAllCarriedItems();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category="Data")
	TArray<ACarriableObject*> ObjectsCarried;

private:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
