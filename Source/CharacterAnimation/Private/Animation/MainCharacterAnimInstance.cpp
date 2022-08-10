// Created by Bionic Ape. All rights reseved.

#include "Animation/MainCharacterAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Implementables/LookingAtLocationInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"


bool UMainCharacterAnimInstance::TrySetCharacterOwner()
{
	const USkeletalMeshComponent* OwnerComponent = GetSkelMeshComponent();
	if (AActor* OwnerActor = OwnerComponent->GetOwner())
	{
		CharacterOwner = Cast<ACharacter>(OwnerActor);
	}
	return CharacterOwner != nullptr;
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super method is empty, so it does nothing
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (CharacterOwner || TrySetCharacterOwner())
	{
		if (const UCharacterMovementComponent* MovComp = CharacterOwner->GetCharacterMovement())
		{
			MovementMode = MovComp->MovementMode;
			bInAir = MovComp->IsFalling();
			bCrouching = MovComp->IsCrouching();
		}

		UpdateLookAtThing(DeltaSeconds);

		FVector PawnSpeed = CharacterOwner->GetVelocity();
		PawnSpeed.Z = 0;

		CalculatedSpeed = PawnSpeed.Size();
		CalculatedDirection = CalculatedSpeed > KINDA_SMALL_NUMBER ? UKismetAnimationLibrary::CalculateDirection(PawnSpeed, CharacterOwner->GetActorRotation()) : 0;

		const FRotator ControlRot = CharacterOwner->GetControlRotation();

		CalculatedPitch = FMath::ClampAngle(ControlRot.Pitch, -90, 90);

		if (CollectableMeshComponent.IsValid())
		{
			LHandSocket = CollectableMeshComponent->GetSocketTransform(LHandSocketName, ERelativeTransformSpace::RTS_World);
		}
	}
}

void UMainCharacterAnimInstance::SetCollectableTypeAndMesh(EGrabbingTypeEnum NewType, UMeshComponent* NewCollectableMeshComponent)
{
	CollectableTypeEnum = NewType;

	switch (CollectableTypeEnum)
	{
	case EGrabbingTypeEnum::BALL:
	case EGrabbingTypeEnum::BOX:
	case EGrabbingTypeEnum::NO_COLLECTABLE:
		AimAlpha = 0.0f;
		break;
	case EGrabbingTypeEnum::TURRET:
	case EGrabbingTypeEnum::RIFLE:
		AimAlpha = 0.9f;
	}

	CollectableMeshComponent = NewCollectableMeshComponent;
}

void UMainCharacterAnimInstance::UpdateLookAtThing(float DeltaTime)
{
	float NewLookAtPitch = 0.f;
	float NewLookAtYaw = 0.f;

	if (CharacterOwner)
	{
		if (const AController* Controller = CharacterOwner->GetController())
		{
			const ILookingAtLocationInterface* LookingAtLocationController = Cast<ILookingAtLocationInterface>(Controller);
			if (LookingAtLocationController)
			{
				const FVector LocationToLookAt = LookingAtLocationController->GetLocationToLookAt();

				if (LocationToLookAt != FVector::ZeroVector)
				{

					//const FVector ViewLocation = CharacterOwner->GetLocationToBeLookedAt();
					const FVector ViewLocation = CharacterOwner->GetPawnViewLocation();
					const FRotator WorldLookAtRotator = UKismetMathLibrary::FindLookAtRotation(ViewLocation, LocationToLookAt);
					const FRotator RelativeLookAtRotator = WorldLookAtRotator - CharacterOwner->GetActorRotation();

					const FRotator ContRot = Controller->GetControlRotation();
					const FRotator ConDesRot = Controller->GetDesiredRotation();

					NewLookAtPitch = FMath::ClampAngle(RelativeLookAtRotator.Pitch, -90, 90);
					NewLookAtYaw = FMath::ClampAngle(RelativeLookAtRotator.Yaw, -90, 90);

				}
			}
		}
	}

	LookAtProperties.LookAtPitch = FMath::FInterpTo(LookAtProperties.LookAtPitch, NewLookAtPitch, DeltaTime, LookAtProperties.LookAtPitchSpeed);
	LookAtProperties.LookAtYaw = FMath::FInterpTo(LookAtProperties.LookAtYaw, NewLookAtYaw, DeltaTime, LookAtProperties.LookAtYawSpeed);
}

void UMainCharacterAnimInstance::PlayInvalidLoveWar()
{
	if (InvalidLoveWarMontage)
	{
		float AnimationLenght = Montage_Play(InvalidLoveWarMontage);
	}
}