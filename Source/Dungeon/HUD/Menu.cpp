#include "Menu.h"
#include "Components/Button.h"
#include "Dungeon/Controllers/DungeonPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &ThisClass::Quit);
	ResumeButton->OnClicked.AddDynamic(this, &ThisClass::Resume);
}

void UMenu::Quit()
{
	ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
		PlayerController->ConsoleCommand("quit");
}

void UMenu::Resume()
{
	ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
		PlayerController->ResumeGame();
}