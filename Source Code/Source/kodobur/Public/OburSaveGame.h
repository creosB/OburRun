#pragma once

#include "CoreMinimal.h"
#include "ConfigurationDataStruct.h"
#include "GameFramework/SaveGame.h"
#include "OburSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KODOBUR_API UOburSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// Spawner Configuration
	UPROPERTY(VisibleAnywhere, Category = "Saved Game Data")
	FConfigurationDataStruct ConfigurationData;
	//SCORES
	UPROPERTY(VisibleAnywhere, Category = "Saved Game Data")
	int LastScore;
	UPROPERTY(VisibleAnywhere, Category = "Saved Game Data")
	int BestScore;
};
