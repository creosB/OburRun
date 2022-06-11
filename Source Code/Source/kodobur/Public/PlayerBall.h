// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OburSaveGame.h"
#include "Engine/TriggerBox.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Pawn.h"
#include "PlayerBall.generated.h"

UCLASS()
class KODOBUR_API APlayerBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerBall();
	
	UFUNCTION()
	void PlayerDead();

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* CharacterColliderComp;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SkelethalMeshComp;
	
	void MoveLeft(float value);
	void MoveUp(float value);
	void Movement(float DeltaTime);
	void Rotate(float DeltaTime);
	void EarnScore();
	void Pause();
	
	float MoveUpDirection = 0.0f;
	float MoveDirection = 0.0f;
	UPROPERTY(EditAnywhere)
	float Speed = 0.0f;
	UPROPERTY(EditAnywhere, Category= "Movement Properties")
	float TargetSpeed = 600.f;
	float TurnSpeed;
	UPROPERTY(EditAnywhere, Category= "Movement Properties")
	float TargetTilt = 120.f;
	UPROPERTY(EditAnywhere, Category= "Movement Properties")
	float TiltLimit = 20.f;

	UPROPERTY(EditAnywhere, Category= "Movement Properties")
	int EarnScoreValue = 100;

	FTimerHandle ScoreTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
