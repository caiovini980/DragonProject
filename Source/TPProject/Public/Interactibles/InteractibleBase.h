// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/IInteractable.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "InteractibleBase.generated.h"

UCLASS()
class TPPROJECT_API AInteractibleBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	AInteractibleBase();
	
	// OVERRIDES
	virtual void Interact() override;

protected:
	// OVERRIDES
	virtual void BeginPlay() override;

	// PROPERTIES
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider{};	// Get overlaps

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* InteractibleMesh{};	// Object mesh

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool IsPlayerOnRange{ false };
	
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent{};

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	EInteractableType InteractableType { EInteractableType::EIT_Default };

	// FUNCTIONS
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxExitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void TogglePlayerOnRange(bool isOnRange);
	
	UFUNCTION(BlueprintCallable)
	virtual void ToggleInteractionWidget(bool isPlayerNear);

public:
	bool CanBeCarried() const { return bIsPortable; }
	EInteractableType GetInteractableType() const { return InteractableType; }
};
