// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarriableObject.generated.h"

class UPhysicsConstraintComponent;
class UChildActorComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS(Blueprintable)
class TPPROJECT_API ACarriableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ACarriableObject();

	// void ConnectsTo(AActor* Connector);
	void Disconnects();

	UStaticMesh* GetActorMesh() const;
	
	bool IsProperlyAttachedTo(AActor* Parent);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* PhysicsConstraint;

	UPROPERTY(VisibleAnywhere, Category = "Utils")
	AActor* PreviousParent;

	UPROPERTY(EditAnywhere, Category = "Utils")
	float CarryOffset{0.0f};
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
