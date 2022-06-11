// Fill out your copyright notice in the Description page of Project Settings.


#include "Bound.h"

#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABound::ABound()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = RootCmp;
	UpBound = CreateDefaultSubobject<UBoxComponent>(TEXT("Up Bound"));
	UpBound->SetupAttachment(RootCmp);
	DownBound = CreateDefaultSubobject<UBoxComponent>(TEXT("Down Bound"));
	DownBound->SetupAttachment(RootCmp);
	LeftBound = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Bound"));
	LeftBound->SetupAttachment(RootCmp);
	RightBound = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Bound"));
	RightBound->SetupAttachment(RootCmp);
}

// Called when the game starts or when spawned
void ABound::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerBall>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ABound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// check player is in bound
	if (Player != nullptr)
	{
		if (LeftBound->IsOverlappingActor(Player) || RightBound->IsOverlappingActor(Player) || UpBound->
			IsOverlappingActor(Player) || DownBound->IsOverlappingActor(Player))
		{
			Player->SetActorLocation(FVector(-720.000000, 1110.000000, 192.000000));
		}
	}
}
