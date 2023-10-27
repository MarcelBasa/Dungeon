#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "Fire_Room.generated.h"

class AFireWall;

UCLASS()
class DUNGEON_API AFire_Room : public ARoom
{
	GENERATED_BODY()
	
public:
	virtual void Destroyed() override;
	virtual void StartRoom(int32 lvl) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AFireWall> FireWallClass;

	FVector SpawnLocation = FVector(0, 600, 0);
	TArray<AFireWall*> Wallarr;

	virtual void CreateFireWallPath();

};
