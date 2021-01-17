// Fill out your copyright notice in the Description page of Project Settings.

#include "Implementables/LookingAtLocationInterface.h"

ULookingAtLocationInterface::ULookingAtLocationInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector ILookingAtLocationInterface::GetLocationToLookAt() const
{
	return FVector::ZeroVector;
}