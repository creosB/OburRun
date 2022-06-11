// Copyright Epic Games, Inc. All Rights Reserved.

#include "kodobur/Public/kodoburGameMode.h"
#include "UObject/ConstructorHelpers.h"

AkodoburGameMode::AkodoburGameMode()
{

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Pawns/BP_PlayerBall"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
