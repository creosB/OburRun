// Fill out your copyright notice in the Description page of Project Settings.
#include "kodobur/Public/Spawner.h"
#include "CollectableObjectSpawner.h"
#include "ObstacleSpawner.h"
#include "Road.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "kodobur/Public/PlayerBall.h"


// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance
	PrimaryActorTick.bCanEverTick = false;
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Spawner Mesh");
	RootComponent = SpawnerMesh;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	// Calling main player.
	Player = Cast<APlayerBall>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (RoadTypeArray != nullptr)
	{
		AttachmentLocation = GetActorLocation() - FVector(1200, 500, 100);
		for (int i = 0; i < 3; i++)
		{
			RoadSpawn();
		}
	}
}

// Call Function with Timer
void ASpawner::SetSpawnTimer()
{
	GetWorldTimerManager().SetTimer(ObstacleSpawnTimer, this, &ASpawner::ObstacleSpawn,
	                                ConfigurationData.ObstacleSpawnSpeed, true,
	                                3.0f);
	GetWorldTimerManager().SetTimer(CoinSpawnTimer, this, &ASpawner::ColllectableSpawn,
	                                ConfigurationData.CoinSpawnSpeed, true,
	                                5.0f);
}

// 0. element for collectable object
void ASpawner::ObstacleSpawn()
{
	// Repeating array 0 to max and restarting.
	if (0 <= SpawnObject.Num())
	{
		auto randobs = FMath::RandRange(0, 8);
		for (int k = 0; k < ConfigurationData.ObstacleSpawnAmount + randobs; k++)
		{
			GetWorld()->SpawnActor<AObstacleSpawner>(
				SpawnObject[0].ActorToSpawn, SpawnChoice(0), SpawnRotation(0));
		}
	}
}

void ASpawner::RoadSpawn()
{
	if (RoadTypeArray != nullptr)
	{
		ARoad* SpawnedActor = GetWorld()->SpawnActor<ARoad>(RoadTypeArray,
		                                                    FVector(AttachmentLocation.X,
		                                                            GetActorLocation().Y,
		                                                            GetActorLocation().Z), GetActorRotation());
		if (SpawnedActor != nullptr && FirstRoadSpawn)
		{
			AttachmentLocation = SpawnedActor->GetAttachLocation() - FVector(1200, 0, 0);
			ObjectLocation = SpawnedActor->GetObjectLocation();
			SetSpawnTimer();
			SpawnedActor->RoadSpawner = this;
			FirstRoadSpawn = false;
		}
		else if (SpawnedActor != nullptr && !FirstRoadSpawn)
		{
			SpawnedActor->RoadSpawner = this;
			AttachmentLocation = SpawnedActor->GetAttachLocation() - FVector(1200, 0, 0);
		}
	}
}

// 1. element for collectable object
void ASpawner::ColllectableSpawn()
{
	if (0 < SpawnObject.Num())
	{
		GetWorld()->SpawnActor<ACollectableObjectSpawner>(
			SpawnObject[1].ActorToSpawn, SpawnChoice(1) - FVector(0.f, 0.f, 50.f), GetActorRotation());
	}
}


// Set Properties
FVector ASpawner::SpawnChoice(int i)
{
	// It's giving random value to each array elements and repeats every time we call this function.
	switch (SpawnObject[i].SpawnSettings.SpawnDirection)
	{
	case SpawnDirectionZ:
		{
			FVector SpawnerLocation = ObjectLocation;
			SpawnerLocation.Z = ObjectLocation.Z - FMath::RandRange(
				SpawnObject[i].SpawnSettings.MinSpawnLocation,
				SpawnObject[i].SpawnSettings.MaxSpawnLocation);
			return SpawnerLocation;
		}
	case SpawnDirectionY:
		{
			FVector SpawnerLocation = ObjectLocation;
			SpawnerLocation.Y = ObjectLocation.Y - FMath::RandRange(
				SpawnObject[i].SpawnSettings.MinSpawnLocation,
				SpawnObject[i].SpawnSettings.MaxSpawnLocation);
			return SpawnerLocation;
		}
	case SpawnDirectionX:
		{
			FVector SpawnerLocation = ObjectLocation;
			SpawnerLocation.X = ObjectLocation.X - FMath::RandRange(
				SpawnObject[i].SpawnSettings.MinSpawnLocation,
				SpawnObject[i].SpawnSettings.MaxSpawnLocation);
			return SpawnerLocation;
		}
	default:
		return GetActorLocation();
	}
}

// Set Properties
FRotator ASpawner::SpawnRotation(int i)
{
	// It's giving random value to each array elements and repeats every time we call this function.

	FRotator SpawnerRotator = FRotator(FMath::RandRange(SpawnObject[i].SpawnSettings.MinSpawnRotation,
	                                                    SpawnObject[i].SpawnSettings.MaxSpawnRotation),
	                                   GetActorRotation().Yaw,
	                                   GetActorRotation().Roll);
	return SpawnerRotator;
}
