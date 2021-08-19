// Created by Bionic Ape. All rights reseved.

#include "Implementables/AlsAnimableCamera.h"

UAlsAnimableCamera::UAlsAnimableCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector IAlsAnimableCamera::GetLocationToLookAt() const
{
	return FVector::ZeroVector;
}