// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerUp_Overlay.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class DUNGEON_API UPowerUp_Overlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* LeftButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RightButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* LeftButtonText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* RightButtonText;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void OnClickedLeft();
	UFUNCTION()
		void OnClickedRight();

private:
	FString RandUpdgade(float& RandUpgrade, FString& RandUpgradeName);
	void ApplyUpgrade(float Upgrade, FString UpgradeName);
	void CloseUpgradeWidget();

	float UpgradeLeft;
	FString UpgradeLeftName;

	float UpgradeRight;
	FString UpgradeRightName;

};
