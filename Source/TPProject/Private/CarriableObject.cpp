// Fill out your copyright notice in the Description page of Project Settings.


#include "CarriableObject.h"

#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ACarriableObject::ACarriableObject()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	RootComponent = MeshComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetupAttachment(MeshComponent);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(MeshComponent);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// AddToRoot();
}

ACarriableObject::~ACarriableObject()
{
	// RemoveFromRoot();
}

void ACarriableObject::BeCarried()
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	GetActorMesh()->SetSimulatePhysics(false);
}

void ACarriableObject::BeDropped(const FVector& DroppedPosition)
{
	SetActorLocation(DroppedPosition);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	// enable physics only on MeshComponent
	for (UActorComponent* Component : GetComponents())
	{
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Component))
		{
			MeshComp->SetSimulatePhysics(true);
		}
	}

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ACarriableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACarriableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACarriableObject::IsProperlyAttachedTo(AActor* Parent)
{
	if (IsAttachedTo(Parent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Object already attached to this parent."))
		return false;	
	}
	
	return true;
}

UStaticMeshComponent* ACarriableObject::GetActorMesh() const
{
	return MeshComponent;
}

