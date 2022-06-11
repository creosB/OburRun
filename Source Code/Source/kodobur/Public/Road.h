// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMovement.h"
#include "PlayerBall.h"
#include "Spawner.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Road.generated.h"

UCLASS()
class KODOBUR_API ARoad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoad();
	
	FVector GetAttachLocation();
	FVector GetObjectLocation();

	// Cast Spawner
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	ASpawner* RoadSpawner = nullptr;
	
private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RoadMesh;
	UPROPERTY(EditAnywhere)
	UArrowComponent* AttachDirection;
	UPROPERTY(EditAnywhere)
	UArrowComponent* ObjectPoint;
	UPROPERTY(EditAnywhere)
	UBoxComponent* EndTrigger;
	UPROPERTY(EditAnywhere)
	UActorMovement* ActorMovement;
	
	FConfigurationDataStruct ConfigurationData;
	UPROPERTY()
	APlayerBall* Player;

	void DestroyOldRoad();
	FTimerHandle DestroyTimer;
	FTimerHandle RoadSpawnTimer;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
