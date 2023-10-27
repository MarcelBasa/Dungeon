#pragma once

#include "CoreMinimal.h"
#include "Enemy_Room.h"
#include "Enemy_Explode_Room.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class DUNGEON_API AEnemy_Explode_Room : public AEnemy_Room
{
	GENERATED_BODY()
	
public:
	AEnemy_Explode_Room();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* Pillar;

	int32 Temp;
	FVector SpawnVector = FVector(350, 0, 0);

	void CreatePillarPath();
};
