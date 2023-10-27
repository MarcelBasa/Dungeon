#include "Enemy_Explode_Room.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


AEnemy_Explode_Room::AEnemy_Explode_Room()
{
	Pillar = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Pillar"));
	Pillar->SetupAttachment(RootComponent);
}

void AEnemy_Explode_Room::BeginPlay()
{
	Super::BeginPlay();

	Temp = SpawnVector.Y -= 600 - 70;
	CreatePillarPath();
}

void AEnemy_Explode_Room::CreatePillarPath()
{
	int32 Y = Temp;
	while (SpawnVector.X <= RoomLength - 200)
	{
		while (Y <= 600 - 100)
		{
			SpawnVector.Y = Y;
			Pillar->AddInstance(FTransform(SpawnVector));
			Y += UKismetMathLibrary::RandomIntegerInRange(150, 300);
		}
		Y = Temp;
		SpawnVector.X += UKismetMathLibrary::RandomIntegerInRange(150, 400);
	}
	
}