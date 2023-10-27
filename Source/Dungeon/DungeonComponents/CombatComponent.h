#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class APlayerCharacter;
class AWeapon;
class AShield;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY()
		APlayerCharacter* Character = nullptr;

	void SetupWeapon(AWeapon* WeaponToEquip);
	void SetupShield(AShield* ShieldToEquip);

	void AttackButtonPressed(bool bPressed);
	void BlockButtonPressed(bool bPressed);
	bool bBlockingAnimation = false;
	bool bBlocking = false;
	void BlockFinish();

	void DealDamage(AActor* OverlappedActor);

protected:
	virtual void BeginPlay() override;

private:	
	AWeapon* Weapon;
	AShield* Shield;

	bool bAttackButtonPressed = false;
	bool bBlockButtonPressed = false;
	bool bCanInteract = true;

	FTimerHandle AttackTimer;
	FTimerHandle BlockTimer;
	TArray<AActor*> HitedActors;

	void Attack();
	void StartAttackTimer();
	void AttackTimerFinished();
	
	void Block();
	void StartBlockingTimer();
	void BlockStart();
};
