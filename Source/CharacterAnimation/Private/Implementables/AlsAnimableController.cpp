// Created by Bionic Ape. All rights reseved.

#include "Implementables/AlsAnimableController.h"

UAlsAnimableController::UAlsAnimableController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector IAlsAnimableController::GetLocationToLookAt() const
{
	return FVector::ZeroVector;
}