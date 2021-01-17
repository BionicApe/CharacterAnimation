#pragma once

#include "GameFramework/Actor.h"
#include "AlsTypes.h"
#include "AlsAnimable.generated.h"

UINTERFACE(Blueprintable)
class CHARACTERANIMATION_API UAlsAnimable : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class CHARACTERANIMATION_API IAlsAnimable
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = ALS)
	void BPI_Jumped() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = ALS)
	void BPI_SetGroundedEntryState(EAlsGroundedEntryStateEnum GroundedEntryState) const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = ALS)
	void BPI_SetOverlayOverrideState(int32 OverlayOverrideState) const;

};