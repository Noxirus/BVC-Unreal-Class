// Have a great day.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BVCUNREALCLASS_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ChangeScore(int ChangeAmount);

private:
	int CurrentScore = 0;
};
