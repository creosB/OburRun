// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARoad::ARoad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Root;

	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Road"));
	RoadMesh->SetupAttachment(Root);

	AttachDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Direction"));
	AttachDirection->SetupAttachment(RoadMesh);

	ObjectPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Object Spawn Point"));
	ObjectPoint->SetupAttachment(RoadMesh);
	
	ActorMovement = CreateDefaultSubobject<UActorMovement>(TEXT("Actor Movement"));
	ActorMovement->TransporterForwardSpeed = ConfigurationData.RoadMovementSpeed;

	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("End Trigger"));
	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoad::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerBall>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(RoadSpawnTimer, this, &ARoad::DestroyOldRoad, 1.0f, true,
		                                ConfigurationData.RoadSpawnSpeed);
}

// return attachment location
FVector ARoad::GetAttachLocation()
{
	return AttachDirection->GetRelativeLocation();
}
// return object spawn location
FVector ARoad::GetObjectLocation()
{
	return ObjectPoint->GetRelativeLocation();
}


void ARoad::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr && OtherActor != Player) { return; }
	if (RoadSpawner != nullptr)
	{
		//RoadSpawner->RoadSpawn();
		GetWorldTimerManager().SetTimer(DestroyTimer, this, &ARoad::DestroyOldRoad, 1.0, false,
		                                      ConfigurationData.RoadDestroyDelay);
	}
}


void ARoad::DestroyOldRoad()
{
	if(RoadSpawner != nullptr)
	{
		RoadSpawner->RoadSpawn();
	}
	GetWorldTimerManager().ClearTimer(DestroyTimer);
	EndTrigger->OnComponentBeginOverlap.RemoveAll(this);
	Destroy();
}
