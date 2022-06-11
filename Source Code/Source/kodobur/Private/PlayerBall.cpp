// Fill out your copyright notice in the Description page of Project Settings.

#include "kodobur/Public/PlayerBall.h"

#include "GameHUD.h"
#include "OburGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APlayerBall::APlayerBall()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterColliderComp = CreateDefaultSubobject<USphereComponent>(TEXT("Character Collision"));
	RootComponent = CharacterColliderComp;

	// Character Camera
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(CharacterColliderComp);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComp);

	SkelethalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	SkelethalMeshComp->SetupAttachment(CharacterColliderComp);

	CharacterColliderComp->InitSphereRadius(50.f);
	CharacterColliderComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterColliderComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	// CAMERA SETTINGS
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritYaw = false;
	SpringArmComp->bInheritRoll = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.f;
}

// Called when the game starts or when spawned
void APlayerBall::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ScoreTimer, this, &APlayerBall::EarnScore, 2, true, 4.0f);
}

// Called every frame
void APlayerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movement(DeltaTime);
	Rotate(DeltaTime);
}

// Called to bind functionality to input
void APlayerBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerBall::Pause);
	PlayerInputComponent->BindAxis("Move Left", this, &APlayerBall::MoveLeft);
	PlayerInputComponent->BindAxis("Move Up", this, &APlayerBall::MoveUp);
}

// set movement value
void APlayerBall::MoveUp(float value)
{
	MoveUpDirection = value;
}


// set movement value
void APlayerBall::MoveLeft(float value)
{
	MoveDirection = value;
}

// set player movement
void APlayerBall::Movement(float DeltaTime)
{
	Speed = FMath::Lerp(Speed, TargetSpeed, DeltaTime * 4.f);
	CharacterColliderComp->AddWorldOffset(GetActorRightVector() * Speed * DeltaTime * MoveDirection, false, false);
	CharacterColliderComp->AddWorldOffset(GetActorUpVector() * Speed * DeltaTime * MoveUpDirection, false, false);
}

// set player rotation
void APlayerBall::Rotate(float DeltaTime)
{
	TurnSpeed = MoveDirection * 120.f;
	TargetTilt = MoveDirection * TiltLimit;
	SkelethalMeshComp->SetRelativeRotation(UKismetMathLibrary::RLerp(SkelethalMeshComp->GetRelativeRotation(),
	                                                                 FRotator(TargetTilt, 0.f, 0.f), DeltaTime * 5.f,
	                                                                 false));
}

// add score
void APlayerBall::EarnScore()
{
	if(!IsActorBeingDestroyed())
	{
		AGameHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AGameHUD>();
		if (Hud != nullptr)
		{
			Hud->AddScore(EarnScoreValue);
		}
	}
}

// when player dead
void APlayerBall::PlayerDead()
{
	UOburGameInstance* Instance = Cast<UOburGameInstance>(GetGameInstance());
	if (!ensure(Instance != nullptr)) { return; }
	this->GetVelocity() = FVector(0, 0, 0);
	Instance->DeadScreen();
}

// call pause menu
void APlayerBall::Pause()
{
	UOburGameInstance* Instance = Cast<UOburGameInstance>(GetGameInstance());
	if (!ensure(Instance != nullptr)) { return; }
	this->GetVelocity() = FVector(0, 0, 0);
	Instance->PauseLoadMenu();
}
