// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Implementables/AlsAnimableCharacter.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Engine/DataTable.h>
#include "AlsCharacter.generated.h"

class UTimelineComponent;

UCLASS()
class CHARACTERANIMATION_API AAlsCharacter : public ACharacter, public IAlsAnimableCharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(Transient)
	UAnimInstance* MyAnimInstance;

	UPROPERTY()
	UTimelineComponent* MantleTimeline;


	//**Essential Information**
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	bool bHasMovementInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	FRotator LastVelocityRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	FRotator LastMovementInputRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	float MovementInputAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Information")
	float AimYawRate;
	//**End Essential Information**

	
	
	//**Camera System**//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera System")
	float ThirdPersonFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera System")
	float FirstPersonFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	bool bRightShoulder;
	//**End Camera System**//


	//**State Values**//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsMovementStateEnum MovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsMovementStateEnum PrevMovementState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsMovementActionEnum MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsRotationModeEnum RotationMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsGaitEnum Gait;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsStanceEnum Stance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsViewModeEnum ViewMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Values")
	EAlsOverlayStateEnum OverlayState;
	//**End State Values**//


		
	//**Movement System**
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement System")
	FDataTableRowHandle MovementModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement System")
	FMovementSettingsState MovementData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement System")
	FAlsMovementSettings CurrentMovementSettings;
	//**End Movement System**//


	//**Rotation System**
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation System")
	FRotator TargetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation System")
	FRotator InAirRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation System")
	float YawOffset;
	//**End Rotation System**//



	//** Cached Variables**//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cached Variables")
	FVector PreviousVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cached Variables")
	float PreviousAimYaw;
	//** End Cached Variables**//


	
	//**Input**//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	EAlsRotationModeEnum DesiredRotationMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	EAlsGaitEnum DesiredGait;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	EAlsStanceEnum DesiredStance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookUpRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookRightRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	int32 TimesPressedStance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bBreakFall;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bSprintHeld;
	//**End Input**//


public:

	AAlsCharacter();

protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaTime);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);



	//***IAlsAnimableCharacter***//
	//Character Information
	void GetAnimCurrentStates_Implementation(
		TEnumAsByte<EMovementMode>& PawnMovementMode, EAlsMovementStateEnum& MovementState, EAlsMovementStateEnum& PrevMovementState, EAlsMovementActionEnum& MovementAction,
		EAlsRotationModeEnum& RotationMode, EAlsGaitEnum& ActualGait, EAlsStanceEnum& ActualStance, EAlsViewModeEnum& ViewMode, EAlsOverlayStateEnum& OverlayState);
	void GetAnimEssentialValues_Implementation(FVector& Velocity, FVector& Acceleration, FVector& MovementInput, bool& IsMoving, bool& HasMovementInput, float& Speed, float& MovementInputAmount, FRotator& AimingRotation, float& AimYawRate);
	//Character States
	void SetAnimMovementState_Implementation(EAlsMovementStateEnum NewMovementState);
	void BPI_Set_MovementAction_Implementation(EAlsMovementActionEnum NewMovementAction);
	void BPI_Set_RotationMode_Implementation(EAlsRotationModeEnum NewRotationMode);
	void BPI_Set_Gait_Implementation(EAlsGaitEnum NewGait);
	void BPI_Set_ViewMode_Implementation(EAlsViewModeEnum NewViewMode);
	void BPI_Set_OverlayState_Implementation(EAlsOverlayStateEnum NewOverlayState);
	//***End IAlsAnimableCharacter***//

	//**Utility**//
	UFUNCTION(BlueprintCallable, Category="Utility")
	void GetControlForwardRightVector(FVector& ForwardVector, FVector& RightVector) const;

	UFUNCTION(BlueprintCallable, Category = "Utility")
	FVector GetCalpsuleBaseLocation(float ZOffset) const;

	UFUNCTION(BlueprintCallable, Category = "Utility")
	FVector GetCapsuleLocationFromBase(FVector BaseLocation, float ZOffset) const;
	
	UFUNCTION(BlueprintCallable, Category = "Utility")
	float GetAnimCurveValue(FName CurveName) const;
	//**End Utility**//

	//**Essential Information**//
	UFUNCTION(BlueprintCallable, Category = "Utility")
	void SetEssentialValues();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	void CacheValues();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	FVector CalculateAcceleration() const;
	//**Essential Information**//

	//State Changes
	void OnCharacterMovementModeChanged(EMovementMode PrevMovementMode, EMovementMode NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode);
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	void OnMovementStateChanged(EAlsMovementStateEnum NewMovementState);
	void OnMovementActionChanged(EAlsMovementActionEnum NewMovementAction);
	void OnStanceChanged(EAlsStanceEnum NewStance);
	void OnRotationModeChange(EAlsRotationModeEnum NewRotationMode);
	void OnGaitChanged(EAlsGaitEnum NewActualGait);
	void OnViewModeChanged(EAlsViewModeEnum NewViewMode);
	void OnOverlayStateChanged(EAlsOverlayStateEnum NewOverlayState);
	//End State Changes
	
	
	
	//**Movement System**//
	UFUNCTION(BlueprintCallable, Category = "Movement System")
	void SetMovementModel();
	
	UFUNCTION(BlueprintCallable, Category = "Movement System")
	void UpdateCharacterMovement();

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	void UpdateDynamicMovementSettings(EAlsGaitEnum NewGait);

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	FAlsMovementSettings GetTargetMovementSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	EAlsGaitEnum GetAllowedGait() const;

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	EAlsGaitEnum GetActualGait(EAlsGaitEnum ActualGait) const;

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	bool CanSprint() const;

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	float GetMappedSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Movement System")
	UAnimMontage* GetRollAnimation() const;
	//**End Movement System**//

	
	
	
	//**Rotation System**//
	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	void UpdateGroudedRotation();

	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	void UpdateInAirRotation();
	
	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	void SmoothCharacterRotation(FRotator Target, float TargetInterpSpeed, float ActorInterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	void AddToCharacterRotation(FRotator DeltaRotation);

	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	void LimitRotation(float AimYawMin, float AimYawMax,float InterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	void UpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport);

	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	float CalculateGroundedRotationRate() const;

	UFUNCTION(BlueprintCallable, Category = "Rotation System")
	bool CanUpdateMovingRotation() const;
	//**End Rotation System**//


	
	
	//**Mantle System**//
	UFUNCTION(BlueprintCallable, Category = "Mantle System")
	bool MantleCheck(FMantleTraceSettings TraceSettings, EDrawDebugTrace::Type DebugType);

	UFUNCTION(BlueprintCallable, Category = "Mantle System")
	void MantleStart(float MantleHeight, UPrimitiveComponent* Component, FTransform CompTransform, EAlsMantleTypeEnum MantleType);

	UFUNCTION(BlueprintCallable, Category = "Mantle System")
	void MantleEnd();

	UFUNCTION(BlueprintCallable, Category = "Mantle System")
	void MantleUpdate(float BlendIn);

	UFUNCTION(BlueprintCallable, Category = "Mantle System")
	bool CapsuleHasRoomCheck(UCapsuleComponent* Capsule, FVector TargetLocation, float HeightOffset, float RadiusOffset, EDrawDebugTrace::Type DebugType) const;

	UFUNCTION(BlueprintCallable, Category = "Mantle System")
	FMantleAsset GetMantleAsset(EAlsMantleTypeEnum MantleType) const;
	//**End Mantle System**//

	
	
	
	//**Ragdoll System**//
	UFUNCTION(BlueprintCallable, Category = "Ragdoll System")
	void RagdollStart();

	UFUNCTION(BlueprintCallable, Category = "Ragdoll System")
	void RagdollEnd();

	UFUNCTION(BlueprintCallable, Category = "Ragdoll System")
	void RagdollUpdate();

	UFUNCTION(BlueprintCallable, Category = "Ragdoll System")
	void SetActorLocationDuringRagdoll();

	UFUNCTION(BlueprintCallable, Category = "Ragdoll System")
	virtual UAnimMontage* GetGetUpAnimation(bool bRagdollFaceUp) const;
	//**End Ragdoll System**//

	
	
	//**Debug//
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DrawDebugShapes();

	UFUNCTION(BlueprintCallable, Category = "Debug")
	EDrawDebugTrace::Type GetTraceDebugType(EDrawDebugTrace::Type ShowTraceType);	
	//**End Debug//

	
	
	//**Input**//
	UFUNCTION(BlueprintCallable, Category = "Input")
	void PlayerMovementInput(bool bIsForwardAxis);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	FVector GetPlayerMovementInput() const;
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void FixDiagonalGamepadValues(float InY, float InX, float& OutY, float& OutX) const;
	//**End Input**//
};
