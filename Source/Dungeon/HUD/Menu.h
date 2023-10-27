#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;

UCLASS()
class DUNGEON_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
		UButton* ResumeButton;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void Quit();
	UFUNCTION()
		void Resume();
};
