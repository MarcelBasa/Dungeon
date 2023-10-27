#include "BTTask_Attack.h"
#include "Dungeon/Controllers/EnemyAIController.h"
#include "Dungeon/Characters/Enemy.h"


UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& ObjectInitializer):
	UBTTask_BlackboardBase{ObjectInitializer}
{

}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (EnemyController)
	{
		AEnemy* Enemy = Cast<AEnemy>(EnemyController->GetPawn());
		if (Enemy)
		{
			Enemy->StartAttack();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
