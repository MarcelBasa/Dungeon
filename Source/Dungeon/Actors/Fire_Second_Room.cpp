#include "Fire_Second_Room.h"
#include "Kismet/KismetMathLibrary.h"


void AFire_Second_Room::BeginPlay() 
{
	Super::BeginPlay();

}

void AFire_Second_Room::StartRoom(int32 lvl)
{
	Super::StartRoom(lvl);

	counter = UKismetMathLibrary::RandomIntegerInRange(0, Wallarr.Num() - 1);
	StartFire();
}

void AFire_Second_Room::CreateFireWallPath()
{
	Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, GetActorLocation() + FVector(0, 200, 0), FRotator(0, -50, 0)));
	Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, GetActorLocation() + FVector(424, 600, 0), FRotator(0, -90, 0)));
	Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, GetActorLocation() + FVector(1008, 619, 0), FRotator(0, -140, 0)));

	Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, GetActorLocation() + FVector(1410, -154, 0), FRotator(0, 140, 0)));
	Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, GetActorLocation() + FVector(1024, -600, 0), FRotator(0, 90, 0)));
	Wallarr.Add(GetWorld()->SpawnActor<AFireWall>(FireWallClass, GetActorLocation() + FVector(487, -639, 0), FRotator(0, 50, 0)));
}

void AFire_Second_Room::StartFire()
{
	if (Wallarr[counter % Wallarr.Num()] == nullptr) return;

	Wallarr[counter % Wallarr.Num()]->Fire();
	counter++;
	GetWorldTimerManager().SetTimer(
		FireTimer,
		this,
		&ThisClass::StartFire,
		float(1 - (0.01 * Roomlvl)),
		true
	);
}