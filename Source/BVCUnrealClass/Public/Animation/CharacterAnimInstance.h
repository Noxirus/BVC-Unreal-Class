// Have a great day.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class BVCUNREALCLASS_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float YawRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;

private:
	void UpdateYawRotation();

};
