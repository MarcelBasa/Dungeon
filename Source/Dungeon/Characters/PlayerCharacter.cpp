#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Dungeon/DungeonComponents/CombatComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Dungeon/Actors/Weapon.h"
#include "Dungeon/Actors/Shield.h"
#include "PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon/CameraShake/ReactCameraShake.h"
#include "Dungeon/DungeonGameModeBase.h"
#include "Dungeon/Controllers/DungeonPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	GetMesh()->SetupAttachment(Camera);

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms mesh"));
	ArmsMesh->SetupAttachment(Camera);
	ArmsMesh->CastShadow = false;

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetupAttachment(Camera);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
FRotator APlayerCharacter::GetCameraRotation()
{
	if (Camera)
		return Camera->GetComponentRotation();
	else
		return FRotator(0, 0, 0);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::TakeDamage);

	SetHealthMax();
	SpawnWeapon();
	SpawnShield();

	DungeonPlayerController = DungeonPlayerController == nullptr ? Cast<ADungeonPlayerController>(Controller) : DungeonPlayerController;
	if (DungeonPlayerController)
	{
		DungeonPlayerController->HandleMatchHasStarted();
	}
	UpdateHUDHealth();
	UpdateHUDStarts();
	PlayUnsheatheAnimation();
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Combat)
	{
		Combat->Character = this;
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Combat)
	{
		Combat->DealDamage(OtherActor);
	}
}

void APlayerCharacter::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetActorLocation(), GetActorRotation());
	if (Weapon)
	{
		Weapon->SetActorScale3D(Camera->GetRelativeScale3D());
		Weapon->SetOwner(this);
		const USkeletalMeshSocket* HandSocket = ArmsMesh->GetSocketByName(FName("SwordSocket"));
		if (HandSocket)
		{
			HandSocket->AttachActor(Weapon, ArmsMesh);
		}
		if (Combat)
		{
			Combat->SetupWeapon(Weapon);
		}
	}
}
void APlayerCharacter::SpawnShield()
{
	Shield = GetWorld()->SpawnActor<AShield>(ShieldClass, GetActorLocation(), GetActorRotation());
	if (Shield)
	{
		Shield->SetActorScale3D(Camera->GetRelativeScale3D());
		Shield->SetOwner(this);
		const USkeletalMeshSocket* HandSocket = ArmsMesh->GetSocketByName(FName("ShieldSocket"));
		if (HandSocket)
		{
			HandSocket->AttachActor(Shield, ArmsMesh);
		}
		if (Combat)
		{
			Combat->SetupShield(Shield);
		}
	}
}

void APlayerCharacter::SetWeaponCollision(bool Active)
{
	if (Active)
	{
		CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ThisClass::AttackButtonPressed);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ThisClass::AttackButtonReleased);
	PlayerInputComponent->BindAction(TEXT("Block"), IE_Pressed, this, &ThisClass::BlockButtonPressed);
	PlayerInputComponent->BindAction(TEXT("Block"), IE_Released, this, &ThisClass::BlockButtonReleased);
	PlayerInputComponent->BindAction(TEXT("Menu"), IE_Pressed, this, &ThisClass::MenuButtonPressed);
}
void APlayerCharacter::MenuButtonPressed()
{
	DungeonPlayerController = DungeonPlayerController == nullptr ? Cast<ADungeonPlayerController>(Controller) : DungeonPlayerController;
	if (DungeonPlayerController)
		DungeonPlayerController->HandleOpenCloseMenu();
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}
void APlayerCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}
void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}
void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::AttackButtonPressed()
{
	if (Combat)
	{
		Combat->AttackButtonPressed(true);
	}
}
void APlayerCharacter::AttackButtonReleased()
{
	if (Combat)
	{
		Combat->AttackButtonPressed(false);
	}
}
void APlayerCharacter::BlockButtonPressed()
{
	if (Combat)
	{
		Combat->BlockButtonPressed(true);
	}
}
void APlayerCharacter::BlockButtonReleased()
{
	if (Combat)
	{
		Combat->BlockButtonPressed(false);
	}
}

void APlayerCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = ArmsMesh->GetAnimInstance();
	if (AnimInstance && AttackMontage && Weapon)
	{
		TArray<FName> SectionName = { "Attack1", "Attack2", "Attack3", "Attack4" };
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_SetPlayRate(AttackMontage, Weapon->AttackRate);
		AnimInstance->Montage_JumpToSection(SectionName[UKismetMathLibrary::RandomIntegerInRange(0, SectionName.Num() - 1)]);
	}
}

void APlayerCharacter::PlayShieldImpactMontage()
{
	if (BlockCameraShake)
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(BlockCameraShake);
	if (ImpactMontage)
	{
		UAnimInstance* AnimInstance = ArmsMesh->GetAnimInstance();
		AnimInstance->Montage_Play(ImpactMontage);
	}
}

void APlayerCharacter::PlayHitImpactMontage()
{
	if (ReactCameraShake)
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(ReactCameraShake);
}

void APlayerCharacter::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageCauser == this || Combat == nullptr) return;

	if(Combat->bBlocking)
	{
		PlayShieldImpactMontage();
		Health = UKismetMathLibrary::Clamp(Health - (Damage - (Damage * Shield->BlockAbsorbe)/100), 0.f, MaxHealth);
	}
	else
	{
		PlayHitImpactMontage();
		Health = UKismetMathLibrary::Clamp(Health - Damage, 0.f, MaxHealth);
	}
	if (Health <= 0)
	{
		Dead();
	}
	UpdateHUDHealth();
}
void APlayerCharacter::Dead()
{
	GameMode = Cast<ADungeonGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
		GameMode->RestartGame();
}

bool APlayerCharacter::IsBlocking()
{
	return (Combat && Combat->bBlockingAnimation);
}

float APlayerCharacter::GetBlockRate()
{
	if (Shield)
		return  Shield->BlockRate;
	else
		return 1;
}

void APlayerCharacter::PlayUnsheatheAnimation()
{
	if (ArmsMesh && UnsheatheAnim)
		ArmsMesh->GetAnimInstance()->Montage_Play(UnsheatheAnim);
}

void APlayerCharacter::UpdateHUDHealth()
{
	DungeonPlayerController = DungeonPlayerController == nullptr ? Cast<ADungeonPlayerController>(Controller) : DungeonPlayerController;
	if (DungeonPlayerController)
	{
		DungeonPlayerController->SetHUDHealth(Health, MaxHealth);
	}
}

void APlayerCharacter::UpdateHUDStarts()
{
	DungeonPlayerController = DungeonPlayerController == nullptr ? Cast<ADungeonPlayerController>(Controller) : DungeonPlayerController;
	if (DungeonPlayerController)
	{
		DungeonPlayerController->SetHUDStats(
			Weapon->Damage,
			Weapon->AttackRate,
			Weapon->StunChance,
			Weapon->StunTime,
			Weapon->CritChance,
			Weapon->CritImprove,
			Shield->BlockRate,
			Shield->BlockAbsorbe
			);
	}
}
