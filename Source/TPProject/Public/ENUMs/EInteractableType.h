// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	EIT_Default UMETA(DisplayName = "Default"),
	EIT_Activable UMETA(DisplayName = "Activable"),
	EIT_Grabbable UMETA(DisplayName = "Grabbable"),
	EIT_Movable UMETA(DisplayName = "Movable"),
	EIT_Pressable UMETA(DisplayName = "Pressable"),
};
