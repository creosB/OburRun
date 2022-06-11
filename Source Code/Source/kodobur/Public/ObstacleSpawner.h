#pragma once

#include "CoreMinimal.h"
#include "ActorMovement.h"
#include "Spawner.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class KODOBUR_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleSpawner();

private:
	// Main Settings
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ObstacleMesh = nullptr; // Effect start location
	// Movement
	UPROPERTY(EditAnywhere)
	UActorMovement* ActorMovement = nullptr;
	
	void ObstacleDestroy();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	
	// Config Dat
	FConfigurationDataStruct ConfigurationData;
	FTimerHandle DestroyTimer;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
