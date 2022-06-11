// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "DeadScreen.generated.h"


class UButton;

UCLASS()
class KODOBUR_API UDeadScreen : public UMenuWidget
{
	GENERATED_BODY()

public:
	UDeadScreen(const FObjectInitializer& ObjectInitializer);

private:
	// DEAD SCREEN BUTTONS
	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnMenuButton; // join button in join a join menu
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartGameButton; // back button in join menu
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton; // back button in join menu
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BestScoreText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LastScoreText;

	UFUNCTION()
	void ReturnMenu();
	UFUNCTION()
	void RestartGame();
	UFUNCTION()
	void Quit();

	// Hover Widget functions
	UFUNCTION()
	void OnHoveredReturnMenu();
	UFUNCTION()
	void OnHoveredGame();
	UFUNCTION()
	void OnHoveredQuit();

	// UnHover Widget functions
	UFUNCTION()
	void OnUnHoveredReturnMenu();
	UFUNCTION()
	void OnUnHoveredGame();
	UFUNCTION()
	void OnUnHoveredQuit();

	// WIDGET ANIMATION
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* ReturnMenuAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* GameAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* ScoreAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* QuitAnim;
	UPROPERTY()
	class UOburSaveGame* SaveGameData = nullptr;

	virtual void NativeDestruct() override;
	virtual bool Initialize() override;
};
