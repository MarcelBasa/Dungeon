#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dungeon_HUD.generated.h"

class UCharacterOverlay;
class UPowerUp_Overlay;
class UMenu;
class UUserWidget;

UCLASS()
class DUNGEON_API ADungeon_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "PlayerStats")
		TSubclassOf<UUserWidget> CharacterOverlayClass;
	void AddCharacterOverlay();

	UPROPERTY(EditAnywhere, Category = "PlayerStats")
		TSubclassOf<UUserWidget> PowerUpOverlayClass;
	void AddPowerUpOverlay();

	UPROPERTY(EditAnywhere, Category = "PlayerStats")
		TSubclassOf<UUserWidget> MenuClass;
	void AddMenu();
	void DestroyMenu();

	UPROPERTY()
		UCharacterOverlay* CharacterOverlay;
	UPROPERTY()
		UPowerUp_Overlay* PowerUpOverlay;
	UPROPERTY()
		UMenu* Menu = nullptr;
};

