#include "Enemy_Explode.h"
#include "Kismet/GameplayStatics.h"


AEnemy_Explode::AEnemy_Explode()
{
	
}

void AEnemy_Explode::Attack()
{
	Destroy();
}

void AEnemy_Explode::Destroyed()
{
	Super::Destroyed();

	if(ExplodeEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeEffect, GetActorTransform());

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		ExplodeDamage, 
		GetActorLocation(), 
		ExplodeRadius, 
		ExplodeDamageType, 
		ActorToIgnoreExplode, 
		this,
		GetController(),
		true);
}