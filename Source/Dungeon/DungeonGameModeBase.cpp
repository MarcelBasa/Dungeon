#include "DungeonGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon/Actors/Room.h"
#include "Dungeon/Actors/Door.h"
#include "Kismet/KismetMathLibrary.h"
#include "Dungeon/Controllers/DungeonPlayerController.h"


void ADungeonGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (StartRoomClass)
	{
		LastRoom = GetWorld()->SpawnActor<ARoom>(StartRoomClass, SpawnVector, FRotator(0, 0, 0));
		SpawnVector.X += LastRoom->GetRoomLength();
	}
}

void ADungeonGameModeBase::CreateConnector()
{
	if (ConnectorClass == nullptr) return;

	DestroyConnector();
	LastConnector = GetWorld()->SpawnActor<ARoom>(ConnectorClass, SpawnVector, FRotator(0, 0, 0));
	SpawnVector.X += LastConnector->GetRoomLength();
}
void ADungeonGameModeBase::DestroyConnector()
{
	if (ConnectorClass && LastConnector)
	{
		DoorToDestroy = LastDoor;
		GetWorldTimerManager().SetTimer(
			DestroyTimer,
			this,
			&ThisClass::DestroyDoor,
			1.f,
			false
		);
		LastDoor = LastConnector->DeleteRoom();
	}
}

void ADungeonGameModeBase::CreateRoom()
{
	RoomClassToSpawn = GetRandomRoom();
	if (RoomClassToSpawn == nullptr) return;

	DestroyRoom();
	LastRoom = GetWorld()->SpawnActor<ARoom>(RoomClassToSpawn, SpawnVector, FRotator(0, 0, 0));
	LastRoom->StartRoom(level);
	SpawnVector.X += LastRoom->GetRoomLength();
}
void ADungeonGameModeBase::DestroyRoom()
{
	if (RoomClassToSpawn && LastRoom)
	{
		DoorToDestroy = LastDoor;
		GetWorldTimerManager().SetTimer(
			DestroyTimer,
			this,
			&ThisClass::DestroyDoor,
			1.f,
			false
		);
		LastDoor = LastRoom->DeleteRoom();
	}
}

void ADungeonGameModeBase::CreateNextLevel()
{
	if (ConnectorRound)
	{
		CreateConnector();
		PlayerController = PlayerController == nullptr ? Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)) : PlayerController;
		if (PlayerController)
		{
			PlayerController->HandlePowerUp();
		}
	}
	else
	{
		CreateRoom();
		UpdateRoomLevel();
		level++;
	}
	ConnectorRound = !ConnectorRound;
}

void ADungeonGameModeBase::DestroyDoor()
{
	if (DoorToDestroy)
	{
		DoorToDestroy->Destroy();
	}
}

void ADungeonGameModeBase::UpdateRoomLevel()
{
	PlayerController = PlayerController == nullptr ? Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)) : PlayerController;
	if (PlayerController)
	{
		PlayerController->SetRoomLvl(level);
	}
}

TSubclassOf<ARoom> ADungeonGameModeBase::GetRandomRoom()
{
	return RoomClasses[UKismetMathLibrary::RandomIntegerInRange(0, RoomClasses.Num() - 1)];
}

void ADungeonGameModeBase::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}