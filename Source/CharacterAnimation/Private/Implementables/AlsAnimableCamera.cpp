// Fill out your copyright notice in the Description page of Project Settings.

#include "Implementables/AlsAnimableCamera.h"

UAlsAnimableCamera::UAlsAnimableCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector IAlsAnimableCamera::GetLocationToLookAt() const
{
	return FVector::ZeroVector;
}