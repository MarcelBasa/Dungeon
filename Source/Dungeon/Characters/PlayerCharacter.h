#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dungeon/CameraShake/ReactCameraShake.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class AWeapon;
class AShield;
class UAnimMontage;
class UCombatComponent;
class UBoxComponent;
class UReactCameraShake;
class ADungeonGameModeBase;
class ADungeonPlayerController;

UCLASS()
class DUNGEON_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
		void SetWeaponCollision(bool Active);
	void PlayAttackMontage();
	void PlayShieldImpactMontage();
	void PlayHitImpactMontage();
	void PlayUnsheatheAnimation();

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionMesh = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UReactCameraShake> ReactCameraShake;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UReactCameraShake> BlockCameraShake;
	UPROPERTY()
		AWeapon* Weapon = nullptr;
	UPROPERTY()
		AShield* Shield = nullptr;

	void DestroyShield();
	UFUNCTION(BlueprintCallable)
		void Dead();
	void UpdateHUDHealth();
	void UpdateHUDStarts();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	UFUNCTION()
		virtual void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera = nullptr;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* ArmsMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCombatComponent* Combat;

	UPROPERTY(EditAnywhere, Category = Item)
		TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, Category = Item)
		TSubclassOf<AShield> ShieldClass;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* ImpactMontage;
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* UnsheatheAnim;

	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.f;
	float Health;

	ADungeonGameModeBase* GameMode;
	ADungeonPlayerController* DungeonPlayerController;

	void SpawnWeapon();
	void SpawnShield();

	void AttackButtonPressed();
	void AttackButtonReleased();

	void BlockButtonPressed();
	void BlockButtonReleased();

	void MenuButtonPressed();

public:
	bool IsBlocking();
	float GetBlockRate();

	FRotator GetCameraRotation();
	FORCEINLINE void AddHealth(float HealthToAdd) { Health += HealthToAdd; MaxHealth += HealthToAdd; }
	FORCEINLINE void SetHealthMax() { Health = MaxHealth; }
};
