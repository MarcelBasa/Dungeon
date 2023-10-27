#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class UStaticMeshComponent;
class ADoor;

UCLASS()
class DUNGEON_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoom();
	ADoor* DeleteRoom();
	virtual void StartRoom(int32 lvl);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int32 RoomLength = 1200;
	int32 Roomlvl = 1;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ADoor> DoorClass;
	ADoor* Door;
	FTimerHandle DestroyTimer;

	void HandleDestroy();

public:
	FORCEINLINE int32 GetRoomLength() const { return RoomLength; }
};
