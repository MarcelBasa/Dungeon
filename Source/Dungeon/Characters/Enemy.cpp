#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"
#include "Components/TimelineComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetupAttachment(GetMesh());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponMesh)
	{
		if (WeaponHand == "Left")
		{
			WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SKT_Bow"));
		}
		else 
			WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SKT_Sword"));
	}

	Health = MaxHealth;
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::TakeDamage);

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("StartGrowingUp"));
	
	FOnTimelineEvent FinishEvent;
	FinishEvent.BindUFunction(this, FName("FinishGrowingUp"));

	GrowingUpTimeline.AddInterpFloat(GrowingUpCurve, ProgressUpdate);
	GrowingUpTimeline.SetTimelineFinishedFunc(FinishEvent);
}

void AEnemy::StartGrowingUp(float Value)
{
	FVector NewLoc = FMath::Lerp(StartLoc, EndLoc, Value);
	SetActorRelativeLocation(NewLoc);
}

void AEnemy::FinishGrowingUp()
{
	GetCharacterMovement()->SetActive(true);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GrowingUpTimeline.TickTimeline(DeathTime);
}

void AEnemy::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageCauser != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) return;

	Health = UKismetMathLibrary::Clamp(Health - Damage, 0.f, MaxHealth);
	PlayDamageTakenMontage();

	if (Health <= 0.f)
	{
		GetWorldTimerManager().ClearAllTimersForObject(this);
		if (bStuned)
			StunFinish();
		if (bIgnited)
			IgniteFinish();
		if (Controller)
			Controller->Destroy();

		if (DeathEffect)
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				DeathEffect,
				GetMesh()->GetComponentLocation()
			);

		SetActorEnableCollision(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(
			DeathTimer,
			this,
			&ThisClass::DeathTimerFinish,
			DeathTime
			);
	}
}

void AEnemy::DeathTimerFinish()
{
	Destroy();
}

void AEnemy::PlayDamageTakenMontage()
{
	AnimInstance = AnimInstance == nullptr ? GetMesh()->GetAnimInstance() : AnimInstance;
	if (AnimInstance && DamageTakenMontage && AnimInstance->IsAnyMontagePlaying() == false)
	{
		AnimInstance->Montage_Play(DamageTakenMontage);
	}
}

void AEnemy::PlayAttackMontage()
{
	AnimInstance = AnimInstance == nullptr ? GetMesh()->GetAnimInstance() : AnimInstance;
	if (AnimInstance && AttackMontage)
	{
		TArray<FName> SectionName = { "Attack1", "Attack2"};
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(SectionName[UKismetMathLibrary::RandomIntegerInRange(0, SectionName.Num() - 1)]);
	}
}
void AEnemy::StartAttack()
{
	if (bStuned || bCanAttack == false) return;

	bCanAttack = false;
	PlayAttackMontage();
	if (WeaponMesh && WeaponAnim)
		WeaponMesh->PlayAnimation(WeaponAnim, false);

	GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&ThisClass::AttackEvent,
		AttackEventDelay
	);
}
void AEnemy::AttackEvent()
{
	Attack();
	GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&ThisClass::AttackFinish,
		AttackRate
	);
}
void AEnemy::Attack()
{
	PlayerCharacter = PlayerCharacter == nullptr ? Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		UGameplayStatics::ApplyDamage(PlayerCharacter, EnemyDamage, GetController(), this, EnemyDamageType);
	}
}
void AEnemy::AttackFinish()
{
	bCanAttack = true;
}

void AEnemy::OnSpawn(FVector SpawnLocation)
{
	if (GrowingUpCurve == nullptr) return;

	GetCharacterMovement()->SetActive(false);
	StartLoc= SpawnLocation - FVector(0, 0, 100);
	EndLoc = SpawnLocation + FVector(0, 0, 88);
	SetActorLocation(StartLoc);
	GrowingUpTimeline.PlayFromStart();
}

void AEnemy::Stun(float Time)
{
	if (bStuned) return;

	bStuned = true;
	if (StunEffect)
		StunEffectComp = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			StunEffect, 
			GetActorLocation() + FVector(0, 0, 70)
		);

	GetCharacterMovement()->SetActive(false);
	GetWorldTimerManager().SetTimer(
		StunTimer,
		this,
		&ThisClass::StunFinish,
		Time
	);
}

void AEnemy::StunFinish()
{
	bStuned = false;
	if (StunEffect)
		StunEffectComp->DestroyComponent(); 

	GetCharacterMovement()->SetActive(true);
}

void AEnemy::Ignite(int32 TickCount, float IgniteDamage)
{
	if (bIgnited) return;

	bIgnited = true;
	if (IgniteEffect)
		IgniteEffectComp = UGameplayStatics::SpawnEmitterAttached(
			IgniteEffect, 
			GetMesh(), 
			NAME_None, 
			GetActorLocation(), 
			GetActorRotation(), 
			EAttachLocation::KeepWorldPosition
		);
	IgniteEffectComp->SetRelativeScale3D(IgniteEffectSize);

	IgniteDamageDelegate = IgniteDamage;
	IgniteTime = TickCount;
	IgniteTick();
	GetWorldTimerManager().SetTimer(
		IgniteTimer,
		this,
		&ThisClass::IgniteTick,
		1.5f,
		true
	);
}

void AEnemy::IgniteTick()
{
	--IgniteTime;
	PlayerCharacter = PlayerCharacter == nullptr ? Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) : PlayerCharacter;

	UGameplayStatics::ApplyDamage(
		this,
		IgniteDamageDelegate,
		PlayerCharacter->GetController(),
		PlayerCharacter,
		UDamageType::StaticClass()
		);	

	if (IgniteTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(IgniteTimer);
		IgniteFinish();
	}
}

void AEnemy::IgniteFinish()
{
	bIgnited = false;
	if (IgniteEffect)
		IgniteEffectComp->DestroyComponent();
}