// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType) // this type can be used as a variable type on a blueprint
struct TPPROJECT_API FPlayerData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayerHealth{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayerWalkSpeed{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayerRunSpeed{};
};
