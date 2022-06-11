#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class KODOBUR_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

private:
	// MAIN MENU BUTTONS
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton; // join button in join a join menu
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton; // back button in join menu
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;
	
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void Quit();

	// Hover Widget functions
	UFUNCTION()
	void OnHoveredStart();
	UFUNCTION()
	void OnHoveredQuit();

	// UnHover Widget functions
	UFUNCTION()
	void OnUnHoveredStart();
	UFUNCTION()
	void OnUnHoveredQuit();

	// WIDGET ANIMATION
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* StartAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* QuitAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* ScoreAnim;
	
	// Save Game
	UPROPERTY()
	class UOburSaveGame* SaveGameData = nullptr;
	
	virtual void NativeDestruct() override;
	virtual bool Initialize() override;
};