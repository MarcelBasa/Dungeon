#include "CharacterProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Dungeon/Characters/Enemy.h"
#include "Dungeon/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


ACharacterProjectile::ACharacterProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Comp"));
	ParticleComp->SetupAttachment(RootComponent);
}

void ACharacterProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
}

void ACharacterProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	Destroy();
}

void ACharacterProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Enemy && Player && Player->Weapon)
	{
		UGameplayStatics::ApplyDamage(Enemy, Player->Weapon->DamagePower, Player->GetController(), Player, Player->Weapon->WeaponDamageType);
		if (ImpactEffect)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Enemy->GetActorLocation(), GetActorRotation(), FVector(0.2, 0.2, 0.2));
	}
}

void ACharacterProjectile::Destroyed()
{
	Super::Destroyed();

	if (ImpactEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, GetActorLocation(), GetActorRotation(), FVector(ExplodeSize, ExplodeSize, ExplodeSize));
}