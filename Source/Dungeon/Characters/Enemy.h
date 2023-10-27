#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UAnimMontage;
class UAnimationAsset;
class APlayerCharacter;
class UAnimInstance;
class UCurveFloat;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UParticleSystem;
class UParticleSystemComponent;
class UDamageType;

UCLASS()
class DUNGEON_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	void OnSpawn(FVector SpawnLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyDamage = 10;
	UPROPERTY(EditAnywhere)
		float AttackRate = 1.5f;
	UPROPERTY(EditAnywhere)
		float AttackEventDelay = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UDamageType> EnemyDamageType = nullptr;

	void StartAttack();
	void Stun(float Time);
	FTimerHandle StunTimer;
	void Ignite(int32 TickCount, float IgniteDamage);
	FTimerHandle IgniteTimer;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
private:
	UPROPERTY(EditAnywhere, Category = AI)
		UBehaviorTree* EnemyBehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* DamageTakenMontage = nullptr;
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* AttackMontage = nullptr;
	UAnimInstance* AnimInstance = nullptr;

	UPROPERTY(EditAnywhere, Category = Anim)
		UCurveFloat* GrowingUpCurve = nullptr;
	FTimeline GrowingUpTimeline;
	FVector StartLoc;
	FVector EndLoc;
	UPROPERTY(EditAnywhere)
		float ZOffSet = 170;
	UFUNCTION()
		void StartGrowingUp(float Value);
	UFUNCTION()
		void FinishGrowingUp();

	APlayerCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.f;
	float Health;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (GetOptions = "ChooseHand"))
		FString WeaponHand = "Right";
	UFUNCTION()
		TArray<FString> ChooseHand() const
	{
		return { "Left", "Right" };
	}	
	UPROPERTY(EditAnywhere, Category = Weapon)
		UAnimationAsset* WeaponAnim = nullptr;

	UPROPERTY(EditAnywhere, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh = nullptr;

	FTimerHandle DeathTimer;
	UPROPERTY(EditAnywhere)
		float DeathTime = 1.5f;
	UPROPERTY(EditAnywhere)
		UParticleSystem* DeathEffect;
	void DeathTimerFinish();
	void PlayDamageTakenMontage();

	bool bCanAttack = true;
	FTimerHandle AttackTimer;
	virtual void Attack();
	void AttackEvent();
	void AttackFinish();
	void PlayAttackMontage();

	bool bStuned = false;
	void StunFinish();
	UPROPERTY(EditAnywhere)
		UParticleSystem* StunEffect;
	UParticleSystemComponent* StunEffectComp;
	
	bool bIgnited = false;
	int32 IgniteTime = 0;
	float IgniteDamageDelegate = 0.f;
	void IgniteTick();
	void IgniteFinish();
	UPROPERTY(EditAnywhere)
		UParticleSystem* IgniteEffect;
	UParticleSystemComponent* IgniteEffectComp;
	UPROPERTY(EditAnywhere)
		FVector IgniteEffectSize = FVector(0.5f, 0.5f, 1.f);

public:
	FORCEINLINE bool IsAlive() const { return Health > 0 ? true : false; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return EnemyBehaviorTree; }
	FORCEINLINE UAnimInstance* GetAnimInstance() const { return AnimInstance; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
};
