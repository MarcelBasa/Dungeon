#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	}
	if (PlayerCharacter == nullptr) return;

	FVector Velocity = PlayerCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
	bBlocking = PlayerCharacter->IsBlocking();
	blockRate = PlayerCharacter->GetBlockRate();
	bIsInAir = PlayerCharacter->GetCharacterMovement()->IsFalling();
}