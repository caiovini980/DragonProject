// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactibles/InteractibleBase.h"
#include "Rock.generated.h"

/**
 * 
 */
UCLASS()
class TPPROJECT_API ARock : public AInteractibleBase
{
public:
	GENERATED_BODY()
	ARock();

	
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;
	
	void AttachTo(const ACharacter* Character, const FName& SocketName) const;
};
