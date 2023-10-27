#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

class USkeletalMeshComponent;

UCLASS()
class DUNGEON_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	AShield();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Stats)
	float BlockRate = 1.f;
	UPROPERTY(EditAnywhere, Category = Stats)
	int32 BlockAbsorbe = 70;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* ShieldMesh;
};
