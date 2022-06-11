#pragma once

#include "CoreMinimal.h"
#include "OburSaveGame.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class KODOBUR_API AGameHUD : public AHUD
{
	
	GENERATED_BODY()
	
private:
	const int LeftOffset{ 75 };
	const int TopOffset{ 50 };
	const FString ScoreLabel{ "Score: " };
	int Score{ 0 };

	// saved for efficiency
	UPROPERTY()
	UOburSaveGame* SaveGameInstance;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = HUDFont)
	UFont* HudFont;

	/**
	 * Sets default values for this hud's properties
	*/
	AGameHUD();

	/**
	 * Draws the HUD
	*/
	virtual void DrawHUD() override;
	/**
	 * Adds a score to the score count
	*/
	UFUNCTION()
	void AddScore(int Amount);
	UFUNCTION()
	void PlayerDead();
	
};
