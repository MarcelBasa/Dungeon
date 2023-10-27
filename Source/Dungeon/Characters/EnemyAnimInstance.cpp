#include "EnemyAnimInstance.h"
#include "Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyPawn = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (EnemyPawn == nullptr)
	{
		EnemyPawn = Cast<AEnemy>(TryGetPawnOwner());
	}
	if (EnemyPawn == nullptr) return;

	bAlive = EnemyPawn->IsAlive();
	FVector Velocity = EnemyPawn->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
}