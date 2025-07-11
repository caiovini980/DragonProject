// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarriableObject.generated.h"

class UPhysicsConstraintComponent;
class UChildActorComponent;
class UStaticMeshComponent;
class USphereComponent;
class UWidgetComponent;

UCLASS(Blueprintable)
class TPPROJECT_API ACarriableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ACarriableObject();
	virtual ~ACarriableObject() override;

	void BeCarried();
	void BeDropped(const FVector& DroppedPosition);
	
	UStaticMeshComponent* GetActorMesh() const;
	
	bool IsProperlyAttachedTo(AActor* Parent);

	void SetInteractionWidgetVisibility(bool IsVisible);


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* PhysicsConstraint;

	UPROPERTY(EditAnywhere, Category = "Components")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "Utils")
	AActor* PreviousParent;

	UPROPERTY(EditAnywhere, Category = "Utils")
	float CarryOffset{ 0.0f };
};
