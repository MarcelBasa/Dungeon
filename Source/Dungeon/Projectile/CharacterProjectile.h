#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class DUNGEON_API ACharacterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterProjectile();
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit
		);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		float ExplodeSize = 0.2;

private:	
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleComp;
	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactEffect;

};
