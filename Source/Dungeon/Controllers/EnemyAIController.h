#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AEnemy;
class UBlackboardComponent;

UCLASS()
class DUNGEON_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

protected:

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere)
		UBlackboardComponent* EnemyBlackboard;

	APawn* PlayerPawn;
	AEnemy* ControlledEnemy;
};
