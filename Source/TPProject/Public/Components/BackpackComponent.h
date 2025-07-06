// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/Delegate.h"
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
	
	UFUNCTION(BlueprintNativeEvent)
	void OnSetMaxBackpackCapacity(int32 Amount);

	UFUNCTION()
	bool TryAddObjectToBackpack(ACarriableObject* Object, AActor* Owner);

	UFUNCTION()
	bool TryRemoveTopItemFromBackpack(AActor* Owner);

	UFUNCTION()
	ACarriableObject* GetLastCarriedItem();

	UFUNCTION()
	TArray<ACarriableObject*> GetAllCarriedItems();
	
	bool HasReachedMaxCapacity() const;

	UFUNCTION(BlueprintCallable)
	int32 GetMaxCapacity() const;
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentCapacity() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category="Data")
	TArray<ACarriableObject*> ObjectsCarried;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxCapacity{ 2 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector DropPositionOffset{ FVector(100.f, 0.f, 0.f) };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector CarryPositionOffset{ FVector(0, -20.f, 0.f) }; // Dragon TODO: This isn't working properly

private:
	UPROPERTY(VisibleAnywhere) 
	bool bReachedMaxCapacity{ false };

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
