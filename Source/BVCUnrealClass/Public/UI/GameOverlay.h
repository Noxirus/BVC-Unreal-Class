// Have a great day.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlay.generated.h"

class UTextBlock;

UCLASS()
class BVCUNREALCLASS_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateScoreText(int CurrentScore);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
};
