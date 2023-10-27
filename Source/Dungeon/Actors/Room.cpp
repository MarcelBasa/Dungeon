#include "Room.h"
#include "Door.h"
#include "Dungeon/Characters/Enemy.h"
#include "Kismet/GameplayStatics.h"


ARoom::ARoom()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
	if (DoorClass)
		Door = GetWorld()->SpawnActor<ADoor>(DoorClass, GetActorLocation() + FVector(RoomLength,0,0), FRotator(0, -180, 0));
}

void ARoom::StartRoom(int32 lvl)
{
	Roomlvl = lvl;
}

ADoor* ARoom::DeleteRoom()
{
	if (Door)
		Door->CloseDoor();

	GetWorldTimerManager().SetTimer(
		DestroyTimer,
		this,
		&ThisClass::HandleDestroy,
		1.f
	);
	return Door;
}

void ARoom::HandleDestroy()
{
	Destroy();
}