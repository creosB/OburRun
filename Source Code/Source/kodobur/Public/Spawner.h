// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConfigurationDataStruct.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

// Direction Choice
UENUM(BlueprintType)
enum ESpawnDirection
{
	SpawnDirectionX UMETA(Display = "X direction"),
	SpawnDirectionY UMETA(Display = "Y direction"),
	SpawnDirectionZ UMETA(Display = "Z direction")
};

// Choice for every array elements.
USTRUCT(BlueprintType)
struct KODOBUR_API FSpawnSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESpawnDirection> SpawnDirection;
	// Min-Max value for Spawn Location and Rotation
	UPROPERTY(EditAnywhere)
	float MinSpawnLocation;
	UPROPERTY(EditAnywhere)
	float MaxSpawnLocation;
	UPROPERTY(EditAnywhere)
	float MinSpawnRotation;
	UPROPERTY(EditAnywhere)
	float MaxSpawnRotation;
};

// Choice for every array elements.
USTRUCT(BlueprintType)
struct KODOBUR_API FSpawnObjectStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FSpawnSettings SpawnSettings;

	UPROPERTY(EditAnywhere, Category = "Main Settings")
	TSubclassOf<AActor> ActorToSpawn;
};

UCLASS()
class KODOBUR_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();
	
	void RoadSpawn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Function
	void ObstacleSpawn(); // creating actor

	virtual void SetSpawnTimer(); // calling timer
	FVector SpawnChoice(int i); // defines values.
	FRotator SpawnRotation(int i);
	void ColllectableSpawn();


	// Spawn Object
	FTimerHandle ObstacleSpawnTimer;
	FTimerHandle CoinSpawnTimer;

private:
	// Spawner Main Settings
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SpawnerMesh = nullptr;
	
	FConfigurationDataStruct ConfigurationData;

	// Cast Main Player
	UPROPERTY()
	class APlayerBall* Player = nullptr;

	// Info from struct
	UPROPERTY(EditAnywhere)
	TArray<struct FSpawnObjectStruct> SpawnObject;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> RoadTypeArray;
	// Spawner temp value for set the actor.
	FVector ObjectLocation;
	FVector AttachmentLocation;

	bool FirstRoadSpawn = true;
};
