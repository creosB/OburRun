// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "Engine/DataTable.h"

#include "ConfigurationDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FConfigurationDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FConfigurationDataStruct()
		: CoinSpawnSpeed(5)
		  , CoinMovementSpeed(400)
		  , CoinDestroyDelay(10)
		  , CoinScoreAmount(500)
			,BombScoreAmount(-20)
		  , ObstacleSpawnAmount(9)
		  , ObstacleSpawnSpeed(3)
		  , ObstacleDestroyDelay(10)
		  , ObstacleMovementSpeed(400)
		  , RoadSpawnSpeed(1)
		  , RoadMovementSpeed(200)
		  , RoadDestroyDelay(2)
	{
	}

	// COIN SPAWNER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Spawner Data Struct")
	float CoinSpawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Spawner Data Struct")
	float CoinMovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Spawner Data Struct")
	float CoinDestroyDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Spawner Data Struct")
	int CoinScoreAmount;

	// Bomb
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Spawner Data Struct")
	int BombScoreAmount;

	// OBSTACLE SPAWNER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Spawner Data Struct")
	float ObstacleSpawnAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Spawner Data Struct")
	float ObstacleSpawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Spawner Data Struct")
	float ObstacleDestroyDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Spawner Data Struct")
	float ObstacleMovementSpeed;

	// ROAD SPAWNER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Spawner Data Struct")
	float RoadSpawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Spawner Data Struct")
	float RoadMovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Spawner Data Struct")
	float RoadDestroyDelay;
};
