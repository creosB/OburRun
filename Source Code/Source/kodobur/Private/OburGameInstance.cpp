// Fill out your copyright notice in the Description page of Project Settings.


#include "kodobur/Public/OburGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


UOburGameInstance::UOburGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// find menu widget class and define to MenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Blueprints/Widgets/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	// find pause menu widget class and define to PauseMenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr)) return;
	PauseMenuClass = PauseMenuBPClass.Class;

	// find pause menu widget class and define to DeadScreenBPClass.
	ConstructorHelpers::FClassFinder<UUserWidget> DeadScreenBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_DeadScreen"));
	if (!ensure(DeadScreenBPClass.Class != nullptr)) return;
	DeadScreenClass = DeadScreenBPClass.Class;
}

// Start Game
void UOburGameInstance::StartGame()
{
	// load to the main map
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World,TEXT("/Game/Maps/Level1"), TRAVEL_Absolute);
}

// Restart Game
void UOburGameInstance::RestartGame()
{
	// load to the main map
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World,TEXT("/Game/Maps/Level1"), TRAVEL_Absolute);
}

// create main dead screen widget
void UOburGameInstance::DeadScreen()
{
	if (!ensure(DeadScreenClass != nullptr)) return;
	DeadMenu = CreateWidget<UDeadScreen>(this, DeadScreenClass); // create menu widget with MenuClass
	if (!ensure(DeadMenu != nullptr)) { return; }
	DeadMenu->Setup(); // add to viewport and show cursor
	DeadMenu->SetMenuInterface(this);
}

// create main menu widget
void UOburGameInstance::LoadMenu()
{
	// Create menu widget
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass); // create menu widget with MenuClass
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup(); // add to viewport and show cursor
	Menu->SetMenuInterface(this);
}

// create pause menu widget
void UOburGameInstance::PauseLoadMenu()
{
	if (!ensure(PauseMenuClass != nullptr)) return;
	PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass); // create menu widget with MenuClass
	if (!ensure(PauseMenu != nullptr)) return;
	PauseMenu->Setup(); // add to viewport and show cursor
	PauseMenu->SetMenuInterface(this);
}

// open the main menu
void UOburGameInstance::LoadMainMenu()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World,TEXT("/Game/Maps/Level0"), TRAVEL_Absolute);
}
