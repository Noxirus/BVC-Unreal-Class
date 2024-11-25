// Have a great day.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelayedMine.generated.h"

class UBoxComponent;

UCLASS()
class BVCUNREALCLASS_API ADelayedMine : public AActor
{
	GENERATED_BODY()
	
public:	
	ADelayedMine();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void MineExplosion();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MineMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxOverlap;

	UPROPERTY(EditAnywhere, Category = "Mine Details")
	float CountdownTime = 5.f;

	FTimerHandle DelayedTimerHandle;
};
