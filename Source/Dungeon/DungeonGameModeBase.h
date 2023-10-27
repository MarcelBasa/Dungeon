#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonGameModeBase.generated.h"

class ARoom;
class ADoor;
class ADungeonPlayerController;

UCLASS()
class DUNGEON_API ADungeonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void CreateNextLevel();
	void RestartGame();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ARoom> StartRoomClass;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ARoom>> RoomClasses;
	TSubclassOf<ARoom> RoomClassToSpawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ARoom> ConnectorClass;

	ARoom* LastRoom = nullptr;
	ARoom* LastConnector = nullptr;
	ADoor* LastDoor = nullptr;
	ADoor* DoorToDestroy = nullptr;
	FVector SpawnVector = FVector(0, 0, 0);
	FTimerHandle DestroyTimer;
	bool ConnectorRound = true;
	int32 level = 1;
	ADungeonPlayerController* PlayerController = nullptr;

	void CreateConnector();
	void DestroyConnector();

	void CreateRoom();
	void DestroyRoom();

	void UpdateRoomLevel();

	void DestroyDoor();
	TSubclassOf<ARoom> GetRandomRoom();
};
