// Have a great day.


#include "Actor/DelayedMine.h"
#include "Components/BoxComponent.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

ADelayedMine::ADelayedMine()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxOverlap = CreateDefaultSubobject<UBoxComponent>("Box Overlap");
	SetRootComponent(BoxOverlap);

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mine Mesh");
	MineMesh->SetupAttachment(BoxOverlap);
}

void ADelayedMine::BeginPlay()
{
	Super::BeginPlay();
	BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &ADelayedMine::OnBoxOverlap);
}

void ADelayedMine::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Started Timer"));
		GetWorldTimerManager().SetTimer(DelayedTimerHandle, this, &ADelayedMine::MineExplosion, CountdownTime);
	}
}

void ADelayedMine::MineExplosion()
{
	UE_LOG(LogTemp, Warning, TEXT("Mine Exploded"));
	TArray<FHitResult> OutHits;

	bool bBlockingHit = UKismetSystemLibrary::SphereTraceMulti(
		this,
		GetActorLocation(),
		GetActorLocation(),
		100.f,
		ETraceTypeQuery::TraceTypeQuery8,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForDuration,
		OutHits,
		true
	);

	if (bBlockingHit)
	{
		for (FHitResult HitResult : OutHits)
		{
			if (APlayerCharacter* Player = Cast<APlayerCharacter>(HitResult.GetActor()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit the Player!"));
			}
		}
	}
}
