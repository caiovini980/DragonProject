// Fill out your copyright notice in the Description page of Project Settings.


#include "CarriableObject.h"

#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/WidgetComponent.h"
#include "DragonPlayer.h"

#include <Kismet/GameplayStatics.h>

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

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InetractionWidget"));
	WidgetComponent->SetupAttachment(MeshComponent);
	
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

	GetActorMesh()->SetSimulatePhysics(true);
}

void ACarriableObject::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACarriableObject::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACarriableObject::OnOverlapEnd);

	WidgetComponent->SetVisibility(false);
}

void ACarriableObject::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ADragonPlayer* Player = Cast<ADragonPlayer>(OtherActor))
	{
		if (Player->CanCarryMoreItems())
		{
			WidgetComponent->SetVisibility(true);
		}
	}
}

void ACarriableObject::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		WidgetComponent->SetVisibility(false);
	}
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

void ACarriableObject::SetInteractionWidgetVisibility(bool IsVisible)
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(IsVisible);
	}
}

UStaticMeshComponent* ACarriableObject::GetActorMesh() const
{
	return MeshComponent;
}

