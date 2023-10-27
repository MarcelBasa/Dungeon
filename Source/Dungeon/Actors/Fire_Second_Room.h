#pragma once

#include "CoreMinimal.h"
#include "Fire_Room.h"
#include "Fire_Second_Room.generated.h"


UCLASS()
class DUNGEON_API AFire_Second_Room : public AFire_Room
{
	GENERATED_BODY()
	
public:
	virtual void StartRoom(int32 lvl) override;

protected:
	virtual void BeginPlay() override;
	virtual void CreateFireWallPath() override;

private:
	void StartFire();
	int32 counter = 0;
	FTimerHandle FireTimer;

};
