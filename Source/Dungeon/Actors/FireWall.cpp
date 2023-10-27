#include "FireWall.h"
#include "Kismet/GameplayStatics.h"


AFireWall::AFireWall()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	RootComponent = WallMesh;
}

void AFireWall::FireLoopStart()
{
	Fire();
	GetWorldTimerManager().SetTimer(
		FireTimer,
		this,
		&ThisClass::Fire,
		FireRate,
		true
	);
}

void AFireWall::Fire()
{
	if (ProjectileClass == nullptr || 
		WallMesh == nullptr || 
		SpawnEffect == nullptr) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEffect, WallMesh->GetSocketTransform(FName("FireSocket")));
	AActor* Bolt = GetWorld()->SpawnActor<AActor>(ProjectileClass, WallMesh->GetSocketLocation(FName("FireSocket")), WallMesh->GetSocketRotation(FName("FireSocket")));
	Bolt->SetOwner(this);
}