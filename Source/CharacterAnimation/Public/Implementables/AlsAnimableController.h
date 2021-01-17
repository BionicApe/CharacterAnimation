#pragma once

#include "GameFramework/Actor.h"
#include "AlsAnimableController.generated.h"

UINTERFACE(Blueprintable)
class CHARACTERANIMATION_API UAlsAnimableController : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class CHARACTERANIMATION_API IAlsAnimableController
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector GetLocationToLookAt() const;
};