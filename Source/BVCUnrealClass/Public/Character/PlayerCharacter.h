// Have a great day.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;
struct FInputActionValue;

UCLASS()
class BVCUNREALCLASS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void Movement(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpStart();

	/*
	**	Input
	*/
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> JumpMontage;

public:
	FORCEINLINE	UCameraComponent* GetGamera() { return Camera; }
};
