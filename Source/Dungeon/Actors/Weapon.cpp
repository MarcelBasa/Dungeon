#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->CastShadow = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}