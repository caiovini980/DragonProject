// Fill out your copyright notice in the Description page of Project Settings.


#include "CarriableObject.h"

#include "DragonPlayer.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ACarriableObject::ACarriableObject()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetupAttachment(MeshComponent);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(MeshComponent);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// AddToRoot();
}

ACarriableObject::~ACarriableObject()
{
	// RemoveFromRoot();
}

void ACarriableObject::BeCarried(const ACharacter* CarriedBy)
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	GetActorMesh()->SetSimulatePhysics(false);
		
	AttachToComponent(CarriedBy->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CarrySocket"));
}

void ACarriableObject::BeDropped(const FVector& DroppedPosition)
{
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	SetActorLocation(DroppedPosition);

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

// void ACarriableObject::ConnectsTo(AActor* Connector)
// {
// 	if (PreviousParent == Connector)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Object already being carried by this owner"))
// 		return;
// 	}
// #if UE_EDITOR
// 	float itemHeight = MeshComponent->Bounds.GetBox().GetSize().Z;
// 	FVector ConnectorLocation = Connector->GetActorLocation() + FVector(0, 0, CarryOffset + itemHeight);
//
//
// 	UE_LOG(LogTemp, Warning, TEXT("Object Height: %f"), itemHeight)
// #endif
// 	
// 	// MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
// 	// FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::, true);
// 	// AttachToActor(Connector, AttachmentTransformRules, FName("CarrySocket"));
//
// 	this->AttachToComponent(Cast<ADragonPlayer>(Connector)->GetMeshComponent(),
// 		FAttachmentTransformRules::SnapToTargetIncludingScale, FName("CarrySocket"));
//
// 	PreviousParent = Connector;
// }

UStaticMeshComponent* ACarriableObject::GetActorMesh() const
{
	return MeshComponent;
}

