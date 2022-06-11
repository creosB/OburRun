#include "DeadScreen.h"
#include "OburSaveGame.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

UDeadScreen::UDeadScreen(const FObjectInitializer& ObjectInitializer)
{
	SaveGameData = Cast<UOburSaveGame>(UGameplayStatics::LoadGameFromSlot("OburSaveSlot", 0));

	if (SaveGameData != nullptr)
	{
		// check save
		UE_LOG(LogTemp, Warning, TEXT("Dead Screen Best Score %d"), SaveGameData->BestScore);
		UE_LOG(LogTemp, Warning, TEXT("Dead Screen Score %d"), SaveGameData->LastScore);
	}
	else
	{
		// couldn't load save game
		SaveGameData = Cast<
			UOburSaveGame>(UGameplayStatics::CreateSaveGameObject(UOburSaveGame::StaticClass()));
	}
}

bool UDeadScreen::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	// DEAD SCREEN BINDINGS
	if (!ensure(ReturnMenuButton != nullptr)) { return false; }
	ReturnMenuButton->OnClicked.AddDynamic(this, &UDeadScreen::ReturnMenu);
	ReturnMenuButton->OnHovered.AddDynamic(this, &UDeadScreen::OnHoveredReturnMenu);
	ReturnMenuButton->OnUnhovered.AddDynamic(this, &UDeadScreen::OnUnHoveredReturnMenu);
	if (!ensure(RestartGameButton != nullptr)) { return false; }
	RestartGameButton->OnClicked.AddDynamic(this, &UDeadScreen::RestartGame);
	RestartGameButton->OnHovered.AddDynamic(this, &UDeadScreen::OnHoveredGame);
	RestartGameButton->OnUnhovered.AddDynamic(this, &UDeadScreen::OnUnHoveredGame);
	if (!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UDeadScreen::Quit);
	QuitButton->OnHovered.AddDynamic(this, &UDeadScreen::OnHoveredQuit);
	QuitButton->OnUnhovered.AddDynamic(this, &UDeadScreen::OnUnHoveredQuit);
	if (!ensure(BestScoreText != nullptr)) { return false; }
	SaveGameData = Cast<UOburSaveGame>(UGameplayStatics::LoadGameFromSlot("OburSaveSlot", 0));
	if (SaveGameData != nullptr)
	{
		BestScoreText->SetText(
			FText::FromString(TEXT("Best Score: ") + FString::FromInt(SaveGameData->BestScore)));
		BestScoreText->SetVisibility(ESlateVisibility::Visible);
	}
	if (!ensure(LastScoreText != nullptr)) { return false; }
	if (SaveGameData != nullptr)
	{
		LastScoreText->SetText(
			FText::FromString(TEXT("Last Score: ") + FString::FromInt(SaveGameData->LastScore)));
		LastScoreText->SetVisibility(ESlateVisibility::Visible);
	}
	if (ScoreAnim != nullptr)
	{
		PlayAnimation(ScoreAnim, 0.0f, 0, EUMGSequencePlayMode::Forward, 2.0f, false);
	}

//	UGameplayStatics::SaveGameToSlot(SaveGameData, "OburSaveSlot", 0);
	
	return true;
}

// Return to the main menu
void UDeadScreen::ReturnMenu()
{
	MainMenuInterface->LoadMainMenu();
}

// Restart game func
void UDeadScreen::RestartGame()
{
	MainMenuInterface->RestartGame();
}

// Exit to the game
void UDeadScreen::Quit()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	PlayerController = World->GetFirstPlayerController(); // call player controller
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

// On Hovered Functions
void UDeadScreen::OnHoveredReturnMenu()
{
	if (ReturnMenuAnim)
	{
		PlayAnimation(ReturnMenuAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UDeadScreen::OnHoveredGame()
{
	if (GameAnim)
	{
		PlayAnimation(GameAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UDeadScreen::OnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

// On UnHovered Functions
void UDeadScreen::OnUnHoveredReturnMenu()
{
	if (ReturnMenuAnim)
	{
		PlayAnimation(ReturnMenuAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UDeadScreen::OnUnHoveredGame()
{
	if (GameAnim)
	{
		PlayAnimation(GameAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UDeadScreen::OnUnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UDeadScreen::NativeDestruct()
{
	Super::NativeDestruct();

	// unbinding
	ReturnMenuButton->OnClicked.RemoveAll(this);
	ReturnMenuButton->OnHovered.RemoveAll(this);
	ReturnMenuButton->OnUnhovered.RemoveAll(this);
	RestartGameButton->OnClicked.RemoveAll(this);
	RestartGameButton->OnHovered.RemoveAll(this);
	RestartGameButton->OnUnhovered.RemoveAll(this);
	QuitButton->OnClicked.RemoveAll(this);
	QuitButton->OnHovered.RemoveAll(this);
	QuitButton->OnUnhovered.RemoveAll(this);
}
