// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InGameHUDViewModel.generated.h"

class UBackpackComponent;

UCLASS()
class TPPROJECT_API UInGameHUDViewModel : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct();

	UFUNCTION()
	void SetMaxBackpackCapacity(int NewCapacity);
	UFUNCTION()
	void AddToBackpackCurrentCapacity(int ValueToAdd);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentBackpackCapacityText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxBackpackCapacityText;

private:
	UPROPERTY()
	TObjectPtr<UBackpackComponent> BackpackComponent;

	int CurrentBackpackCapacity;

	FText ConvertIntegerToString(int Input);
};
