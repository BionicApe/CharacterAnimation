#pragma once

#include "GameFramework/Actor.h"
#include "AlsTypes.h"
#include "Engine/EngineTypes.h"
#include "AlsAnimableCharacter.generated.h"

UINTERFACE(Blueprintable)
class CHARACTERANIMATION_API UAlsAnimableCharacter : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class CHARACTERANIMATION_API IAlsAnimableCharacter
{
	GENERATED_IINTERFACE_BODY()

public:


	//Character Information
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Information")
	void GetAnimCurrentStates(
		TEnumAsByte<EMovementMode>& PawnMovementMode, EAlsMovementStateEnum& MovementState, EAlsMovementStateEnum& PrevMovementState, EAlsMovementActionEnum& MovementAction,
		EAlsRotationModeEnum& RotationMode, EAlsGaitEnum& ActualGait, EAlsStanceEnum& ActualStance, EAlsViewModeEnum& ViewMode, EAlsOverlayStateEnum& OverlayState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Information")
	void GetAnimEssentialValues(FVector& Velocity, FVector& Acceleration, FVector& MovementInput, bool& IsMoving, bool& HasMovementInput, float& Speed, float& MovementInputAmount, FRotator& AimingRotation, float& AimYawRate);


	//Character States
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = "Character States")
	void SetAnimMovementState(EAlsMovementStateEnum NewMovementState);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = "Character States")
	void BPI_Set_MovementAction(EAlsMovementActionEnum NewMovementAction);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = "Character States")
	void BPI_Set_RotationMode(EAlsRotationModeEnum NewRotationMode);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = "Character States")
	void BPI_Set_Gait(EAlsGaitEnum NewGait);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character States")
	void BPI_Set_ViewMode(EAlsViewModeEnum NewViewMode);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = "Character States")
	void BPI_Set_OverlayState(EAlsOverlayStateEnum NewOverlayState);
};