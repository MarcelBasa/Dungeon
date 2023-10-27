#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "Enemy_Room.generated.h"

class AEnemy;
class UArrowComponent;

UCLASS()
class DUNGEON_API AEnemy_Room : public ARoom
{
	GENERATED_BODY()

public:
	AEnemy_Room();
	virtual void StartRoom(int32 lvl) override;


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AEnemy>> EnemyToSpawnClasses;
	UPROPERTY(EditAnywhere)
		TArray<UArrowComponent*> SpawnPoints;
	UPROPERTY(EditAnywhere)
		int32 SpawnPointsCount = 6;

	void SpawnEnemy();
	TSubclassOf<AEnemy> GetRandomEnemyClass();
	UArrowComponent* GetRandomSpawnPoint(TArray<UArrowComponent*> arr);
	void UpdateNavMeshLocation();
};
