#include "Dungeon_HUD.h"
#include "GameFramework/PlayerController.h"
#include "CharacterOverlay.h"
#include "PowerUp_Overlay.h"
#include "Menu.h"
#include "Dungeon/DungeonGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void ADungeon_HUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
		CharacterOverlay->AddToViewport();
	}
}

void ADungeon_HUD::AddPowerUpOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && PowerUpOverlayClass)
	{
		PowerUpOverlay = CreateWidget<UPowerUp_Overlay>(PlayerController, PowerUpOverlayClass);
		PowerUpOverlay->AddToViewport();
	}
}

void ADungeon_HUD::AddMenu()
{
	ADungeonGameModeBase* GameMode = Cast<ADungeonGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && MenuClass)
	{
		Menu = CreateWidget<UMenu>(PlayerController, MenuClass);
		Menu->AddToViewport();
	}
}

void ADungeon_HUD::DestroyMenu()
{
	if (Menu)
	{
		Menu->RemoveFromParent();
		Menu = nullptr;
	}
}
