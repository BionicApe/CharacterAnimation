#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AlsTypes.generated.h"

class UCurveVector;
class UAnimMontage;

UENUM(BlueprintType)
enum class EAlsGaitEnum : uint8
{
  Walking,
  Running,
  Sprinting
};


UENUM(BlueprintType)
enum class EAlsMovementActionEnum : uint8
{
  None,
  LowMantle,
  HighMantle,
  Rolling,
  GettingUp
};

UENUM(BlueprintType)
enum class EAlsMovementStateEnum : uint8
{
  None,
  Grounded,
  InAir,
  Mantling,
  Ragdoll,
};

UENUM(BlueprintType)
enum class EAlsOverlayStateEnum : uint8
{
  Default,
  Masculine,
  Feminine,
  Injured,
  HandsTied,
  Rifle,
  Pistol1H,
  Pistol2H,
  Bow,
  Torch,
  Binoculars,
  Box,
  Barrel,
  Combat
};
UENUM(BlueprintType)
enum class EAlsRotationModeEnum : uint8
{
  VelocityDirection,
  LookingDirection,
  Aiming
};

UENUM(BlueprintType)
enum class EAlsStanceEnum : uint8
{
  Standing,
  Crouching
};
UENUM(BlueprintType)
enum class EAlsViewModeEnum : uint8
{
  ThirdPerson,
  FirstPerson
};
UENUM(BlueprintType)
enum class EAlsFootstepEnum : uint8
{
  Step,
  WalkRun,
  Jump,
  Land
};

UENUM(BlueprintType)
enum class EAlsGroundedEntryStateEnum : uint8
{
  None,
  Roll
};
UENUM(BlueprintType)
enum class EAlsHipsDirectionEnum : uint8
{
  F,
  B,
  RF,
  RB,
  LF,
  LB
};

UENUM(BlueprintType)
enum class EAlsMantleTypeEnum : uint8
{
  HighMantle,
  LowMantle,
  FallingCatch
};

UENUM(BlueprintType)
enum class EAlsMovementDirectionEnum : uint8
{
  Forward,
  Right,
  Left,
  Backward
};

USTRUCT(BlueprintType)
struct CHARACTERANIMATION_API FAlsInputValues
{
  GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    EAlsRotationModeEnum DesiredRotationMode;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    EAlsGaitEnum DesiredGait;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    EAlsStanceEnum DesiredStance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LookUpRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LookRightRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    int32 TimesPressedStance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    bool bBreakFall;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    bool bSprintHeld;

  FAlsInputValues() :
    DesiredRotationMode(EAlsRotationModeEnum::LookingDirection),
    DesiredGait(EAlsGaitEnum::Running),
    DesiredStance(EAlsStanceEnum::Standing),
    LookUpRate(1.25),
    LookRightRate(1.25),
    TimesPressedStance(0),
    bBreakFall(false),
    bSprintHeld(false)
  {

  }
};


USTRUCT(BlueprintType)
struct CHARACTERANIMATION_API FMantleTraceSettings
{
  GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float MaxLedgeHeight;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float MinLedgeHeight;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float ReachDistance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float ForwardTraceRadius;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float DownwardTraceRadius;

  FMantleTraceSettings() :
    MaxLedgeHeight(0.f),
    MinLedgeHeight(0.f),
    ReachDistance(0.f),
    ForwardTraceRadius(0.f),
    DownwardTraceRadius(0.f)
  {
  }
};




USTRUCT(BlueprintType)
struct CHARACTERANIMATION_API FMantleAsset
{
  GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    UAnimMontage* AnimMontage;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    UCurveVector* PositionCorrectionCurve;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    FVector StartingOffset;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LowHeight;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LowPlayRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LowStartPosition;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float HighHeight;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float HighPlayRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float HighStartPosition;

  FMantleAsset() :
    AnimMontage(nullptr),
    PositionCorrectionCurve(nullptr),
    StartingOffset(FVector::ZeroVector),
    LowHeight(0.f),
    LowPlayRate(0.f),
    LowStartPosition(0.f),
    HighHeight(0.f),
    HighPlayRate(0.f),
    HighStartPosition(0.f)
  {
  }
};



USTRUCT(BlueprintType)
struct CHARACTERANIMATION_API FAlsMovementSettings
{
  GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float WalkSpeed;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float RunSpeed;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float SprintSpeed;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    UCurveVector* MovementCurve;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    UCurveVector* RotationRateCurve;

  FAlsMovementSettings() :
    WalkSpeed(0.f),
    RunSpeed(0.f),
    SprintSpeed(0.f),
    MovementCurve(nullptr),
    RotationRateCurve(nullptr)
  {
  }
};


USTRUCT(BlueprintType)
struct CHARACTERANIMATION_API FMovementSettingsStance
{
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    FAlsMovementSettings Standing;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    FAlsMovementSettings Crouching;

  GENERATED_USTRUCT_BODY()
    FMovementSettingsStance()
  {

  }
};


USTRUCT(BlueprintType)
struct CHARACTERANIMATION_API FMovementSettingsState
{
  GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    UAnimMontage* AnimMontage;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    UCurveVector* PositionCorrectionCurve;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    FVector StartingOffset;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LowHeight;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LowPlayRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float LowStartPosition;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float HighHeight;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float HighPlayRate;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ALS)
    float HighStartPosition;

  FMovementSettingsState() :
    AnimMontage(nullptr),
    PositionCorrectionCurve(nullptr),
    StartingOffset(FVector::ZeroVector),
    LowHeight(0.f),
    LowPlayRate(0.f),
    LowStartPosition(0.f),
    HighHeight(0.f),
    HighPlayRate(0.f),
    HighStartPosition(0.f)
  {
  }
};
