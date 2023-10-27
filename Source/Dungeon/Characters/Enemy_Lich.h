#pragma once

#include "CoreMinimal.h"
#include "Enemy_range.h"
#include "Enemy_Lich.generated.h"

class AEnemy;
class UAnimMontage;

UCLASS()
class DUNGEON_API AEnemy_Lich : public AEnemy_range
{
	GENERATED_BODY()

public:
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

private:
	float SpawnRange = 800.f;
	UPROPERTY(EditAnywhere)
		float SpawnRate = 8.f;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemy> EnemyToSpawnClass;
	UPROPERTY(EditAnywhere)
		UAnimMontage* SpawnMontage;
	UPROPERTY(EditAnywhere)
		UParticleSystem* SpawnEffect;
	UParticleSystemComponent* SpawnEffectComp;
	UPROPERTY(EditAnywhere)
		float SpawnEffectTime = 1.3f;
	FTimerHandle SpawnEffectTimer;
	FTimerHandle SpawnTimer;

	void SpawnNewEnemy();
	void PlaySpawnMontage();
	void FinishSpawnEffect();
	FNavLocation GetRandomNavMeshPoint();
};
