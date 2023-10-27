#include "Enemy_range.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemy_range::AEnemy_range()
{
	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow mesh"));
	ArrowMesh->SetupAttachment(GetWeaponMesh());

	ArrowMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemy_range::BeginPlay()
{
	Super::BeginPlay();

	if (ArrowMesh->GetStaticMesh())
		ArrowMesh->AttachToComponent(GetWeaponMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SKT_Arrow"));
}

void AEnemy_range::SetArrowVisibility(bool Active)
{
	if (ArrowMesh)
		ArrowMesh->SetVisibility(Active);
}

void AEnemy_range::Attack()
{
	if (ProjectileClass)
	{
		AActor* Arrow = GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorLocation(), GetActorRotation());
		Arrow->SetOwner(this);
	}
}