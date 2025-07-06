// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"

// Sets default values
AActorSpawner::AActorSpawner()
{

}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActorSpawner::SpawnObject()
{
	int32 RandomIndex = FMath::RandRange(0, ActorsToSpawn.Num() - 1);
	GetWorld()->SpawnActor<AActor>(ActorsToSpawn[RandomIndex], GetActorLocation(), GetActorRotation());
}

