#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Enemy_Explode.generated.h"


UCLASS()
class DUNGEON_API AEnemy_Explode : public AEnemy
{
	GENERATED_BODY()
	
public:
	AEnemy_Explode();
	virtual void Destroyed() override;
	virtual void Attack() override;

private:
	UPROPERTY(EditAnywhere)
		float ExplodeDamage = 50.f;
	UPROPERTY(EditAnywhere)
		float ExplodeRadius = 200.f;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class UDamageType > ExplodeDamageType = nullptr;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> ActorToIgnoreExplode;
	UPROPERTY(EditAnywhere)
		UParticleSystem* ExplodeEffect;

};
