// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableObjectSpawner.h"

#include "ActorMovement.h"
#include "GameHUD.h"
#include "NiagaraComponent.h"
#include "Components/NamedSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerBall.h"

// Sets default values
ACollectableObjectSpawner::ACollectableObjectSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	CoinMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CoinMesh->SetupAttachment(SceneRoot);

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Trigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACollectableObjectSpawner::OnOverlapBegin);
	Trigger->SetupAttachment(SceneRoot);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(SceneRoot);

	// Actor Movement settings on details page.
	ActorMovement = CreateDefaultSubobject<UActorMovement>("Movement");
	// Config Data
	ActorMovement->TransporterForwardSpeed = ConfigurationData.CoinMovementSpeed;

	CoinTimeLineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
}

// Called when the game starts or when spawned
void ACollectableObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Get player info
	Player = Cast<APlayerBall>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Set timeline info
	UpdateRotationTrack.BindDynamic(this, &ACollectableObjectSpawner::UpdateRotation);
	UpdateLocationTrack.BindDynamic(this, &ACollectableObjectSpawner::UpdateLocation);
	UpdatePickupTrack.BindDynamic(this, &ACollectableObjectSpawner::UpdatePickup);

	if (RotationCurve && LocationCurve && PickupCurve)
	{
		CoinTimeLineComponent->SetPlaybackPosition(FMath::RandRange(0.f, 5.f), false);
		CoinTimeLineComponent->AddInterpFloat(RotationCurve, UpdateRotationTrack);
		CoinTimeLineComponent->AddInterpFloat(LocationCurve, UpdateLocationTrack);

		// start timeline
		CoinTimeLineComponent->Play();
		CoinTimeLineComponent->SetLooping(true);

		GetWorldTimerManager().SetTimer(DestroyTimer, this, &ACollectableObjectSpawner::CollectableDestroy,
		                                1.0f, false,
		                                ConfigurationData.CoinDestroyDelay);
	};
	if (FMath::RandRange(0, 1) == 0)
	{
		SelectedType = 0;
		CoinMesh->SetStaticMesh(CollectableMeshes[0]);
	}
	else
	{
		SelectedType = 1;
		CoinMesh->SetStaticMesh(CollectableMeshes[1]);
		CoinMesh->SetRelativeScale3D(FVector(1,1,1));
	}
}

// Get actor location information from timeline and set
void ACollectableObjectSpawner::UpdateRotation(float Value)
{
	const FRotator NewRotation = FRotator(0.f, Value, 0.f);
	CoinMesh->SetWorldRotation(NewRotation);
}

void ACollectableObjectSpawner::UpdateLocation(float Value)
{
	const FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, Value + GetActorLocation().Z);
	CoinMesh->SetWorldLocation(NewLocation);
}

void ACollectableObjectSpawner::UpdatePickup(float Value)
{
	const FVector NewLocation = UKismetMathLibrary::VLerp(CoinMesh->GetComponentLocation(),
	                                                      Player->GetActorLocation() + FVector(0.f, 0.f, 40.f), Value);
	CoinMesh->SetWorldLocation(NewLocation);

	const FVector NewScale = UKismetMathLibrary::VLerp(FVector(1.f, 1.f, 1.f), FVector(0.1f, 0.1f, 0.1f), Value);
	CoinMesh->SetRelativeScale3D(NewScale);
}

void ACollectableObjectSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp,
                                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Player && OtherActor == Player)
	{
		AGameHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AGameHUD>();
		if (Hud != nullptr)
		{
			if (SelectedType == 0)
			{
				Hud->AddScore(ConfigurationData.CoinScoreAmount);
			}
			else
			{
				Hud->AddScore(ConfigurationData.BombScoreAmount);
				Hud->PlayerDead();
			}
		}

		CoinTimeLineComponent->SetLooping(false);
		CoinTimeLineComponent->AddInterpFloat(PickupCurve, UpdatePickupTrack);

		Trigger->DestroyComponent();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PickupEffect, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

void ACollectableObjectSpawner::CollectableDestroy()
{
	GetWorldTimerManager().ClearTimer(DestroyTimer);
	Destroy();
}
