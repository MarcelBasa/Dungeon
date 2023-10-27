#include "PowerUp_Overlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Dungeon/Characters/PlayerCharacter.h"
#include "Dungeon/Controllers/DungeonPlayerController.h"
#include "Dungeon/Actors/Weapon.h"
#include "Dungeon/Actors/Shield.h"
#include "Kismet/GameplayStatics.h"

void UPowerUp_Overlay::NativeConstruct()
{
	Super::NativeConstruct();

	LeftButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedLeft);
	RightButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedRight);

	LeftButtonText->SetText(FText::FromString(RandUpdgade(UpgradeLeft, UpgradeLeftName)));
	RightButtonText->SetText(FText::FromString(RandUpdgade(UpgradeRight, UpgradeRightName)));

	bIsFocusable = true;
}

void UPowerUp_Overlay::OnClickedLeft()
{
	ApplyUpgrade(UpgradeLeft, UpgradeLeftName);
	CloseUpgradeWidget();
}
void UPowerUp_Overlay::OnClickedRight()
{
	ApplyUpgrade(UpgradeRight, UpgradeRightName);
	CloseUpgradeWidget();
}

FString UPowerUp_Overlay::RandUpdgade(float& RandUpgrade, FString& RandUpgradeName)
{
	FString UpgradeText;
	int32 Rand = UKismetMathLibrary::RandomIntegerInRange(0, 8);
	switch (Rand)
	{
		case 0:
		{
			RandUpgrade = UKismetMathLibrary::RandomIntegerInRange(1, 10);
			RandUpgradeName = TEXT("Damage");
			UpgradeText = FString::Printf(TEXT("Damage +%d"), FMath::CeilToInt(RandUpgrade));
			break;
		}
		case 1:
		{
			RandUpgrade = UKismetMathLibrary::RandomFloatInRange(0.1, 0.2);
			RandUpgradeName = TEXT("Attack Rate");
			UpgradeText = FString::Printf(TEXT("Attack Rate +%.2f"), RandUpgrade);
			break;
		}
		case 2:
		{
			RandUpgrade = UKismetMathLibrary::RandomIntegerInRange(1, 10);
			RandUpgradeName = TEXT("Stun Chance");
			UpgradeText = FString::Printf(TEXT("Stun Chance +%d%%"), FMath::CeilToInt(RandUpgrade));
			break;
		}
		case 3:
		{
			RandUpgrade = UKismetMathLibrary::RandomIntegerInRange(1, 5);
			RandUpgradeName = TEXT("Stun Time");
			UpgradeText = FString::Printf(TEXT("Stun Time +%d"), FMath::CeilToInt(RandUpgrade));
			break;
		}
		case 4:
		{
			RandUpgrade = UKismetMathLibrary::RandomIntegerInRange(1, 10);
			RandUpgradeName = TEXT("Crit Chance");
			UpgradeText = FString::Printf(TEXT("Crit Chance +%d%%"), FMath::CeilToInt(RandUpgrade));
			break;
		}
		case 5:
		{
			RandUpgrade = UKismetMathLibrary::RandomFloatInRange(0.1, 0.2);
			RandUpgradeName = TEXT("Crit Improve");
			UpgradeText = FString::Printf(TEXT("Crit Improve +%.2f"), RandUpgrade);
			break;
		}
		case 6:
		{
			RandUpgrade = UKismetMathLibrary::RandomFloatInRange(0.1, 0.2);
			RandUpgradeName = TEXT("Block Rate");
			UpgradeText = FString::Printf(TEXT("Block Rate +%.2f"), RandUpgrade);
			break;
		}
		case 7:
		{
			RandUpgrade = UKismetMathLibrary::RandomIntegerInRange(1, 10);
			RandUpgradeName = TEXT("Block Absorbe");
			UpgradeText = FString::Printf(TEXT("Block Absorbe +%d%%"), FMath::CeilToInt(RandUpgrade));
			break;
		}
		case 8:
		{
			RandUpgrade = UKismetMathLibrary::RandomIntegerInRange(50, 100);
			RandUpgradeName = TEXT("Health");
			UpgradeText = FString::Printf(TEXT("Health +%d"), FMath::CeilToInt(RandUpgrade));
			break;
		}
		default:
			break;
	}
	return UpgradeText;
}

void UPowerUp_Overlay::ApplyUpgrade(float Upgrade, FString UpgradeName)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (Player == nullptr || 
		Player->Weapon == nullptr || 
		Player->Shield == nullptr) return;

	if (UpgradeName == "Damage")
	{
		Player->Weapon->Damage += Upgrade;
	}
	else if (UpgradeName == "Attack Rate")
	{
		Player->Weapon->AttackRate += Upgrade;
	}
	else if (UpgradeName == "Stun Chance")
	{
		Player->Weapon->StunChance += Upgrade;
	}
	else if (UpgradeName == "Stun Time")
	{
		Player->Weapon->StunTime += Upgrade;
	}
	else if (UpgradeName == "Crit Chance")
	{
		Player->Weapon->CritChance += Upgrade;
	}
	else if (UpgradeName == "Crit Improve")
	{
		Player->Weapon->CritImprove += Upgrade;
	}
	else if (UpgradeName == "Block Rate")
	{
		Player->Shield->BlockRate += Upgrade;
	}
	else if (UpgradeName == "Block Absorbe")
	{
		Player->Shield->BlockAbsorbe += Upgrade;
	}
	else if (UpgradeName == "Health")
	{
		Player->AddHealth(Upgrade);
	}
}

void UPowerUp_Overlay::CloseUpgradeWidget()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(Player->Controller);

	if (PlayerController && Player)
	{
		PlayerController->HandlePowerUpClose();
		PlayerController->HideMouse();
		Player->UpdateHUDStarts();
		Player->UpdateHUDHealth();
		RemoveFromParent();
	}
}