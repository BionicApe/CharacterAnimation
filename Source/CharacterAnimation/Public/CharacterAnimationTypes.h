#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterAnimationTypes.generated.h"


UENUM(BlueprintType)
enum class EGrabbingTypeEnum : uint8
{
	NO_COLLECTABLE	UMETA(DisplayName = "NoCollectable"),
	BALL			UMETA(DisplayName = "Ball"),
	BOX				UMETA(DisplayName = "Box"),
	TURRET			UMETA(DisplayName = "Turret"),
	RIFLE			UMETA(DisplayName = "Rifle")
};