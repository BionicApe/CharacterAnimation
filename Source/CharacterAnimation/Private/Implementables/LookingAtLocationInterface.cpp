// Created by Bionic Ape. All rights reseved.

#include "Implementables/LookingAtLocationInterface.h"

ULookingAtLocationInterface::ULookingAtLocationInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector ILookingAtLocationInterface::GetLocationToLookAt() const
{
	return FVector::ZeroVector;
}