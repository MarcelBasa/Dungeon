#include "Shield.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon/Characters/PlayerCharacter.h"


AShield::AShield()
{
	PrimaryActorTick.bCanEverTick = true;

	ShieldMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shield Mesh"));
	SetRootComponent(ShieldMesh);
	ShieldMesh->CastShadow = false;
}

void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}