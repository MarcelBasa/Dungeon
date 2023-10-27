#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Enemy_range.generated.h"

class UStaticMeshComponent;

UCLASS()
class DUNGEON_API AEnemy_range : public AEnemy
{
	GENERATED_BODY()
	
public:
	AEnemy_range();
	UFUNCTION(BlueprintCallable)
		void SetArrowVisibility(bool Active);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Weapon)
		UStaticMeshComponent* ArrowMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = Weapon)
		TSubclassOf<AActor> ProjectileClass;
	
	virtual void Attack() override;
};
