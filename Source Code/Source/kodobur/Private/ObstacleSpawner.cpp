// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "ActorMovement.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Mesh");
	RootComponent = SceneComponent;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Start");
	ObstacleMesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);
	ObstacleMesh->SetupAttachment(SceneComponent);

	// Actor Movement settings on details page.
	ActorMovement = CreateDefaultSubobject<UActorMovement>("Movement");
	ActorMovement->TransporterForwardSpeed = ConfigurationData.ObstacleMovementSpeed;
}


// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AObstacleSpawner::ObstacleDestroy,
	                                1.0f, false,
	                                ConfigurationData.ObstacleDestroyDelay);
}

// called when the ball overlaps
void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && !OtherActor->ActorHasTag("Player")) { return; }

	// get reference to HUD and add score
	AGameHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AGameHUD>();
	if (Hud != nullptr)
	{
		Hud->PlayerDead();
	}
	if(!IsActorBeingDestroyed())
	{
		Destroy();
	}
}


void AObstacleSpawner::ObstacleDestroy()
{
	GetWorldTimerManager().ClearTimer(DestroyTimer);
	if(!IsActorBeingDestroyed())
	{
		Destroy();
	}
}
