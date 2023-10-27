#include "Fire_Room.h"
#include "FireWall.h"
#include "Kismet/KismetMathLibrary.h"


void AFire_Room::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation += GetActorLocation();
}

void AFire_Room::StartRoom(int32 lvl)
{
	Super::StartRoom(lvl);

	CreateFireWallPath();
}

void AFire_Room::CreateFireWallPath()
{
	if (FireWallClass == nullptr) return;

	for (int i = 0; i < 3; i++)
	{
		Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, SpawnLocation, FRotator(0, -90, 0)));
		Wallarr[i]->SetOwner(this);
		Wallarr[i]->SetFireRate(float(1 - (0.01 * Roomlvl)));
		Wallarr[i]->FireLoopStart();
		SpawnLocation.X += 600;
	}
}

void AFire_Room::Destroyed()
{
	Super::Destroyed();

	for(AFireWall* x : Wallarr)
	{
		x->Destroy();
	}
}