// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuViewModel.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TPPROJECT_API UMainMenuViewModel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* BTN_Submit;

private:
	UFUNCTION()
	void OnSubmitButtonClicked();
};
