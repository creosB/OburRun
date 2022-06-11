#include "GameHUD.h"

#include "PlayerBall.h"
#include "Kismet/GameplayStatics.h"
#include "kodobur/Public/OburSaveGame.h"

/**
 * Sets default values for this hud's properties
*/
AGameHUD::AGameHUD()
{
	// try to load saved number of score
	SaveGameInstance = Cast<UOburSaveGame>(UGameplayStatics::LoadGameFromSlot("OburSaveSlot", 0));

	if (SaveGameInstance != nullptr)
	{
		/*		// check save
				UE_LOG(LogTemp, Warning, TEXT("Gamehud Start %d"), SaveGameInstance->ConfigurationData.BestScore);
				UE_LOG(LogTemp, Warning, TEXT("Gamehud Start %d"), SaveGameInstance->ConfigurationData.LastScore); */
	}
	else
	{
		// couldn't load saved game
		SaveGameInstance = Cast<UOburSaveGame>(UGameplayStatics::CreateSaveGameObject(UOburSaveGame::StaticClass()));
	}

	// development use only; reset saved MaxScore to 0
	// comment out when not needed
	//SaveGameInstance->MaxScore = 0;
	//UGameplayStatics::SaveGameToSlot(SaveGameInstance,
	//	"OburSaveSlot", 0);
}

/**
 * Draws the HUD
*/
void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	// draw score
	DrawText(ScoreLabel + FString::FromInt(Score),
	         FLinearColor::White,
	         LeftOffset, TopOffset, HudFont);
}

/**
 * Adds a score to the score count
*/
void AGameHUD::AddScore(int Amount)
{
	Score += Amount;
/*
	// save number of scores
	if (SaveGameInstance != nullptr)
	{
		if (SaveGameInstance->BestScore < Score)
		{
			SaveGameInstance->BestScore = Score;
			UE_LOG(LogTemp, Warning, TEXT("Best Score Saved"));
		}
		SaveGameInstance->LastScore = Score;
		// check save
		UE_LOG(LogTemp, Warning, TEXT("Game Hud%d"), SaveGameInstance->BestScore);
		UE_LOG(LogTemp, Warning, TEXT("Game Hud %d"), SaveGameInstance->LastScore);
	} */
}

void AGameHUD::PlayerDead()
{
	// test
	SaveGameInstance = Cast<UOburSaveGame>(UGameplayStatics::LoadGameFromSlot("OburSaveSlot", 0));
	if (SaveGameInstance != nullptr)
	{
		if (SaveGameInstance->BestScore < Score)
		{
			SaveGameInstance->BestScore = Score;
			UE_LOG(LogTemp, Warning, TEXT("Best Score Saved"));
		}
		SaveGameInstance->LastScore = Score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "OburSaveSlot", 0);
		// check save
/*		UE_LOG(LogTemp, Warning, TEXT("Game Saved from GameHud"));
		UE_LOG(LogTemp, Warning, TEXT("Game Saved Hud %d"), SaveGameInstance->BestScore);
		UE_LOG(LogTemp, Warning, TEXT("Game Saved Hud %d"), SaveGameInstance->LastScore);
*/
		UE_LOG(LogTemp, Warning, TEXT("Player is dead"));
		APlayerBall* Ball = Cast<APlayerBall>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (Ball != nullptr)
		{
			Ball->PlayerDead();
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("SaveGameInstance is returning nullptr"));
	}
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
