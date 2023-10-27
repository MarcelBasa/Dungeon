#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon/Characters/Enemy.h"
#include "Dungeon/Characters/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"


AEnemyAIController::AEnemyAIController()
{
	EnemyBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("EnemyBlackboard"));

	if (EnemyBlackboard)
		PrimaryActorTick.bCanEverTick = true;
	else
		PrimaryActorTick.bCanEverTick = false;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledEnemy = Cast<AEnemy>(InPawn);
	if (ControlledEnemy && ControlledEnemy->GetBehaviorTree())
	{
		RunBehaviorTree(ControlledEnemy->GetBehaviorTree());
	}
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ControlledEnemy && PlayerPawn)
	{
		EnemyBlackboard->SetValueAsVector(FName("PlayerLocation"), PlayerPawn->GetActorLocation());
		EnemyBlackboard->SetValueAsBool(FName("IsPlayerInRange"), LineOfSightTo(PlayerPawn, ControlledEnemy->GetActorLocation()));
	}
}
