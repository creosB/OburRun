// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBall.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Bound.generated.h"

UCLASS()
class KODOBUR_API ABound : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABound();

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* RootCmp;
	UPROPERTY(EditAnywhere)
	UBoxComponent* UpBound;
	UPROPERTY(EditAnywhere)
	UBoxComponent* DownBound;
	UPROPERTY(EditAnywhere)
	UBoxComponent* LeftBound;
	UPROPERTY(EditAnywhere)
	UBoxComponent* RightBound;
	UPROPERTY()
	APlayerBall* Player;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
