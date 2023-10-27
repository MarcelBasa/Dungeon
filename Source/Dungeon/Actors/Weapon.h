#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;

UCLASS()
class DUNGEON_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Stats)
		float AttackRate = 1.f;
	UPROPERTY(EditAnywhere, Category = Stats)
		float Damage = 10.f;
	UPROPERTY(EditAnywhere, Category = Stats)
		int32 StunChance = 10;
	UPROPERTY(EditAnywhere, Category = Stats)
		float StunTime = 2.f;
	UPROPERTY(EditAnywhere, Category = Stats)
		int32 CritChance = 10;
	UPROPERTY(EditAnywhere, Category = Stats)
		float CritImprove = 1.5f;


	UPROPERTY(EditAnywhere, Category = Stats)
		float DamagePower = 10.f;
	UPROPERTY(EditAnywhere, Category = Stats)
		float Precision = 1.f;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class UDamageType > WeaponDamageType;
	UPROPERTY(EditAnywhere)
		UParticleSystem* HitEffect;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh;

};
