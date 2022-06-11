// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadScreen.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Engine/GameInstance.h"
#include "OburGameInstance.generated.h"


UCLASS()
class KODOBUR_API UOburGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UOburGameInstance(const FObjectInitializer& ObjectInitializer);
	

	// INTERFACE FUNCTIONS
	virtual void StartGame() override;
	virtual void LoadMainMenu() override;
	virtual void RestartGame() override;

	// Menu Functions
	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	UFUNCTION()
	void PauseLoadMenu();
	UFUNCTION(BlueprintCallable)
	void DeadScreen();

private:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> MenuClass = nullptr;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> PauseMenuClass = nullptr;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> DeadScreenClass = nullptr;
	
	UPROPERTY()
	UMainMenu* Menu = nullptr;
	UPROPERTY()
	UPauseMenu* PauseMenu = nullptr;
	UPROPERTY()
	UDeadScreen* DeadMenu = nullptr;
};