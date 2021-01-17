// Created by Bionic Ape. All Rights Reserved.


#include "GameFramework/AlsCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAlsCharacter::AAlsCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AAlsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AAlsCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Make sure the mesh and animbp update after the CharacterBP to ensure it gets the most recent values.
	GetMesh()->AddTickPrerequisiteActor(this);//TODO: Check if is redundant or how to do it properly

	MyAnimInstance = GetMesh()->GetAnimInstance();

	SetMovementModel();

	//Update states to use the initial desired values.
	OnGaitChanged(DesiredGait);
	OnRotationModeChange(DesiredRotationMode);
	OnViewModeChanged(ViewMode);
	OnOverlayStateChanged(OverlayState);

	if (DesiredStance == EAlsStanceEnum::Crouching)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}

	//Set default rotation values.
	const FRotator ActorRotator = GetActorRotation();
	TargetRotation = ActorRotator;
	LastVelocityRotation = ActorRotator;
	LastMovementInputRotation = ActorRotator;
}


// Called to bind functionality to input
void AAlsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAlsCharacter::GetAnimCurrentStates_Implementation(TEnumAsByte<EMovementMode>& OutPawnMovementMode, EAlsMovementStateEnum& OutMovementState, EAlsMovementStateEnum& OutPrevMovementState, EAlsMovementActionEnum& OutMovementAction, EAlsRotationModeEnum& OutRotationMode, EAlsGaitEnum& OutActualGait, EAlsStanceEnum& OutActualStance, EAlsViewModeEnum& OutViewMode, EAlsOverlayStateEnum& OutOverlayState)
{
	OutPawnMovementMode = GetCharacterMovement()->MovementMode;
	OutMovementState = MovementState;
	OutPrevMovementState = PrevMovementState;
	OutMovementAction = MovementAction;
	OutRotationMode = RotationMode;
	OutActualGait = Gait;
	OutActualStance = Stance;
	OutViewMode = ViewMode;
	OutOverlayState = OverlayState;
}

void AAlsCharacter::GetAnimEssentialValues_Implementation(FVector& OutVelocity, FVector& OutAcceleration, FVector& OutMovementInput, bool& OutIsMoving, bool& OutHasMovementInput, float& OutSpeed, float& OutMovementInputAmount, FRotator& OutAimingRotation, float& OutAimYawRate)
{
	OutVelocity = GetVelocity();
	OutAcceleration = Acceleration;
	OutMovementInput = GetCharacterMovement()->GetCurrentAcceleration();
	OutIsMoving = bIsMoving;
	OutHasMovementInput = bHasMovementInput;
	OutSpeed = Speed;
	OutMovementInputAmount = MovementInputAmount;
	OutAimingRotation = GetControlRotation();
	OutAimYawRate = AimYawRate;
}

void AAlsCharacter::SetAnimMovementState_Implementation(EAlsMovementStateEnum NewMovementState)
{
	if (MovementState != NewMovementState)
	{
		OnMovementStateChanged(NewMovementState);
	}
}

void AAlsCharacter::BPI_Set_MovementAction_Implementation(EAlsMovementActionEnum NewMovementAction)
{
	if (MovementAction != NewMovementAction)
	{
		OnMovementActionChanged(NewMovementAction);
	}
}

void AAlsCharacter::BPI_Set_RotationMode_Implementation(EAlsRotationModeEnum NewRotationMode)
{
	if (RotationMode != NewRotationMode)
	{
		OnRotationModeChange(NewRotationMode);
	}
}

void AAlsCharacter::BPI_Set_Gait_Implementation(EAlsGaitEnum NewGait)
{
	if (NewGait != Gait)
	{
		OnGaitChanged(NewGait);
	}
}

void AAlsCharacter::BPI_Set_ViewMode_Implementation(EAlsViewModeEnum NewViewMode)
{
	if (NewViewMode != ViewMode)
	{
		OnViewModeChanged(NewViewMode);
	}
}

void AAlsCharacter::BPI_Set_OverlayState_Implementation(EAlsOverlayStateEnum NewOverlayState)
{
	if (OverlayState != NewOverlayState)
	{
		OnOverlayStateChanged(NewOverlayState);
	}
}

void AAlsCharacter::GetControlForwardRightVector(FVector& ForwardVector, FVector& RightVector) const
{
	float const ControlRotationYaw = GetControlRotation().Yaw;
	ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.f, 0.f, ControlRotationYaw));
	RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.f, 0.f, ControlRotationYaw));
}

FVector AAlsCharacter::GetCalpsuleBaseLocation(float ZOffset) const
{
	const FVector CapsuleLocation = GetCapsuleComponent()->GetComponentLocation();
	const FVector CapsuleUpVector = GetCapsuleComponent()->GetUpVector();
	const float CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * ZOffset;
	return CapsuleLocation - CapsuleUpVector * CapsuleHalfHeight;
}

FVector AAlsCharacter::GetCapsuleLocationFromBase(FVector BaseLocation, float ZOffset) const
{
	FVector Vector = FVector::ZeroVector;
	Vector.Z = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + ZOffset;
	return Vector;
}

float AAlsCharacter::GetAnimCurveValue(FName CurveName) const
{
	return MyAnimInstance ? MyAnimInstance->GetCurveValue(CurveName) : 0.f;
}

/**
 *
These values represent how the capsule is moving as well as how it wants to move,
and therefore are essential for any data driven animation system.They are also used
throughout the system for various functions, so I found it is easiest to manage them all in one place.
*/
void AAlsCharacter::SetEssentialValues()
{
	Acceleration = CalculateAcceleration();
	//Determine if the character is moving by getting it's speed. The Speed equals the length of 
	//the horizontal (x y) velocity, so it does not take vertical movement into account. 
	//If the character is moving, update the last velocity rotation. This value is saved because it might be useful 
	//to know the last orientation of movement even after the character has stopped.
	FVector VelocityVectorZeroZ = GetVelocity();
	VelocityVectorZeroZ.Z = 0.f;
	Speed = VelocityVectorZeroZ.Size();
	bIsMoving = Speed > 1.f;

	if (bIsMoving)
	{
		LastVelocityRotation = UKismetMathLibrary::Conv_VectorToRotator(GetVelocity());//RotationFromXVector
	}
	//Determine if the character has movement input by getting its movement input amount.
	//The Movement Input Amount is equal to the current acceleration divided by the max acceleration 
	//so that it has a range of 0 - 1, 1 being the maximum possible amount of input, and 0 being none.
	//If the character has movement input, update the Last Movement Input Rotation.
	FVector const CurrentAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
	float const MaxAcceleration = GetCharacterMovement()->GetMaxAcceleration();
	MovementInputAmount = CurrentAcceleration.Size() / MaxAcceleration;

	bHasMovementInput = MovementInputAmount > 0.f;
	if (bHasMovementInput)
	{
		LastMovementInputRotation = UKismetMathLibrary::Conv_VectorToRotator(CurrentAcceleration);
	}

	//Set the Aim Yaw rate by comparing the current and previous Aim Yaw value, divided by Delta Seconds.
	//This represents the speed the camera is rotating left to right.
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	if (DeltaSeconds > 0)
	{
		float ControlRotZ = GetControlRotation().Yaw;
		AimYawRate = FMath::Abs(ControlRotZ - PreviousAimYaw / DeltaSeconds);
	}
}

void AAlsCharacter::CacheValues()
{
	PreviousVelocity = GetVelocity();
	PreviousAimYaw = GetControlRotation().Yaw;
}

FVector AAlsCharacter::CalculateAcceleration() const
{
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	if (DeltaSeconds > 0)
	{
		return GetVelocity() - PreviousVelocity / DeltaSeconds;
	}
	return FVector::ZeroVector;
}

void AAlsCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode /*= 0*/)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode /*= 0*/);

	switch (GetCharacterMovement()->MovementMode)
	{
	case EMovementMode::MOVE_Walking:
	case EMovementMode::MOVE_NavWalking:
	SetAnimMovementState_Implementation(EAlsMovementStateEnum::Grounded);
	break;
	case EMovementMode::MOVE_Falling:
	SetAnimMovementState_Implementation(EAlsMovementStateEnum::InAir);
	break;
	}
}

void AAlsCharacter::OnMovementStateChanged(EAlsMovementStateEnum NewMovementState)
{
	PrevMovementState = MovementState;
	MovementState = NewMovementState;

	switch (MovementState)
	{
	case EAlsMovementStateEnum::InAir:
		if (MovementAction == EAlsMovementActionEnum::None)
		{
			InAirRotation = GetActorRotation();
			if (Stance == EAlsStanceEnum::Crouching)
			{
				UnCrouch();
			}
		}
		else if (MovementAction == EAlsMovementActionEnum::Rolling)
		{
			RagdollStart();
		}
		break;
	case EAlsMovementStateEnum::Ragdoll:
		if (PrevMovementState == EAlsMovementStateEnum::Mantling)
		{
			MantleTimeline->Stop();
		}
		break;
	}
}

void AAlsCharacter::OnMovementActionChanged(EAlsMovementActionEnum NewMovementAction)
{
	EAlsMovementActionEnum PrevMovementAction = MovementAction;

	MovementAction = NewMovementAction;
	if (MovementAction == EAlsMovementActionEnum::Rolling)
	{
		Crouch();
	}

	if (PrevMovementAction == EAlsMovementActionEnum::Rolling)
	{
		if (DesiredStance == EAlsStanceEnum::Standing)
		{
			UnCrouch();
		}
		else
		{
			Crouch();
		}
	}
}

void AAlsCharacter::OnRotationModeChange(EAlsRotationModeEnum NewRotationMode)
{
	//If the new rotation mode is Velocity Direction and the character is in First Person, 
	//set the viewmode to Third Person.

	EAlsRotationModeEnum PreviousRotationMode = RotationMode;
	RotationMode = NewRotationMode;

	if (RotationMode == EAlsRotationModeEnum::VelocityDirection && ViewMode == EAlsViewModeEnum::FirstPerson)
	{
		BPI_Set_ViewMode_Implementation(EAlsViewModeEnum::ThirdPerson);
	}
}

void AAlsCharacter::OnStanceChanged(EAlsStanceEnum NewStance)
{
	Stance = NewStance;
}

void AAlsCharacter::OnGaitChanged(EAlsGaitEnum NewGait)
{
	Gait = NewGait;
}

void AAlsCharacter::OnViewModeChanged(EAlsViewModeEnum NewViewMode)
{
	EAlsViewModeEnum PrevViewMode = ViewMode;
	ViewMode = NewViewMode;

	if (ViewMode == EAlsViewModeEnum::ThirdPerson)
	{
		if (RotationMode != EAlsRotationModeEnum::Aiming)
		{
			BPI_Set_RotationMode_Implementation(DesiredRotationMode);
		}
	}
	else
	{
		if (RotationMode == EAlsRotationModeEnum::VelocityDirection)
		{
			BPI_Set_RotationMode_Implementation(EAlsRotationModeEnum::LookingDirection);
		}
	}
}

void AAlsCharacter::OnOverlayStateChanged(EAlsOverlayStateEnum NewOverlayState)
{
	OverlayState = NewOverlayState;
}

void AAlsCharacter::SetMovementModel()
{
	MovementData = *MovementModel.GetRow<FMovementSettingsState>(TEXT("Normal"));
}

void AAlsCharacter::UpdateCharacterMovement()
{
	EAlsGaitEnum const AllowedGait = GetAllowedGait();

	//Determine the Actual Gait.If it is different from the current Gait, Set the new Gait Event.
	EAlsGaitEnum const ActualGait = GetActualGait(AllowedGait);
	if (Gait != ActualGait)
	{
		BPI_Set_Gait_Implementation(ActualGait);
	}
	UpdateDynamicMovementSettings(AllowedGait);
}

void AAlsCharacter::UpdateDynamicMovementSettings(EAlsGaitEnum NewGait)
{
	CurrentMovementSettings = GetTargetMovementSettings();

	//Update the Character Max Walk Speed to the configured speeds based on the currently Allowed Gait.
	
	//CONTINUAR AQUI!!!!

}

FAlsMovementSettings AAlsCharacter::GetTargetMovementSettings() const
{
	return FAlsMovementSettings();
}

EAlsGaitEnum AAlsCharacter::GetAllowedGait() const
{
	return EAlsGaitEnum::Running;
}

EAlsGaitEnum AAlsCharacter::GetActualGait(EAlsGaitEnum ActualGait) const
{
	return EAlsGaitEnum::Running;
}

bool AAlsCharacter::CanSprint() const
{
	return true;
}

float AAlsCharacter::GetMappedSpeed() const
{
	return 0.f;
}

UAnimMontage* AAlsCharacter::GetRollAnimation() const
{
	return nullptr;
}

void AAlsCharacter::UpdateGroudedRotation()
{

}

void AAlsCharacter::UpdateInAirRotation()
{

}

void AAlsCharacter::SmoothCharacterRotation(FRotator Target, float TargetInterpSpeed, float ActorInterpSpeed)
{

}

void AAlsCharacter::AddToCharacterRotation(FRotator DeltaRotation)
{

}

void AAlsCharacter::LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed)
{

}

void AAlsCharacter::UpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport)
{

}

float AAlsCharacter::CalculateGroundedRotationRate() const
{
	return 0.f;
}

bool AAlsCharacter::CanUpdateMovingRotation() const
{
	return false;
}

bool AAlsCharacter::MantleCheck(FMantleTraceSettings TraceSettings, EDrawDebugTrace::Type DebugType)
{
	return false;
}

void AAlsCharacter::MantleStart(float MantleHeight, UPrimitiveComponent* Component, FTransform CompTransform, EAlsMantleTypeEnum MantleType)
{

}

void AAlsCharacter::MantleEnd()
{

}

void AAlsCharacter::MantleUpdate(float BlendIn)
{

}

bool AAlsCharacter::CapsuleHasRoomCheck(UCapsuleComponent* Capsule, FVector TargetLocation, float HeightOffset, float RadiusOffset, EDrawDebugTrace::Type DebugType) const
{
	return false;
}

FMantleAsset AAlsCharacter::GetMantleAsset(EAlsMantleTypeEnum MantleType) const
{
	return FMantleAsset();
}

void AAlsCharacter::RagdollStart()
{

}

void AAlsCharacter::RagdollEnd()
{

}

void AAlsCharacter::RagdollUpdate()
{

}

void AAlsCharacter::SetActorLocationDuringRagdoll()
{

}

UAnimMontage* AAlsCharacter::GetGetUpAnimation(bool bRagdollFaceUp) const
{
	return nullptr;
}

void AAlsCharacter::DrawDebugShapes()
{

}

EDrawDebugTrace::Type AAlsCharacter::GetTraceDebugType(EDrawDebugTrace::Type ShowTraceType)
{
	return EDrawDebugTrace::None;
}

void AAlsCharacter::PlayerMovementInput(bool bIsForwardAxis)
{

}

FVector AAlsCharacter::GetPlayerMovementInput() const
{
	return FVector::ZeroVector;
}

void AAlsCharacter::FixDiagonalGamepadValues(float InY, float InX, float& OutY, float& OutX) const
{

}

