#include "MainMenu.h"

#include "OburGameInstance.h"
#include "OburSaveGame.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	SaveGameData = Cast<UOburSaveGame>(UGameplayStatics::LoadGameFromSlot("OburSaveSlot", 0));

	if (SaveGameData != nullptr)
	{
		// check save
		UE_LOG(LogTemp, Warning, TEXT("%d"), SaveGameData->BestScore);
		UE_LOG(LogTemp, Warning, TEXT("%d"), SaveGameData->LastScore);
	}
	else
	{
		// couldn't load save game
		SaveGameData = Cast<
			UOburSaveGame>(UGameplayStatics::CreateSaveGameObject(UOburSaveGame::StaticClass()));
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	// MAIN MENU
	if (!ensure(StartButton != nullptr)) { return false; }
	StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartGame);
	StartButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredStart);
	StartButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredStart);
	if (!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);
	QuitButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredQuit);
	QuitButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredQuit);
	if (!ensure(ScoreText != nullptr)) { return false; }
	// test
	SaveGameData = Cast<UOburSaveGame>(UGameplayStatics::LoadGameFromSlot("OburSaveSlot", 0));
	if (SaveGameData != nullptr)
	{
		ScoreText->SetText(FText::FromString(TEXT("Best Score ") + FString::FromInt(SaveGameData->BestScore)));
		ScoreText->SetVisibility(ESlateVisibility::Visible);
	}
	if (ScoreAnim != nullptr)
	{
		PlayAnimation(ScoreAnim, 0.0f, 0, EUMGSequencePlayMode::Forward, 2.0f, false);
	}

	return true;
}

// call start game func. from interface
void UMainMenu::StartGame()
{
	MainMenuInterface->StartGame();
}

// Exit to the game
void UMainMenu::Quit()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	PlayerController = World->GetFirstPlayerController(); // call player controller
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

// On Hovered Functions
void UMainMenu::OnHoveredStart()
{
	if (StartAnim)
	{
		PlayAnimation(StartAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

// On UnHovered Functions
void UMainMenu::OnUnHoveredStart()
{
	if (StartAnim)
	{
		PlayAnimation(StartAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UMainMenu::OnUnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	// MAIN MENU
	StartButton->OnClicked.RemoveAll(this);
	StartButton->OnHovered.RemoveAll(this);
	StartButton->OnUnhovered.RemoveAll(this);
	QuitButton->OnClicked.RemoveAll(this);
	QuitButton->OnHovered.RemoveAll(this);
	QuitButton->OnUnhovered.RemoveAll(this);
}
