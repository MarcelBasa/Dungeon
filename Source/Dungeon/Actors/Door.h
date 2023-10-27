#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ADungeonGameModeBase;

UCLASS()
class DUNGEON_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OpenDoor(float Value);
	void CloseDoor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	FTimeline Timeline;
	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere)
		float DoorRotateAngle = 90.f;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorFrame;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LeftDoor;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RightDoor;
	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerBox;

	ADungeonGameModeBase* GameMode;
};
