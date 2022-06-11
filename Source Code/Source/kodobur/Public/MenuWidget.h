// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class KODOBUR_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();
	void SetMenuInterface(IMenuInterface* MenuInterface);
protected:
	IMenuInterface* MainMenuInterface = nullptr;
	UPROPERTY()
	APlayerController* PlayerController = nullptr;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override; // delete widget and set controller
	
};