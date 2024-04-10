// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/InteractibleBase.h"

// Sets default values
AInteractibleBase::AInteractibleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = InteractibleMesh;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollider"));
	BoxCollider->SetupAttachment(GetRootComponent());

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AInteractibleBase::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AInteractibleBase::OnBoxOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AInteractibleBase::OnBoxExitOverlap);
}

void AInteractibleBase::OnBoxOverlap(UPrimitiveComponent* OverlapComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player ENTERED the interactible area"));
}

void AInteractibleBase::OnBoxExitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Player EXITED the interactible area"));
}

void AInteractibleBase::TogglePlayerOnRange(bool isOnRange)
{
	UE_LOG(LogTemp, Warning, TEXT("Toggle Player On Range"));
	IsPlayerOnRange = isOnRange;
}

void AInteractibleBase::ToggleInteractionWidget(bool isPlayerNear)
{
	UE_LOG(LogTemp, Warning, TEXT("Toggling interaction widget"));

	if (WidgetComponent == nullptr) { return; }
	WidgetComponent->SetVisibility(isPlayerNear);
}

// Called every frame
void AInteractibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractibleBase::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Interacting with base object"));
}

