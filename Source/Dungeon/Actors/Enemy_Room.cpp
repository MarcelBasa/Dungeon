#include "Enemy_Room.h"
#include "Dungeon/Characters/Enemy.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"


AEnemy_Room::AEnemy_Room()
{
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	for (int32 i = 0; i < SpawnPointsCount; i++)
	{
		SpawnPoints.Add(CreateDefaultSubobject<UArrowComponent>(FName("Spawn Point " + FString::FromInt(i))));
		SpawnPoints[i]->SetupAttachment(RootComponent);
	}
}

void AEnemy_Room::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy_Room::StartRoom(int32 lvl)
{
	Super::StartRoom(lvl);
	
	UpdateNavMeshLocation();
	SpawnEnemy();
}

void AEnemy_Room::SpawnEnemy()
{
	TArray<UArrowComponent*> LoopArr = SpawnPoints;
	int32 EnemyToSpawnCount = (Roomlvl/5)+1;
	for (int i = 0; i < EnemyToSpawnCount; i++)
	{
		TSubclassOf<AEnemy> RandEnemyClass = GetRandomEnemyClass();
		UArrowComponent* RandSpawnPoint = GetRandomSpawnPoint(LoopArr);
		LoopArr.RemoveAt(LoopArr.Find(RandSpawnPoint));
		if (RandEnemyClass && RandSpawnPoint)
		{
			GetWorld()->SpawnActor<AEnemy>(RandEnemyClass, RandSpawnPoint->GetComponentLocation(), FRotator(0, 0, 0));
		}
	}
}

TSubclassOf<AEnemy> AEnemy_Room::GetRandomEnemyClass()
{
	return EnemyToSpawnClasses[UKismetMathLibrary::RandomIntegerInRange(0, EnemyToSpawnClasses.Num() - 1)];
}

UArrowComponent* AEnemy_Room::GetRandomSpawnPoint(TArray<UArrowComponent*> arr)
{
	return arr[UKismetMathLibrary::RandomIntegerInRange(0, arr.Num() - 1)];
}

void AEnemy_Room::UpdateNavMeshLocation()
{
	ANavMeshBoundsVolume* NavMesh = Cast<ANavMeshBoundsVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), ANavMeshBoundsVolume::StaticClass()));
	if (NavMesh)
	{
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		NavMesh->SetActorLocation(GetActorLocation()+FVector((RoomLength/2), 0, 0));
		NavSystem->OnNavigationBoundsUpdated(NavMesh);
	}
}