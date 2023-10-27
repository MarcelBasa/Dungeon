#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireWall.generated.h"

class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class DUNGEON_API AFireWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AFireWall();
	void FireLoopStart();
	void Fire();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage = 10.f;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* WallMesh;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere)
		float FireRate = 0.8f;
	FTimerHandle FireTimer;
	UPROPERTY(EditAnywhere)
		UParticleSystem* SpawnEffect;

public:
	FORCEINLINE void SetFireRate(float newFireRate) { FireRate = newFireRate; }
};
