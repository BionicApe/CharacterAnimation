#pragma once

#include "GameFramework/Actor.h"
#include "LookingAtLocationInterface.generated.h"

UINTERFACE(Blueprintable)
class CHARACTERANIMATION_API ULookingAtLocationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class CHARACTERANIMATION_API ILookingAtLocationInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector GetLocationToLookAt() const;
};