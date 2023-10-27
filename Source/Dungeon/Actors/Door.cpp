#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Dungeon/DungeonGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon/Characters/Enemy.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	RootComponent = DoorFrame;
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door"));
	LeftDoor->SetupAttachment(DoorFrame);
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door"));
	RightDoor->SetupAttachment(DoorFrame);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(DoorFrame);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADoor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void ADoor::OpenDoor(float Value)
{
	FRotator Rot = FRotator(0.f, DoorRotateAngle * Value, 0.f);

	RightDoor->SetRelativeRotation(Rot * -1);
	LeftDoor->SetRelativeRotation(Rot);
}

void ADoor::CloseDoor()
{
	Timeline.Reverse();
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> Enemy;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemy);

	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0) && Enemy.Num() <= 0)
	{
		GameMode = Cast<ADungeonGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GameMode->CreateNextLevel();
		}
		Timeline.Play();
	}
}
