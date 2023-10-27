#include "Enemy_Lich.h"
#include "NavigationSystem.h"
#include "Dungeon/Controllers/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


void AEnemy_Lich::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		SpawnTimer,
		this,
		&ThisClass::SpawnNewEnemy,
		SpawnRate,
		true
	);
}

FNavLocation AEnemy_Lich::GetRandomNavMeshPoint()
{
	FNavLocation ResultLocation;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), SpawnRange, ResultLocation);

	return ResultLocation;
}

void AEnemy_Lich::SpawnNewEnemy()
{
	if (EnemyToSpawnClass)
	{
		PlaySpawnMontage();

		FNavLocation ResultLocation = GetRandomNavMeshPoint();

		if (SpawnEffect)
			SpawnEffectComp = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				SpawnEffect,
				ResultLocation
			);
		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyToSpawnClass, ResultLocation.Location, FRotator(0, 0, 0));
		SpawnedEnemy->OnSpawn(ResultLocation.Location);
		GetWorldTimerManager().SetTimer(
			SpawnEffectTimer,
			this,
			&ThisClass::FinishSpawnEffect,
			SpawnEffectTime
		);
	}
}

void AEnemy_Lich::FinishSpawnEffect()
{
	if (SpawnEffect)
		SpawnEffectComp->SetActive(false);
}

void AEnemy_Lich::PlaySpawnMontage()
{
	if (GetAnimInstance() && SpawnMontage)
	{
		GetAnimInstance()->Montage_Play(SpawnMontage);
	}
}

void AEnemy_Lich::Destroyed()
{
	Super::Destroyed();

	if (SpawnEffectComp && SpawnEffectComp->IsActive())
		SpawnEffectComp->SetActive(false);
}
