// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/MainMenuViewModel.h"

void UMainMenuViewModel::NativeConstruct()
{
	Super::NativeConstruct();

	if (BTN_Submit)
	{
		BTN_Submit->OnClicked.AddDynamic(this, &UMainMenuViewModel::OnSubmitButtonClicked);
	}
}

void UMainMenuViewModel::OnSubmitButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Text Submitted!"));
}
