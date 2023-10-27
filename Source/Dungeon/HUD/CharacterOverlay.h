#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class DUNGEON_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DamageText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* AttackRateText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* StunChanceText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* StunTimeText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CritChanceText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CritImproveText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* BlockRateText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* BlockAbsorbeText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LevelText;
};
