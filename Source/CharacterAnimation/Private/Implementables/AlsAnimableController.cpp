// Fill out your copyright notice in the Description page of Project Settings.

#include "Implementables/AlsAnimableController.h"

UAlsAnimableController::UAlsAnimableController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


FVector IAlsAnimableController::GetLocationToLookAt() const
{
	return FVector::ZeroVector;
}