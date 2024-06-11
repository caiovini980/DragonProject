// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	Health = 100.f;
	WalkSpeed = 50.0f;
	RunSpeed = 100.0f;
	// JumpForce = 100.0f;
}

bool UAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	return true;
}

float UAttributeComponent::GetRunSpeed() const
{
	return RunSpeed;
}

float UAttributeComponent::GetWalkSpeed() const
{
	return WalkSpeed;
}

// float UAttributeComponent::GetJumpForce() const
// {
// 	return JumpForce;
// }
