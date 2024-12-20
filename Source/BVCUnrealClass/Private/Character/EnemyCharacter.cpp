// Have a great day.


#include "Character/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "../BVCUnrealClass.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Target = UGameplayStatics::GetActorOfClass(this, APlayerCharacter::StaticClass());

	EnemyController = Cast<AAIController>(GetController());

	if (Target && EnemyController)
	{
		EnemyController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AEnemyCharacter::OnMoveComplete);	
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector VectorToTarget = Target->GetActorLocation() - GetActorLocation();

	float DistanceToTarget = VectorToTarget.Length();

	VectorToTarget.Normalize();
	float Dot = FVector::DotProduct(VectorToTarget, GetActorForwardVector());

	FString DebugString = FString::Printf(TEXT("Dot: %f"), Dot);
	SCREEN_MESSAGE(DebugString);

	bool bCanSeeTarget = !bAggressive && DistanceToTarget < AggroRadius && Dot > FieldOfView;

	if (bCanSeeTarget)
	{
		ChaseTarget();
	}
}

void AEnemyCharacter::OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success)
	{
		Attack();
	}
}

void AEnemyCharacter::Attack()
{
	GetMesh()->GetAnimInstance()->Montage_Play(CombatMontage);

	int RandomAttack = FMath::RandRange(0, AttackNames.Num() - 1);
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(AttackNames[RandomAttack]);

	GetWorldTimerManager().SetTimer(AttackCooldownTimer, this, &AEnemyCharacter::ChaseTarget, AttackCooldown);
}

void AEnemyCharacter::ChaseTarget()
{
	if (EnemyController)
	{
		bAggressive = true;
		EnemyController->MoveToActor(Target, 15.f);
	}
}
