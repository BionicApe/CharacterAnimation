#pragma once

#include "GameFramework/Actor.h"
#include "AlsAnimableCamera.generated.h"

UINTERFACE(Blueprintable)
class CHARACTERANIMATION_API UAlsAnimableCamera : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class CHARACTERANIMATION_API IAlsAnimableCamera
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector GetLocationToLookAt() const;
};