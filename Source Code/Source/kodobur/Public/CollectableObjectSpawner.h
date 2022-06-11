// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "NiagaraSystem.h"
#include "PlayerBall.h"
#include "Spawner.h"
#include "CollectableObjectSpawner.generated.h"


UCLASS()
class KODOBUR_API ACollectableObjectSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectableObjectSpawner();

private:
	UPROPERTY(VisibleDefaultsOnly)
	APlayerBall* Player;

	// functions
	UFUNCTION()
	void UpdateRotation(float Value);
	UFUNCTION()
	void UpdateLocation(float Value);
	UFUNCTION()
	void UpdatePickup(float Value);
	void CollectableDestroy();

	// Components
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneRoot; // head of the tree
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CoinMesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* Trigger;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* Light;
	UPROPERTY(EditAnywhere)
	UTimelineComponent* CoinTimeLineComponent;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect;

	// Movement
	UPROPERTY(EditAnywhere)
	class UActorMovement* ActorMovement = nullptr;

	// Collectable type
	int SelectedType = 0;
	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> CollectableMeshes;
	
	// All graphs
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* RotationCurve;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* LocationCurve;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* PickupCurve;

	// Float value tracker
	FOnTimelineFloat UpdateRotationTrack;
	FOnTimelineFloat UpdateLocationTrack;
	FOnTimelineFloat UpdatePickupTrack;

	FConfigurationDataStruct ConfigurationData;
	FTimerHandle DestroyTimer;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
