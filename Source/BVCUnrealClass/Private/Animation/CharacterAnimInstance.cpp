// Have a great day.


#include "Animation/CharacterAnimInstance.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	APawn* PlayerCharacterPawn = TryGetPawnOwner();
	if (PlayerCharacterPawn)
	{
		PlayerCharacter = Cast<APlayerCharacter>(PlayerCharacterPawn);
		if (PlayerCharacter)
		{
			MovementComponent = Cast<UCharacterMovementComponent>(PlayerCharacter->GetMovementComponent());		
		}
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (MovementComponent)
	{
		MoveSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		bIsFalling = MovementComponent->IsFalling();
		UpdateYawRotation();		
	}
}

FORCEINLINE void UCharacterAnimInstance::UpdateYawRotation()
{
	if (PlayerCharacter)
	{
		const FVector CurrentFacingDirection = PlayerCharacter->GetActorForwardVector();
		FVector CurrentVelocityDirection = MovementComponent->Velocity;
		CurrentVelocityDirection.Normalize();

		const float DotProduct = FVector::DotProduct(CurrentFacingDirection, CurrentVelocityDirection);
		YawRotation = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

		const FVector CrossProduct = FVector::CrossProduct(CurrentFacingDirection, CurrentVelocityDirection);

		YawRotation = CrossProduct.Z < 0 ? -YawRotation : YawRotation;
	}
}
