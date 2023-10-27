#include "CombatComponent.h"
#include "Dungeon/Characters/PlayerCharacter.h"
#include "Dungeon/Characters/Enemy.h"
#include "Dungeon/Actors/Weapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon/Actors/Weapon.h"
#include "Dungeon/Actors/Shield.h"
#include "Kismet/KismetMathLibrary.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UCombatComponent::SetupWeapon(AWeapon* WeaponToEquip)
{
	Weapon = WeaponToEquip;
}

void UCombatComponent::SetupShield(AShield* ShieldToEquip)
{
	Shield = ShieldToEquip;
}

void UCombatComponent::AttackButtonPressed(bool bPressed)
{
	if (Character == nullptr || Character->CollisionMesh == nullptr || Weapon == nullptr) return;

	bAttackButtonPressed = bPressed;
	if (bAttackButtonPressed)
	{
		Attack();
	}
}
void UCombatComponent::Attack()
{
	if (bCanInteract && bAttackButtonPressed)
	{
		bCanInteract = false;
		Character->PlayAttackMontage();
		StartAttackTimer(); 
	}
}
void UCombatComponent::StartAttackTimer()
{
	if (Character == nullptr || Weapon == nullptr) return;

	Character->GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&ThisClass::AttackTimerFinished,
		1/Weapon->AttackRate
	);
}
void UCombatComponent::AttackTimerFinished()
{
	HitedActors.Empty();
	bCanInteract = true;
	if (bCanInteract && bAttackButtonPressed)
	{
		Attack();
	}
	else if(bCanInteract && bBlockButtonPressed && Shield)
	{
		Block();
	}
}

void UCombatComponent::BlockButtonPressed(bool bPressed)
{
	if (Character == nullptr || Shield == nullptr) return;

	bBlockButtonPressed = bPressed;
	Block(); 
}
void UCombatComponent::Block()
{
	if (bCanInteract && bBlockButtonPressed)
	{
		BlockStart();
	}
	else if ( bBlockButtonPressed == false)
	{
		BlockFinish();
		if (bCanInteract && bAttackButtonPressed)
		{
			Attack();
		}
	}
}
void UCombatComponent::StartBlockingTimer()
{
	bBlocking = true;
}
void UCombatComponent::BlockStart() 
{
	bCanInteract = false;
	bBlockingAnimation = true;
	Character->GetWorldTimerManager().SetTimer(
		BlockTimer,
		this,
		&ThisClass::StartBlockingTimer,
		1 / Shield->BlockRate * 0.4
	);
}
void UCombatComponent::BlockFinish()
{
	bCanInteract = true;
	bBlockingAnimation = false;
	if (Character->GetWorldTimerManager().IsTimerActive(BlockTimer))
		Character->GetWorldTimerManager().ClearTimer(BlockTimer);
	bBlocking = false;
}

void UCombatComponent::DealDamage(AActor* OverlappedActor)
{
	AEnemy* Enemy = Cast<AEnemy>(OverlappedActor);
	if (Enemy == nullptr || HitedActors.Contains(OverlappedActor)) return;
	

	int32 Rand = UKismetMathLibrary::RandomIntegerInRange(1, 100);
	if(Rand < Weapon->StunChance)
		Enemy->Stun(Weapon->StunTime);
	
	Rand = UKismetMathLibrary::RandomIntegerInRange(1, 100);
	FVector HitEffectSize = FVector(0.3);
	float Damage = Weapon->Damage;
	if (Rand < Weapon->CritChance)
	{
		Damage *= Weapon->CritImprove;
		HitEffectSize = FVector(0.6);
	}
	//Enemy->Ignite(5, 5);

	if (Weapon->HitEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Weapon->HitEffect, FTransform(Character->GetActorRotation(), Enemy->GetActorLocation(), HitEffectSize));
	HitedActors.Add(OverlappedActor);
	UGameplayStatics::ApplyDamage(
		Enemy,
		Damage,
		Character->GetController(), 
		Character, 
		Weapon->WeaponDamageType);
}