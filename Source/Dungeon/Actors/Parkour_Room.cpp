#include "Parkour_Room.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


AParkour_Room::AParkour_Room()
{
	Platform = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Platform"));
	RootComponent = Platform;
}

void AParkour_Room::BeginPlay()
{
	Super::BeginPlay();

	RoomWidth -= 100;
	CreatePlatformPath();
}

void AParkour_Room::CreatePlatformPath()
{
	if (Platform == nullptr) return;

	float X = SpawnLocation.X;
	while (X <= RoomLength - 300)
	{
		Platform->AddInstance(FTransform(FRotator(0, 0, 0), SpawnLocation, FVector(1, 1, 1)));

		X = UKismetMathLibrary::RandomFloatInRange(SpawnLocation.X + 200, SpawnLocation.X + 350);
		if (X <= RoomLength - 400)
			SpawnLocation.X = X;
		else
			SpawnLocation.X = X - 120;

		float Y = UKismetMathLibrary::RandomFloatInRange(SpawnLocation.Y - 300, SpawnLocation.Y + 300);
		if(Y > -1 * RoomWidth && Y < RoomWidth)
			SpawnLocation.Y = Y;
		SpawnLocation.Z = UKismetMathLibrary::RandomFloatInRange(SpawnLocation.Z - 10, SpawnLocation.Z + 70);
	}
}