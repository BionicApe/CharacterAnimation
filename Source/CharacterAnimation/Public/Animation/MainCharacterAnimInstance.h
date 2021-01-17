#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimationTypes.h"
#include "MainCharacterAnimInstance.generated.h"

class ACharacter;
class UAnimMontage;


USTRUCT(BlueprintType)
struct FLookAtProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float LookAtPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float LookAtYaw = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float LookAtYawSpeed = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float LookAtPitchSpeed = 6.f;

	FLookAtProperties()
	{

	}
};


UCLASS()
class CHARACTERANIMATION_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:


	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* InvalidLoveWarMontage;

	UPROPERTY(Transient, BlueprintReadOnly, Category = LoveWarDreams)
	ACharacter* CharacterOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	bool bInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	bool bCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Disturber)
	bool bSnapCover = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float CalculatedSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float CalculatedDirection = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float CalculatedPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	float AimAlpha = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	FLookAtProperties LookAtProperties;

	UPROPERTY(Transient, BlueprintReadWrite, Category = LoveWarDreams)
	FTransform LHandSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	TEnumAsByte<enum EMovementMode> MovementMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	FName LHandSocketName = "LHandSocket";

	TWeakObjectPtr<UMeshComponent> CollectableMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	uint8 FightingStyle = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LoveWarDreams)
	EGrabbingTypeEnum CollectableTypeEnum = EGrabbingTypeEnum::NO_COLLECTABLE;

public:
	
	void SetCollectableTypeAndMesh(EGrabbingTypeEnum NewType, UMeshComponent* NewCollectableMeshComponent);

	/**
	* Returns positive Speed if is a Left Speed and Positive values if is Right
	*/
	UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe))
	float GetDirectionalSpeed() const {	return  CalculatedDirection > 0.f ? CalculatedSpeed : -CalculatedSpeed;	}

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	float GetLookAtPitch() const { return  LookAtProperties.LookAtPitch; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	float GetLookAtYaw() const { return  LookAtProperties.LookAtYaw; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	virtual float GetBlockValue() const { return 0.f; }

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	bool TrySetCharacterOwner();

	void UpdateLookAtThing(float DeltaTime);
public:
	void PlayInvalidLoveWar();
};
