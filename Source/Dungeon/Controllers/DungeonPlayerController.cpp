#include "DungeonPlayerController.h"
#include "Dungeon/HUD/Dungeon_HUD.h"
#include "Dungeon/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Camera/PlayerCameraManager.h"
#include "Dungeon/Characters/PlayerCharacter.h"


void ADungeonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
}

void ADungeonPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;

	bool bHUDValid = DungeonHUD &&
		DungeonHUD->CharacterOverlay &&
		DungeonHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		FString HealthText = FString::Printf(TEXT("Health: %d"), FMath::CeilToInt(Health));
		DungeonHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void ADungeonPlayerController::SetHUDStats(float Damage, float AttackRate, int32 StunChance, float StunTime, int32 CritChance, float CritImprove, float BlockRate, int32 BlockAbsorbe)
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;

	bool bHUDValid = DungeonHUD &&
		DungeonHUD->CharacterOverlay &&
		DungeonHUD->CharacterOverlay->DamageText &&
		DungeonHUD->CharacterOverlay->AttackRateText &&
		DungeonHUD->CharacterOverlay->StunChanceText &&
		DungeonHUD->CharacterOverlay->StunTimeText &&
		DungeonHUD->CharacterOverlay->CritChanceText &&
		DungeonHUD->CharacterOverlay->CritImproveText && 
		DungeonHUD->CharacterOverlay->BlockRateText &&
		DungeonHUD->CharacterOverlay->BlockAbsorbeText
		;
	if (bHUDValid)
	{
		FString Text = FString::Printf(TEXT("Damage: %d"), FMath::CeilToInt(Damage));
		DungeonHUD->CharacterOverlay->DamageText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Attack Rate: %.2f"), AttackRate);
		DungeonHUD->CharacterOverlay->AttackRateText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Stun Chance: %d%%"), StunChance);
		DungeonHUD->CharacterOverlay->StunChanceText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Stun Time: %.2f"), StunTime);
		DungeonHUD->CharacterOverlay->StunTimeText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Crit Chance: %d%%"), CritChance);
		DungeonHUD->CharacterOverlay->CritChanceText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Crit Improve: %.2f"), CritImprove);
		DungeonHUD->CharacterOverlay->CritImproveText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Block Rate: %.2f"), BlockRate);
		DungeonHUD->CharacterOverlay->BlockRateText->SetText(FText::FromString(Text));
		Text = FString::Printf(TEXT("Block Absorbe: %d%%"), BlockAbsorbe);
		DungeonHUD->CharacterOverlay->BlockAbsorbeText->SetText(FText::FromString(Text));
	}
}

void ADungeonPlayerController::SetRoomLvl(int32 level)
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;

	bool bHUDValid = DungeonHUD &&
		DungeonHUD->CharacterOverlay &&
		DungeonHUD->CharacterOverlay->LevelText;
	if (bHUDValid)
	{
		FString LevelText = FString::Printf(TEXT("Level: %d"), level);
		DungeonHUD->CharacterOverlay->LevelText->SetText(FText::FromString(LevelText));
	}
}

void ADungeonPlayerController::HandleMatchHasStarted()
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;
	if (DungeonHUD)
	{
		if (DungeonHUD->CharacterOverlay == nullptr) 
			DungeonHUD->AddCharacterOverlay();
	}
}

void ADungeonPlayerController::HandlePowerUp()
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;
	PlayerCharacter = PlayerCharacter == nullptr ? Cast<APlayerCharacter>(GetCharacter()) : PlayerCharacter;

	if (DungeonHUD && PlayerCharacter)
	{
		DungeonHUD->AddPowerUpOverlay();
		ShowMouse();
	}
}
void ADungeonPlayerController::HandlePowerUpClose()
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;

	if (DungeonHUD)
	{
		DungeonHUD->PowerUpOverlay = nullptr;
	}
}

void ADungeonPlayerController::HandleOpenCloseMenu()
{
	DungeonHUD = DungeonHUD == nullptr ? Cast<ADungeon_HUD>(GetHUD()) : DungeonHUD;

	if (DungeonHUD && DungeonHUD->PowerUpOverlay == nullptr)
	{
		if (DungeonHUD->Menu)
		{
			ResumeGame();
		}
		else if (DungeonHUD->Menu == nullptr)
		{
			OpenMenu();
		}		
	}	
}

void ADungeonPlayerController::ResumeGame()
{
	if (DungeonHUD)
	{
		HideMouse();
		DungeonHUD->DestroyMenu();
	}
}

void ADungeonPlayerController::OpenMenu()
{
	if (DungeonHUD)
	{
		ShowMouse();
		DungeonHUD->AddMenu();
	}
}

void ADungeonPlayerController::ShowMouse()
{
	bShowMouseCursor = true;
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	SetMouseLocation(ViewportSizeX * 0.5, ViewportSizeY * 0.5);
	SetInputMode(FInputModeGameAndUI());
}

void ADungeonPlayerController::HideMouse()
{
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}