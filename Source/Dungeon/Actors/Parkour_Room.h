#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "Parkour_Room.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class DUNGEON_API AParkour_Room : public ARoom
{
	GENERATED_BODY()
	
public:
	AParkour_Room();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* Platform;
	
	void CreatePlatformPath();
	FVector SpawnLocation = FVector(500, 0, -400);
	UPROPERTY(EditAnywhere)
		float RoomWidth = 600.f;

};
