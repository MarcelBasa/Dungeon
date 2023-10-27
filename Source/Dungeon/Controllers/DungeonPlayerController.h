#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonPlayerController.generated.h"

class ADungeon_HUD;
class UCharacterOverlay;
class APlayerCharacter;

UCLASS()
class DUNGEON_API ADungeonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ShowMouse();
	void HideMouse();
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDStats(
		float Damage, 
		float AttackRate,
		int32 StunChance,
		float StunTime,
		int32 CritChance,
		float CritImprove,
		float BlockRate,
		int32 BlockAbsorbe
		);
	void SetRoomLvl(int32 level);
	void HandleMatchHasStarted();
	void HandlePowerUp();
	void HandlePowerUpClose();
	void HandleOpenCloseMenu();
	void ResumeGame();
	void OpenMenu();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		ADungeon_HUD* DungeonHUD;
	APlayerCharacter* PlayerCharacter;

};
